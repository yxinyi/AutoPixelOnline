#pragma once
#include <memory>


class CAttribute {
public:
    std::vector<uint64_t> m_eight_byte;
};

using CAttribute_t = std::shared_ptr<CAttribute>;