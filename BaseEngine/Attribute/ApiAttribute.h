#pragma once
#include "Attribute.h"
#include "AttributeDefine.h"
#include <string>
#include <memory>
//����ϵͳ��Ƹ�Ҫ
/*
    ����ϵͳΪ��Ϸ�����ж����ṩ�Զ������ԵĹ���,���뵥��������ģ��ϵͳ,�ڿɼ���δ����,���׿���������ʹ��,����,�ɶ����븴�ӶȲ�����ҪĿ��,�����Ա��������λ,��Ϊ����ϰ���Բ�����ִ��Ч������,������һ�����Ż��ռ�

    ������Ƹ����ж�,������˵���Է�Ϊ4���,
    ����
    ʹ��
    ���л�
    ������

    4���ľ���Ŀ��Ҫ��
    ���Զ���: ������������չ��,�������κ�ʱ��,�κεط����κζ���������Զ���,Ҳ���Ժ����׵���չ��������ʽ
    ����ʹ��: ʹ�� get �� set API �������úͻ�ȡ���Ե�ֵ,�����ٶ�һ��GetConfig����,���Ի�ȡ���Ե�����
    �������л�: ������Է�������л��� protobuf ��protobuf �����ɶ�Ӧ�����Խṹ,��ʹ����������ֵҲ����ֱ������֮ǰ�Ľӿ����������κδ���    
    ���Լ�����: ����Ϸ����������,�ڷ���֮ǰ�����Գ�������,���������µ�����ʱ,ֻ��򵥵�ת�����뼴����ɼ���������,�������¶�������,

    ʵ��˼·:
    ���Զ���:
        Define("Player","BaseAttr","speed","0.0","float",Save)
        Player: ʲô������������
        Model: ʲôģ�������,���������ֱ�洢
        Speed: ��������
        0.0: ���Գ�ʼֵ
        float: ��������
        Save: enum ,��ʾ�Ƿ�洢�����ݿ�
        ����ȫ��ʹ���ַ���������,ע����һ�ű���,�ڶ����ʼ��ʱ,������Ƿ���� delay isntall
    ����ʹ��:
        ����ʵ�������������ʱ,ͨ�������������ͱ�����������ݴ洢,��:
        Define("Player","BaseAttr","speed","5.0","float",Save)
        Define("Player","BaseAttr","money","0","int64_t",Save)
        Define("Player","BaseAttr","special_money","200","uint64_t",Save)
        Define("Player","BaseAttr","name","default","string",Save)
        Define("Player","BaseAttr","attack","50","float",Save)
        ���ʵ��ӳ����
        vector<float> 
        vector<int64_t>
        vector<uint64_t>
        vector<string>
        vector<float>
        �ڶ���ʱ�̶�����vector ��С,Ȼ������ȡʱҲֱ�Ӵ�vector�д�ȡ
        //�����ӿ�
       Attribute.Get("speed")
       Attribute.Set("speed",0.1)
        //��չ�ӿ�
       Attribute.add("speed",0.1)
       Attribute.sub("speed",0.1)

    �������л�:
        Message* _msg = Attribute.ToProto();
        Attribute.FromProto(Message* );
        ���л�ĳ������ʱ,�׵����Զ����,�������������Ե����л�, һ������ת���� key val type,���� key �� val ��Ϊ string �����ж���, type Ϊʵ��type ,�ڵ���Ŀ���,��ԭ�ɶ�� vector ����ʽ

    ���Եļ���:
        ApiAttrDefine("Player","BaseAttr","attack:float:50",Save)
        ApiAttrDefineNewVer("Player","BaseAttr",,"attack:double:50",Save,[](){
            д��ת��
        })
        �ڶ������Ժ�׷�Ӷ��ת������,���Խ�������ת����������
*/


//����������,�米������.
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
