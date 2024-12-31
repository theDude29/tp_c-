#include <iostream>
#include <random>
#include <vector>
#include <cmath>

#include "../header/Obstacle.h"
#include "../header/Bird.h"
#include "../header/Predator.h"

using namespace std;

int const WIDTH = 1600;
int const HEIGHT = 900;

struct global_t {
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

	// random
	std::random_device rd;
	std::default_random_engine eng;
	std::uniform_real_distribution<float> rand;

};

global_t g;

void do_render(const vector<Entity*> entities) {
	SDL_SetRenderDrawColor(g.renderer, 255u, 255u, 255u, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g.renderer);
	
	for(const auto entity : entities) {
		entity->draw(g.renderer);
	}

	SDL_RenderPresent(g.renderer);
}

void do_update(vector<MovingEntity*> movingEntities) {
	for(auto entity : movingEntities) {
		entity->updatePosition();
	}
}

int main(int argc, char ** argv)
{
	vector<Obstacle*> obstacles;
	int size=50;
	obstacles.push_back(new Obstacle(0,0,WIDTH,size));
	obstacles.push_back(new Obstacle(WIDTH-size,0,size,HEIGHT));
	obstacles.push_back(new Obstacle(0,0,size,HEIGHT));
	obstacles.push_back(new Obstacle(0,HEIGHT-size,WIDTH,size));
	obstacles.push_back(new Obstacle(WIDTH/2,HEIGHT/2,size*2,size*2));
	obstacles.push_back(new Obstacle(WIDTH/4,HEIGHT/4,size*2,size*2));

	float max_rotation_speed = 3.14*0.01;
	float max_speed = 1.5;
	
	vector<Bird*> birds;
	birds.push_back(new Bird(1000, 200, 30, max_speed, max_rotation_speed, {0,-1}));
	birds.push_back(new Bird(1200, 200, 30, max_speed, max_rotation_speed, {0,-1}));
	birds.push_back(new Bird(1400, 200, 30, max_speed, max_rotation_speed, {0,-1}));
	birds.push_back(new Bird(1300, 500, 30, max_speed, max_rotation_speed, {0,-1}));
	birds.push_back(new Bird(800, 800, 30, max_speed, max_rotation_speed, {-1,0}));
	for(auto& bird : birds) {bird->setFriends(birds); bird->setObstacles(obstacles);}
	
	vector<Predator*> predators;
	predators.push_back(new Predator(0, 0, 40, max_speed*1.1, max_rotation_speed*1.1, {0,1}));
	vector<MovingEntity*> p; // petite manipe pour convertir les Predator en MovingEntity, pas très propre...
	p.insert(p.end(), predators.begin(), predators.end());
	for(auto& predator : predators) {predator->setPreys(birds);}
	for(auto& bird : birds) {bird->setPredators(p);}

	vector<Entity*> entities;
	entities.insert(entities.end(), obstacles.begin(), obstacles.end());
	entities.insert(entities.end(), birds.begin(), birds.end());
	entities.insert(entities.end(), predators.begin(), predators.end());
	
	vector<MovingEntity*> movingEntities;
	movingEntities.insert(movingEntities.end(), birds.begin(), birds.end());
	movingEntities.insert(movingEntities.end(), predators.begin(), predators.end());

	int status;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
		return 1;
	}

	g.window = SDL_CreateWindow("BOIDS",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (not g.window) {
		return 1;
	}

	// get the default renderer
	g.renderer = SDL_CreateRenderer(g.window, -1, 0);
	if (not g.renderer) {
		return 1;
	}

	bool end = false;
	while (not end) {
		SDL_Event event;
		if (SDL_WaitEventTimeout(&event, 2)) {
			switch (event.type) {
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_CLOSE:
						end = true;
						break;
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						// Should never happen
						break;
					default:
						break;
				}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					end = true;
				}
				break;
			case SDL_KEYUP:
				break;
			}
		} else {
			// Got time out or error
			char const * e = SDL_GetError();
			if (e != NULL) {
				if (strlen(e) != 0) {
					// Print and Ignore errors (MacOS has error)
					std::cout << "ERROR: " << e << std::endl;
					SDL_ClearError();
				}
			}

			do_update(movingEntities);
			do_render(entities);
		}
	}

	SDL_DestroyRenderer(g.renderer);
	SDL_DestroyWindow(g.window);
	SDL_CloseAudio();
	SDL_Quit();
	
	for (auto obstacle : obstacles) delete obstacle;
	for (auto bird : birds) delete bird;
	for (auto predator : predators) delete predator;
	
	return 0;
}

