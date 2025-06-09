#include <SDL.h>
#include <iostream>

//Create pointers (variable declaration?)
SDL_Window* window;
SDL_Surface* winSurface;
SDL_Surface* image1;
SDL_Surface* image2;

//Declare methods (?)
bool init();
bool load();
bool loop();
void kill();


int main(int argc, char** args) {
	
	//Error on initliazing
	if( !init() ) return 1;
	
	//Error while loading images (sprites?)
	if( !load() ) return 1;
	
	while( loop() ) {
		//Wait before processing next frame (kind of thread sleep to avoid overwhelming CPU?)
		SDL_Delay(10);
	}
	
	kill();
	return 0;
}



bool init() {
		
	//Initialize SDL (if SDL init fails, it returns -1, so)
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	
	//Create window
	window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	
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
	//but the images/sprites/surfaces are still not loaded into the main surface, they were just "created", "loaded" by the
	//bytes of the bmp files, to actually place them in the main surface we need to "Blit" them in to
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


bool loop() {
	
	SDL_Event e;
	
	// Blit image 1 to entire window
	SDL_BlitSurface( image1, NULL, winSurface, NULL );
	
	//Process events (queued ones): if there is at least one
	
	static bool renderImage2; //static to persist value in this function and not reset to null
	//because it resets to null on every frame and in theory, it will become true after the conditions below if we
	//hold a key, for example, however, SDL does not queue events (holding a key will throw as many events as we persist)
	//as fast as the frame rate of our computer/program/code, this means, some events are not queued, that means
	//sometimes it does not enter the loop (due to no queued events) and become true even if we are holding a key	
	while(SDL_PollEvent(&e) != 0) {
		
		switch(e.type) {
			
			case SDL_QUIT:
					return false;
			case SDL_KEYDOWN:
					renderImage2 = true;
					break;
			case SDL_KEYUP:
					renderImage2 = false;
					break;
		}
	}
	
	if(renderImage2) {
		
		SDL_Rect dest; //dimentions?
		dest.x = 160;
		dest.y = 120;
		dest.w = 320;
		dest.h = 240;
		
		//Blit image 2 scaled (using prev dimentions and positions)
		SDL_BlitScaled(image2, NULL, winSurface, &dest);
	}
	
	//Refresh window
	SDL_UpdateWindowSurface(window);
	
	return true; //and continue game loop
}


void kill() {
	
	//Destroy window (and surface)
	SDL_DestroyWindow(window);
	window = NULL;
	winSurface = NULL;
	
	//Quit (stop/close/shutdown) SDL
	SDL_Quit();
}