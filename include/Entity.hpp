#pragma once
#include <SDL2/SDL.h>

#include "../include/Math.hpp"

class Entity
{
	public:
		Entity(Vector2f p_pos, SDL_Texture* p_tex);
		Vector2f& getPos();
		void setPos(int x, int y);
		SDL_Texture* getTex();
		SDL_Rect getCurrentFrame();
		
	private:
		Vector2f pos;
		SDL_Texture* tex;
		SDL_Rect currentFrame;
};