#include "../header/MovingEntity.h"
#include <iostream>

MovingEntity::MovingEntity(float x,float y,float size, float max_speed, float max_acceleration, float max_rotation_speed, Float2 direction) : Entity(x,y,size,size) {
	this->max_speed = max_speed;
	this->max_acceleration = max_acceleration;
	this->max_rotation_speed = max_rotation_speed;
	this->direction = direction;
}

Float2 MovingEntity::getDirection() { return direction;}
