#include "BasicEnemy.h"

bool aabb_block(BasicEnemy& p, Block& b){
	return (p.getPos().x() < b.getPos().x() + b.getSize().x() && p.getPos().x() + p.getSize().x() > b.getPos().x())&&
	       (p.getPos().y() < b.getPos().y() + b.getSize().y() && p.getPos().y() + p.getSize().y() > b.getPos().y());}

/*
* it's practically a carbon copy of the Player
* update function. But that is because
* it practically has to be.
*/
void BasicEnemy::update(float dt, std::vector<Block>& blocks){
	velocity.y() += gravity*dt;
	BasicEnemy pred = *this;
	pred.pos.x() += velocity.x() *dt;
	for(auto& b : blocks){
		if(aabb_block(pred, b)){
			// I make him go the other way if touching something.
			// or I should use an enum with an int value...
			velocity.x() = -velocity.x();
			break;
		}
	}
	pred = *this;
	pred.pos.y() += velocity.y() * dt;
	for( auto & b : blocks ){
		if(aabb_block(pred, b)){
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
	pos.y() += velocity.y() * dt;
}
