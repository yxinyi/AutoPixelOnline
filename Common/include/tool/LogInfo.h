#pragma once
#include <iostream>

#define LogInfo std::cout << "LogInfo: " 
#define LogWarn std::cout << "LogWarn: " 
#define LogError std::cout << "LogError: " 

#define FlushLog std::endl;

#define RETURN_VOID   \
        std::cout << "RETURN_VOID: " << __FILE__  << " : " << __LINE__ << std::endl;\
        return;
