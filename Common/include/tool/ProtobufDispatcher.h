#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
#include <memory>
#include <functional>
#include "include/tool/LogInfo.h"

using namespace google::protobuf;

using MessagePtr = std::shared_ptr<google::protobuf::Message>;
// muduo  module

class Callback
{
public:
    virtual ~Callback() = default;
    virtual void onMessage(const uint64_t,
        const MessagePtr&,
        const int64_t&) const = 0;
};

template <typename T>
class CallbackT : public Callback
{
    static_assert(std::is_base_of<google::protobuf::Message, T>::value,
        "T must be derived from gpb::Message.");
public:
    using ProtobufMessageTCallback = std::function<void(const uint64_t, const std::shared_ptr<T>& message, const int64_t&)>;

    CallbackT(const ProtobufMessageTCallback& callback_)
        : m_callback(callback_) {
    }

    void onMessage(const uint64_t socket_,
        const MessagePtr& msg_,
        const int64_t& receive_time_) const override {
        std::shared_ptr<T> _concrete = std::static_pointer_cast<T>(msg_);
        assert(_concrete != NULL);
        m_callback(socket_, _concrete, receive_time_);
    }

private:
    ProtobufMessageTCallback m_callback;
};

class ProtobufDispatch : public Singleton<ProtobufDispatch> {
public:
    using ProtobufMessageCallback = std::function<void(const uint64_t, const MessagePtr&, const int64_t&)>;

    ProtobufDispatch() :m_defaultCallback([](const uint64_t, const MessagePtr& msg_, const int64_t&) {
        LogInfo << "[ProtobufDispatch] onUnknowMessageType: " << msg_->GetTypeName() << FlushLog;
    }) {}

    void onProtobufMessage(const uint64_t conn_,
        const MessagePtr& message_,
        const int64_t& receive_time_) const {
        CallbackListMap::const_iterator it = m_callbacks.find(message_->GetDescriptor());
        if (it != m_callbacks.end()) {
            for (auto&& _cb_it : it->second) {
                _cb_it->onMessage(conn_, message_, receive_time_);
            }
        }
        else {
            m_defaultCallback(conn_, message_, receive_time_);
        }
    }

    void SetDefaultCallback(ProtobufMessageCallback cb_) {
        m_defaultCallback = cb_;
    }

    template<typename T>
    void registerMessageCallback(const typename CallbackT<T>::ProtobufMessageTCallback& callback_) {
        T _tmp;
        m_message_type_str.push_back(_tmp.GetTypeName());
        std::shared_ptr<CallbackT<T> > pd(new CallbackT<T>(callback_));
        m_callbacks[T::descriptor()].push_back(pd);
    }
    std::vector<string> GetAllMessageTypeStr() {
        return m_message_type_str;
    }
private:
    using CallbackListMap = std::map<const google::protobuf::Descriptor*, std::vector<std::shared_ptr<Callback> > >;
    std::vector<string> m_message_type_str;
    CallbackListMap m_callbacks;
    ProtobufMessageCallback m_defaultCallback;

};


#define EventRegister(event_,func_)  \
    Singleton<ProtobufDispatch>::getInstance()->registerMessageCallback<event_ >(func_);



#define DispatcherEvent(socket_,msg_,tm_)  \
    Singleton<ProtobufDispatch>::getInstance()->onProtobufMessage(socket_,msg_,tm_);
