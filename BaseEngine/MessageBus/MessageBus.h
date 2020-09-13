#pragma once
#include <functional>
#include <tuple>
#include <string>
#include <Any>
#include <map>
#include "include/tool/SingletonTemplate.h"


#define MsgEvent 

template<typename T>
struct function_traits;

//普通函数
template<typename Ret, typename... Args>
struct function_traits<Ret(Args...)>{
    //const size_t _arity = sizeof...(Args);
    enum {_arity = sizeof...(Args) };
    typedef Ret function_type(Args...);
    typedef Ret return_type;
    using stl_function_type = std::function<function_type>;
    typedef Ret(*pointer)(Args...);

    template<size_t I>
    struct args {
        static_assert(I < _arity, "index is out of range, index must less than sizeof args");
        using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
    };
};

//函数指针
template<typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)> {};
//std::function
template<typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)> {};
//member function
#define FUNCTION_TRAITS(...)                                                                    \
template<typename Ret, typename Class, typename... Args>                                        \
struct function_traits<Ret(Class::*)(Args...)__VA_ARGS__> : function_traits<Ret(Args...)> {};   \


FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(const volatile)
FUNCTION_TRAITS(volatile)
//函数对象
template<typename Callable>
struct function_traits :function_traits<decltype(&Callable::operator())> {};

template<typename Function>
typename function_traits<Function>::stl_function_type to_function(const Function& lambda) {
    return static_cast<typename function_traits<Function>::stl_function_type>(lambda);
}

template<typename Function>
typename function_traits<Function>::stl_function_type to_function(Function&& lambda) {
    return static_cast<typename function_traits<Function>::stl_function_type>(std::forward<Function>(lambda));
}

template<typename Function>
typename function_traits<Function>::pointer to_function_pointer(const Function& lambda) {
    return static_cast<typename function_traits<Function>::pointer>(lambda);
}

class MessageBus : public Singleton<MessageBus>{
    MessageBus& operator=(const MessageBus&) = delete;
    MessageBus(const MessageBus&) = delete;
    friend class Singleton<MessageBus>;
public:
    template<typename F>
    void Attach(F&& f_, const std::string& topic_ = "") {
        typename function_traits<F>::stl_function_type _func = to_function(std::forward<F>(f_));
        add(topic_, _func);
    }

    void SendReq(const std::string& topic_ = "") {
        using function_type = std::function<void ()>;
        std::string _msg_type = topic_ + typeid(function_type).name();
        
        std::pair<Iterater, Iterater> _range = m_map.equal_range(_msg_type);
        for (Iterater _start = _range.first; _start != _range.second;_start++) {
            std::any_cast<function_type>(_start->second)();
        }
    }
    template<typename... Args>
    void SendReq(Args... args_,const std::string& topic_ = "") {
        using function_type = std::function<void(Args...)>;
        std::string _msg_type = topic_ + typeid(function_type).name();
        std::pair<Iterater, Iterater> _range = m_map.equal_range(_msg_type);
        for (Iterater _start = _range.first; _start != _range.second; _start++) {
            std::any_cast<function_type>(_start->second)(args_...);
        }
    }

    template<typename... Args>
    void Remove(const std::string& topic_ ) {
        using function_type = std::function<void(Args...)>;
        std::string _msg_type = topic_ + typeid(function_type).name();
        
        std::pair<Iterater, Iterater> _range = m_map.equal_range(_msg_type);
        m_map.erase(_range.first, _range.second);
    }



private:
    template<typename F>
    void add(const std::string& topic_, F&& f_) {
        const std::string _msg_type = topic_ + typeid(F).name();
        m_map.emplace(std::move(_msg_type),std::forward<F>(f_));
    }
    MessageBus() {}
    std::multimap<std::string, std::any> m_map;

    using Iterater = std::multimap<std::string, std::any>::iterator;
};

