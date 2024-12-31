#include "../header/Bird.h"
#include <iostream>

Bird::Bird(float x, float y, float size, float max_speed, float max_rotation_speed, num2<float> direction) : MovingEntity(x,y,size,max_speed, max_rotation_speed, direction) {living=true;}

void Bird::draw(SDL_Renderer * renderer) {

	if(living) {
		SDL_SetRenderDrawColor(renderer, 0u, 0u, 255u, SDL_ALPHA_OPAQUE);
		SDL_Rect r = {(int)position.x, (int)position.y, (int)size.x, (int)size.y};
		SDL_RenderFillRect(renderer, &r);
	}
}

void Bird::setFriends(std::vector<Bird*> friends){this->friends = friends;}

void Bird::setPredators(std::vector<MovingEntity*> predators) {this->predators = predators;};

void Bird::setObstacles(std::vector<Obstacle*> obstacles){this->obstacles = obstacles;}

void Bird::kill() {living=false;}

bool Bird::isLiving() {return living;}

void Bird::updatePosition() {

	if(living) {
		
		//gestion des obtacles
		float coefEviterIntersection=0;
		num2<float> directionEviterIntersection = {0,0};
		float distanceIntersecion=INFINITY;
		for(auto obstacle : obstacles) {
			float distance = obstacle->intersection(direction, position);
			if(distance<20) living = false;
			if(distance<distanceIntersecion) distanceIntersecion = distance;
		}
		directionEviterIntersection = {-direction.y, direction.x};
		coefEviterIntersection = 100/distanceIntersecion;
		if(distanceIntersecion<150) max_rotation_speed *= 30; //on tourne plus vite si on est sur le point de se prendre un obstacle dans la tete...
		
		//gestion des autres oiseaux amis
		num2<float> centreTroupeau={0,0};
		num2<float> directionTroupeau={0,0};
		num2<float> posPlusProche={0,0};
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
		num2<float> directionCentreTroupeau;
		try {directionCentreTroupeau = (centreTroupeau - position).normalize();}
		catch(Division_by_zero_error) {directionCentreTroupeau = {0,0};}
		try {directionTroupeau.normalize();}
		catch(Division_by_zero_error) {directionTroupeau={0,0};}
		num2<float> directionPlusProche = (posPlusProche - position).normalize();
		float distanceCentreTroupeau = (centreTroupeau - position).norme();
		
		float coefDirTroupeau = 0.5;
		float coefDirCentreTroupeau = distanceCentreTroupeau/100;
		float coefRepulsion = 50/distancePlusProche;
		
		//gestion des predateurs
		float coefPredator=0;
		num2<float> directionPredators={0,0};
		float distancePredators=INFINITY;
		if(predators.size() > 0) {
			num2<float> centrePredators={0,0};
			for(auto& predator : predators) {
				centrePredators += predator->getPosition();
			}
			centrePredators /= predators.size();
			try {directionPredators = (centrePredators - position).normalize();}
			catch(Division_by_zero_error) {directionPredators = {0,0};}
			distancePredators = (centrePredators - position).norme();
			coefPredator = 100/distancePredators;
		}
		
		//on assemble tout
		num2<float> directionVoulue;
		try {directionVoulue = (directionTroupeau*coefDirTroupeau + directionCentreTroupeau*coefDirCentreTroupeau - directionPlusProche*coefRepulsion - directionPredators*coefPredator + directionEviterIntersection*coefEviterIntersection).normalize();}
		catch(Division_by_zero_error) {directionVoulue={0,0};}
		
		setNewDirection(directionVoulue);
		
		position += direction * (max_speed + max_speed*distanceCentreTroupeau/(2*sqrt(1500*500)) + max_speed*30/distancePredators); //on va plus vite si on est loin du troupeau et si on est poursuivit par des predateurs
		
		if(distanceIntersecion<150) max_rotation_speed /= 30; //on retablit la vitesse de rotation
	}
}
