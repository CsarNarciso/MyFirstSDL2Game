#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
	
	std::cout << "Started" << std::endl;
	
	//Create pointers (variable declaration?)
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;
	
	//Initialize SDL (if SDL init fails, it returns -1, so)
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		
		//Avoid program to close by itself (until user press a key)
		system("pause");
		
		//Then end program
		return 1;
	}
	
	//Create window
	window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	
	//If creating windows failed
	if(!window) {
		
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}
	
	//Get surface from window
	winSurface = SDL_GetWindowSurface(window);
	
	//If it failed
	if(!winSurface) {
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}
	
	//Fill (draw) the window (surface) with a rectangle
	SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));
	
	//Update the window display (kind of re load the now updated surface in the window)
	SDL_UpdateWindowSurface(window);
	
	//Wait (kind of the famous 'game loop' to avoid our game to close automatically)
	system("pause");
	
	//And whenever user press a key (get out manually from game loop):
	
	//Destroy window (and surface)
	SDL_DestroyWindow(window);
	
	//Quit (stop/close/shutdown) SDL
	SDL_Quit();
	window = NULL;
	winSurface = NULL;
	
	//And end program (successfully, without failures)
	return 0;
}