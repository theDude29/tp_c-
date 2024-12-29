#ifndef BIRD
#define BIRD

#include "../header/MovingEntity.h"
#include "../header/Obstacle.h"
#include <vector>

class Bird : public MovingEntity {
	public:
		Bird(int x, int y, int size, int max_speed, int max_acceleration, int max_rotation_speed, Int2 direction);
		void updatePosition();
		void setFriends(std::vector<Bird*> friends);
		void setObstacles(std::vector<Obstacle*> obstacles);
		void draw(SDL_Renderer * renderer);
	private:
		std::vector<Bird*> friends;
		std::vector<Obstacle*> obstacles;
};

#endif
