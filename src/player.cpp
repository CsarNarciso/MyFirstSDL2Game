#include <SDL2/SDL.h>

#include "./RenderWindow.hpp"
#include "./Entity.hpp"

#include "../include/Player.hpp"

Player::Player(RenderWindow* window) : Entity(Vector2f(0, 0), window->loadTexture("gfx/player1.png"))
{}

int& Player::getPlayerMovementPx()
{return playerMovementPx;}

int& Player::getRotationSpeed()
{return rotationSpeed;}