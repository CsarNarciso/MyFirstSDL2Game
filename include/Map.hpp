#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <random>

#include "./RenderWindow.hpp"
#include "./Entity.hpp"

class Map
{
    public:
        Map(int rows, int columns, unsigned seed = std::random_device{}());
        std::vector< Entity > generate(RenderWindow* window);
    private:
        int rows;
        int columns;
        
        int generateRandomTaleReference() { return dist(gen); }
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
};