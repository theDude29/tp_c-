#ifndef OBSTACLE
#define OBSTACLE

#include "Entity.h"

class Obstacle : public Entity {
	public:
		Obstacle(float x, float y, float size_x, float size_y);
		void draw(SDL_Renderer * renderer);
		float intersection(num2<float> a, num2<float> b);
};

#endif
