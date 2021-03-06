#include "GLCanvas.h"
#include "EditorFrame.h"
#include "PropertyPanel.h"
#include "../Block.h"
#include <iostream>

Vec2 mousePos;

GLCanvas::GLCanvas( wxWindow* parent, const wxGLAttributes& disp, wxWindowID id, const wxPoint & pos, const wxSize& size, long style )
: wxGLCanvas(parent, disp, id, pos, size, style){
	player=Player(Vec2(300), Vec2(73,73), Vec2(100), Vec4(1.0));
	property = ((EditorFrame*)parent)->property;
	// I create two dummies to "work on"
	SDL_Window* dummy;
	gl_info_struct_t blank;
	// The original IDevice class was ment for SDL2 use mainly
	// other wise provided a wrapper that was typesafe for
	// OpenGL functions.
	wxGLContextAttrs ctx_attributes;
	ctx_attributes.CoreProfile().OGLVersion(4,5).EndList();
	dev = std::make_shared<GLDevice>(dummy, blank);
	ctx_obj = new wxGLContext(this, NULL, &ctx_attributes);
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	SetCurrent(*ctx_obj);
	glewExperimental=true;
	if(glewInit()!=GLEW_OK){
		wxMessageBox("GLEW failed to initialize", "Error", wxICON_ERROR);
	}
	ds = std::make_shared<DefaultShader>(dev);
	ls = std::make_shared<LightShader>(dev);
	sb = std::make_shared<SpriteBatcher>(dev);
	tm = std::make_shared<TextureManager>();
	ftr = std::make_shared<TextRenderer>( dev, "textures\\ui\\ocr.ttf" )	;
	tm->add_texture("tiles", "textures\\tiles.png", get_device());
	tm->add_texture("player", "textures\\test_player.png", get_device());
	tm->add_texture("coin", "textures\\coin_base.png", get_device());
	// set up matrix and stuff
	projection = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f, -1.f, 1.f);
}

void GLCanvas::PaintScene( wxPaintEvent& pnt ){
	camera.refresh();
	SetCurrent(*ctx_obj);
	wxPaintDC (this);
	
	dev->viewport(0, 0, viewPort_sz.x, viewPort_sz.y);
	dev->clearColor(1.0, 1.0, 1.0, 1.0);
	dev->clear(BufferClear::COLOR_BUFFER);
	dev->enableAlpha();
	ds->use();
	ds->setTextured(false);	
	ds->setMatrices(projection, camera.get_matrix());
	if(lighting){
	ls->use();
	ls->setTex(0);
	ls->setTextured(true);
	ls->setProj(projection);
	ls->setView(camera.get_matrix());
	for(int i = 0; i < 10; ++i ){
		ls->setLight(i, lights[i]);
	}
	}else{
		ds->setTex(0);
		ds->setTextured(true);
	}
	// render the lights
	
	tm->get_tex("tiles")->bind();
	sb->draw(Vec2(-78000), Vec4(Block::get_uv_from_type(BlockTypes::FlatColor)), Vec2(12390120), Vec4(0.0, 0.0, 0.1, 1.0));
	entity_manager.draw_background_props( camera.getPos(), *sb, parallax );
	entity_manager.draw_progressor(*sb);	
	entity_manager.draw_blocks(*sb);
	entity_manager.draw_jumping_enemies(*sb);
	entity_manager.draw_basic_enemies(*sb);
	tm->get_tex("coin")->bind();
	entity_manager.draw_coins(*sb);
	tm->get_tex("player")->bind();
	sb->draw( player.getPos(), player.getUvs(), player.getSize(), Vec4(1.0f) );
	sb->render();
	ls->unuse();
	ds->use();
	ds->setTextured(false);
	if(currentEnt!=nullptr){
		sb->draw( currentEnt->getPos(), Vec4(0), currentEnt->getSize(), Vec4(1.0, 0.0, 0.0, 1.0) );
		sb->render();
	}
	SwapBuffers();
}

void GLCanvas::LogicRefresh(){
	if(!current.loaded){
		current.load(player, entity_manager, lights);
	}
}

