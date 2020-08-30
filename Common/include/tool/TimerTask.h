#pragma once
#include "SingletonTemplate.h"
#include <chrono>
#include <functional>
#include <string>
#include <map>
#include <memory>
#include <any>
#include <vector>
#include <queue>

using TaskFunc = std::function<void()>;
struct TimerTask {
    std::string m_name;
    int64_t m_start_time = 0;
    int64_t m_intervals = 0;
    int32_t m_loop_times = 0;
    TaskFunc m_func;
};
using TimerTask_t = std::shared_ptr<TimerTask>;



struct TSCompare //ÖØÐ´·Âº¯Êý
{
    bool operator() (TimerTask_t lhs_, TimerTask_t rhs_)
    {
        return lhs_->m_start_time > rhs_->m_start_time; //´ó¶¥¶Ñ
    }
};


class TimerTaskManager: public Singleton<TimerTaskManager> {
public:
    bool RegisterTask(const std::string& name_, const int64_t start_time, const int64_t intervals_, int32_t loop_times_, TaskFunc func_);
    void Run();

private:
    std::priority_queue<TimerTask_t, std::vector<TimerTask_t>, TSCompare> m_task_pool;
};

#define TimerTaskMgr Singleton<TimerTaskManager>::getInstance()
