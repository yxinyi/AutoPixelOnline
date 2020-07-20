#include "BaseEngine.h"
#include "../Common/include/tool/ProtobufDispatcher.h"
#include "include/proto/Shakehand.pb.h"


CBaseEngine::CBaseEngine() {
    EventRegister(ShakeHandEvent, [](std::shared_ptr<SChannel> socket_, const std::shared_ptr<ShakeHandEvent>& message_, const int64_t& tm_) {
        LogInfo << "ShakeHandEvent src_name : [" << message_->src_name() <<"]"<< FlushLog;
        return true;
    });
}
void CBaseEngine::run(const int64_t& receive_time_) {
    std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>> _recv = Singleton<CTcpConnonetManager>::getInstance()->pool();
    for (auto&& _packet_it : *_recv) {
        DispatcherEvent(_packet_it->m_channel, _packet_it->m_msg, receive_time_);
    }
    Singleton<CTcpConnonetManager>::getInstance()->ShakeHand();
    Singleton<CSendMsgPool>::getInstance()->run();
    
}
