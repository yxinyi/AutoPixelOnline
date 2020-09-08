#pragma once
enum class NodeType {
    Client,
    GateServer,
    LogicServer,
    DataBaseServer
};
NodeType getNodeType();
//后续迁入DB配置,根据ip返回gate信息
const char* GetGateIP();
uint32_t GetGatePort();