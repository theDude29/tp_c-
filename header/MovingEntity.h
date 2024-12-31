#ifndef MOVING_ENTITY
#define MOVING_ENTITY

#include "../header/Entity.h"

class MovingEntity : public Entity {
	public:
		MovingEntity(float x, float y, float size, float max_speed, float max_rotation_speed, num2<float> direction);
		virtual void updatePosition() =0;
		virtual void draw(SDL_Renderer * renderer) =0;
		num2<float> getDirection();
	protected:
		float max_speed;
		float max_rotation_speed;
		num2<float> direction;
		
		void setNewDirection(num2<float> directionVoulue);
};

#endif
