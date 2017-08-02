#include "GameCamera.h"
#include "Player.h"

void GameCamera::update(Player& p){
	matrix = glm::mat4();
	pos.x() = -p.getPos().x() + screenResolution.x() / 2.0f;
	pos.y() = -p.getPos().y() + screenResolution.y() / 2.0f;
	if( pos.x() < screenResolution.x() + limits.x() ){
		pos.x() = limits.x();
	}
	if( pos.y() < screenResolution.y() + limits.y() ){
		pos.y() = limits.y();
	}
	if( pos.x() > screenResolution.x() + lowerLimits.x() ){
		pos.x() = lowerLimits.x();
	}
	if( pos.y() > screenResolution.y() + lowerLimits.y() ){
		pos.y() = lowerLimits.y();
	}
	matrix = glm::translate(matrix , glm::vec3(pos.x(), pos.y(), 0.0f));
}
