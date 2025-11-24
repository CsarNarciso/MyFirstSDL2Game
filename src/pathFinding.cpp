#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <unordered_map>

#include "../include/Map.hpp"

#include "../include/PathFinding.hpp"

PathFinding::PathFinding() 
{}

bool PathFinding::isClosed(const NodeId& id) const
{
    return closedMap.find(id) != closedMap.end();
}

void PathFinding::generateNeigbor(int row, int column, std::unordered_map<NodeId, Node, NodeIdHash> neighbors, Map* map)
{
    // Create node
    // Check if valid neighbor
    // Add to rest of neighbors
    Node node = Node(row, column);
    if (map->canMove(row, column) && !isClosed(node.getId())) neighbors[node.getId()] = node;
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
    generateNeigbor(row - 1, column, neighbors, map);

    // down
    generateNeigbor(row + 1, column, neighbors, map);

    // right
    generateNeigbor(row, column + 1, neighbors, map);

    // left
    generateNeigbor(row, column - 1, neighbors, map);
}

Node::Node(int row, int column)
{
    id = NodeId(row, column);
}