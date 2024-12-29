#include "../header/MovingEntity.h"
#include <iostream>

MovingEntity::MovingEntity(int x,int y,int size, int max_speed, int max_acceleration, int max_rotation_speed, Int2 direction) : Entity(x,y,size,size) {
	this->max_speed = max_speed;
	this->max_acceleration = max_acceleration;
	this->max_rotation_speed = max_rotation_speed;
	this->direction = direction;
}
