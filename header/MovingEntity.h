#ifndef MOVING_ENTITY
#define MOVING_ENTITY

#include "../header/Entity.h"

class MovingEntity : public Entity {
	public:
		MovingEntity(float x, float y, float size, float max_speed, float max_acceleration, float max_rotation_speed, Float2 direction);
		virtual void updatePosition() =0;
		virtual void draw(SDL_Renderer * renderer) =0;
		Float2 getDirection();
	protected:
		float max_speed;
		float max_acceleration;
		float max_rotation_speed;
		Float2 direction;
};

#endif
