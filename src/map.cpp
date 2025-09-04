#include <SDL2/SDL.h>
#include <iostream>
#include <random>

#include "../include/Map.hpp"
#include "../include/RenderWindow.hpp"
#include "../include/Entity.hpp"

#include "../include/Math.hpp"

Map::Map(int rows, int columns, unsigned seed)
    : rows(rows)
    , columns(columns)
    , gen(seed)
    , dist(0, 2)

{};

void Map::generate(RenderWindow* window)
{
    // Declare map tales references
    int water = 0;
    int dirt = 1;
    int grass = 2;

    // Load map textures
    SDL_Texture* waterTexture = window->loadTexture("gfx/water.png");
    SDL_Texture* dirtTexture = window->loadTexture("gfx/dirt.png");
    SDL_Texture* grassTexture = window->loadTexture("gfx/grass.png");

    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            // Generate random map tale
            int taleReference = generateRandomTaleReference();
            SDL_Texture* texture = (taleReference == 0) ? waterTexture
                                 : (taleReference == 1) ? dirtTexture
                                                        : grassTexture;
            // Draw texture
            Entity entity(Vector2f(32*(column+1), 32*(row+1)), texture);
            window->render(entity);
        }
    }

}