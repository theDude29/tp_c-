#ifndef MOVING_ENTITY
#define MOVING_ENTITY

#include "../header/Entity.h"

class MovingEntity : public Entity {
	public:
		MovingEntity(int x, int y, int size, int max_speed, int max_acceleration, int max_rotation_speed, Int2 direction);
		virtual void updatePosition() =0;
		virtual void draw(SDL_Renderer * renderer) =0;
	protected:
		int max_speed;
		int max_acceleration;
		int max_rotation_speed;
		Int2 direction;
};

#endif
