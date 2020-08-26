#pragma once
#include "../../../BaseEngine/System/BaseSystem.h"

class ShakeHandSystem :public BaseSystem {
public:
    ShakeHandSystem():BaseSystem("ShakeHandSystem"){}
    bool EnvDefine(); 
    bool PreInit(); 
    bool Init(); 
    bool Loop(const uint64_t interval_); 
    bool Quit();
    bool Destroy();

private:
    void ShakeHandPrint();

};


