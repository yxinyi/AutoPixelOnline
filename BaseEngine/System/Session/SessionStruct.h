#pragma once
#include<map>
#include<memory>
#include "google/protobuf/message.h"
#include "proto/Session.pb.h"


/*
    简介:
    session 是作为客户端在各个终端服务器的镜像通信凭证,由GateServer确定并分发
    在各个服务器中session_id 是唯一的,而 conn_id 是根据GateServer在本地生成的连接而确定的
    当客户端并连入GateServer时候,生成 session_id , 当传入需要转发的消息时,GateServer将加上其session_id生成 SessionPack

    conn_id 是目标服务器, session_id 是辅助目标服务器进行转发,一般情况下上述的目标服务器是 gate 进行处理
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