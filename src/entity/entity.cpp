#include <SDL2/SDL.h>

#include "../../include/Math.hpp"

#include "../../include/entity/Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0; 
	currentFrame.y = 0; 
	currentFrame.w = 32; 
	currentFrame.h = 32; 
}

SDL_Texture* Entity::getTex()
{return tex;}

SDL_Rect Entity::getCurrentFrame()
<<<<<<< HEAD:src/entity.cpp
{
	return currentFrame;
}

void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

float Entity::getAngle()
{
	return angle;
}
=======
{return currentFrame;}

void Entity::setPos(int x, int y)
{pos = Vector2f(x, y);}

Vector2f& Entity::getPos()
{return pos;}

void Entity::setAngle(float p_angle)
{angle = p_angle;}

float Entity::getAngle()
{return angle;}
>>>>>>> fix/ModularizeCollisionAndMovementLogic:src/entity/entity.cpp
