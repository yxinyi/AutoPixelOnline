#include "./AttributeManager.h"
#include "tool/StringHelper.h"
#include "tool/LogInfo.h"
#include <vector>
#include <stack>
#include <tuple>

std::weak_ptr<CAttribute> AttributeMager::create(const uint64_t oid_, const std::string& obj_str_) {
    if (m_attr_pool.find(oid_) != m_attr_pool.end()) {
        LogInfo << "[Attr] oid [%llu] is exists " << FlushLog;
    }
    CAttribute_t _obj_attr = CAttrDefineManager::getInstance()->CreateAttr(obj_str_);
    m_attr_pool[oid_] = _obj_attr;
    return CAttribute_wt(_obj_attr);
}
