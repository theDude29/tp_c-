#include "../header/Entity.h"
#include <iostream>

Entity::Entity(float x, float y, float size_x, float size_y) {position={x,y}; size={size_x,size_y};}

num2<float> Entity::getPosition() {return position;}
