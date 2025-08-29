#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include <../include/RenderWindow.hpp>
#include "../include/Math.hpp"


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

	//game loop
	bool gameRunning = true;

	SDL_Event event;

	while(gameRunning)
	{
		//Process events
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) gameRunning = false;

			window.clear();
			
			// Create Loop to load all entities (textures) in window
			for(int i = 1; i < 10; i++) {
				// On each lap create new entity texture
				SDL_Texture* grassTexture = window.loadTexture("gfx/ground_grass_1.png");
				
				// And place entity in diferent window position
				Entity entity(Vector2f(i*32, i*32), grassTexture);
				
				// And render
				window.render(entity);
			}
			
			window.display();
		}
	}
	
	//destroy window and shutdown SDL
	window.cleanUp();
	SDL_Quit();

	//Get out program successfully
	return 0;
}