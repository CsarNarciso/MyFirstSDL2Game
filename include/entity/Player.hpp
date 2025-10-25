#pragma once
#include <SDL2/SDL.h>

#include "../Input.hpp"
#include "../RenderWindow.hpp"
#include "./Map.hpp"
#include "./MovableEntity.hpp"

class Player : public MovableEntity
{
	public:
		Player(RenderWindow* window);
        void handlePlayerMovement(Map& map, const InputState input);
};