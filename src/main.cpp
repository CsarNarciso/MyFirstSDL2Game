#include <SDL.h>
#include <iostream>

#include <render.hpp>


int main(int argc, char** args) {
	
	//Initialize SDL attributes (on fialures, it always returns -1, so)

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		std::cout << "Error initializing SDL video: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ( SDL_Init(SDL_INIT_PNG) < 0 ) {
		std::cout << "Error initializing SDL png: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	//Init window and renderer
	RenderWindow window("title", 640, 480);

	//Create a texture
	SDL_Texture grassTexture = window.loadTexture("media/ground_grass_1.png");

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
			window.render(grassTexture);
			window.display();
		}
	}
	
	//destroy window and shutdown SDL
	window.cleanUp();
	SDL_Quit();

	//Get out program successfully
	return 0;
}