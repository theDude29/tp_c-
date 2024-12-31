#ifndef ENTITY
#define ENTITY

#include <SDL2/SDL.h>

#include "./utils.h"

class Entity {
	public:
		Entity(float x, float y, float size_x, float size_y);
		virtual void draw(SDL_Renderer * renderer) =0;
		num2<float> getPosition();
	protected:
		num2<float> position;
		num2<float> size;
};

#endif
