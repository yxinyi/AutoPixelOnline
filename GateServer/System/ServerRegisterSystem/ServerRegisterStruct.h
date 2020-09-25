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
    节点类型
    gate 服务器
    1: 客户端  Client
    功能: 连入gate时,会向单点服务器或集群进行消息
    MSG: 如果目标地址是单点服务器,由于单点服务器连入时会提前注册对应的消息关键字,gate无需额外处理即可转发,转发时候需要进行封装,如果有
    需要返回的信息加上 session id 让gate 来找到对应的Client 完成答复.
    所以 Client连入 gate 的时候需要生成一个 session ID, session ID 将是这个服务器体系中唯一的存在

    2: 单点服务器 AccountServer
    功能 连入 gate 的时候注册当前所有的消息,当 其他节点节点发送消息至 gate 时,gate会转发对应的消息, 消息包将带有 session id
    单点服务器发送返回包时携带该参数就能找到对应的目标
    

    3: 集群?? GameServer, Server

    如果一个服务器节点压力很大,就可能有多个节点组成一组类型,那么牵扯到了一个问题, 典型的比如 客户端在服务器上的数据往往是只有一份,
    那么如何处理这一种问题就很值得思考了,当然肯定还有可能存在多个节点的情况,即使不考虑这种情况,也要设计好如何相互之间关系的确定,
    更何况还有在相同类型间数据跳转的情况,如何在框架层上进行维护,保证不会转发至错误的目的地,还有当发生了客户端宕机或者服务器宕机,
    对应的链接关系如果处理,是断开还是自动连接至其他服务器,都是很值得考虑的.
    如果这类节点类似于客户端也在注册 gate 时候生成一个唯一 session, 那么当客户端第一次发送目的地为集群的消息时,就分配一个最低
    负载的节点关联至客户端, 
    这种关联需要由 gate 维护吗?
    
    如果是gate 维护, 那么当 client 断开时, 就接触对应的维护关系, 如果Game 服务器断开,那么是否要自动重连呢???
    自动重连行不通,必须踢掉,由客户端重新发起登陆流程.

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
    //该服务器注册的消息是否需要先在gate上通过验证后进行转发
    bool m_need_authenticate = true;
    //是否是集群
    bool m_slave = false;
    ServerState m_state = ServerState::Error;
    std::vector<std::string> m_message_register;
};

//gate 将进行消息的分发


enum class GateSessionState {
    Error,
    Pass,
    NeedAuthenticate,
};

struct GateSession {
    /*
        假如一个服务器类型有多个集群形式
        那么需要指定当前客户端与哪一个在通信
    */
    uint32_t m_conn_id = 0;
    uint32_t m_session_id = 0;
    GateSessionState m_state = GateSessionState::Error;
    std::set<uint32_t> m_type_conn;
};
using GateSession_t = std::shared_ptr<GateSession>;