#include "Player.h"
#include <algorithm>
#include <iostream>
#include "BasicEnemy.h"
#include "JumpingEnemy.h"
#include <SDL2/SDL.h>
//TEST DEBUG FUNC
void Player::print_state(){
	switch(pState){
		case PlayerState::WALKING:
			std::cout << "Player is walking" << std::endl;
			break;
		case PlayerState::FALLING:
			std::cout << "Player is falling" << std::endl;
			break;
		case PlayerState::JUMPING:
			std::cout << "Player is jumping" << std::endl;
			break;
		case PlayerState::STANDING:
			std::cout << "Player is standing" << std::endl;
			break;
		case PlayerState::DEAD:
			std::cout << "Player is dead" << std::endl;
			break;
		case PlayerState::HURT:
			std::cout << "Player was hurt" << std::endl;
			break;
		default:
			std::cout << "Unknown State" << std::endl;
			break;
	}
}
// moving functions for organization.
void Player::collide_blocks( float dt, std::vector<Block>& blocks ){
	Player pred = *this;
	pred.pos.x() += velocity.x() * dt;
	for(auto& b : blocks){	
		if(pred.intersect(b)){
			velocity.x() = 0;
			break;
		}
	}
	pred = *this;
	pred.pos.y() += velocity.y() * dt;
	for(auto& b : blocks){
		if(pred.intersect(b)){
			velocity.y() = 0;
			if(b.getPos().y() + b.getSize().y() < pos.y()){
			}
			else{
				onGround = true;
			}
			break;
		}else{
			onGround = false;
		}
	}
}
void Player::move_left(float dt){
	velocity.x() = -190;
	playerDir = Direction::LEFT;
	pState = PlayerState::WALKING;
}
void Player::move_right(float dt){
	velocity.x() = 190;
	playerDir = Direction::RIGHT;
	pState = PlayerState::WALKING;
}
void Player::jump(float dt){
	// the extended jump function.
	if(!onGround && jump_delay > 0){
		velocity.y() -= 135*dt;
		jump_delay -= dt;
	}else if(onGround){
		velocity.y() = -262.0f;
		onGround = false;
	}
	pState = PlayerState::JUMPING;
}
// this makes the moving controls feel floaty and more difficult in air.
void Player::floaty_jump(float dt){
		if( velocity.x() < 0 ){
			velocity.x() += 190*dt;
			velocity.x() = std::min<float>(velocity.x(), 0);
			playerDir = Direction::RIGHT;
		}
		else{
			velocity.x() -= 190*dt;
			velocity.x() = std::max<float>(velocity.x(), 0);
			playerDir = Direction::LEFT;
		}
}
// and organize everything more.
void Player::update(float dt, std::vector<Block> &blocks, std::vector<BasicEnemy>& be, std::vector<JumpingEnemy>& je){
	const Uint8* keys = SDL_GetKeyboardState(NULL);	
	if(velocity.x() == 0 && onGround){
		pState = PlayerState::STANDING;
	}
	if(onGround)
	velocity.x() = 0; // cannot control your movements in air bro.
	else{
		floaty_jump(dt);
	}
	if(keys[SDL_SCANCODE_A]||keys[SDL_SCANCODE_LEFT]){
		move_left(dt);
	}
	if(keys[SDL_SCANCODE_D]||keys[SDL_SCANCODE_RIGHT]){
		move_right(dt);
	}
	if(keys[SDL_SCANCODE_SPACE]){
		jump(dt);
	}
	if( velocity.y() > 0 && !onGround ){
		pState = PlayerState::FALLING;
	}
	velocity.y() += gravity * dt;

	collide_blocks( dt, blocks );

	if(onGround==true){
		jump_delay = 10;
	}
	
	for(auto& b : be){
		if(intersect( b )){
			// cheating a little by adding "padding space"
			// cause I realized the case won't execute since I'd be out of collision range and even
			// if it would work the cpu steps to fast to ever check this.
			if(b.getPos().y()+5 > pos.y() + size.y()){
				velocity.y() = -200;
				b.kill();
			}
			else{
				if(!b.isDead())
				exit(0);
			}
		}
	}
	for(auto& b : je){
		if(intersect( b )){
			if(b.getPos().y()+5 > pos.y() + size.y()){
				velocity.y() = -200;
				b.kill();
			}
			else{
				if(!b.isDead())
				exit(0);
			}
		}
	}

	pos.y() += velocity.y() * dt;
	// clamp gravity
	velocity.y() = std::min<float>(velocity.y(), 330.0f);
	pos.x() += velocity.x() * dt;
//	print_state();
}
