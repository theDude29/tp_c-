#include "../header/Predator.h"
#include <iostream>

Predator::Predator(float x, float y, float size, float max_speed, float max_acceleration, float max_rotation_speed, Float2 direction) : MovingEntity(x,y,size,max_speed,max_acceleration, max_rotation_speed, direction) {}

void Predator::draw(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 255u, 0u, 0u, SDL_ALPHA_OPAQUE);
	SDL_Rect r = {position.x, position.y, size.x, size.y};
	SDL_RenderFillRect(renderer, &r);
	
	//std::cout<<position.x<<' '<<position.y<<std::endl;
}

void Predator::setPreys(std::vector<Bird*> preys){ this->preys = preys; }

void Predator::updatePosition() {
	float distancePlusProche=INFINITY;
	Float2 positionPlusProche={0,0};
	for(auto& prey : preys) {
		if(prey->isLiving()) {
			float distance = (prey->getPosition() - position).norme();
			if(distance < distancePlusProche) {
				distancePlusProche = distance;
				positionPlusProche = prey->getPosition();
				
				if(distance < 40) prey->kill();
			}
		}
	}
	
	Float2 directionVoulue = (positionPlusProche - position).normalize();
	
	if(acos((directionVoulue.x*direction.x + directionVoulue.y*direction.y)/(directionVoulue.norme()*direction.norme())) < max_rotation_speed) {
			direction = directionVoulue;
		}
	else {
		Float2 newDirection;
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
	
	position += direction*max_speed;
}
