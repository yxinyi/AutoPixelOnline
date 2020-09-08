#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "tool/UniqueNumberFactory.h"
#include "Tcp/NetManager.h"

class Creature {
public:
    Creature():m_attr(nullptr), m_type_name(""), m_oid(0), m_conn_id(0){}
public:
    void init(const string& type_name_, const uint32_t conn_) {
        m_type_name = type_name_;
        m_attr = CAttrManager::getInstance()->CreateAttr(type_name_);
        m_oid = UniqueNumberFactory::getInstance()->build();
        m_conn_id = conn_;
    }


    void reset() {
        m_type_name = "";
        m_attr = nullptr;
        m_oid = 0;
        m_conn_id = 0;
    }


    AllAttributeDataNotify_t BuildUpdateProto() {
        AllAttributeDataNotify_t _ntf = make_shared<AllAttributeDataNotify>();
        _ntf->set_oid(m_oid);
        m_attr->BuildAllProto(_ntf);
        return _ntf;
    }

    void RestoreForProto(AllAttributeDataNotify_t ntf_) {
        const int _size = ntf_->data_size();
        for (int _idx = 0; _idx < _size; _idx++) {
            ModuleData _module_data = ntf_->data(_idx);
            m_attr->RestoreForProto(_module_data.msg_type_str(), _module_data.binary());
        }
    }
    bool SendProtoMsg(Message_t msg_) {
        return NetManager::getInstance()->SendMessageBuff(m_conn_id, msg_);
    }

public:
    uint64_t GetOid() { return m_oid; }
    CAttrs_t GetAttrs() { return m_attr; }
    uint32_t GetConnID() { return m_conn_id; }

private:
    CAttrs_t m_attr;
    string m_type_name;
    uint64_t m_oid;
    uint32_t m_conn_id;
};

using Creature_t = shared_ptr<Creature>;
