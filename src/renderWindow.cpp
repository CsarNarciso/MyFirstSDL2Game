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

    SDL_Texture* loadTexture(const char* p_filePath)
    {
        SDL_Texture* texture = NULL;
        texture = IMG_LoadTexture(renderer, p_filePath);

        if(texture == NULL)
            std::cout << "Error loading texture: " << SDL_GetError() << std::endl;

        return texture;
    }

    void clear()
    {
        SDL_RenderClear(renderer);
    }

    void render(SDL_Texture* p_text)
    {
        SDL_RenderCopy(renderer, p_text, NULL, NULL);
    }

    void display()
    {
        SDL_Present(renderer);
    }

    void RenderWindow::cleanUp()
    {
        SDL_DestroyWindow(window);
    }
}
