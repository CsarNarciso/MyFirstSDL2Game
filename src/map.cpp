#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <random>

#include "../include/Map.hpp"
#include "../include/RenderWindow.hpp"
#include "../include/Entity.hpp"

#include "../include/Math.hpp"

Map::Map(int p_columns, int p_rows, unsigned seed)
    : columns(p_columns/taleSize)
    , rows(p_rows/taleSize)
    , gen(seed)
    , dist(0, 2)
{};

std::vector< Entity > Map::generate(RenderWindow* window)
{
    // Declare map tales references
    int water = 0;
    int dirt = 1;
    int grass = 2;

    // Load map textures
    SDL_Texture* waterTexture = window->loadTexture("gfx/water.png");
    SDL_Texture* dirtTexture = window->loadTexture("gfx/dirt.png");
    SDL_Texture* grassTexture = window->loadTexture("gfx/grass.png");

    std::vector< Entity > mapTalesEntities;

    for(int row = 0; row < rows; row++)
    {
        std::vector< int > talesRow;
        for(int column = 0; column < columns; column++)
        {
            // Generate random map tale
            int taleReference = generateRandomTaleReference();

            // Save reference
            talesRow.push_back(taleReference);

            // Get as texture
            SDL_Texture* texture = (taleReference == 0) ? waterTexture
                                 : (taleReference == 1) ? dirtTexture
                                                        : grassTexture;
            // Save as entity
            Entity entity(Vector2f(taleSize*(column), taleSize*(row)), texture);
			mapTalesEntities.push_back(entity);
        }
        tales.push_back(talesRow);
    }
    return mapTalesEntities;
}

std::vector< std::vector< int >> Map::getTaleReferences()
{return tales;}

int Map::getTaleSize()
{return taleSize;}