#include <SDL2/SDL.h>

#include "../include/Entity.hpp"

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex, SDL_Rect p_currentFrame)
	:x(p_x), y(p_y), tex(p_tex), currentFrame(p_currentFrame)
{}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}