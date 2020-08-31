#pragma once
#include "System/BaseSystem.h"
#include "Attribute/ApiAttribute.h"
#include "tool/UniqueNumberFactory.h"

class Creature {
public:
    Creature():m_attr(nullptr), m_type_name(""), m_oid(0){}
public:
    void init(const string& type_name_) {
        m_type_name = type_name_;
        m_attr = ApiCreateAttr(m_type_name);
        m_oid = UniqueNumberFactory::getInstance()->build();
    }

    void reset() {
        m_type_name = "";
        m_attr = nullptr;
        m_oid = 0;
    }

public:
    uint64_t GetOid() { return m_oid; }

private:
    CAttribute_t m_attr;
    string m_type_name;
    uint64_t m_oid;
};

using Creature_t = shared_ptr<Creature>;
