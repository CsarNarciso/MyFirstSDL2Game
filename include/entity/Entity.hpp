#pragma once
#include <SDL2/SDL.h>

#include "../include/Math.hpp"

class Entity
{
	public:
		Entity(Vector2f p_pos, SDL_Texture* p_tex);
		Vector2f& getPos();
		void setPos(float x, float y);
		SDL_Texture* getTex();
		SDL_FRect getCurrentFrame();
		void setAngle(float p_angle);
		float getAngle();
		
	private:
		Vector2f pos;
		SDL_Texture* tex;
		SDL_FRect currentFrame;
		float angle;
};