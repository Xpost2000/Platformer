#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H
#include "vector_typedef.h"
#include "vec2.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Player;
class GameCamera{
	public:
		GameCamera(){}
		GameCamera(const GameCamera& other) = default;
		GameCamera(Vec2 pos, Vec2 screenResolution, Vec2 limits, Vec2 lowerLimits) : pos(pos), limits(limits), lowerLimits(lowerLimits), screenResolution(screenResolution) {}
		void update(Player& p);
		Vec2 getLimits() { return limits; }
		Vec2 getLowerLimits() { return lowerLimits; }
		Vec2 getPos() { return pos; }
		glm::mat4 get_matrix() { return matrix; }
	private:
		Vec2 screenResolution;
		glm::mat4 matrix;
		Vec2 pos;
		Vec2 limits;
		Vec2 lowerLimits;
};
#endif
