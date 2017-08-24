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
		inline Vec2 transform( Vec2 offset ) { pos.x() += offset.x(); pos.y() += offset.y(); }
		void SetScreenRes( Vec2 res ) { screenResolution=res; }
		void SetPos( Vec2 pos ) { this->pos = pos; }
		void RecenterPlayer( Player& p );	
		inline void refresh(){ matrix = glm::mat4(); matrix = glm::translate(matrix, glm::vec3(pos.x(), pos.y(), 0.0f)); }
		glm::mat4 &get_matrix() { return matrix; }
	private:
		Vec2 screenResolution;
		glm::mat4 matrix;
		Vec2 pos;
		Vec2 limits=Vec2(100000);
		Vec2 lowerLimits=Vec2(-100000);
};
#endif
