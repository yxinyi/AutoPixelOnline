#pragma once
#include <iostream>

#define LogInfo std::cout << "LogInfo: " 
#define LogWarn std::cout << "LogWarn: " 
#define LogError std::cout << "LogError: " 

#define FlushLog std::endl;

#define RETURN_VOID   \
        std::cout << "RETURN_VOID: " << __FILE__  << " : " << __LINE__ << std::endl;\
        return;

#define RETURN_0   \
        std::cout << "RETURN_0: " << __FILE__  << " : " << __LINE__ << std::endl;\
        return 0;


#define RETURN_NULLPTR   \
        std::cout << "RETURN_0: " << __FILE__  << " : " << __LINE__ << std::endl;\
        return nullptr;

#define RETURN_FALSE   \
        std::cout << "RETURN_FALSE: " << __FILE__  << " : " << __LINE__ << std::endl;\
        return false;
#define RETURN_TRUE   \
        std::cout << "RETURN_TRUE: " << __FILE__  << " : " << __LINE__ << std::endl;\
        return true;
#define CONTINUE   \
        std::cout << "CONTINUE: " << __FILE__  << " : " << __LINE__ << std::endl;\
        continue;

#define BREAK   \
        std::cout << "BREAK: " << __FILE__  << " : " << __LINE__ << std::endl;\
        break;