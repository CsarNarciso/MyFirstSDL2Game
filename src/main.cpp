#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

#include "../include/Entity.hpp"
#include "../include/Player.hpp"
#include <../include/RenderWindow.hpp>
#include "../include/Math.hpp"
#include "../include/Map.hpp"


// MOVE ALL THIS CODE TO player or map classes!
bool positionExists(int row, int column, std::vector<std::vector<int>>& map)
{
	return row >= 0 && row < map.size() && 
			column >= 0 && column < map[row].size();
}

bool isWater(int row, int column, std::vector<std::vector<int>>& map)
{
	return map[row][column] == 0;
}

bool canMove(int row, int column, std::vector<std::vector<int>>& map)
{
	return positionExists(row, column, map) && !isWater(row, column, map);
}

enum class Direction { UP, LEFT, DOWN, RIGHT };


void tryMove(Direction dir, Player& player, Map& map, std::vector<std::vector<int>>& mapTileReferences)
{
	Vector2f pos = player.getPos();
	SDL_Rect frame = player.getCurrentFrame();
	
	int speed = player.getPlayerMovementPx();
	int tileSize = map.getTaleSize();

	int edgePos, nextEdgePos, tile, tileLimit, nextTile, pxToMove;
	bool willCollide = false;

	bool incrementPos = (dir == Direction::DOWN || dir == Direction::RIGHT);
	int d = incrementPos ? 1 : -1;

	if (dir == Direction::DOWN || dir == Direction::UP)
	{
		edgePos = pos.y + (incrementPos ? frame.h : 0);
		tile = (edgePos-(1*d))/tileSize;
		tileLimit = (tile * tileSize) + (incrementPos ? tileSize : 0);
		nextEdgePos = edgePos + (speed * d);
		nextTile = nextEdgePos >= 0 ? (nextEdgePos-(1*d))/tileSize : -1;

		willCollide = (incrementPos ? (nextTile > tile) : (nextTile < tile)) && !canMove(nextTile, pos.x/tileSize, mapTileReferences);
		
		pxToMove = willCollide ? tileLimit - edgePos : speed*d;

		if(pxToMove != 0)
			player.setPos(pos.x, pos.y + pxToMove);
	}
	else
	{
		edgePos = pos.x + (incrementPos ? frame.h : 0);
		tile = (edgePos-(1*d))/tileSize;
		tileLimit = (tile * tileSize) + (incrementPos ? tileSize : 0);
		nextEdgePos = edgePos + (speed * d);
		nextTile = nextEdgePos >= 0 ? (nextEdgePos-(1*d))/tileSize : -1;

		willCollide = (incrementPos ? (nextTile > tile) : (nextTile < tile)) && !canMove(pos.y/tileSize, nextTile, mapTileReferences);

		pxToMove = willCollide ? tileLimit - edgePos : speed*d;

		if(pxToMove != 0)
			player.setPos(pos.x + pxToMove, pos.y);
	}
}

int main(int argc, char** args) {
	
	//Initialize SDL attributes (on fialures, it always returns -1, so)

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		std::cout << "Error initializing SDL video: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ( SDL_Init(IMG_INIT_PNG) < 0 ) {
		std::cout << "Error initializing SDL png: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	//Init window and renderer
	int window_width = 640;
	int window_height = 480;
	RenderWindow window("title", window_width, window_height);

	// Generate random map
	Map map(window_width, window_height);	
	std::vector<Entity> mapTaleEntities = map.generate(&window);
	std::vector< std::vector< int >> mapTaleReferences = map.getTaleReferences();

	// Declare Player
	Player player(&window);
	const std::map<SDL_Keycode, std::pair<int, int>>& directions = player.getDirections();
	std::map<SDL_Keycode, std::pair<int, int>>::const_iterator it;


	//game loop
	bool gameRunning = true;

	SDL_Event event;
	
	while(gameRunning)
	{
		//Process events
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				// Exit game
				case SDL_QUIT:
					gameRunning = false;
					break;

				// Player movement
				case SDL_KEYDOWN:
					
					switch (event.key.keysym.sym)
					{
						case SDLK_UP: tryMove(Direction::UP, player, map, mapTaleReferences); break;
						case SDLK_LEFT: tryMove(Direction::LEFT, player, map, mapTaleReferences); break;
						case SDLK_DOWN: tryMove(Direction::DOWN, player, map, mapTaleReferences); break;
						case SDLK_RIGHT: tryMove(Direction::RIGHT, player, map, mapTaleReferences); break;
					}
					break;
			}
		}

		// Clear
		window.clear();
			
		// Render each map tale
		for(int i = 0; i < mapTaleEntities.size(); i++)
		{
			window.render(mapTaleEntities[i]);
		}
		// Render player
		window.render(player);

		// Draw
		window.display();
	}
	
	//destroy window and shutdown SDL
	window.cleanUp();
	SDL_Quit();

	//Get out program successfully
	return 0;
}