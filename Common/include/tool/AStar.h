#pragma once
#include <vector>
#include <set>
#include <memory>
#include <map>
struct SAstarPoint {
    int64_t m_id = 0;
    int32_t m_x = 0;
    int32_t m_y = 0;
    float m_h = 0; //到出发点的估算距离
    float m_g = 0; //到目的地的估算距离
    float m_rate = 1.f; //如果是对角,路径要长一点
    std::shared_ptr<SAstarPoint> m_parent = nullptr;
};
using SAstarPoint_t = std::shared_ptr<SAstarPoint>;
class Astar {
public:
    Astar(std::vector<std::vector<uint32_t>> maze_) :m_maze(maze_),m_maze_clounmn(maze_.size()),m_maze_row(maze_[0].size()) {

    }

    SAstarPoint_t getPath(const uint32_t start_x_, const uint32_t start_y_, const uint32_t end_x, const uint32_t end_y_) {
        m_open_list.clear();
        m_close_list.clear();
        SAstarPoint_t _start_point = getNode(nullptr, start_x_, start_y_);
        SAstarPoint_t _end_point = getNode(nullptr, end_x, end_y_);
        if (!_start_point||!_end_point) {
            return nullptr;
        }
        m_open_list[_start_point->m_id] = _start_point;
        _start_point->m_g = 1;
        SAstarPoint_t _start_node_point = _start_point;
        
        while (m_open_list.size() && _start_node_point){
            std::vector<SAstarPoint_t> _round_point = getRoundPoints(_start_node_point);
            for (auto& _it : _round_point) {
                if (_it->m_x == _end_point->m_x && _it->m_y == _end_point->m_y) {
                    return _it;
                }
                _it->m_h = CalcDistance(_it,_start_point);
                _it->m_g = _start_node_point->m_g+1;
                m_open_list[_it->m_id] = _it;
            }
            m_open_list.erase(_start_node_point->m_id);
            m_close_list.insert(_start_node_point->m_id);
            _start_node_point = getMinOpenNode();
        } 
        return nullptr;
    }

private:


    float CalcDistance(SAstarPoint_t start, SAstarPoint_t end) {
        return (abs(start->m_x - end->m_x) + abs(start->m_y - end->m_y)) * end->m_rate;
    }

    SAstarPoint_t getNode(SAstarPoint_t point_, const uint32_t x_, const uint32_t y_) {
        if (x_ < 0 || y_ < 0 || x_ >= m_maze_row || y_ >= m_maze_clounmn) {
            return nullptr;
        }
        if (m_maze[y_][x_] == 2) {
            return nullptr;
        }
        const uint64_t _unique_id = getUniqueID(x_, y_);
        if (m_open_list.find(_unique_id) != m_open_list.end()) {
            return nullptr;
        }
        if (m_close_list.find(_unique_id) != m_close_list.end()) {
            return nullptr;
        }


        SAstarPoint_t _new_point = std::make_shared<SAstarPoint>();
        _new_point->m_x = x_;
        _new_point->m_y = y_;
        _new_point->m_parent = point_;
        _new_point->m_id = _unique_id;
        return _new_point;
    }


    std::vector<SAstarPoint_t> getRoundPoints(SAstarPoint_t point_) {
        std::vector< SAstarPoint_t> _rst_ptr;
        uint32_t _point_x = point_->m_x;
        uint32_t _point_y = point_->m_y;

        if (SAstarPoint_t _point = getNode(point_, _point_x - 1, _point_y - 1)) {
            _point->m_rate = 1.4f;
            _rst_ptr.push_back(_point);
        }
        if (SAstarPoint_t _point = getNode(point_, _point_x - 1, _point_y)) {
            _rst_ptr.push_back(_point);
        }
        if (SAstarPoint_t _point = getNode(point_, _point_x - 1, _point_y + 1)) {
            _point->m_rate = 1.4f;
            _rst_ptr.push_back(_point);
        }
        if (SAstarPoint_t _point = getNode(point_, _point_x, _point_y - 1)) {
            _rst_ptr.push_back(_point);
        }
        if (SAstarPoint_t _point = getNode(point_, _point_x, _point_y + 1)) {
            _rst_ptr.push_back(_point);
        }
        if (SAstarPoint_t _point = getNode(point_, _point_x + 1, _point_y - 1)) {
            _point->m_rate = 1.4f;
            _rst_ptr.push_back(_point);
        }
        if (SAstarPoint_t _point = getNode(point_, _point_x + 1, _point_y)) {
            _rst_ptr.push_back(_point);
        }
        if (SAstarPoint_t _point = getNode(point_, _point_x + 1, _point_y + 1)) {
            _point->m_rate = 1.4f;
            _rst_ptr.push_back(_point);
        }
        return _rst_ptr;
    }

    uint64_t getUniqueID(const uint32_t x_, const uint32_t y_) {
        return (uint64_t)(x_) << 32 | (uint64_t)(y_);
    }

    uint64_t getUniqueID(SAstarPoint_t point_) {
        return getUniqueID(point_->m_x, point_->m_y);
    }

    SAstarPoint_t getMinOpenNode() {
        SAstarPoint_t _rst_node;
        float _rst_min = 9999999999.f;
        for (auto& _it : m_open_list) {
            const float _f = _it.second->m_g + _it.second->m_h;
            if (_f < _rst_min) {
                _rst_min = _f;
                _rst_node = _it.second;
            }
        }
        return _rst_node;
    }


    std::map<uint64_t, SAstarPoint_t> m_open_list;
    std::set<uint64_t> m_close_list;

    std::vector<std::vector<uint32_t>> m_maze;
    uint64_t m_maze_clounmn;
    uint64_t m_maze_row;

};

using Astar_t = std::shared_ptr<Astar>;