#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/Map.hpp"

#include "../include/PathFinding.hpp"

PathFinding::PathFinding() 
{}

void PathFinding::getNeighbors(Node node, Map* map)
{
    int row = node.getId().row;
    int column = node.getId().column;

    Node[] neighbors = {};

    // top
    if (map->canMove(row - 1, column)) neigbors.pushBack(Node(row - 1, column));
    
    // down
    if (map->canMove(row + 1, column)) neigbors.pushBack(Node(row + 1, column));

    // right
    if (map->canMove(row, column + 1)) neigbors.pushBack(Node(row, column + 1));

    // left
    if (map->canMove(row, column - 1)) neigbors.pushBack(Node(row, column - 1));
}

Node::Node(int row, int column)
{
    id = NodeId(row, column);
}