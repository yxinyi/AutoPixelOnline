#pragma once
#include<map>
#include<memory>
#include "google/protobuf/message.h"
#include "proto/Session.pb.h"


/*
    ���:
    session ����Ϊ�ͻ����ڸ����ն˷������ľ���ͨ��ƾ֤,��GateServerȷ�����ַ�
    �ڸ�����������session_id ��Ψһ��,�� conn_id �Ǹ���GateServer�ڱ������ɵ����Ӷ�ȷ����
    ���ͻ��˲�����GateServerʱ��,���� session_id , ��������Ҫת������Ϣʱ,GateServer��������session_id���� SessionPack

    conn_id ��Ŀ�������, session_id �Ǹ���Ŀ�����������ת��,һ�������������Ŀ��������� gate ���д���
*/
using Session = uint32_t;
using SessionConn = uint64_t;
using SessionPack_t = std::shared_ptr<SessionPack>;
using SessionDestory_t = std::shared_ptr<SessionDestory>;

Session ApiGetSession(SessionConn);
uint32_t ApiGetConnID(SessionConn);
