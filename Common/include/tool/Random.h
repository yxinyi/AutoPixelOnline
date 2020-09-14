#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <string.h>
#include <memory>
#include <stack>
#include "SingletonTemplate.h"

class RandomNumber : public Singleton<RandomNumber> {
public:
    RandomNumber() {
        srand((int)time(0));  
    }

    // <= x <
    uint64_t random(uint64_t left_limit_, uint64_t right_limit_) {
        return rand() % (right_limit_ - left_limit_) + left_limit_;
    }

};

