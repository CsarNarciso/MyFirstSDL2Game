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
    return closedList.find(id) != closedList.end();
}

void PathFinding::generateNeigbor(int row, int column, std::unordered_map<NodeId, Node, NodeIdHash>& neighbors, Map& map)
{
    // Create node
    // Check if valid neighbor
    // Add to rest of neighbors
    Node node = Node(row, column);
    if (map.canMove(row, column) && !isClosed(node.getId())) neighbors[node.getId()] = node;
}

// Get neighbors (no in closed list)

// Check for updates if they are in open list already, if not in open list yet, compute them
// Then add to open list

// Pick the one with lowest f
// Move it from open to closed list

void PathFinding::getNeighbors(int y, int x, Map& map)
{
    int row = y / map.getTileSize();
    int column = x / map.getTileSize();
    Node playerNode = Node(row, column); // target for enemy nodes

    std::unordered_map<NodeId, Node, NodeIdHash> neighbors;

    // top
    generateNeigbor(row - 1, column, neighbors, map);

    // top-left
    generateNeigbor(row - 1, column - 1, neighbors, map);

    // left
    generateNeigbor(row, column - 1, neighbors, map);
    
    // left-down
    generateNeigbor(row + 1, column - 1, neighbors, map);

    // down
    generateNeigbor(row + 1, column, neighbors, map);

    // down-right
    generateNeigbor(row + 1, column + 1, neighbors, map);

    // right
    generateNeigbor(row, column + 1, neighbors, map);

    // right-top
    generateNeigbor(row - 1, column + 1, neighbors, map);

    std::cout << "Current node -> " << "Row: " << row << " Column: " << column << std::endl;
    std::cout << "Neighbors: " << std::endl;

    for(const auto& pair: neighbors)
    {
        NodeId nodeId = pair.first;
        Node node = pair.second;

        // Test: set target
        node.setTarget(playerNode);

        // Add each generated neighbor to open list
        if(openList.find(nodeId) != openList.end())
        {
            // (only if they not already in open list)

            // then, first compute,
            node.compute();

            // then add
            openList[nodeId] = node;
        }
        else
        {
            // if already in open list, re-compute
            node.compute();
            // and replace
            openList[nodeId] = node;
        }
        std::cout << "Row: " << pair.first.row << " Column: " << pair.first.column << std::endl;
        std::cout << "H: " << pair.second.h << std::endl;
    }
}

Node::Node(int row, int column)
{
    id = NodeId(row, column);
}

NodeId Node::getId()
{
    return id;
}

void Node::setTarget(Node& p_target)
{
    target = &p_target;
}

int Node::getH()
{
    return h;
}

void Node::compute()
{
    int row = id.row;
    int column = id.column;

    int t_row = target->id.row;
    int t_column = target->id.column;
    
    // compute h (manhatan distance)
    h = 0;

    // Row
    // no same row?
    if (row != t_row)
    {
        // compute row

        // higher?
        if(row > t_row)
        {
            h = row - (t_row + 1);
        }
        else
        {
            // lower?
            h = t_row - (row + 1);
        }
    }
    // Column
    // no same column?
    if (column != t_column)
    {
        // compute column

        // higher?
        if(column > t_column)
        {
            h = column - (t_column + 1);
        }
        else
        {
            // lower?
            h = t_column - (column + 1);
        }
    }
    //g and f (?)
}