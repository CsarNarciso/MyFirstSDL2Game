#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>

#include "Map.hpp"

class PathFinding
{
    public:
        PathFinding();
        void compute();
        void getNeighbors(Node node, Map* map);
        int computeF();
        std::vector<Node> getOpenList();
        bool isClosed(const NodeId& id) const;
    private:
        std::vector<Node> openList;
        std::unordered_map<NodeId, Node, NodeIdHash> closedMap;
};


class Node
{
    public:
        Node(int row, int column){};
        NodeId getId();
        NodeId getParentId();
        int getG();
        int getH();
        int getF();

    private:
        NodeId id, parentId;
        int g, h, f;
};

struct NodeId
{
    NodeId(int p_column, int p_row)
    :column(p_column), row(p_row)
    {}
    int column, row;
    bool operator==(const NodeId& other) const noexcept {
        return row == other.row && column == other.column;
    }
};

struct NodeIdHash {
    std::size_t operator()(const NodeId& id) const noexcept {
        return std::hash<int>()(id.row) ^ (std::hash<int>()(id.column) << 1);
    }
};