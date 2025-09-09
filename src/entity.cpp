#include <SDL2/SDL.h>

#include "../include/Entity.hpp"
#include "../include/Math.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0; 
	currentFrame.y = 0; 
	currentFrame.w = 32; 
	currentFrame.h = 32; 
}

Vector2f& Entity::getPos()
{
	return pos;
}

void Entity::setPos(int x, int y)
{
	pos = Vector2f(x, y);
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}