#include "include/tool/Time.h"
#include "include/tool/Timer.h"
#include "include/tool/LogInfo.h"
#include "BaseEngine.h"
#include "EngineInclude.h"
#include "include/leveldb/db.h"
#include <Windows.h>

const uint32_t g_frame = 1000;
const NodeType g_node_type = NodeType::GateServer;
NodeType getNodeType() {
    return g_node_type;
}


void MainLoop() {

    try {
        const float _one_frame_time = 1000.f / static_cast<float>(g_frame);
        Timer _frame_timer;
        Timer _tick_timer;
        Timer _second_fps_timer;
        uint32_t _fps_cnt = 1;
        SetConsoleTitleA("GateServer");
        if (!NetManager::getInstance()->Start()) {
            std::cout << "server start error " << std::endl;
        }

        while (true) {
            const int64_t _this_frame_time = _frame_timer.elapsed();
            if (_this_frame_time >= _one_frame_time) {
                _tick_timer.reset();
                Singleton<CBaseEngine>::getInstance()->run(_this_frame_time);
                _frame_timer.reset();

                int64_t _tick_time = _tick_timer.elapsed();
                if (_tick_time > 150) {
                    if (_tick_time > 300) {
                        LogError << "frame tick :  " << _tick_timer.elapsed() << FlushLog;
                    }
                    else {
                        LogWarn << "frame tick :  " << _tick_timer.elapsed() << FlushLog;
                    }
                }
                if (_second_fps_timer.elapsed() < 1000) {
                    _fps_cnt++;
                }
                else {
                    std::string _title = "GateServer fps : ";
                    _title += std::to_string(_fps_cnt);
                    SetConsoleTitleA(_title.c_str());
                    _second_fps_timer.reset();
                    _fps_cnt = 1;
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        LogError << "Exception: " << e.what() << FlushLog;
        system("pause");
    }
    catch (...)
    {
        LogError << "Threw an unknown exception. Please derive from std::exception." << FlushLog;
    }
}


int main() {

    MainLoop();
    return 0;
}