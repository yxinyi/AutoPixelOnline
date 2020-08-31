#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include <memory>
#include "Attribute.h"
#include "tool/SingletonTemplate.h"


enum class AttrCfg {
    NONE = 0,
    SAVE = 1,
};

struct CAttrDefine {
    std::string m_key;
    std::string m_val;
    std::string m_type;
    AttrCfg    m_cfg;
};


class CAttributePrototype {
public:
    CAttribute_t Clone();
    CAttribute_t m_attr;
};
using CAttributePrototype_t = std::shared_ptr<CAttributePrototype>;

struct AttrComplexDef {
    std::string m_type;
    std::vector<CAttrDefine> m_complex;
};

class CAttrModule {
public:
    void RegAttrDefine(const std::string& attr_info_, const AttrCfg cfg_);
    std::vector<CAttrDefine> m_attr_pool;
    std::vector<CAttrDefine> m_vector_pool;
};


using CAttrModule_t = std::shared_ptr<CAttrModule>;
class CObjAttr {
public:
    void RegAttrDefine(const std::string& module_name_, const std::string& attr_info_, const AttrCfg cfg_);
    std::map<std::string, uint32_t> m_index;
    std::map<std::string, CAttrModule_t> m_module_pool;
};

using CObjAttr_t = std::shared_ptr<CObjAttr>;
using ObjAttrMap = std::unordered_map<std::string, CObjAttr_t>;
using PrototypeAttrMap = std::unordered_map<std::string, CAttributePrototype_t>;
class CAttrDefineManager: public Singleton<CAttrDefineManager> {
    friend class Singleton<CAttrDefineManager>;
public:
    void RegAttrDefine(const std::string& obj_name, const std::string& module_name_, const std::string& attr_info_, const AttrCfg cfg_);
    void InitPrototype(const std::string& obj_name);
    CAttribute_t CreateAttr(const std::string& obj_name);

private:
    CAttrDefineManager() = default;
    ObjAttrMap m_obj_attr_pool;
    PrototypeAttrMap m_obj_prototype_pool;
};

