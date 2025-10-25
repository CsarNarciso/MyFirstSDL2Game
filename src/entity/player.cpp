#include <SDL2/SDL.h>

#include "../../include/RenderWindow.hpp"
#include "../../include/entity/MovableEntity.hpp"
#include "../../include/Direction.hpp"
#include "../../include/Map.hpp"
#include "../../include/Input.hpp"

#include "../../include/entity/Player.hpp"

Player::Player(RenderWindow* window) : MovableEntity(Vector2f(0, 0), window->loadTexture("gfx/player.png"), 2, 5, 5)
{}

void Player::handlePlayerMovement(Map& map, const InputState input)
{
	// Running?
	setRunning(input.running);

	//	Move forward and backward
	if(input.up)
	{
		move(Direction::UP, map);
	}
	if(input.down)
	{
		move(Direction::DOWN, map);
	}
	//	Rotation
	if(input.left)
	{
		rotate(Direction::LEFT);
	}
	if(input.right)
	{
		rotate(Direction::RIGHT);
	}
}