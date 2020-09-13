#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "tool/UniqueNumberFactory.h"
#include "Tcp/NetManager.h"
#include "System/Session/SessionStruct.h"

class Creature {
public:
    Creature():m_attr(nullptr), m_type_name(""), m_oid(0), m_session_id(0){}
public:
    void init(const string& type_name_, const SessionConn SessionConn_) {
        m_type_name = type_name_;
        m_attr = CAttrManager::getInstance()->CreateAttr(type_name_);
        //如果是老玩家会在载入的时候修改成正确数值
        m_oid = UniqueNumberFactory::getInstance()->build();
        m_session_id = SessionConn_;
    }


    void reset() {
        m_type_name = "";
        m_attr = nullptr;
        m_oid = 0;
        m_session_id = 0;
    }


    AllAttributeDataNotify_t BuildUpdateProto() {
        AllAttributeDataNotify_t _ntf = std::make_shared<AllAttributeDataNotify>();
        _ntf->set_oid(m_oid);
        m_attr->BuildAllProto(_ntf);
        return _ntf;
    }
    void RestoreForProtoData(std::string proto_str_) {
        AllAttributeDataNotify_t _msg = std::make_shared<AllAttributeDataNotify>();
        _msg->ParseFromString(proto_str_);
        RestoreForProto(_msg);
    }
    void RestoreForProto(AllAttributeDataNotify_t ntf_) {
        const int _size = ntf_->data_size();
        for (int _idx = 0; _idx < _size; _idx++) {
            ModuleData _module_data = ntf_->data(_idx);
            m_attr->RestoreForProto(_module_data.msg_type_str(), _module_data.binary());
        }
    }
    bool SendProtoMsg(Message_t msg_) {
        return NetManager::getInstance()->SendMessageBuff(m_session_id, msg_);
    }

public:
    uint64_t GetOid() { return m_oid; }
    CAttrs_t GetAttrs() { return m_attr; }
    uint64_t GetSessionConn() { return m_session_id; }

private:
    CAttrs_t m_attr;
    string m_type_name;
    uint64_t m_oid;
    SessionConn m_session_id;
};

using Creature_t = std::shared_ptr<Creature>;
