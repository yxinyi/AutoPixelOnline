#include "EngineInclude.h"
#include "BaseEngine.h"
#include "../Common/include/proto/Shakehand.pb.h"
#include "RenderManager.h"
#include <Windows.h>

const uint32_t g_frame = 100;
const NodeType g_node_type = NodeType::Client;
NodeType getNodeType() {
    return g_node_type;
}


void MainLoop() {

    try {
        const float _one_frame_time = 1000.f / static_cast<float>(g_frame);
        //const float _one_frame_time = 1000.f / static_cast<float>(30);
        Timer _frame_timer;
        Timer _tick_timer;
        Timer _second_fps_timer;
        uint32_t _fps_cnt = 1;
        SetConsoleTitleA("client");
        NetManager::getInstance()->Start();
        if (!RenderManager::getInstance()->WindowInit()) {
            system("pause");
            return;
        }
        while (true) {
            const int64_t _this_frame_time = _frame_timer.elapsed();
            if (_this_frame_time >= _one_frame_time) {
                _tick_timer.reset();
                CBaseEngine::getInstance()->run(_this_frame_time);
                RenderManager::getInstance()->Loop(_this_frame_time);
                
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
                    std::string _title = "client fps : ";
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
    }
    catch (...)
    {
        LogError << "Threw an unknown exception. Please derive from std::exception." << FlushLog;
    }
}


int main(int argc, char* argv[]) {

    MainLoop();
    return 0;
}