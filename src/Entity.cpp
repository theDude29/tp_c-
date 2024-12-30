#include "../header/Entity.h"
#include <iostream>

Entity::Entity(float x, float y, float size_x, float size_y) {position={x,y}; this->size={size_x,size_y};}

void Entity::draw(SDL_Renderer * renderer) {std::cout<<"dessin";}

Float2 Entity::getPosition() {return position;}
