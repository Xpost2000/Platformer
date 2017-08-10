#include "BasicEnemy.h"
#include <algorithm>

/*
* it's practically a carbon copy of the Player
* update function. But that is because
* it practically has to be.
*/
#ifdef DEBUG_BUILD
void BasicEnemy::print_state(){
	switch(eState){
		case EnemyState::STANDING:
			// should be impossible
			std::cout << "Standing" << std::endl;
			break;
		case EnemyState::JUMPING:
			std::cout << "Jumping" << std::endl;
			break;
		case EnemyState::WALKING:
			std::cout << "Walking" << std::endl;
			break;
		case EnemyState::FALLING:
			std::cout << "Falling" << std::endl;
			break;
		case EnemyState::DEAD:
			std::cout << "Dead" << std::endl;
			break;
		default:
			std::cout << "Unknown state" << std::endl;
			break;
	}
}
#endif
void BasicEnemy::update(float dt, std::vector<Block>& blocks){
	if(!isDead()){
	velocity.y() += gravity*dt;
	BasicEnemy pred = *this;
	pred.pos.x() += velocity.x() *dt;
	pred.set_aabb(pred.pos, pred.size);
	for(auto& b : blocks){
		if(pred.intersect_aabb(b)){
			// I make him go the other way if touching something.
			// or I should use an enum with an int value...
			velocity.x() = -velocity.x();
			break;
		}
	}
	pred = *this;
	pred.pos.y() += velocity.y() * dt;
	pred.set_aabb(pred.pos, pred.size);
	for( auto & b : blocks ){
		if(pred.intersect_aabb(b)){
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
	if(velocity.x() != 0 && onGround){
		eState = EnemyState::WALKING;
	}
	if(velocity.y() < 0 && !onGround){
		eState = EnemyState::JUMPING;
	}else if ( velocity.y() > 0 && !onGround ){
		eState = EnemyState::FALLING;
	}
	if(velocity.x() > 0){
		dir = Direction::RIGHT;
	}else{
		dir = Direction::LEFT;
	}
	pos.x() += velocity.x() * dt;
	velocity.y() = std::min<float>( velocity.y() , 330.0f );
	pos.y() += velocity.y() * dt;
	set_aabb(pos, size);
}
}
