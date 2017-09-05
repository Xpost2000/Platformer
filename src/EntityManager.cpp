#include "EntityManager.h"
#include "FreeTypeText.h"

void EntityManager::create_coin( const Coin c ){
	coins.push_back(c);
}

void EntityManager::create_block(const Block b){
	blocks.push_back(b);
}
void EntityManager::create_block(const BackgroundBlock b){
	bs.push_back(b);
}
void EntityManager::create_text( const EnvironmentText ev ){
	evtxt.push_back(ev);
}
void EntityManager::create_block(const BackgroundBlockStatic b){
	bss.push_back(b);
}
void EntityManager::create_enemy(const JumpingEnemy je){
	jumpingEnemies.push_back(je);
}
void EntityManager::create_enemy(const BasicEnemy be){
	basicEnemies.push_back(be);
}
void EntityManager::clear_entities(){
	blocks.clear();
	jumpingEnemies.clear();
	basicEnemies.clear();
}
void EntityManager::draw_text( TextRenderer& txt){
	for(auto& text : evtxt){
		txt.render(text.str, glm::vec2(text.pos.x(), text.pos.y()), text.scale, glm::vec3(text.color.x(), text.color.y(), text.color.z()), true );
	}
}
void EntityManager::draw_coins( SpriteBatcher& sb ){
	for(auto &c : coins){
		sb.draw( c.getPos(), Vec4(0, 0, 1, 1), c.getSize(), c.getColor() );
	}
	sb.render();
}
void EntityManager::draw_blocks( SpriteBatcher& sb ){
	for(auto &b : blocks)	{
		if(b.get_type()!=KILLZONE_BLOCK)
		sb.draw(b.getPos(), b.getUvs(), b.getSize(), b.getColor());
	}
	sb.render();
}
void EntityManager::draw_progressor( SpriteBatcher& sb ){
	sb.draw(p.getPos(), p.getUvs(), p.getSize(), p.getColor());
	sb.render();
}

void EntityManager::draw_jumping_enemies( SpriteBatcher& sb ){
	for(auto &je : jumpingEnemies)	{
		sb.draw(je.getPos(), je.getUvs(), je.getSize(), je.getColor());
	}
	sb.render();
}
void EntityManager::draw_basic_enemies( SpriteBatcher& sb ){
	for(auto &be : basicEnemies)	{
		sb.draw(be.getPos(), be.getUvs(), be.getSize(), be.getColor());
	}
	sb.render();
}
void EntityManager::draw_background_props( Vec2 camPos, SpriteBatcher& sb, bool p ){
	if(p){
	for(auto &e : bs){
		sb.draw(Vec2(-camPos.x()*e.scrollFactor.x()+e.getPos().x(), -camPos.y()*e.scrollFactor.y()+e.getPos().y()), e.getUvs(), e.getSize(), e.getColor());
	}
	}else{
	for(auto &e : bs){
		sb.draw(e.getPos(), e.getUvs(), e.getSize(), e.getColor());
	}
	}
	for(auto &e : bss){
		sb.draw(e.getPos(), e.getUvs(), e.getSize(), e.getColor());
	}
	sb.render();
}
void EntityManager::update( float dt ){
	// enemies
	for(int i = 0; i < basicEnemies.size(); ++i){
		if(basicEnemies[i].isDead()){
			if(basicEnemies[i].DeathAnimation(dt))
			basicEnemies.erase(basicEnemies.begin() + i);
		}
		basicEnemies[i].update(dt, blocks);
	}
	for(int i = 0; i < jumpingEnemies.size(); ++i){
		if(jumpingEnemies[i].isDead()){
			if(jumpingEnemies[i].DeathAnimation(dt))
			jumpingEnemies.erase(jumpingEnemies.begin() + i);
		}
		jumpingEnemies[i].update(dt, blocks);
	}
	for(int i = 0; i < coins.size(); ++i){
		if(coins[i].isDead()){
			coins.erase(coins.begin() + i);
		}
	}
}
