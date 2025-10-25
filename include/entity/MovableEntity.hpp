#pragma once
#include <SDL2/SDL.h>

#include "./Entity.hpp"
#include "../RenderWindow.hpp"
#include "../Direction.hpp"
#include "../Map.hpp"

class MovableEntity : public Entity
{
	public:
		MovableEntity(Vector2f p_pos, SDL_Texture* p_tex, int p_speed, int p_runningSpeed, int p_rotationSpeed);
		int& getSpeed();
		int& getRotationSpeed();
		void setRunning(bool running);

		void rotate(Direction dir);
		bool collidesWithMap(const SDL_Rect& box, Map& map);
		void tryMoveWithCollision(float dx, float dy, Map& map);
		void move(Direction dir, Map& map);

	private:
		int speed;
		int runningSpeed;
		int rotationSpeed;
		bool running;
};