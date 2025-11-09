#include <SDL2/SDL.h>
#include <cmath>

#include "../../include/RenderWindow.hpp"
#include "../../include/entity/MovableEntity.hpp"
#include "../../include/Math.hpp"

#include "../../include/entity/Enemy.hpp"

Enemy::Enemy(RenderWindow* window) : MovableEntity(Vector2f(45, 45), window->loadTexture("gfx/enemy.png"), 2, 5, 5)
{}

void Enemy::facePlayer(Vector2f playerPos)
{
	// Get angle to point to
	int dx = playerPos.x - getPos().x;
	int dy = playerPos.y - getPos().y;
	float angleRadians = atan2(dy, dx);
	
	// Convert to degrees to get real target point
	float targetAngle = angleRadians * (180.0f / M_PI);
	
	float currentAngle = getAngle();
	std::cout << "currentAngle: " << currentAngle << std::endl;
	std::cout << "targetAngle: " << targetAngle << std::endl;
	
	if(currentAngle < targetAngle)
	{		
		setAngle(currentAngle + getRotationSpeed());
	}
}