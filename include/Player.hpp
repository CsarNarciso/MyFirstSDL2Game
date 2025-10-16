#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <utility>

#include "./Entity.hpp"
#include "./RenderWindow.hpp"

class Player : public Entity
{
	public:
		Player(RenderWindow* window);
		const std::map<SDL_Keycode, std::pair<int, int>>& getDirections();
		int& getPlayerMovementPx();
	
	private:
		int playerMovementPx = 5; // Player speed (pixels per frame)
		const std::map<SDL_Keycode, std::pair<int, int>> directions = { // Define direction values (y, x)
			{ SDLK_UP, { -1, 0 } },
			{ SDLK_LEFT, { 0, -1 } },
			{ SDLK_DOWN, { 1, 0 } },
			{ SDLK_RIGHT, { 0, 1 } }
		};
};