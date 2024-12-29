#ifndef ENTITY
#define ENTITY

#include <SDL2/SDL.h>

struct Int2 {
	int x;
	int y;
	
	Int2 operator+(Int2 b) {
		return {x+b.x,y+b.y};
	};
	
	Int2 operator-(Int2 b) {
		return {x-b.x,y-b.y};
	};
	
	Int2 operator+=(Int2 b) {
		x += b.x;
		y += b.y;
		return *this;
	};
	
	Int2 operator-=(Int2 b) {
		x -= b.x;
		y -= b.y;
		return *this;
	};
	
	Int2 operator/(int b) {
		return {x/b,y/b};
	};
	
	Int2 operator*(int b) {
		return {x*b,y*b};
	};
	
	Int2& normalize() {
		x /= x*x + y*y;
		y /= x*x + y*y;
		return *this;
	};
};

class Entity {
	public:
		Entity(int x, int y, int size_x, int size_y);
		virtual void draw(SDL_Renderer * renderer);
		Int2 getPosition();
	protected:
		Int2 position;
		Int2 size;
};

#endif
