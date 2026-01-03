#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <ostream>

#include "Map.hpp"


struct NodeId
{
    int row, column;
    NodeId();
    NodeId(int row, int column);

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

const NodeId NO_PARENT = {-1, -1};

struct Node
{
    Node() : id() {};
    Node(int row, int column, NodeId parentId);
    NodeId getId() const;
    NodeId getParentId();
    int getH();
    int getG() const;
    int getF();
    int h;
    int g;
    int f;
    NodeId parentId;

    private:
        NodeId id;
};

class PathFinding
{
    std::unordered_map<NodeId, Node, NodeIdHash> closedList;
    std::unordered_map<NodeId, Node, NodeIdHash> openList;
    std::vector<std::pair<int,int>> neighborSides = { 
        {-1, 0}, // up 
        {-1, -1}, // up-left 
        {0, -1}, // left 
        {1, -1}, // down-left 
        {1, 0}, // down 
        {1, 1}, // down-right 
        {0, 1}, // right 
        {-1, 1} // up-right 
    };
    
    public:
        PathFinding();
        std::vector<Node> getPath(int y, int x, int target_y, int target_x, Map& map);
        void getNeighbors(Node* parent, Node* target, Map& map);
        bool isClosed(const NodeId& id) const;
        int computeH(NodeId nodeId, NodeId targetId);
        int computeG(NodeId nodeId, const Node& parent);
};