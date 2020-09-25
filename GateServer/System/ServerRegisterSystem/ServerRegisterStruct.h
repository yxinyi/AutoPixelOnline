#pragma once
#include "System/BaseSystem.h"
#include <vector>
#include <string>
#include <memory>
#include "ServerTypeStruct.h"
#include "proto/ServerLink.pb.h"

enum class ServerState {
    Error,
    Touch,
    close,
    runing,
};

struct  ServerInfo{
    uint32_t m_conn_id;
    NodeType m_node_type;
    ServerState m_state = ServerState::Error;
    std::vector<std::string> m_message_register;
    uint32_t m_load_number = 0;
};
using ServerInfo_t = std::shared_ptr<ServerInfo>;
using ServerInfo_wt = std::weak_ptr<ServerInfo>;

/*
    �ڵ�����
    gate ������
    1: �ͻ���  Client
    ����: ����gateʱ,���򵥵��������Ⱥ������Ϣ
    MSG: ���Ŀ���ַ�ǵ��������,���ڵ������������ʱ����ǰע���Ӧ����Ϣ�ؼ���,gate������⴦����ת��,ת��ʱ����Ҫ���з�װ,�����
    ��Ҫ���ص���Ϣ���� session id ��gate ���ҵ���Ӧ��Client ��ɴ�.
    ���� Client���� gate ��ʱ����Ҫ����һ�� session ID, session ID ���������������ϵ��Ψһ�Ĵ���

    2: ��������� AccountServer
    ���� ���� gate ��ʱ��ע�ᵱǰ���е���Ϣ,�� �����ڵ�ڵ㷢����Ϣ�� gate ʱ,gate��ת����Ӧ����Ϣ, ��Ϣ�������� session id
    ������������ͷ��ذ�ʱЯ���ò��������ҵ���Ӧ��Ŀ��
    

    3: ��Ⱥ?? GameServer, Server

    ���һ���������ڵ�ѹ���ܴ�,�Ϳ����ж���ڵ����һ������,��ôǣ������һ������, ���͵ı��� �ͻ����ڷ������ϵ�����������ֻ��һ��,
    ��ô��δ�����һ������ͺ�ֵ��˼����,��Ȼ�϶����п��ܴ��ڶ���ڵ�����,��ʹ�������������,ҲҪ��ƺ�����໥֮���ϵ��ȷ��,
    ���ο���������ͬ���ͼ�������ת�����,����ڿ�ܲ��Ͻ���ά��,��֤����ת���������Ŀ�ĵ�,���е������˿ͻ���崻����߷�����崻�,
    ��Ӧ�����ӹ�ϵ�������,�ǶϿ������Զ�����������������,���Ǻ�ֵ�ÿ��ǵ�.
    �������ڵ������ڿͻ���Ҳ��ע�� gate ʱ������һ��Ψһ session, ��ô���ͻ��˵�һ�η���Ŀ�ĵ�Ϊ��Ⱥ����Ϣʱ,�ͷ���һ�����
    ���صĽڵ�������ͻ���, 
    ���ֹ�����Ҫ�� gate ά����?
    
    �����gate ά��, ��ô�� client �Ͽ�ʱ, �ͽӴ���Ӧ��ά����ϵ, ���Game �������Ͽ�,��ô�Ƿ�Ҫ�Զ�������???
    �Զ������в�ͨ,�����ߵ�,�ɿͻ������·����½����.

    struct Node{
        NodeType
        ConnectID
        SessionID
        SessionConn
    };
    struct Nodemanager{
        map<NodeType <<32 | NodeTyep, map<SessionConn,SessionConn>> node_avert_contornl;
    };

*/


struct SServerInfo{
    uint32_t m_conn_id;
    NodeType m_node_type;
    //�÷�����ע�����Ϣ�Ƿ���Ҫ����gate��ͨ����֤�����ת��
    bool m_need_authenticate = true;
    //�Ƿ��Ǽ�Ⱥ
    bool m_slave = false;
    ServerState m_state = ServerState::Error;
    std::vector<std::string> m_message_register;
};

//gate ��������Ϣ�ķַ�


enum class GateSessionState {
    Error,
    Pass,
    NeedAuthenticate,
};

struct GateSession {
    /*
        ����һ�������������ж����Ⱥ��ʽ
        ��ô��Ҫָ����ǰ�ͻ�������һ����ͨ��
    */
    uint32_t m_conn_id = 0;
    uint32_t m_session_id = 0;
    GateSessionState m_state = GateSessionState::Error;
    std::set<uint32_t> m_type_conn;
};
using GateSession_t = std::shared_ptr<GateSession>;