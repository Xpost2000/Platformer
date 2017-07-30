#include "BasicEnemy.h"
#include <algorithm>

/*
* it's practically a carbon copy of the Player
* update function. But that is because
* it practically has to be.
*/
void BasicEnemy::update(float dt, std::vector<Block>& blocks){
	if(!isDead()){
	velocity.y() += gravity*dt;
	BasicEnemy pred = *this;
	pred.pos.x() += velocity.x() *dt;
	for(auto& b : blocks){
		if(pred.intersect(b)){
			// I make him go the other way if touching something.
			// or I should use an enum with an int value...
			velocity.x() = -velocity.x();
			break;
		}
	}
	pred = *this;
	pred.pos.y() += velocity.y() * dt;
	for( auto & b : blocks ){
		if(pred.intersect(b)){
			velocity.y() = 0;
			if(b.getPos().y() + b.getSize().y() < pos.y()){
			}else{
				onGround = true;
			}
			break;
		}
		else{
			onGround = false;
		}
	}
	pos.x() += velocity.x() * dt;
	velocity.y() = std::min<float>( velocity.y() , 330.0f );
	pos.y() += velocity.y() * dt;
}
}
