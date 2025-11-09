#pragma once
#include <SDL2/SDL.h>

#include "../RenderWindow.hpp"
#include "./MovableEntity.hpp"

class Enemy : public MovableEntity
{
	public:
		Enemy(RenderWindow* window);
                void facePlayer(Vector2f playerPos);
                void approachesPlayer();
};