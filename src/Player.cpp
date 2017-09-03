#include "Player.h"
#include "Sound.h"
#include "EntityManager.h"
#include <algorithm>
#include <iostream>
#include "BasicEnemy.h"
#include "JumpingEnemy.h"
#include <SDL2/SDL.h>
void Player::calculate_uvs(){
	switch(pState){
		case PlayerState::FALLING:
		case PlayerState::JUMPING:
			if(playerDir == Direction::LEFT){
				uvs = Vec4(0, 0, 30.0f/64.0f, 30.0f/64.0f);
				return;
			}
			if(playerDir == Direction::RIGHT){
				uvs = Vec4(32.0f/64.0f, 0, 62.0f/64.0f, 30.0f/64.0f);
				return;
			}
			break;
		case PlayerState::STANDING:
		case PlayerState::WALKING:
		case PlayerState::DEAD:
			uvs = Vec4(0, 32.0f/64.0f, 30.0f/64.0f, 62.0f/64.0f);
			return;
			break;
	}
}
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
	pred.reposition_aabb();
	for(auto& b : blocks){	
		if(pred.intersect_aabb(b)){
			if(b.get_type() == KILLZONE_BLOCK){ kill(); }
			velocity.x() = 0;
			break;
		}
	}
	pred = *this;
	pred.pos.y() += velocity.y() * dt;
	pred.reposition_aabb();
	for(auto& b : blocks){
		if(pred.intersect_aabb(b)){
			if(b.get_type() == KILLZONE_BLOCK){ kill(); }
			velocity.y() = 0;
			if(b.get_aabb().pos.y() + b.get_aabb().size.y() < bb.pos.y()){
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
	if(!onGround)
	pState = PlayerState::WALKING;
}
void Player::move_right(float dt){
	velocity.x() = 190;
	playerDir = Direction::RIGHT;
	if(!onGround)
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
		Sound::play_sound("jump");
	}
	pState = PlayerState::JUMPING;
}
// this makes the moving controls feel floaty and more difficult in air.
void Player::floaty_jump(float dt){
		if( velocity.x() < 0 ){
			velocity.x() += 190*dt;
			velocity.x() = std::min<float>(velocity.x(), 0);
		}
		else{
			velocity.x() -= 190*dt;
			velocity.x() = std::max<float>(velocity.x(), 0);
		}
}
void Player::update(float dt, EntityManager& em){
	update(dt, em.get_blocks(), em.get_basic_enemies(), em.get_jumping_enemies(), em.get_progressor());
}
// and organize everything more.
void Player::update(float dt, std::vector<Block> &blocks, std::vector<BasicEnemy>& be, std::vector<JumpingEnemy>& je, Progressor& p){
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
	if( !onGround ){
		pState = PlayerState::FALLING;
	}
	velocity.y() += gravity * dt;

	collide_blocks( dt, blocks );

	if(onGround==true){
		jump_delay = 10;
	}
	
	for(auto& b : be){
		if(intersect_aabb( b )){
			// cheating a little by adding "padding space"
			// cause I realized the case won't execute since I'd be out of collision range and even
			// if it would work the cpu steps to fast to ever check this.
			if((b.get_aabb().pos.y()+10 > bb.pos.y() + bb.size.y())&& !b.isDead()){
				velocity.y() = -200;
				b.kill();
				score += 350;
			}
			else{
				if(!b.isDead()){
					if(playerDir == Direction::RIGHT){
						velocity.x() = -290;
						velocity.y() = -300;
						health -= 20;
					}
					if(playerDir == Direction::LEFT){
						velocity.x() = 290;
						velocity.y() = -300;
						health -= 20;
					}
				}
			}
		}
	}
	for(auto& b : je){
		if(intersect_aabb( b )){
			if((b.get_aabb().pos.y()+10 > bb.pos.y() + bb.size.y())&& !b.isDead()){
				velocity.y() = -200;
				b.kill();
				score += 400;
			}
			else{
				if(!b.isDead()){
					if(playerDir == Direction::RIGHT){
						velocity.x() = -290;
						velocity.y() = -300;
						health -= 20;
					}
					if(playerDir == Direction::LEFT){
						velocity.x() = 290;
						velocity.y() = -300;
						health -= 20;
					}
				}
			}
		}
	}

	if(intersect(p)){
		p.mark();
		score += 10;
	}

	pos.y() += velocity.y() * dt;
	// clamp gravity
	velocity.y() = std::min<float>(velocity.y(), 330.0f);
	pos.x() += velocity.x() * dt;
	calculate_uvs();
	reposition_aabb();
}
