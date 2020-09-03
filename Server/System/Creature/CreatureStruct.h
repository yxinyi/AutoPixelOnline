#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "tool/UniqueNumberFactory.h"


class CAttrCreature : public CAttr {
public:
    CAttrCreature() :CAttr("CAttrCreature") {}

    shared_ptr<Message> ToDataBaseProto() {
        return nullptr;
    }
    shared_ptr<Message> ToClientProto() {
        return nullptr;
    }
    bool decodeSaveData(shared_ptr<Message> msg_) {
        shared_ptr<Message> _msg = std::dynamic_pointer_cast<Message>(msg_);

        if (!_msg) {
            return false;
        }
        return true;
    }

    shared_ptr<CAttr> Clone() {
        shared_ptr<CAttrCreature> _attr = make_shared<CAttrCreature>();
        return _attr;
    }
private:
};

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

public:
    uint64_t GetOid() { return m_oid; }
    CAttrs_t GetAttrs() { return m_attr; }
    uint64_t GetConnID() { return m_conn_id; }

private:
    CAttrs_t m_attr;
    string m_type_name;
    uint64_t m_oid;
    uint64_t m_conn_id;
};

using Creature_t = shared_ptr<Creature>;
