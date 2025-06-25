#pragma once
#include <SDL2/SDL.h>

class Entity
{
	public:
	
		Entity(float p_x, float p_y, SDL_Texture* p_tex, SDL_Rect p_currentFrame);
		float getX();
		float getY();
		SDL_Texture* getTex();
		SDL_Rect getCurrentFrame();
		
	private:
		float x;
		float y;
		SDL_Texture* tex;
		SDL_Rect currentFrame;
};