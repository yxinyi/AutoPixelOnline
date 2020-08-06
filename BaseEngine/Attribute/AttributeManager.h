#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "AttributeDefine.h"
#include "Attribute.h"

class AttributeMager {
public:
    std::weak_ptr<CAttribute> create(const uint64_t oid_, const std::string& obj_str_);

private:
    std::unordered_map<uint64_t, std::shared_ptr<CAttribute>> m_attr_pool;
};
