#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <ostream>

#include "Map.hpp"


struct NodeId
{
    int row, column;
    NodeId(): row(), column() {};
    NodeId(int p_row, int p_column) :row(p_row), column(p_column) {};

    // For hashing: to know how to identify a NodeId object from others quickly
    bool operator==(const NodeId& other) const noexcept {
        return row == other.row && column == other.column;
    }
};
struct NodeIdHash {
    std::size_t operator()(const NodeId& id) const noexcept {
        return std::hash<int>()(id.row) ^ (std::hash<int>()(id.column) << 1);
    }
};

struct Node
{
    Node() : id() {};
    Node(int row, int column);
    NodeId getId();
    void setTarget(Node& p_target);
    int getH();
    int h;
    void compute();

    private:
        NodeId id;
        Node* target = nullptr;
};

class PathFinding
{
    std::unordered_map<NodeId, Node, NodeIdHash> closedList;
    std::unordered_map<NodeId, Node, NodeIdHash> openList;
    
    public:
        PathFinding();
        void getNeighbors(int y, int x, Map& map);
        bool isClosed(const NodeId& id) const;
        void generateNeigbor(int row, int column, std::unordered_map<NodeId, Node, NodeIdHash>& neighbors, Map& map);
};