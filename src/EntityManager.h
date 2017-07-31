#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <vector>
#include "Block.h"
#include "JumpingEnemy.h"
#include "SpriteBatcher.h"
#include "BasicEnemy.h"
class EntityManager{
	public:
		EntityManager(){}
		~EntityManager(){}
		void create_block(const Block)	;
		void create_enemy(const JumpingEnemy) ;
		void create_enemy(const BasicEnemy) ;
		void clear_entities();
		std::vector<JumpingEnemy>& get_jumping_enemies(){ return jumpingEnemies; }
		std::vector<Block>& get_blocks(){ return blocks; }
		std::vector<BasicEnemy>& get_basic_enemies(){ return basicEnemies; }
		void draw_blocks( SpriteBatcher& );	
		void draw_jumping_enemies( SpriteBatcher& );	
		void draw_basic_enemies( SpriteBatcher& );	
		void update( float dt );
	private:
		std::vector<JumpingEnemy> jumpingEnemies;
		std::vector<Block> blocks;
		std::vector<BasicEnemy> basicEnemies;
};
#endif
