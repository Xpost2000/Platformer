#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <vector>
#include "Block.h"
#include "Progressor.h"
#include "JumpingEnemy.h"
#include "SpriteBatcher.h"
#include "BackgroundSprites.h"
#include "EnvText.h"
#include "BasicEnemy.h"
class TextRenderer;
class EntityManager{
	public:
		EntityManager(){}
		EntityManager(const EntityManager& other) = default;
		~EntityManager(){}
		void create_block(const Block)	;
		void create_block(const BackgroundBlock) ;
		void create_block(const BackgroundBlockStatic) ;
		void create_enemy(const JumpingEnemy) ;
		void create_enemy(const BasicEnemy) ;
		void create_text(const EnvironmentText);
		void set_progressor(const Progressor other) { p = other; }
		void set_progressor_pos( Vec2 pos ) { p.getPos().x() = pos.x(); p.getPos().y() = pos.y(); }
		void clear_entities();
		std::vector<JumpingEnemy>& get_jumping_enemies(){ return jumpingEnemies; }
		std::vector<Block>& get_blocks(){ return blocks; }
		std::vector<EnvironmentText>& get_env_text() { return evtxt; }
		std::vector<BasicEnemy>& get_basic_enemies(){ return basicEnemies; }
		std::vector<BackgroundBlock>& get_background_blocks() { return bs; }
		std::vector<BackgroundBlockStatic>& get_background_static_blocks() { return bss; }
		Progressor& get_progressor() { return p; }
		void draw_text( TextRenderer& );
		void draw_blocks( SpriteBatcher& );	
		void draw_progressor( SpriteBatcher& );
		void draw_background_props( Vec2 camPos, SpriteBatcher&, bool p=true );	
		void draw_jumping_enemies( SpriteBatcher& );	
		void draw_basic_enemies( SpriteBatcher& );	
		void update( float dt );
	private:
		std::vector<EnvironmentText> evtxt;
		std::vector<BackgroundBlock> bs;
		std::vector<BackgroundBlockStatic> bss;
		std::vector<JumpingEnemy> jumpingEnemies;
		std::vector<Block> blocks;
		std::vector<BasicEnemy> basicEnemies;
		Progressor p;
};
#endif
