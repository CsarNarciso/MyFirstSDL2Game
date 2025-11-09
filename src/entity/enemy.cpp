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
    float dx = playerPos.x - getPos().x;
    float dy = playerPos.y - getPos().y;

    float targetAngle = atan2(dy, dx) * (180.0f / M_PI);
    float currentAngle = getAngle();

    // Normalize both to 0-360
    if (targetAngle < 0) targetAngle += 360.0f; 
    if (currentAngle < 0) currentAngle += 360.0f; 

    // Get angles needed to rotate (difference of angles beetwen target and enemy)
    float diff = targetAngle - currentAngle;
    
    // Get shortest rotation direction
    if (diff < -180.0f) diff += 360.0f; 
    if (diff > 180.0f) diff -= 360.0f; 

    // Apply rotation
    float rotationSpeed = getRotationSpeed();
    if (diff > rotationSpeed) diff = rotationSpeed;
    if (diff < -rotationSpeed) diff = -rotationSpeed;

    setAngle(currentAngle + diff);
}

void Enemy::approachesPlayer()
{}
