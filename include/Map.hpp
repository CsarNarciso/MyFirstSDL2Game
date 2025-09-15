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
    std::vector< Entity > generate(RenderWindow* window);
    Map(int columns, int rows, unsigned seed = std::random_device{}());
    private:
        int columns;
        int rows;
        
        int generateRandomTaleReference() { return dist(gen); }
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
};