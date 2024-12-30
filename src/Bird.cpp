#include "../header/Bird.h"
#include <iostream>

Bird::Bird(float x, float y, float size, float max_speed, float max_acceleration, float max_rotation_speed, Float2 direction) : MovingEntity(x,y,size,max_speed,max_acceleration, max_rotation_speed, direction) {living=true;}

void Bird::draw(SDL_Renderer * renderer) {

	if(living) {
		SDL_SetRenderDrawColor(renderer, 0u, 0u, 255u, SDL_ALPHA_OPAQUE);
		SDL_Rect r = {position.x, position.y, size.x, size.y};
		SDL_RenderFillRect(renderer, &r);
	}
	
	//std::cout<<position.x<<' '<<position.y<<std::endl;
}

void Bird::setFriends(std::vector<Bird*> friends){ this->friends = friends; }

void Bird::setPredators(std::vector<MovingEntity*> predators) {this->predators = predators;};

void Bird::setObstacles(std::vector<Obstacle*> obstacles){ this->obstacles = obstacles; }

void Bird::kill() { living=false; }

bool Bird::isLiving() { return living; }

void Bird::updatePosition() {

	if(living) {
		Float2 centreTroupeau={0,0};
		Float2 directionTroupeau={0,0};
		Float2 posPlusProche={0,0};
		float distancePlusProche=INFINITY;
		int nbLiving=0;
		for(auto& bird : friends) {
			if(bird->isLiving()) {
				centreTroupeau += bird->getPosition();
				directionTroupeau += bird->getDirection();
				float distance = (bird->getPosition() - position).norme();
				if(distance > 0 && distance < distancePlusProche) {
					distancePlusProche = distance;
					posPlusProche = bird->getPosition();
				}
				
				nbLiving++;
			}
		}
		
		centreTroupeau /= nbLiving;
		Float2 directionCentreTroupeau = (centreTroupeau - position).normalize();
		directionTroupeau.normalize();
		Float2 directionPlusProche = (posPlusProche - position).normalize();
		float distanceCentreTroupeau = (centreTroupeau - position).norme();
		
		float coefDirTroupeau = 0.5;
		float coefDirCentreTroupeau = distanceCentreTroupeau/100;
		float coefRepulsion = 50/distancePlusProche;
		
		float coefPredator=0;
		Float2 directionPredators={0,0};
		float distancePredators=0;
		if(predators.size() > 0) {
			Float2 centrePredators={0,0};
			for(auto& predator : predators) {
				centrePredators += predator->getPosition();
			}
			centrePredators /= predators.size();
			directionPredators = (centrePredators - position).normalize();
			distancePredators = (centrePredators - position).norme();
			coefPredator = 2000/distancePredators;
		}
		
		Float2 directionVoulue = (directionTroupeau*coefDirTroupeau + directionCentreTroupeau*coefDirCentreTroupeau - directionPlusProche*coefRepulsion - directionPredators*coefPredator).normalize();
		
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
		
		position += direction * (max_speed + max_speed*distanceCentreTroupeau/(2*sqrt(WIDTH*HEIGHT)));
	}
}
