#include "RenderWindow.hpp"

class Render
{
    RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
        :window(NULL), renderer(NULL) 
    {
       //Init window and renderer
       window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

        //If creating window failed
	    if(!window) {
		    std::cout << "Error creating window: " << SDL_GetError() << std::endl;
	    }

       //-1 means: use the device graphic card if possible, if not, then the GPU
       renderer = SDL_CreateWindow(window, -1, SDL_RENDERER_ACCELERATED);

       //If creating renderer failed
	    if(!renderer) {
		    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
	    }
    }

    void render(SDL_Texture* texture)
    {
        //Clear screen
        SDL_RenderClear(render);

        //Render texture to screen
        SDL_RenderCopy(render, texture, NULL, NULL);
        
        //Update screen
        SDL_RenderPresent(render);    
    }
}
