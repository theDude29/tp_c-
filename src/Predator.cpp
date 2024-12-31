#include "../header/Predator.h"
#include <iostream>

Predator::Predator(float x, float y, float size, float max_speed, float max_rotation_speed, num2<float> direction) : MovingEntity(x,y,size,max_speed, max_rotation_speed, direction) {}

void Predator::draw(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 255u, 0u, 0u, SDL_ALPHA_OPAQUE);
	SDL_Rect r = {(int)position.x, (int)position.y, (int)size.x, (int)size.y};
	SDL_RenderFillRect(renderer, &r);
}

void Predator::setPreys(std::vector<Bird*> preys){this->preys = preys;}

void Predator::updatePosition() {
	float distancePlusProche=INFINITY;
	num2<float> positionPlusProche={0,0};
	for(auto& prey : preys) { //on attaque la proie la plus proche
		if(prey->isLiving()) {
			float distance = (prey->getPosition() - position).norme();
			if(distance < distancePlusProche) {
				distancePlusProche = distance;
				positionPlusProche = prey->getPosition();
				
				if(distance < 40) prey->kill();
			}
		}
	}
	
	num2<float> directionVoulue;
	try {directionVoulue = (positionPlusProche - position).normalize();}
	catch(Division_by_zero_error) {directionVoulue={0,0};}
	
	setNewDirection(directionVoulue);
	
	position += direction*max_speed;
}
