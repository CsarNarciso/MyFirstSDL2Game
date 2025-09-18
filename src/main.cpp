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
	int currentPlayer_x;
	int currentPlayer_y;
	int currentPlayer_taleRow;
	int currentPlayer_taleColumn;
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
			// Get player pos
			currentPlayer_y = player.getPos().y;
			currentPlayer_x = player.getPos().x;
			currentPlayer_taleRow = currentPlayer_y/map.getTaleSize();
			currentPlayer_taleColumn = currentPlayer_x/map.getTaleSize();
			it = directions.find(event.key.keysym.sym);

			switch (event.type)
			{
				// Exit game
				case SDL_QUIT:
					gameRunning = false;
					break;

				// Player movement
				case SDL_KEYDOWN:
					
					if(it != directions.end())
					{
						int dy = it->second.first;
						int dx = it->second.second;

						if(canMove(currentPlayer_taleRow+dy, currentPlayer_taleColumn+dx, mapTaleReferences))
							player.setPos(
								currentPlayer_x + (player.getPlayerMovementPx() * dx), 
								currentPlayer_y + (player.getPlayerMovementPx() * dy));
					}
					break;
					
				default:
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