#include <SDL.h>
#include <iostream>

//Create pointers (variable declaration?)
SDL_Window* window;
SDL_Surface* winSurface;
SDL_Surface* image1;
SDL_Surface* image2;

//Declare methods (?)
bool init();
void kill();
bool load();


int main(int argc, char* argv[]) {
	
	//Error on initliazing
	if(!init()) {
		
		//Avoid program to close by itself (until user press a key)
		system("pause");
		
		//Then end program
		return 1;
	}
	
	//Error while loading images (sprites?)
	if( !load() ) return 1;
	
	// Blit image to entire window
	SDL_BlitSurface( image1, NULL, winSurface, NULL );

	// Blit image to scaled portion of window
	SDL_Rect dest;
	dest.x = 160;
	dest.y = 120;
	dest.w = 320;
	dest.h = 240;
	SDL_BlitScaled( image2, NULL, winSurface, &dest );
	
	//Fill (draw) a rectangle in the window (surface)
	//SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));
	
	//Update the window display (kind of re load the now updated surface in the window)
	SDL_UpdateWindowSurface(window);
	
	//Wait (kind of the famous 'game loop' to avoid our game to close automatically)
	system("pause");
	
	//And whenever user press a key (get out manually from game loop):
	kill();
	
	//And end program (successfully, without failures)
	return 0;
}



bool init() {
		
	//Initialize SDL (if SDL init fails, it returns -1, so)
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	
	//Create window
	window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	
	//If creating windows failed
	if(!window) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return false;
	}
	
	//Get surface from window
	winSurface = SDL_GetWindowSurface(window);
	
	//If it failed
	if(!winSurface) {
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		return false;
	}
	
	//Successfull initializaiton!
	return true;
}



bool load() {
	
	//Temporary surfaces to load images into
	SDL_Surface *temp1, *temp2;
	
	//Load images into these surfaces
	temp1 = SDL_LoadBMP("src/media/test1.bmp");
	temp2 = SDL_LoadBMP("src/media/test2.bmp");
	
	//If failed
	if(!temp1 || !temp2) {
		std::cout << "Error loading image: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}
	
	//Format surfaces (?)
	//Bmp files (kind of image, sprite) is loaded into a temporary surface, this temp surface is formated/converted as 
	//part of the main win surface (a sprite in to it), and the result is allocated into the main image surface
	image1 = SDL_ConvertSurface(temp1, winSurface->format, 0);
	image2 = SDL_ConvertSurface(temp2, winSurface->format, 0);
	
	//Free (clean/get rid of) temporary surfaces (they were needed just for the formatting (?))
	SDL_FreeSurface(temp1);
	SDL_FreeSurface(temp2);
	
	//If format failed
	if(!image1 || !image2) {
		std::cout << "Error converting surface: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}
	
	return true;
}



void kill() {
	
	//Destroy window (and surface)
	SDL_DestroyWindow(window);
	window = NULL;
	winSurface = NULL;
	
	//Quit (stop/close/shutdown) SDL
	SDL_Quit();
}