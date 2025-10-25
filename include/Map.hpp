#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <random>

#include "./RenderWindow.hpp"
#include "./entity/Entity.hpp"

class Map
{
    public:
        std::vector< Entity > generate(RenderWindow* window);
        Map(int columns, int rows, unsigned seed = std::random_device{}());
        std::vector<std::vector< int >> getTileReferences();
        int getTileSize();
		
		bool positionExists(int row, int column);
		bool isWater(int row, int column);
		bool canMove(int row, int column);
		
    private:
		int tileSize = 32;
        int columns;
        int rows;
        std::vector<std::vector< int >> tileReferences;
        
        int generateRandomTileReference() { return dist(gen); }
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
};