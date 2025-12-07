#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <ostream>

#include "Map.hpp"


struct NodeId
{
    int column, row;
    NodeId(): column(), row() {};
    NodeId(int p_column, int p_row) :column(p_column), row(p_row) {};

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
    
    private:
        NodeId id;
};

class PathFinding
{
    std::unordered_map<NodeId, Node, NodeIdHash> closedMap;
    
    public:
        PathFinding();
        void getNeighbors(Node node, Map map);
        bool isClosed(const NodeId& id) const;
        void generateNeigbor(int row, int column, std::unordered_map<NodeId, Node, NodeIdHash>& neighbors, Map map);
};