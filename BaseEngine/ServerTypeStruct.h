#pragma once
enum class NodeType {
    Client,
    GateServer,
    LogicServer,
    DataBaseServer,
    AccountServer,
    NodeError
};
const char* GetNodeTypeStr(NodeType);

NodeType getNodeType();
//����Ǩ��DB����,����ip����gate��Ϣ
const char* GetGateIP();
uint32_t GetGatePort();