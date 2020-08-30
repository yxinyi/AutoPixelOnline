#include "TimerTask.h"
#include "Time.h"
#include <iostream>


bool TimerTaskManager::RegisterTask(const std::string& name_, const int64_t start_time_, const int64_t intervals_, int32_t loop_times_, TaskFunc func_) {
    TimerTask_t _task(new TimerTask);
    _task->m_name = name_;
    _task->m_start_time = start_time_ ? start_time_: NowTime->NowMillisecond();
    _task->m_intervals = intervals_;
    _task->m_loop_times = loop_times_;
    _task->m_func = func_;
    m_task_pool.push(_task);
    return true;
}
void  TimerTaskManager::Run() {
    if (!m_task_pool.size()) {
        return;
    }
    const int64_t _now_time = NowTime->NowMillisecond();
    for (;;) {
        TimerTask_t _task = m_task_pool.top();
        if (_task->m_start_time <= _now_time) {
            m_task_pool.pop();
            _task->m_func();
            --_task->m_loop_times;
            //std::cout << _task->m_loop_times << std::endl;
            if (_task->m_loop_times) {
                _task->m_start_time += _task->m_intervals;
                m_task_pool.push(_task);
            }
        }
        else {
            break;
        }
    }
}
