#include <SDL.h>

int main(int argc, char* argv[]) {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// Handle initialization error
		SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"My First SDL Window", // Title
		SDL_WINDOWPOS_UNDEFINED, // X position
		SDL_WINDOWPOS_UNDEFINED, // Y position
		640, // Width
		480, // Height
		SDL_WINDOW_SHOWN // Flags
	);

	if (window == nullptr) {
		// Handle window creation error
		SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}
}