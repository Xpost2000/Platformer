#include "Player.h"
#include <iostream>
#include "BasicEnemy.h"
#include <SDL2/SDL.h>

bool aabb_basic_enemy(Player& p, BasicEnemy& b){
	return (p.getPos().x() < b.getPos().x() + b.getSize().x() && p.getPos().x() + p.getSize().x() > b.getPos().x())&&
	       (p.getPos().y() < b.getPos().y() + b.getSize().y() && p.getPos().y() + p.getSize().y() > b.getPos().y());}

bool aabb_block(Player& p, Block& b){
	return (p.getPos().x() < b.getPos().x() + b.getSize().x() && p.getPos().x() + p.getSize().x() > b.getPos().x())&&
	       (p.getPos().y() < b.getPos().y() + b.getSize().y() && p.getPos().y() + p.getSize().y() > b.getPos().y());}

// TODO: add input handling.
// and organize everything more.
void Player::update(float dt, std::vector<Block> &blocks, std::vector<BasicEnemy>& be){
	const Uint8* keys = SDL_GetKeyboardState(NULL);	
	velocity.x() = 0;
	if(keys[SDL_SCANCODE_A]||keys[SDL_SCANCODE_LEFT]){
		velocity.x() = -190;
	}
	if(keys[SDL_SCANCODE_D]||keys[SDL_SCANCODE_RIGHT]){
		velocity.x() = 190;
	}
	if(keys[SDL_SCANCODE_SPACE]){
		if(onGround == false && jump_delay > 0){
			velocity.y() -= 135 * dt;
			jump_delay -= dt;
		}
		if(onGround == true ){
			velocity.y() = -262.0f ;
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
	
	std::cout << onGround << std::endl;
	for(auto& b : be){
		if(aabb_basic_enemy(*this, b)&&!onGround){
			if(b.getPos().y() < pos.y()+size.y()){
				velocity.y() = -200;
				b.kill();
			}
		}
		else if ( aabb_basic_enemy(*this, b) ){
			// basic idea of death
			exit(0);
		}
	}

}
