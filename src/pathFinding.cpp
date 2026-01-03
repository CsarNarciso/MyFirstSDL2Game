#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <unordered_map>

#include "../include/Map.hpp"

#include "../include/PathFinding.hpp"

PathFinding::PathFinding() {}

bool PathFinding::isClosed(const NodeId& id) const
{
    return closedList.find(id) != closedList.end();
}

std::vector<Node> PathFinding::getPath(int y, int x, int target_y, int target_x, Map& map)
{
    // Reset lists (?)
    openList.clear();
    closedList.clear();

    Node target = Node(target_y / map.getTileSize(), target_x / map.getTileSize(), NO_PARENT);
    
    // Start by starting point node
    Node currentPosNode = Node(y / map.getTileSize(), x / map.getTileSize(), NO_PARENT);
    currentPosNode.g = 0;
    currentPosNode.h = computeH(currentPosNode.getId(), target.getId());
    closedList[currentPosNode.getId()] = currentPosNode;

    // Start loop till find final path to target
    while (!(currentPosNode.getId() == target.getId()))
    {
        // Get current pos node neighbors
        getNeighbors(&currentPosNode, &target, map);

        if (openList.empty()) { // no path 
            break; }

        // Pick lowest cost one
        currentPosNode = openList.begin()->second;
        for (std::pair<NodeId, Node> pair : openList)
        {
            if (pair.second.getF() < currentPosNode.getF()){ currentPosNode = pair.second; }
        }
        // Move it from open to closed list
        openList.erase(currentPosNode.getId());
        closedList[currentPosNode.getId()] = currentPosNode;

        std::cout << "||||||||||||" << currentPosNode.getF() << "|||||||||||||" << std::endl;
        for (std::pair<NodeId, Node> pair : openList)
		{
			std::cout << "Row: " << pair.second.getId().row << " | Column: " << pair.second.getId().column << " (F) = " << pair.second.getF() << " --PARENT--> " << pair.second.getParentId().row << " | Column: " << pair.second.getParentId().column << std::endl; 
		}
    }
    
    // Return closed list as path (fit better this to return exact path instead unnecesary nodes)
    std::vector<Node> ordered_path;
    // Node cn = closedList.begin()->second;
    // // Start loop till find final path to target
    // while (!(cn.getId() == target.getId()))
    // {
    //     for (std::pair<NodeId, Node> pair: closedList)
    //     {
    //         if (pair.second.getParent().getId() == ordered_path.end()->getId())
    //         {
    //             cn = pair.second;
    //             ordered_path.push_back(pair.second);
    //         }
    //     }
    // }
    return ordered_path;
}



void PathFinding::getNeighbors(Node* parent, Node* target, Map& map)
{
    // For each possible neighbor side (laterals and diagonals)
    for (std::pair<int, int> pair: neighborSides)
    {
        // side
        NodeId id = NodeId(parent->getId().row + pair.first, parent->getId().column + pair.second);

        // First check if valid neighbor before add to neighbors
        if (map.canMove(id.row, id.column) && !isClosed(id))
        {
            // But first, if not in open list
            if (openList.find(id) == openList.end())
            {
                // then generate it
                Node node = Node(id.row, id.column, parent->getId());

                // compute
                node.h = computeH(node.getId(), target->getId());
                node.g = computeG(node.getId(), *parent);

                // and add to open list
                openList[id] = node;
            }
            else
            {
                // If they in open list, 
                Node node = openList[id];

                // check for updates (lower g)
                if (computeG(node.getId(), *parent) < node.getG())
                {    
                    // re-compute
                    node.parentId = parent->getId();
                    node.h = computeH(node.getId(), target->getId());
                    node.g = computeG(node.getId(), *parent);

                    // Then re-add (replace) on open list
                    openList[id] = node;
                }
            }
        }
    }
}

int PathFinding::computeH(NodeId nodeId, NodeId targetId)
{
    int row = nodeId.row;
    int column = nodeId.column;

    int t_row = targetId.row;
    int t_column = targetId.column;
    
    // Manhattan distance (h)
    return std::abs(row - t_row) + std::abs(column - t_column);
}


int PathFinding::computeG(NodeId nodeId, const Node& parent)
{
    int row = nodeId.row;
    int column = nodeId.column;
    
    // Is lateral or diagonal neighbor?
    return parent.getG() + ((row == parent.getId().row || column == parent.getId().column) ? 10 : 14);
}



Node::Node(int row, int column, NodeId p_parentId) : id(row, column), parentId(p_parentId), h(0), g(0), f(0) {}

NodeId::NodeId() : row(), column() {};

NodeId::NodeId(int p_row, int p_column) :row(p_row), column(p_column) {};

NodeId Node::getId() const { return id; }

int Node::getH(){ return h; }

int Node::getG() const { return g; }

int Node::getF(){ return h + g;; }

NodeId Node::getParentId(){ return parentId; }