#pragma once
//#include "zmq/cppzmq/zmq.h"
#include "./TcpServer.h"
#include "./TcpConnonetManager.h"
#include "../Common/include/tool/ProtobufCodec.h"
#include "../Common/include/tool/Time.h"
#include "../Common/include/tool/LogInfo.h"
#include "include/proto/Shakehand.pb.h"


bool CTcpClient::init(const std::string& address_, const uint16_t port_) {
    m_socket = std::shared_ptr<zmq::socket_t>(new zmq::socket_t(*TcpMgr->getContext(), zmq::socket_type::dealer));
    std::string _tmp_address = "tcp://";
    _tmp_address += address_;
    _tmp_address += ":";
    _tmp_address += std::to_string(port_);
    m_socket->connect(_tmp_address);
    m_channel = std::shared_ptr<SChannel>(new SChannel());
    m_channel->m_last_shakehand_time = TimeTool->Now();
    m_channel->m_tcp_info = shared_from_this();
    return true;
}
extern std::string getNodeName();
bool CTcpClient::shankhand() {
    const uint64_t _now_time = TimeTool->Now();
    if ((_now_time - m_channel->m_last_shakehand_time) < g_shakehand_time) {
        return true;
    }

    m_channel->m_last_shakehand_time = TimeTool->Now();

    std::shared_ptr<ShakeHandEvent> _shakehand(new ShakeHandEvent());
    _shakehand->set_state(m_shakehand_state);
    _shakehand->set_src_name(getNodeName());
    m_shakehand_state++;
    SendNetMsg(m_channel, _shakehand);
    return true;
}
std::shared_ptr<SChannel> CTcpClient::getChannel(const std::string& route_id_) {
    return m_channel;
}
bool CTcpClient::recv(std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>> msg_vec_) {
    std::vector<std::string> _recv;
    while (true) {
        static zmq::message_t _tmp_msg;
        if (m_socket->recv(_tmp_msg, zmq::recv_flags::dontwait)) {
            _recv.push_back(_tmp_msg.to_string());
            if (!_tmp_msg.more()) {
                break;
            }
        }
        else {
            break;
        }
        if (_recv.size() == 2) {
            std::shared_ptr<google::protobuf::Message> _msg(ProtoCodec->decode(_recv[0], _recv[1]));
            if (_msg.get()) {
                std::shared_ptr<SMsgPacket> _msg_pack(new SMsgPacket);
                _msg_pack->m_msg = _msg;
                _msg_pack->m_channel = getChannel(_recv[0]);
                msg_vec_->push_back(_msg_pack);
            }
            _recv.clear();
        }
    }
    return true;
}



bool CTcpClient::send(std::shared_ptr<SMsgPacket> msg_vec_) {
    static std::string _buff;
    _buff.clear();
    if (msg_vec_->m_msg->SerializeToString(&_buff)) {
        zmq::send_result_t _result = m_socket->send(zmq::buffer(msg_vec_->m_msg->GetTypeName()), zmq::send_flags::sndmore);
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