void GLCanvas::OnResize( wxSizeEvent& evnt ){
	SetSize(evnt.GetSize());
	viewPort_sz = evnt.GetSize();
	projection = glm::ortho(0.0f, static_cast<float>(viewPort_sz.x), static_cast<float>(viewPort_sz.y), 0.0f, -1.f, 1.f);
	camera.SetScreenRes(Vec2(viewPort_sz.x, viewPort_sz.y));
}

// Idk if I need it yet.
void GLCanvas::KeyboardEvents( wxKeyEvent& ev ){
	if( currentEnt != nullptr ){
	if(wxGetKeyState(WXK_ESCAPE)){
		currentEnt = nullptr;
	}
	if(wxGetKeyState(WXK_DELETE)){
		delete_cur();
	}
	switch(ev.GetKeyCode()){
		case WXK_LEFT:
			currentEnt->getPos().x() -= 20;
			break;
		case WXK_RIGHT:
			currentEnt->getPos().x() += 20;
			break;
		case WXK_UP:
			currentEnt->getPos().y() -= 20;
			break;
		case WXK_DOWN:
			currentEnt->getPos().y() += 20;
			break;
			/*
		case WXK_CONTROL_C:
			std::cout << "copied\n";
			copy_f();
			break;
		case WXK_CONTROL_V:
			std::cout << "pasted\n";
			paste();
			break;
			*/
	}
	}
}

void GLCanvas::MouseEvents( wxMouseEvent& ev ){
	const wxPoint center = wxPoint(viewPort_sz.x/2, viewPort_sz.y/2);
	const wxPoint curPos = ScreenToClient(wxGetMousePosition());
	wxPoint last;
	wxPoint mouseDelta = curPos - center;
	should_update=false;
	if(ev.Dragging() && ev.RightIsDown()){
		camera.transform( Vec2(-mouseDelta.x*0.7, -mouseDelta.y*0.7) );
		WarpPointer( center.x, center.y );
	}
	if(ev.LeftIsDown()){

		glm::vec3 mapped = glm::unProject(glm::vec3(curPos.x, viewPort_sz.y-curPos.y, 0.0), camera.get_matrix(), projection, glm::vec4(0, 0, viewPort_sz.x, viewPort_sz.y));
		mousePos = Vec2(mapped.x, mapped.y);
		// iterate through all objects
		// I make a vector of pointers because a pointer can actually
		// contain the data. If I had used the standard Entity vector
		// it might not've worked. Also this should be slightly more faster
		// anyways.
		std::vector<Entity*> entities;
		for( auto& block : entity_manager.get_blocks() ){
			entities.push_back( &block );
		}
		for( auto& jumping_enemy : entity_manager.get_jumping_enemies() ){
			entities.push_back( &jumping_enemy );
		}
		for( auto& basic_enemy : entity_manager.get_basic_enemies() ){
			entities.push_back( &basic_enemy );
		}
		for( auto& bb : entity_manager.get_background_blocks() ){
			entities.push_back( &bb );
		}
		for( auto& bbs : entity_manager.get_background_static_blocks() ){
			entities.push_back( &bbs );
		}
		for( auto& coin : entity_manager.get_coins() ){
			entities.push_back( &coin );
		}
		entities.push_back ( &entity_manager.get_progressor() );
		entities.push_back ( &player );
		if( mode==CREATE_M ){
			// UNKNOWN
		//	int x = (( mousePos.x() + property->gridW()/2 ) / property->gridW())* property->gridW();
		//	int y = (( mousePos.y() + property->gridH()/2 ) / property->gridH())* property->gridH();
		// 
		// 	so after one minute of fucking around with the calculator on windows I figured out grid snapping.
		// 	cause I realized the logic of the expressions I looked up were invalid / wrong. I just modified
		// 	the most common one I found which was this
		// 	(pos / gridW) * gridW (same for height as well)
		// 	I know int usually auto rounds but I'm now starting to think the operations are done in floating point
		// 	first than converted to integer. ( also auto is weird )
			int x = std::floor(mousePos.x()/property->gridW())*property->gridW();
			int y = std::floor(mousePos.y()/property->gridH())*property->gridH();
			//int y;
			switch(property->gridType()){
				case 1:
					entity_manager.create_block(Block(Vec2(x, y), Vec2(property->gridW(), property->gridH()), Vec4(property->gridR(), property->gridG(), property->gridB(), 1), property->gridBlockType()));
					break;
				case 2:
					entity_manager.create_block(BackgroundBlockStatic(Vec2(x, y), Vec2(property->gridW(), property->gridH()), Vec4(property->gridR(), property->gridG(), property->gridB(), 1), property->gridBlockType()));
					break;
				case 3:
					// this was supposed to be for parallax blocks. But you really don't need many of them
					entity_manager.create_coin(Coin(Vec2(x, y), Vec2(property->gridW(), property->gridH())));
					break;
				default:
					break;
			}
			return;
		}
		bool found_anything = false;
		bool already_equal = false;
		for(auto& ent : entities){
			// I made a spelling mistake while naming
			// intersect_point_pos...
			if(ent->interesect_point_pos( mousePos )){
				std::cout << "An entity was clicked" << std::endl;
				if(currentEnt == ent){
					already_equal=true;
					found_anything=true;
					break;
				}
				currentEnt = ent;
				found_anything=true;
				should_update=true;
				break;
			}
		}
		if( !found_anything ) currentEnt = nullptr;
		// so now I'm going to add a new feature based on "mode"
		// perform a dragging operation pretty much
		if(mode==SELECT_M){
		if(already_equal){
			currentEnt->getPos().x() = mapped.x-currentEnt->getSize().x()/2.0f;
			currentEnt->getPos().y() = mapped.y-currentEnt->getSize().y()/2.0f;
			should_update=true;
		}}else if( mode==DELETE_M ){
			delete_cur();
		}
	} 
}

