#ifndef ENTITY
#define ENTITY

#include <SDL2/SDL.h>

#include "./utils.h"

class Entity {
	public:
		Entity(float x, float y, float size_x, float size_y);
		virtual void draw(SDL_Renderer * renderer);
		Float2 getPosition();
	protected:
		Float2 position;
		Float2 size;
};

#endif
