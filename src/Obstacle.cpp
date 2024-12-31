#include "../header/Obstacle.h"
#include <iostream>

Obstacle::Obstacle(float x, float y, float size_x, float size_y) : Entity(x,y,size_x, size_y) {
}

void Obstacle::draw(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 0u, 0u, 0u, SDL_ALPHA_OPAQUE);
	SDL_Rect r = {(int)position.x, (int)position.y, (int)size.x, (int)size.y};
	SDL_RenderFillRect(renderer, &r);
}

float Obstacle::intersection(num2<float> a, num2<float> b) {
	float tMinX, tMaxX, tMinY, tMaxY;
	
	if(a.x == 0) a.x = 0.001; //pour eviter de gerer le cas ==0 separemment...
	if(a.y == 0) a.y = 0.001;

	float t1 = (position.x - b.x)/a.x;
	float t2 = (position.x+size.x - b.x)/a.x;
	
	if(t1<0 && t2<0) return INFINITY;
	
	tMinX = std::max(0.f, std::min(t1,t2));
	tMaxX = std::max(t1,t2);
	
	t1 = (position.y - b.y)/a.y;
	t2 = (position.y+size.y - b.y)/a.y;
	
	if(t1<0 && t2<0) return INFINITY;
	
	tMinY = std::max(0.f, std::min(t1,t2));
	tMaxY = std::max(t1,t2);
	
	t1 = std::max(tMinX, tMinY);
	t2 = std::min(tMaxX, tMaxY);
	
	if(t1<=t2) return t1;
	return INFINITY;
}

