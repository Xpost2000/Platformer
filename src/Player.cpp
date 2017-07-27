#include "Player.h"
#include <SDL2/SDL.h>

bool aabb_block(Player& p, Block& b){
	return (p.getPos().x() < b.getPos().x() + b.getSize().x() && p.getPos().x() + p.getSize().x() > b.getPos().x())&&
	       (p.getPos().y() < b.getPos().y() + b.getSize().y() && p.getPos().y() + p.getSize().y() > b.getPos().y());}

// TODO: add input handling.
// and organize everything more.
void Player::update(float dt, std::vector<Block> &blocks){
	const Uint8* keys = SDL_GetKeyboardState(NULL);	
	velocity.x() = 0;
	if(keys[SDL_SCANCODE_A]){
		velocity.x() = -150;
	}
	if(keys[SDL_SCANCODE_D]){
		velocity.x() = 150;
	}
	if(keys[SDL_SCANCODE_SPACE]){
		if(onGround == false && jump_delay > 0){
			velocity.y() -= 105 * dt;
			jump_delay -= dt;
		}
		if(onGround == true ){
			velocity.y() = -205.0f ;
			onGround = false;
		}
	}
	velocity.y() += gravity * dt;
	Player pred = *this;
	pred.pos.x() += velocity.x() * dt;
	for(auto& b : blocks){	
		if(aabb_block(pred, b)){
			velocity.x() = 0;
			break;
		}
	}
	pred = *this;
	pred.pos.y() += velocity.y() * dt;
	for(auto& b : blocks){
		if(aabb_block(pred, b)){
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

	if(onGround==true){
		jump_delay = 10;
	}
	pos.y() += velocity.y() * dt;
	pos.x() += velocity.x() * dt;
}
