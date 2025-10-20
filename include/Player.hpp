#pragma once
#include <SDL2/SDL.h>

#include "./Entity.hpp"
#include "./RenderWindow.hpp"

class Player : public Entity
{
	public:
		Player(RenderWindow* window);
		int& getPlayerMovementPx();
		int& getRotationSpeed();
	
	private:
		int playerMovementPx = 5; // Player speed (pixels per frame)
		int rotationSpeed = 5;		
};