#pragma once
enum class NodeType {
    Client,
    GateServer,
    LogicServer,
    DataBaseServer,
    AccountServer,
    ListServer,
    NodeError
};
const char* GetNodeTypeStr(NodeType);

NodeType getNodeType();