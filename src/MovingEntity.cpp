#include "../header/MovingEntity.h"
#include <iostream>

MovingEntity::MovingEntity(float x,float y,float size, float max_speed, float max_rotation_speed, num2<float> direction) : Entity(x,y,size,size) {
	this->max_speed = max_speed;
	this->max_rotation_speed = max_rotation_speed;
	this->direction = direction;
}

num2<float> MovingEntity::getDirection() {return direction;}

void MovingEntity::setNewDirection(num2<float> directionVoulue) {
	if(acos((directionVoulue.x*direction.x + directionVoulue.y*direction.y)/(directionVoulue.norme()*direction.norme())) < max_rotation_speed) { //si on peut rejoindre la direction voulue avec notre vitesse de rotation
		direction = directionVoulue;
	}
	else { //sinon on s'en rapproche autant qu'on peut
		num2<float> newDirection;
		if(directionVoulue.x*direction.y - direction.x*directionVoulue.y < 0) {
			newDirection.x = cos(max_rotation_speed)*direction.x - sin(max_rotation_speed)*direction.y;
			newDirection.y = sin(max_rotation_speed)*direction.x + cos(max_rotation_speed)*direction.y;
		}
		else {
			newDirection.x = cos(-max_rotation_speed)*direction.x - sin(-max_rotation_speed)*direction.y;
			newDirection.y = sin(-max_rotation_speed)*direction.x + cos(-max_rotation_speed)*direction.y;
		}
		direction = newDirection;
	}
}
