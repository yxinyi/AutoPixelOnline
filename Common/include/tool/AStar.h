#pragma once
#include <vector>
#include <set>
#include <memory>
#include <map>
struct Point {
    int64_t m_id = 0;
    int32_t m_x = 0;
    int32_t m_y = 0;
    float m_h = 0; //到出发点的估算距离
    float m_g = 0; //到目的地的估算距离
    float m_rate = 1.f; //如果是对角,路径要长一点
    std::shared_ptr<Point> m_parent = nullptr;
};

class Astar {
public:
    Astar(std::vector<std::vector<uint32_t>> maze_) :m_maze(maze_),m_maze_clounmn(maze_.size()),m_maze_row(maze_[0].size()) {

    }

    float CalcDistance(std::shared_ptr<Point> start, std::shared_ptr<Point> end) {
        return (abs(start->m_x - end->m_x) + abs(start->m_y - end->m_y)) * end->m_rate;
    }

    std::shared_ptr<Point> getNode(std::shared_ptr<Point> point_,const uint32_t x_, const uint32_t y_) {
        if (x_ < 0 || y_ < 0 || x_ >= m_maze_row || y_ >= m_maze_clounmn) {
            return nullptr;
        }
        if (m_maze[y_][x_] == 2) {
            return nullptr;
        }
        const uint64_t _unique_id = getUniqueID(x_,y_);
        if (m_open_list.find(_unique_id) != m_open_list.end()) {
            return nullptr;
        }
        if (m_close_list.find(_unique_id) != m_close_list.end()) {
            return nullptr;
        }


        std::shared_ptr<Point> _new_point(new Point);
        _new_point->m_x = x_;
        _new_point->m_y = y_;
        _new_point->m_parent = point_;
        _new_point->m_id = _unique_id;
        return _new_point;
    }


    std::vector<std::shared_ptr<Point>> getRoundPoints(std::shared_ptr<Point> point_) {
        std::vector< std::shared_ptr<Point>> _rst_ptr;
        uint32_t _point_x = point_->m_x;
        uint32_t _point_y = point_->m_y;

        if (std::shared_ptr<Point> _point = getNode(point_, _point_x - 1, _point_y - 1)) {
            _point->m_rate = 1.4f;
            _rst_ptr.push_back(_point);
        }
        if (std::shared_ptr<Point> _point = getNode(point_, _point_x - 1, _point_y)) {
            _rst_ptr.push_back(_point);
        }
        if (std::shared_ptr<Point> _point = getNode(point_, _point_x - 1, _point_y+1)) {
            _point->m_rate = 1.4f;
            _rst_ptr.push_back(_point);
        }
        if (std::shared_ptr<Point> _point = getNode(point_, _point_x, _point_y - 1)) {
            _rst_ptr.push_back(_point);
        }
        if (std::shared_ptr<Point> _point = getNode(point_, _point_x, _point_y + 1)) {
            _rst_ptr.push_back(_point);
        }
        if (std::shared_ptr<Point> _point = getNode(point_, _point_x + 1, _point_y - 1)) {
            _point->m_rate = 1.4f;
            _rst_ptr.push_back(_point);
        }
        if (std::shared_ptr<Point> _point = getNode(point_, _point_x + 1, _point_y)) {
            _rst_ptr.push_back(_point);
        }
        if (std::shared_ptr<Point> _point = getNode(point_, _point_x + 1, _point_y + 1)) {
            _point->m_rate = 1.4f;
            _rst_ptr.push_back(_point);
        }
        return _rst_ptr;
    }

    uint64_t getUniqueID(const uint32_t x_, const uint32_t y_) {
        return (uint64_t)(x_) << 32 | (uint64_t)(y_);
    }

    uint64_t getUniqueID(std::shared_ptr<Point> point_) {
        return getUniqueID(point_->m_x,point_->m_y);
    }

    std::shared_ptr<Point> getMinOpenNode() {
        std::shared_ptr<Point> _rst_node;
        float _rst_min = -1;
        for (auto& _it : m_open_list) {
            const float _f = _it.second->m_g + _it.second->m_h;
            if (_f < _rst_min) {
                _rst_min = _f;
                _rst_node = _it.second;
            }
        }
        return _rst_node;
    }
    
    std::shared_ptr<Point> getPath(Point start_, Point end_) {
        m_open_list.clear();
        m_close_list.clear();
        std::shared_ptr<Point> _start_point = getNode(nullptr, start_.m_x, start_.m_y);
        std::shared_ptr<Point> _end_point = getNode(nullptr, end_.m_x, end_.m_y);
        if (!_start_point||!_end_point) {
            return nullptr;
        }
        m_open_list[_start_point->m_id] = _start_point;
        _start_point->m_g = 1;
        std::shared_ptr<Point> _start_node_point = _start_point;
        
        while (m_open_list.size() && _start_node_point){
            std::vector<std::shared_ptr<Point>> _round_point = getRoundPoints(_start_node_point);
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
    std::map<uint64_t, std::shared_ptr<Point>> m_open_list;
    std::set<uint64_t> m_close_list;

    std::vector<std::vector<uint32_t>> m_maze;
    uint32_t m_maze_clounmn;
    uint32_t m_maze_row;

};