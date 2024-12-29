#include "../header/Obstacle.h"
#include <iostream>

Obstacle::Obstacle(int x, int y, int size_x, int size_y) : Entity(x,y,size_x, size_y) {
}

void Obstacle::draw(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 0u, 0u, 0u, SDL_ALPHA_OPAQUE);
	SDL_Rect r = {position.x, position.y, size.x, size.y};
	SDL_RenderFillRect(renderer, &r);
}

