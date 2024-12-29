#include "../header/Entity.h"
#include <iostream>

Entity::Entity(int x, int y, int size_x, int size_y) {position={x,y}; this->size={size_x,size_y};}

void Entity::draw(SDL_Renderer * renderer) {std::cout<<"dessin";}

Int2 Entity::getPosition() {return position;}
