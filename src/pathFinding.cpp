#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "../include/Map.hpp"

#include "../include/PathFinding.hpp"

PathFinding::PathFinding() 
{}

// Get neighbors

// Check for updates if they are in open list already, if not in open list yet, compute them
// Then add to open list

// Pick the one with lowest f
// Move it from open to closed list

void PathFinding::getNeighbors(Node node, Map* map)
{
    int row = node.getId().row;
    int column = node.getId().column;

    std::vector<Node> neighbors;

    // top
    if (map->canMove(row - 1, column)) neighbors.push_back(Node(row - 1, column));
    
    // down
    if (map->canMove(row + 1, column)) neighbors.push_back(Node(row + 1, column));

    // right
    if (map->canMove(row, column + 1)) neighbors.push_back(Node(row, column + 1));

    // left
    if (map->canMove(row, column - 1)) neighbors.push_back(Node(row, column - 1));

    // Filter neighbors already in closed list
    for (auto neighbor : neighbors)
    {
        // THis is just not working because it needs pointers, no the object directly?
        // How to do this task gaining the most performance possiblem?
        if (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end())
        {
            closedList.erase();
        }
    }
}

Node::Node(int row, int column)
{
    id = NodeId(row, column);
}