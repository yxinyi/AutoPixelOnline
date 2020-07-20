#pragma once
#include "./TcpServer.h"
#include "./TcpConnonetManager.h"
#include "include/tool/ProtobufCodec.h"
#include "include/tool/Time.h"
#include "include/tool/LogInfo.h"




bool CTcpServer::init(const std::string& address_, const uint16_t port_) {
    m_socket = std::shared_ptr<zmq::socket_t>(new zmq::socket_t(*TcpMgr->getContext(), zmq::socket_type::router));
    std::string _tmp_address = "tcp://"; 
    _tmp_address += address_;
    _tmp_address += ":";
    _tmp_address += std::to_string(port_);
    m_socket->bind(_tmp_address);
    return true;
}


bool CTcpServer::shankhand() {
    CheckAndClear();
    return true;
}

bool CTcpServer::CheckAndClear() {
    const uint64_t _now_time = TimeTool->Now();
    std::vector<std::shared_ptr<SChannel>> _clear_channel_vec;
    for (auto&& _it : m_channel_pool) {
        uint64_t _shake_hand_time = _now_time - _it.second->m_last_shakehand_time;
        if (_shake_hand_time > g_shakehand_time*2) {
            LogInfo << "[ShakeHand] _shake_hand_time [" << _shake_hand_time << "]" << FlushLog;
            _clear_channel_vec.push_back(_it.second);
        }
    }
    if (_clear_channel_vec.size()) {
        LogInfo << "[ShakeHand] now time [" << _now_time << "]" << FlushLog;
    }
    for (auto&& _clear_it : _clear_channel_vec) {
        LogInfo << "[ShakeHand][" << _clear_it->m_route_id << "] shake hand out time last time :[" << _clear_it->m_last_shakehand_time << "]" << FlushLog;
        m_channel_pool.erase(_clear_it->m_route_id);
    }
    return true;
}
std::shared_ptr<SChannel> CTcpServer::getChannel(const std::string& route_id_) {
    if (m_channel_pool.find(route_id_) == m_channel_pool.end()) {
        std::shared_ptr<SChannel> _chl(new SChannel);
        _chl->m_route_id = route_id_;
        _chl->m_tcp_info = shared_from_this();
        m_channel_pool[route_id_] = _chl;
    }
    std::shared_ptr<SChannel> _channel = m_channel_pool[route_id_];
    _channel->m_last_shakehand_time = TimeTool->Now();
    return _channel;
}

bool CTcpServer::recv(std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>> msg_vec_) {
    std::vector<std::string> _recv;
    while (true) {
        static zmq::message_t _tmp_msg;
        if (m_socket->recv(_tmp_msg, zmq::recv_flags::dontwait)) {
            _recv.push_back(_tmp_msg.to_string());
            if (_recv.size() == 3) {
                std::shared_ptr<google::protobuf::Message> _msg(ProtoCodec->decode(_recv[1], _recv[2]));
                if (_msg.get()) {
                    std::shared_ptr<SMsgPacket> _msg_pack(new SMsgPacket);
                    _msg_pack->m_msg = _msg;
                    _msg_pack->m_channel = getChannel(_recv[0]);
                    msg_vec_->push_back(_msg_pack);
                }
                _recv.clear();
            }
            if (!_tmp_msg.more()) {
                break;
            }
        }
        else {
            break;
        }

    }
    return true;
}



bool CTcpServer::send(std::shared_ptr<SMsgPacket> msg_pkg_) {
    zmq::send_result_t _route_id_result = m_socket->send(zmq::buffer(msg_pkg_->m_channel->m_route_id), zmq::send_flags::sndmore);
    if (!_route_id_result) {
        zmq::error_t _err;
        LogInfo << "send error: " << _err.what() << FlushLog;
    }
    static std::string _buff;
    _buff.clear();
    if (msg_pkg_->m_msg->SerializeToString(&_buff)) {
        zmq::send_result_t _result = m_socket->send(zmq::buffer(msg_pkg_->m_msg->GetTypeName()), zmq::send_flags::sndmore);
        if (!_result) {
            zmq::error_t _err;
            LogInfo << "send error: " << _err.what() << FlushLog;
        }
        zmq::send_result_t _more_result = m_socket->send(zmq::buffer(_buff), zmq::send_flags::none);
        if (!_result) {
            zmq::error_t _err;
            LogInfo << "send error: " << _err.what() << FlushLog;
        }
    }
    return true;
}