#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include "tool/SingletonTemplate.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
using namespace google::protobuf;

// muduo module
class ProtobufCodec : public Singleton<ProtobufCodec> {
    friend class Singleton<ProtobufCodec>;
public:
    Message* createMessage(const std::string& proto_name_) {
        Message* _msg = nullptr;
        if (const Descriptor* _descripotr = DescriptorPool::generated_pool()->FindMessageTypeByName(proto_name_.data())) {
            if (const Message* _prototype = MessageFactory::generated_factory()->GetPrototype(_descripotr)) {
                _msg = _prototype->New();
            }
        }
        return _msg;
    }
    Message* decode(const std::string& proto_name_, const std::string& msg_) {
        Message* _msg = nullptr;
        if (_msg = createMessage(proto_name_)) {
            _msg->ParseFromString(msg_);
        }
        return _msg;
    }
private:
    ProtobufCodec() {};
};

#define ProtoCodec Singleton<ProtobufCodec>::getInstance()