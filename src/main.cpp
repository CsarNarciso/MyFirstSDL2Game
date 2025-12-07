#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/entity/Entity.hpp"
#include "../include/entity/Player.hpp"
#include "../include/entity/Enemy.hpp"
#include <../include/RenderWindow.hpp>
#include "../include/Math.hpp"
#include "../include/Direction.hpp"
#include "../include/Map.hpp"
#include "../include/Input.hpp"
#include "../include/PathFinding.hpp"


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
	std::vector<Entity> mapTileEntities = map.generate(&window);

	// Declare Player
	Player player(&window);
	InputState input;

	// Declare test enemy
	Enemy enemy(&window);

	// PathFinding (test)
	PathFinding pathFinding;

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

				// Detect gameplay pressed keys
				case SDL_KEYDOWN:
					
					switch (event.key.keysym.sym)
					{
						case SDLK_UP: input.up = true; break;
						case SDLK_DOWN: input.down = true; break;
						case SDLK_LEFT: input.left = true; break;
						case SDLK_RIGHT: input.right = true; break;

						case SDLK_LSHIFT: input.running = true; break;
					}
					break;
					case SDL_KEYUP:
					
					switch (event.key.keysym.sym)
					{
						case SDLK_UP: input.up = false; break;
						case SDLK_DOWN: input.down = false; break;
						case SDLK_LEFT: input.left = false; break;
						case SDLK_RIGHT: input.right = false; break;

						case SDLK_LSHIFT: input.running = false; break;
					}
					break;
			}
		}
		// Path finding. Neighbors.
		pathFinding.getNeighbors(Node(player.getPos().y, player.getPos().x), map);

		// Player movement
		player.handlePlayerMovement(map, input);
		
		// Handle enemy updates
		enemy.facePlayer(player.getPos());
		enemy.move(Direction::UP, map);

		// Clear
		window.clear();
			
		// Render each map tale
		for(int i = 0; i < mapTileEntities.size(); i++)
		{
			window.render(mapTileEntities[i]);
		}
		// Render player
		window.render(player);

		// Render enemy
		window.render(enemy);

		// Draw
		window.display();
	}
	
	//destroy window and shutdown SDL
	window.cleanUp();
	SDL_Quit();

	//Get out program successfully
	return 0;
}