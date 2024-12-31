#ifndef BIRD
#define BIRD

#include "../header/MovingEntity.h"
#include "../header/Obstacle.h"

#include <vector>

class Bird : public MovingEntity {
	public:
		Bird(float x, float y, float size, float max_speed, float max_rotation_speed, num2<float> direction);
		void updatePosition();
		void setFriends(std::vector<Bird*> friends);
		void setPredators(std::vector<MovingEntity*> predators);
		void setObstacles(std::vector<Obstacle*> obstacles);
		void draw(SDL_Renderer * renderer);
		void kill();
		bool isLiving();
	protected:
		std::vector<Bird*> friends;
		std::vector<MovingEntity*> predators;
		std::vector<Obstacle*> obstacles;
		bool living;
};

#endif
