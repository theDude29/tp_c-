#include "../header/Bird.h"
#include <iostream>

Bird::Bird(int x, int y, int size, int max_speed, int max_acceleration, int max_rotation_speed, Int2 direction) : MovingEntity(x,y,size,max_speed,max_acceleration, max_rotation_speed, direction) {}

void Bird::draw(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 0u, 0u, 255u, SDL_ALPHA_OPAQUE);
	SDL_Rect r = {position.x, position.y, size.x, size.y};
	SDL_RenderFillRect(renderer, &r);
	
	std::cout<<position.x<<' '<<position.y<<std::endl;
}

void Bird::setFriends(std::vector<Bird*> friends){ this->friends = friends; }

void Bird::setObstacles(std::vector<Obstacle*> obstacles){ this->obstacles = obstacles; }

void Bird::updatePosition() {
	Int2 direction={0,0};
	for(auto& other : friends) {
		if (other != this) {
			direction += other->getPosition() - position;
		}
	}
	
	position += direction/200;
}
