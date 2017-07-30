#include "JumpingEnemy.h"
#include <algorithm>

void JumpingEnemy::update(float dt, std::vector<Block>& blocks){
	RandomInt jmp_decide(0, 15);
	if(!isDead()){
		// if number is a multiple of five. we're good 
	if( jmp_decide() % 5 == 0 ){
		if(onGround){
		velocity.y() = -350.0f;
		onGround = false;
		eState = EnemyState::JUMPING;
		}
	}
	velocity.y() += gravity*dt;

	JumpingEnemy pred = *this;
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
	if(velocity.x() != 0 && onGround){
		eState = EnemyState::WALKING;
	}
	if ( velocity.y() > 0 && !onGround ){
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
	}
	print_state();
}
