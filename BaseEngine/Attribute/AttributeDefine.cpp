#include "./AttributeDefine.h"
#include "tool/StringHelper.h"
#include <vector>
#include <stack>
#include <tuple>

std::vector<std::tuple<std::string, std::string>>  ComplexStrDecoder(const std::string& src_str_) {
    std::vector<std::tuple<std::string, std::string, std::string>> _ret_string;
    std::stack<size_t> _idx_stack;
    std::string _local_str = ApiStringReplace(src_str_, " ", "");
    for (size_t _idx = 0; _idx != _local_str.size(); _idx++) {
        if (_local_str[_idx] == '{') {
            _idx_stack.push(_idx);
        }
        else if (_local_str[_idx] == '}') {
            size_t _top_it = _idx_stack.top();
            size_t _name_idx = _top_it + 1;
            if (_name_idx == std::string::npos) {
                _name_idx = 0;
            }
            _ret_string.push_back(std::tuple<std::string, std::string, std::string>(std::string(_local_str.begin() + _name_idx, _local_str.begin() + _local_str.find(',', _top_it)), std::string(_local_str.begin() + _local_str.find(',', _top_it) + 1, _local_str.begin() + _idx), std::string(_local_str.begin() + _top_it, _local_str.begin() + _idx + 1)));
            _idx_stack.pop();
        }
    }
    //从后往前遍历
    std::vector<std::tuple<std::string, std::string>> _clear_ret_str;
    for (auto&& _it = _ret_string.rbegin(); _it != _ret_string.rend(); _it++) {
        std::string _new_str = std::get<1>(*_it);
        for (auto&& _sub_it = _it + 1; _sub_it != _ret_string.rend(); _sub_it++) {
            _new_str = ApiStringReplace(_new_str, std::get<2>(*_sub_it), std::get<0>(*_sub_it));
        }
        _clear_ret_str.push_back(std::tuple<std::string, std::string>(std::get<0>(*_it), _new_str));
    }
    return _clear_ret_str;
}

//Define("Player", "BaseAttr", "ItemBag", "{item_id:uint32_t:0,item_id:uint64_t:0,item_attr:{item_de_val:uint64_t:0}}", Save)
void CAttrModule::RegAttrDefine( const std::string& attr_info_, AttrCfg cfg_) {
    if (attr_info_.find('{') == std::string::npos) {
        //single attr
        std::vector<std::string> _split_rst = ApiStringSplit(attr_info_, ":");
        m_attr_pool.push_back(CAttrDefine{ _split_rst[0], _split_rst[1], _split_rst[2], cfg_ });
    }
    else {
        std::vector<std::tuple<std::string, std::string>>  _decode_vec = ComplexStrDecoder(attr_info_);
        for (auto&& _it : _decode_vec) {
            std::string _tmp_name = std::get<0>(_it);
            std::string _tmp_info = std::get<1>(_it);
            std::vector<std::string> _split_rst = ApiStringSplit(_tmp_info, ":");
            //正常属性配置
            if (_split_rst.size() == 3) {
                m_attr_pool.push_back(CAttrDefine{ _split_rst[0], _split_rst[1], _split_rst[2], cfg_ });
            }
            //数组
            if (_split_rst.size() == 2 &&_split_rst[1] == "arr") {
                CAttrDefine _tmp_complex;
                _tmp_complex.m_type = _split_rst[0];
                m_vector_pool.push_back(CAttrDefine{ _split_rst[0], _split_rst[1], "arr", cfg_ });
            }
            //简单复杂类型
            if (_split_rst.size() == 1) {
                m_attr_pool.push_back(CAttrDefine{ _split_rst[0], _split_rst[0], "arr", cfg_ });
            }
        }
        std::vector<std::string> _split_rst = ApiStringSplit(attr_info_, ":");
        m_attr_pool.push_back(CAttrDefine{ _split_rst[0], _split_rst[1], _split_rst[2], cfg_ });
    }
}


void CObjAttr::RegAttrDefine(const std::string& module_name_, const std::string& attr_info_, const AttrCfg cfg_) {
    if (m_module_pool.find(module_name_) == m_module_pool.end()) {
        m_module_pool[module_name_] = CAttrModule_t(new CAttrModule);
    }
    m_module_pool[module_name_]->RegAttrDefine(attr_info_, cfg_);
}


void CAttrDefineManager::RegAttrDefine(const std::string& obj_name, const std::string& module_name_, const std::string& attr_info_, const AttrCfg cfg_) {
    if (m_obj_attr_pool.find(obj_name) == m_obj_attr_pool.end()) {
        m_obj_attr_pool[obj_name] = CObjAttr_t(new CObjAttr);
    }
    m_obj_attr_pool[obj_name]->RegAttrDefine(module_name_, attr_info_, cfg_);
}


CAttribute_t CAttrDefineManager::CreateAttr(const std::string& obj_name_) {
    if (m_obj_prototype_pool.find(obj_name_) == m_obj_prototype_pool.end()) {
        //没找到进行初始化
        InitPrototype(obj_name_);
        //_tmp_attr
    }
    

    return m_obj_prototype_pool[obj_name_]->Clone();
}

uint64_t AttrValConver(const std::string& type_, const std::string& val_) {
    union ParamExchange
    {
        double m_double;
        uint64_t m_u64_t;
        int m_32_t;
        void* m_point;
    };
    if (type_ == "uint64_t" || type_ == "int64_t") {
        //负数?
        return std::atoll(val_.c_str());
    }
    else if(type_ == "uint32_t" || type_ == "int32_t"){
        int _tmp_double = std::atoi(val_.c_str());
        ParamExchange _un;
        _un.m_32_t = _tmp_double;
        return _un.m_u64_t;
    }    
    else if (type_ == "float" ||type_ == "double")  {
        double _tmp_double = std::atof(val_.c_str());
        ParamExchange _un;
        _un.m_double = _tmp_double;
        return _un.m_u64_t;
    }
    else if(type_ == "arr"){
        ParamExchange _un;
        _un.m_point = nullptr;
        return _un.m_u64_t;
    }
    else if(type_ == "string") {
        ParamExchange _un;
        _un.m_point = nullptr;
        return _un.m_u64_t;
    }
    else if (type_ == "point") {
        ParamExchange _un;
        _un.m_point = nullptr;
        return _un.m_u64_t;
    }
    else {
        printf("type [%s] not define conver rule \n", type_.c_str());
    }
    return 0;
}

void CAttrDefineManager::InitPrototype(const std::string& obj_name_) {
    CAttributePrototype_t  _prototype(new CAttributePrototype);
    if (m_obj_attr_pool.find(obj_name_) == m_obj_attr_pool.end()) {
        printf("CAttrDefineManager InitPrototype error  [%s] \n", obj_name_.c_str());
    }

    uint32_t _idx = 0;
    for (auto&& _it : m_obj_attr_pool[obj_name_]->m_module_pool) {
        std::string _module_name = _it.first;
        for (auto&& _module_it : _it.second->m_attr_pool) {
            m_obj_attr_pool[obj_name_]->m_index[_module_name + _module_it.m_key] = _idx++;
            _prototype->m_attr->m_eight_byte.push_back(AttrValConver(_module_it.m_type, _module_it.m_val));
        }
    }
}

CAttribute_t CAttributePrototype::Clone() {
    CAttribute_t _rst_attr(new CAttribute);
    _rst_attr->m_eight_byte.clear();
    AttrValVec _tmp(this->m_attr->m_eight_byte.begin(), this->m_attr->m_eight_byte.end());
    _rst_attr->m_eight_byte.swap(_tmp);
    return _rst_attr;
}
