#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/Entity.hpp"
#include <../include/RenderWindow.hpp>
#include "../include/Math.hpp"
#include "../include/Map.hpp"


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
	RenderWindow window("title", 640, 480);

	// Generate random map
	Map map(4,4);	
	std::vector<Entity> generatedMapTales = map.generate(&window);

	// Declare Player
	SDL_Texture* playerTexture = window.loadTexture("gfx/player.png");
	Entity player(Vector2f(32, 32), playerTexture);

	//game loop
	bool gameRunning = true;

	SDL_Event event;

	while(gameRunning)
	{
		//Process events
		while(SDL_PollEvent(&event))
		{
			// Get player pos
			int currentPlayer_x = player.getPos().x;
			int currentPlayer_y = player.getPos().y;

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
						case SDLK_UP:
							player.setPos(currentPlayer_x, currentPlayer_y - 5);
							break;
						case SDLK_LEFT:
							player.setPos(currentPlayer_x - 5, currentPlayer_y);
							break;
						case SDLK_DOWN:
							player.setPos(currentPlayer_x, currentPlayer_y + 5);
							break;
						case SDLK_RIGHT:
							player.setPos(currentPlayer_x + 5, currentPlayer_y);
							break;
						default:
							break;
					}
					break;

				default:
					break;
			}
		}

		// Clear
		window.clear();
			
		// Render each map tale
		for(int i = 0; i < generatedMapTales.size(); i++)
		{
			window.render(generatedMapTales[i]);
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