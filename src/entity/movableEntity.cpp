#include <SDL2/SDL.h>

#include "../../include/RenderWindow.hpp"
#include "../../include/Direction.hpp"
#include "../../include/Map.hpp"

#include "../../include/entity/MovableEntity.hpp"

MovableEntity::MovableEntity(Vector2f p_pos, SDL_Texture* p_tex, int p_speed, int p_runningSpeed, int p_rotationSpeed) : Entity(p_pos, p_tex)
{
    speed = p_speed;
    runningSpeed = p_runningSpeed;
    rotationSpeed = p_rotationSpeed;
};

int& MovableEntity::getSpeed()
{return speed;}

int& MovableEntity::getRotationSpeed()
{return rotationSpeed;}

void MovableEntity::setRunning(bool p_running)
{running = p_running;};


void MovableEntity::rotate(Direction dir)
{
	int d = (dir == Direction::RIGHT) ? 1 : -1;
	setAngle(getAngle() + d * rotationSpeed);
}


bool MovableEntity::collidesWithMap(const SDL_Rect& box, Map& map) {
    
	int tileSize = map.getTileSize();

    int top = (box.y >= 0) ? box.y / tileSize : -1;
    int left = (box.x >= 0) ? box.x / tileSize : -1;
    int bottom = (box.y + box.h - 1) / tileSize;
    int right = (box.x + box.w - 1) / tileSize;

    for (int row = top; row <= bottom; ++row) {
        for (int col = left; col <= right; ++col) {
            if (!map.canMove(row, col)) {
                return true;
            }
        }
    }
    return false;
}

void MovableEntity::tryMoveWithCollision(float dx, float dy, Map& map) {

    SDL_Rect currentFrame = getCurrentFrame();

    SDL_Rect futureBox = {
        static_cast<int>(getPos().x + dx),
        static_cast<int>(getPos().y + dy),
        currentFrame.w,
        currentFrame.h
    };
    if (!collidesWithMap(futureBox, map)) {
        setPos(getPos().x += dx, getPos().y += dy);
		return;
    }
	
	SDL_Rect xBox = {
        static_cast<int>(getPos().x + dx),
        static_cast<int>(getPos().y),
        currentFrame.w,
        currentFrame.h
    };
    if (!collidesWithMap(xBox, map)) {
        setPos(getPos().x += dx, getPos().y);
		return;
    }
	
	SDL_Rect yBox = {
        static_cast<int>(getPos().x),
        static_cast<int>(getPos().y + dy),
        currentFrame.w,
        currentFrame.h
    };
    if (!collidesWithMap(yBox, map)) {
        setPos(getPos().x, getPos().y += dy);
		return;
    }
}


void MovableEntity::move(Direction dir, Map& map)
{
	float rad = getAngle() * M_PI / 180.0f;
	int d = (dir == Direction::UP) ? 1 : -1;

	float dx = cos(rad) * ((running ? runningSpeed : speed) * d);
	float dy = sin(rad) * ((running ? runningSpeed : speed) * d);

	tryMoveWithCollision(dx, dy, map);
}