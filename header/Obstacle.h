#ifndef OBSTACLE
#define OBSTACLE

#include "Entity.h"

class Obstacle : public Entity {
	public:
		Obstacle(int x, int y, int size_x, int size_y);
		void draw(SDL_Renderer * renderer);
};

#endif
