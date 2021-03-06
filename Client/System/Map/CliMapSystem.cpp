#include "./CliMapSystem.h"
#include "EngineInclude.h"
#include "Error/Error.h"
#include "proto/PlayerLogin.pb.h"
#include <math.h>
#include "SDL_rect.h"

RegSystem(CliMapSystem)

bool CliMapSystem::EnvDefine() {
    EventRegister(SceneMapInfo, [this](const uint64_t conn_,
        const std::shared_ptr<SceneMapInfo>& message_,
        const int64_t& receive_time_) {
        this->InitMap(message_);
        
    });


    ProtobufDispatch::getInstance()->registerMessageCallback<MapTickUpdate>([this](const SessionConn session_conn_,
        const std::shared_ptr<MapTickUpdate>& message_,
        const int64_t& receive_time_) {
        m_move_block_data.clear();
        for (auto&& _it : message_->map_infos()) {
            std::shared_ptr<MapData> _map_data = std::make_shared<MapData>();
            _map_data->ParseFromString(_it);
            m_move_block_data.push_back(_map_data);
        }
    });
    
    return true;
}

void CliMapSystem::InitMap(std::shared_ptr<SceneMapInfo> info_) {
    m_maze_shape.clear();
    m_cell_size = info_->map_block_size();
    auto _colmn_size = info_->map_info_size();
    for (int _colmn_idx = 0; _colmn_idx < _colmn_size; _colmn_idx++) {
        auto _rows_info = info_->map_info(_colmn_idx);
        auto _rows_size = _rows_info.rows_size();
        std::vector<uint32_t> _rows_vec;
        for (int _row_idx = 0; _row_idx < _rows_size; _row_idx++) {
            _rows_vec.push_back(_rows_info.rows(_row_idx).state());
        }
        m_maze_shape.push_back(_rows_vec);
    }
}


bool CliMapSystem::PreInit() {
    return true;
}
bool CliMapSystem::Init() {
    //TimerTaskMgr->RegisterTask("CliMapSystem::Init", 6000, 3000, 1, [this]() {
    //    LogError << "CliMapSystem::Init" << FlushLog;
    //    CConnection_t _server_conn = CConnectionMgr::getInstance()->GetConnection();
    //    shared_ptr<PlayerLoginEvent> _event = make_shared<PlayerLoginEvent>();
    //    NetManager::getInstance()->SendMessageBuff(_server_conn->getConnId(), _event);
    //});
    return true;
}
void CliMapSystem::MapRender(SDL_Window* windows_, SDL_Renderer* render_) {
    for (size_t _column_it = 0; _column_it < m_maze_shape.size();_column_it++) {
        for (size_t _row_it = 0; _row_it < m_maze_shape[_column_it].size();_row_it++) {
            //SDL_Rect _rect;
            //_rect.h = m_cell_size;
            //_rect.w = m_cell_size;
            //_rect.x = m_cell_size * _row_it;
            //_rect.y = m_cell_size * _column_it;
            auto _x = float(m_cell_size * _row_it);
            auto _y = float(m_cell_size * _column_it);
            if (m_maze_shape[_column_it][_row_it] == 1) {
                SDL_SetRenderDrawColor(render_, 0, 0, 0, 255);
            }
            else {
                SDL_SetRenderDrawColor(render_, 255, 255, 255, 255);
            }
            SDL_FRect rectToDraw{ _x, _y, (float)m_cell_size, (float)m_cell_size };
            SDL_RenderFillRectF(render_, &rectToDraw);
        }
    }

    for (auto&& _move_block_it : m_move_block_data) {
        LogInfo << "[CliMapSystem]: _move_block_it [" << _move_block_it->map_postion().postion_x() << " : " << _move_block_it->map_postion().postion_y() << "]" << FlushLog;
        SDL_SetRenderDrawColor(render_, 0, 0, 255, 255);
        SDL_FRect rectToDraw{ _move_block_it->map_postion().postion_x(), _move_block_it->map_postion().postion_y(), (float)5, (float)5 };
        SDL_RenderFillRectF(render_, &rectToDraw);
    }

}
bool CliMapSystem::Loop(const uint64_t interval_) {

    RenderManager::getInstance()->Register([this](SDL_Window* windows_, SDL_Renderer* render_) {
        this->MapRender(windows_, render_);
    });

    if (UIManager::getInstance()->GetNowScene() == UIScene::Game) {
        ImGuiIO& _io = ImGui::GetIO();
        //如果是左键则发送当前坐标给服务器
        if (_io.MouseClicked[0]) {
            
            std::shared_ptr<PlayerMoveTo> _msg = std::make_shared<PlayerMoveTo>();
            auto _pos = _msg->mutable_postion();
            _pos->set_postion_x(_io.MousePos.x);
            _pos->set_postion_y(_io.MousePos.y);
            if (CConnection_t _conn = CConnectionMgr::getInstance()->GetOnlyOneConnection(NodeType::GateServer)) {
                NetManager::getInstance()->SendMessageBuff(_conn->getConnId(),_msg);
            }
            LogError << "[CliMapSystem] PlayerMoveTo x: " << _io.MousePos.x << "y: " << _io.MousePos.y << FlushLog;
        }
    }

    //更顺滑的表现应该是,移动时,发送所有的节点至客户端,客户端和服务器同时进行移动计算,在每关键帧进行校对,当差距超过 当前网络延迟*速度 时,进行坐标修正
    static uint64_t _s_last_update_time = Time::getInstance()->NowMillisecond();
    uint64_t _now_time = Time::getInstance()->NowMillisecond();
    float _tick_proportion = (_now_time - _s_last_update_time) / 1000.f;
    _s_last_update_time = _now_time;
    for (auto&& _move_block_it : m_move_block_data) {

        auto _vec = _move_block_it->vector();
        auto _tar_pos = _move_block_it->target_postion();
        auto _now_pos = _move_block_it->mutable_map_postion();

        float _growup_x = _vec.postion_x() * _tick_proportion;;
        float _growup_y = _vec.postion_y() * _tick_proportion;;

        if (abs(_growup_x) > abs(_tar_pos.postion_x() - _now_pos->postion_x())) {
            _growup_x = _tar_pos.postion_x() - _now_pos->postion_x();
        }

        if (abs(_growup_y) > abs(_tar_pos.postion_y() - _now_pos->postion_y())) {
            _growup_y = _tar_pos.postion_y() - _now_pos->postion_y();
        }
        _now_pos->set_postion_x(_now_pos->postion_x() + _growup_x);
        _now_pos->set_postion_y(_now_pos->postion_y() + _growup_y);
    }
    return true;
}
bool CliMapSystem::Quit() {
    return true;
}
bool CliMapSystem::Destroy() {
    return true;
}