#include <fstream>
void GLCanvas::save(std::string path){
	std::ofstream level_save(path);
	level_save << "player_spawn " << player.getPos().x() << " " << player.getPos().y() << std::endl;	
	level_save << "progressor " << entity_manager.get_progressor().getSize().x() << " " << entity_manager.get_progressor().getSize().y()
		   << " " << entity_manager.get_progressor().getPos().x() << " " << entity_manager.get_progressor().getPos().y()
		   << " " << entity_manager.get_progressor().getColor().x() << " " << entity_manager.get_progressor().getColor().y() << " " << entity_manager.get_progressor().getColor().z() << std::endl;
	for( size_t i = 0; i < lights.size(); ++i ){
		level_save << "light " << i << " " << lights[i].pos.x() << " " << lights[i].pos.y() << " " << lights[i].strength << " " << lights[i].color.r() << " " << lights[i].color.g() << " " << lights[i].color.b() << std::endl;
	}
	for( auto& coins : entity_manager.get_coins() ){
		level_save << "coin " << coins.getSize().x() << " " << coins.getSize().y() << " " << coins.getPos().x() << " " << coins.getPos().y() << std::endl;
	}
	for( auto& block : entity_manager.get_blocks() ){
		level_save << "block " << block.getSize().x() << " " << block.getSize().y() << " " << block.getPos().x() << " " << block.getPos().y() << " "
			   << block.getColor().x() << " " << block.getColor().y() << " " << block.getColor().z() << " " << block.get_type() << std::endl;
	}
	for( auto& jumping_enemy : entity_manager.get_jumping_enemies() ){
		//
	}
	for( auto& basic_enemy : entity_manager.get_basic_enemies() ){
		level_save << "enemy " << basic_enemy.getPos().x() << " " << basic_enemy.getPos().y() << " " << basic_enemy.getSize().x() << " " << basic_enemy.getSize().y() << " " << basic_enemy.getVelocity().x() << " " << basic_enemy.getVelocity().y() << " " << basic_enemy.getColor().x() << " " << basic_enemy.getColor().y() << " " << basic_enemy.getColor().z() << std::endl;
		//
	}
	for( auto& block : entity_manager.get_background_blocks() ){
		level_save << "bgrnd " << block.getSize().x() << " " << block.getSize().y() << " " << block.getPos().x() << " " << block.getPos().y() << " "
			   << block.scrollFactor.x() << " " << block.scrollFactor.y() <<" "<< block.getColor().x() << " " << block.getColor().y() << " " << block.getColor().z() << " " << block.get_type() << std::endl;
	}
	for( auto& block : entity_manager.get_background_static_blocks() ){
		level_save << "bgrnd-static " << block.getSize().x() << " " << block.getSize().y() << " " << block.getPos().x() << " " << block.getPos().y() << " "
			   << block.getColor().x() << " " << block.getColor().y() << " " << block.getColor().z() << " " << block.get_type() << std::endl;
	}
	for( auto& text : entity_manager.get_env_text() )	{
		level_save << text.pos.x() << " " << text.pos.y() << " " << text.color.x() << " " << text.color.y() << " " << text.color.z() << " " << text.scale << " " << text.str << std::endl;
	}
}
void GLCanvas::save(){
	std::string path = "C:\\DEFAULT_LEVEL_NAME.lvl";
	save(path);
}
void GLCanvas::copy_f(){
	if(currentEnt!=nullptr)
	copy = currentEnt;
}
void GLCanvas::paste(){
	if( copy != nullptr ){
//		std::cout << copy->magic << " : Magic Number" << std::endl;
		int& magic = copy->magic; // just to avoid typing a bit of text
		auto& bk_st_blocks = entity_manager.get_background_static_blocks();
		auto& bk_blocks = entity_manager.get_background_blocks();
		auto& blocks = entity_manager.get_blocks();
		auto& coins = entity_manager.get_coins();
		switch(magic){
			case PLAYER:
				break;
			case BLOCK:
				entity_manager.create_block(*(Block*)copy);
				currentEnt = &blocks.back();
				break;
			case BGRNDBLOCK:
				entity_manager.create_block(*(BackgroundBlock*)copy);
				currentEnt = &bk_blocks.back();
				break;
			case STBLOCK:
				entity_manager.create_block(*(BackgroundBlockStatic*)copy);
				currentEnt = &bk_st_blocks.back();
				break;
			case COIN:
				entity_manager.create_coin(*(Coin*)copy);
				currentEnt = &coins.back();
				break;
			default:
				std::cout << "OBJECT UNIDENTIFIABLE\n";
				break;
		}
// normal copy and paste actually keeps the object inside of the clipboard as I've just realized.
#ifdef CUT_PASTE_PASTE_STYLE
		copy = nullptr;
#endif
	}
}

