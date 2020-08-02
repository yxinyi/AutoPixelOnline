#pragma once
#include "Attribute.h"
#include "AttributeDefine.h"
#include <string>
#include <memory>
//属性系统设计概要
/*
    属性系统为游戏中所有对象提供自定义属性的功能,必须单独于所有模块系统,在可见的未来里,整套开发仅个人使用,所以,可读性与复杂度不做主要目标,易用性必须放在首位,因为作练习所以不考虑执行效率问题,但留出一定的优化空间

    属性设计个人判断,总体来说可以分为4大块,
    定义
    使用
    序列化
    兼容性

    4大块的具体目标要求
    属性定义: 必须是容易扩展的,方便在任何时候,任何地方对任何对象进行属性定义,也可以很容易的扩展成配置形式
    属性使用: 使用 get 和 set API 即可设置和获取属性的值,或许再多一个GetConfig属性,可以获取属性的配置
    属性序列化: 必须可以方便的序列化至 protobuf 从protobuf 中生成对应的属性结构,即使在新增属性值也可以直接沿用之前的接口无需新增任何代码    
    属性兼容性: 当游戏开发过程中,在发生之前的属性出现问题,不满足最新的需求时,只需简单的转换代码即可完成兼容性需求,无需重新定义属性,

    实现思路:
    属性定义:
        Define("Player","BaseAttr","speed","0.0","float",Save)
        Player: 什么对象增加属性
        Model: 什么模块的属性,可以用来分表存储
        Speed: 属性名称
        0.0: 属性初始值
        float: 属性类型
        Save: enum ,表示是否存储于数据库
        定义全部使用字符串来进行,注册至一张表里,在对象初始化时,视情况是否进行 delay isntall
    属性使用:
        属性实例化至具体对象时,通过多张数据类型表格来进行数据存储,例:
        Define("Player","BaseAttr","speed","5.0","float",Save)
        Define("Player","BaseAttr","money","0","int64_t",Save)
        Define("Player","BaseAttr","special_money","200","uint64_t",Save)
        Define("Player","BaseAttr","name","default","string",Save)
        Define("Player","BaseAttr","attack","50","float",Save)
        最后实际映射至
        vector<float> 
        vector<int64_t>
        vector<uint64_t>
        vector<string>
        vector<float>
        在定义时固定上述vector 大小,然后具体存取时也直接从vector中存取
        //基本接口
       Attribute.Get("speed")
       Attribute.Set("speed",0.1)
        //扩展接口
       Attribute.add("speed",0.1)
       Attribute.sub("speed",0.1)

    属性序列化:
        Message* _msg = Attribute.ToProto();
        Attribute.FromProto(Message* );
        序列化某个对象时,易得属性定义表,遍历表格进行属性的序列化, 一个属性转换成 key val type,其中 key 和 val 均为 string 来进行定义, type 为实际type ,在到达目标后,还原成多个 vector 的形式

    属性的兼容:
        ApiAttrDefine("Player","BaseAttr","attack:float:50",Save)
        ApiAttrDefineNewVer("Player","BaseAttr",,"attack:double:50",Save,[](){
            写入转换
        })
        在定义属性后方追加多个转换函数,可以将旧属性转换成新属性
*/


//数组解决方案,如背包数组.
/*
struct AttrDef{
    std::string m_key;
    std::string m_val;
    std::string m_type;
};

struct AttrComplexDef{
    std::vector<AttrDefine> m_complex;
};


Define("Player","BaseAttr","ItemBag","{item_id:uint32_t:0,item_id:uint64_t:0,item_attr:{item_de_val:}}",Save)

chunk = uint32_t|uint64_t|uint32_t|std::vector<std::shard_ptr<chunk>>
std::map<ItemBag,std::vector<chunk*>>


struct ItemInfo{
    {
        item_id, item_oid,item_val;

    
    }
}





*/




//ApiAttrDefine("Player", "BaseAttr", "attack:float:50", Save)
bool ApiAttrDefine(const std::string& obj_, const std::string& model_, const std::string& attr_info_, const AttrCfg ex_cfg_);

std::string ApiGetAttr(CAttribute_t, const std::string& name_);

bool ApiSetAttr(CAttribute_t, const std::string& name_, const std::string& val_);

CAttribute_t ApiCreateAttr(const std::string& obj_name_);
