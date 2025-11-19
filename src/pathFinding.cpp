#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <unordered_map>

#include "../include/Map.hpp"

#include "../include/PathFinding.hpp"

PathFinding::PathFinding() 
{}

bool isClosed(const NodeId& id) const
{
    return closedMap.find(id) != closedMap.end();
}

// Get neighbors

// Check for updates if they are in open list already, if not in open list yet, compute them
// Then add to open list

// Pick the one with lowest f
// Move it from open to closed list

void PathFinding::getNeighbors(Node node, Map* map)
{
    int row = node.getId().row;
    int column = node.getId().column;

    std::unordered_map<NodeId, Node, NodeIdHash> neighbors;

    // top
    if (map->canMove(row - 1, column)) neighbors.insert(NodeId(row - 1, column), Node(row - 1, column));
    
    // down
    if (map->canMove(row + 1, column)) neighbors.push_back(Node(row + 1, column));

    // right
    if (map->canMove(row, column + 1)) neighbors.push_back(Node(row, column + 1));

    // left
    if (map->canMove(row, column - 1)) neighbors.push_back(Node(row, column - 1));

    // Filter neighbors already in closed list
    for (auto neighbor : neighbors)
    {
        if (isClosed(neighbor.id))
        {
            neighbors.erase();
        }
    }
}

Node::Node(int row, int column)
{
    id = NodeId(row, column);
}