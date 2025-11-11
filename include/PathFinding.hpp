#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Map.hpp"

class PathFinding
{
    public:
        PathFinding();
        void compute();
        void getNeighbors(Node node, Map* map);
        int computeF();
        std::vector<Node> getOpenList();
        std::vector<Node> getClosedList();
    private:
        std::vector<Node> openList;
        std::vector<Node> closedList;
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
};