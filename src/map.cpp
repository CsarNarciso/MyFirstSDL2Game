#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <random>

#include "../include/Map.hpp"
#include "../include/RenderWindow.hpp"
#include "../include/entity/Entity.hpp"

#include "../include/Math.hpp"

Map::Map(int p_columns, int p_rows, unsigned seed)
    : columns(p_columns/tileSize)
    , rows(p_rows/tileSize)
    , gen(seed)
    , dist(0, 2)
{};

std::vector< Entity > Map::generate(RenderWindow* window)
{
    // Declare map tiles references
    int water = 0;
    int dirt = 1;
    int grass = 2;

    // Load map textures
    SDL_Texture* waterTexture = window->loadTexture("gfx/water.png");
    SDL_Texture* dirtTexture = window->loadTexture("gfx/dirt.png");
    SDL_Texture* grassTexture = window->loadTexture("gfx/grass.png");

    std::vector< Entity > mapTileEntities;

    for(int row = 0; row < rows; row++)
    {
        std::vector< int > tilesRow;
        for(int column = 0; column < columns; column++)
        {
            // Generate random map Tile
            int tileReference = generateRandomTileReference();

            // Save reference
            tilesRow.push_back(tileReference);

            // Get as texture
            SDL_Texture* texture = (tileReference == 0) ? waterTexture
                                 : (tileReference == 1) ? dirtTexture
                                                        : grassTexture;
            // Save as entity
            Entity entity(Vector2f(tileSize*(column), tileSize*(row)), texture);
			mapTileEntities.push_back(entity);
        }
        tileReferences.push_back(tilesRow);
    }
    return mapTileEntities;
}

std::vector< std::vector< int >> Map::getTileReferences()
{return tileReferences;}

int Map::getTileSize()
{return tileSize;}


bool Map::positionExists(int row, int column)
{
	return row >= 0 && row < tileReferences.size() && 
			column >= 0 && column < tileReferences[row].size();
}

bool Map::isWater(int row, int column)
{
	return tileReferences[row][column] == 0;
}

bool Map::canMove(int row, int column)
{
	return positionExists(row, column) && !isWater(row, column);
}