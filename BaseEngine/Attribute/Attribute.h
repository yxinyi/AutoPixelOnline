#pragma once
#include <memory>
#include <vector>


using AttrValVec = std::vector<uint64_t>;

class CAttribute {
public:
    AttrValVec m_eight_byte;
};

using CAttribute_t = std::shared_ptr<CAttribute>;
using CAttribute_wt = std::shared_ptr<CAttribute>;