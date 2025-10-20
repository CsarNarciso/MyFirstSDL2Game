#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/Entity.hpp"
#include "../include/Player.hpp"
#include <../include/RenderWindow.hpp>
#include "../include/Math.hpp"
#include "../include/Map.hpp"


// MOVE ALL THIS CODE TO player or map classes!
bool positionExists(int row, int column, std::vector<std::vector<int>>& map)
{
	return row >= 0 && row < map.size() && 
			column >= 0 && column < map[row].size();
}

bool isWater(int row, int column, std::vector<std::vector<int>>& map)
{
	return map[row][column] == 0;
}

bool canMove(int row, int column, std::vector<std::vector<int>>& map)
{
	return positionExists(row, column, map) && !isWater(row, column, map);
}

enum class Direction { UP, LEFT, DOWN, RIGHT };

void rotate(Direction dir, Player& player)
{
	int rotationSpeed = player.getRotationSpeed();
	int d = (dir == Direction::RIGHT) ? 1 : -1;
	player.setAngle(player.getAngle() + d * rotationSpeed);
}


bool collidesWithMap(const SDL_Rect& box, Map& map, std::vector<std::vector<int>>& mapTileReferences) {
    
	int tileSize = map.getTaleSize();

    int top = (box.y >= 0) ? box.y / tileSize : -1;
    int left = (box.x >= 0) ? box.x / tileSize : -1;
    int bottom = (box.y + box.h - 1) / tileSize;
    int right = (box.x + box.w - 1) / tileSize;

    for (int row = top; row <= bottom; ++row) {
        for (int col = left; col <= right; ++col) {
            if (!canMove(row, col, mapTileReferences)) {
                return true;
            }
        }
    }
    return false;
}

void tryMoveWithCollision(Player& player, float dx, float dy, Map& map, std::vector<std::vector<int>>& mapTileReferences) {
    SDL_Rect futureBox = {
        static_cast<int>(player.getPos().x + dx),
        static_cast<int>(player.getPos().y + dy),
        player.getCurrentFrame().w,
        player.getCurrentFrame().h
    };
    if (!collidesWithMap(futureBox, map, mapTileReferences)) {
        player.setPos(player.getPos().x += dx, player.getPos().y += dy);
		return;
    }
	
	SDL_Rect xBox = {
        static_cast<int>(player.getPos().x + dx),
        static_cast<int>(player.getPos().y),
        player.getCurrentFrame().w,
        player.getCurrentFrame().h
    };
    if (!collidesWithMap(xBox, map, mapTileReferences)) {
        player.setPos(player.getPos().x += dx, player.getPos().y);
		return;
    }
	
	SDL_Rect yBox = {
        static_cast<int>(player.getPos().x),
        static_cast<int>(player.getPos().y + dy),
        player.getCurrentFrame().w,
        player.getCurrentFrame().h
    };
    if (!collidesWithMap(yBox, map, mapTileReferences)) {
        player.setPos(player.getPos().x, player.getPos().y += dy);
		return;
    }
}


void move(Direction dir, Player& player, Map& map, std::vector<std::vector<int>>& mapTileReferences)
{
	int rotationSpeed = player.getRotationSpeed();
	float angle = player.getAngle();
	float rad = angle * M_PI / 180.0f;

	int d = (dir == Direction::UP) ? 1 : -1;

	float dx = cos(rad) * (rotationSpeed * d);
	float dy = sin(rad) * (rotationSpeed * d);

	tryMoveWithCollision(player, dx, dy, map, mapTileReferences);
}

bool pressedKeyUp = false;
bool pressedKeyDown = false;
bool pressedKeyLeft = false;
bool pressedKeyRight = false;

void handlePlayerMovement(Player& player, Map& map, std::vector<std::vector<int>>& mapTileReferences)
{
	//	Move forward and backward
	if(pressedKeyUp)
	{
		move(Direction::UP, player, map, mapTileReferences);
	}
	if(pressedKeyDown)
	{
		move(Direction::DOWN, player, map, mapTileReferences);
	}
	//	Rotation
	if(pressedKeyLeft)
	{
		rotate(Direction::LEFT, player);
	}
	if(pressedKeyRight)
	{
		rotate(Direction::RIGHT, player);
	}
}

int main(int argc, char** args) {
	
	//Initialize SDL attributes (on fialures, it always returns -1, so)

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		std::cout << "Error initializing SDL video: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ( SDL_Init(IMG_INIT_PNG) < 0 ) {
		std::cout << "Error initializing SDL png: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	//Init window and renderer
	int window_width = 640;
	int window_height = 480;
	RenderWindow window("title", window_width, window_height);

	// Generate random map
	Map map(window_width, window_height);	
	std::vector<Entity> mapTaleEntities = map.generate(&window);
	std::vector< std::vector< int >> mapTileReferences = map.getTaleReferences();

	// Declare Player
	Player player(&window);

	//game loop
	bool gameRunning = true;

	SDL_Event event;
	
	while(gameRunning)
	{
		//Process events
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				// Exit game
				case SDL_QUIT:
					gameRunning = false;
					break;

				// Detect gameplay pressed keys
				case SDL_KEYDOWN:
					
					switch (event.key.keysym.sym)
					{
						case SDLK_UP: pressedKeyUp = true; break;
						case SDLK_DOWN: pressedKeyDown = true; break;
						case SDLK_LEFT: pressedKeyLeft = true; break;
						case SDLK_RIGHT: pressedKeyRight = true; break;
					}
					break;
				case SDL_KEYUP:
					
					switch (event.key.keysym.sym)
					{
						case SDLK_UP: pressedKeyUp = false; break;
						case SDLK_DOWN: pressedKeyDown = false; break;
						case SDLK_LEFT: pressedKeyLeft = false; break;
						case SDLK_RIGHT: pressedKeyRight = false; break;
					}
					break;
			}
		}
		// Player movement
		handlePlayerMovement(player, map, mapTileReferences);
		
		// Clear
		window.clear();
			
		// Render each map tale
		for(int i = 0; i < mapTaleEntities.size(); i++)
		{
			window.render(mapTaleEntities[i]);
		}
		// Render player
		window.render(player);

		// Draw
		window.display();
	}
	
	//destroy window and shutdown SDL
	window.cleanUp();
	SDL_Quit();

	//Get out program successfully
	return 0;
}