#include "Attribute.h"
#include "ApiAttribute.h"

//ApiAttrDefine("Player", "BaseAttr", "attack:float:50", Save)
bool ApiAttrDefine(const std::string& obj_, const std::string& model_, const std::string& attr_info_, const AttrCfg ex_cfg_) {
    Singleton<CAttrDefineManager>::getInstance()->RegAttrDefine(obj_, model_, attr_info_, ex_cfg_);
    return true;
}

std::string ApiGetAttr(CAttribute_t, const std::string& model_, const std::string& name_) {

    
}

bool ApiSetAttr(CAttribute_t, const std::string& name_, const std::string& val_);

CAttribute_t ApiCreateAttr(const std::string& obj_name_) {
    return Singleton<CAttrDefineManager>::getInstance()->CreateAttr(obj_name_);
}
