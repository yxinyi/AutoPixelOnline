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

struct Session {
    Session(const uint64_t session_id_, const uint32_t conn_id_):
        m_session_id(session_id_), m_conn_id(conn_id_)
    {
    }

    bool SendMessageBuff(std::shared_ptr<google::protobuf::Message>) const;

    uint64_t m_session_id;
    uint32_t m_conn_id;
};
using Session_t = std::shared_ptr<Session>;
using SessionPack_t = std::shared_ptr<SessionPack>;
using SessionCreate_t = std::shared_ptr<SessionCreate>;
using SessionDestory_t = std::shared_ptr<SessionDestory>;