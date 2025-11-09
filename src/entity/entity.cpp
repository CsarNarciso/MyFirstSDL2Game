#include <SDL2/SDL.h>

#include "../../include/Math.hpp"

#include "../../include/entity/Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0.0f; 
	currentFrame.y = 0.0f; 
	currentFrame.w = 32.0f; 
	currentFrame.h = 32.0f; 
}

SDL_Texture* Entity::getTex()
{return tex;}

SDL_FRect Entity::getCurrentFrame()
{return currentFrame;}

void Entity::setPos(float x, float y)
{pos = Vector2f(x, y);}

Vector2f& Entity::getPos()
{return pos;}

void Entity::setAngle(float p_angle)
{angle = p_angle;}

float Entity::getAngle()
{return angle;}