void GLCanvas::delete_cur(){
	// check magic number for identification	
	if( currentEnt != nullptr ){
		int& magic = currentEnt->magic; // just to avoid typing a bit of text
		auto& bk_st_blocks = entity_manager.get_background_static_blocks();
		auto& bk_blocks = entity_manager.get_background_blocks();
		auto& blocks = entity_manager.get_blocks();
		auto& coins = entity_manager.get_coins();
		// if the number matches we loop through the appropriete
		// container and check if the addresses match. I know for these
		// classes they don't implement the == operator but pointers
		// always have it covered, and besides this is the one that makes the most 
		// sense.
		switch(magic){
			case PLAYER:
				wxMessageBox(wxT("You cannot delete the player."), wxT("Illegal Action"));
				break;
			case PROGRESSOR:
				wxMessageBox(wxT("You cannot delete the progressor. Merely transform it :)"), wxT("Illegal Action"));
				break;
			case BLOCK:
				for(int i = 0; i < blocks.size(); ++i){
					if(&blocks[i] == currentEnt){
						blocks.erase(blocks.begin()+i);
						break;
					}
				}
				break;
			case BGRNDBLOCK:
				for(int i = 0; i < bk_blocks.size(); ++i){
					if(&bk_blocks[i] == currentEnt){
						bk_blocks.erase(bk_blocks.begin()+i);
						break;
					}
				}
				break;
			case STBLOCK:
				for(int i = 0; i < bk_st_blocks.size(); ++i){
					if(&bk_st_blocks[i] == currentEnt){
						bk_st_blocks.erase(bk_st_blocks.begin()+i);
						break;
					}
				}
				break;
			case COIN:
				for(int i = 0; i < coins.size(); ++i){
					if(&coins[i] == currentEnt){
						coins.erase(coins.begin()+i);
						break;
					}
				}
				break;
			default:
				break;
		}
		currentEnt = nullptr;
	}
}

wxBEGIN_EVENT_TABLE( GLCanvas, wxGLCanvas )
	EVT_PAINT(GLCanvas::PaintScene)
	EVT_SIZE(GLCanvas::OnResize)
	EVT_MOUSE_EVENTS(GLCanvas::MouseEvents)
	EVT_KEY_DOWN(GLCanvas::KeyboardEvents)
wxEND_EVENT_TABLE()
