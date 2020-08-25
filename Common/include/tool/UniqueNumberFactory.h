#pragma once
#include <cstdint>
#include <iostream>
#include "include/tool/SingletonTemplate.h"

class UniqueNumberFactory : public Singleton<UniqueNumberFactory> {
    friend Singleton<UniqueNumberFactory>;
private:
    UniqueNumberFactory();
public:
    uint64_t build();
};

uint64_t APIGetUniqueNumber();
