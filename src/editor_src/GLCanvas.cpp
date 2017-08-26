#include "GLCanvas.h"
#include "../Block.h"
#include <iostream>

Vec2 mousePos;

GLCanvas::GLCanvas( wxWindow* parent, const wxGLAttributes& disp, wxWindowID id, const wxPoint & pos, const wxSize& size, long style )
: wxGLCanvas(parent, disp, id, pos, size, style){
	player=Player(Vec2(300), Vec2(73,73), Vec2(100), Vec4(1.0));
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
	tm->add_texture("tiles", "textures\\tiles.png", get_device());
	tm->add_texture("player", "textures\\test_player.png", get_device());
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
	entity_manager.draw_background_props( camera.getPos(), *sb );
	entity_manager.draw_progressor(*sb);	
	entity_manager.draw_blocks(*sb);
	entity_manager.draw_jumping_enemies(*sb);
	entity_manager.draw_basic_enemies(*sb);
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
}

void GLCanvas::MouseEvents( wxMouseEvent& ev ){
	const wxPoint center = wxPoint(viewPort_sz.x/2, viewPort_sz.y/2);
	const wxPoint curPos = ScreenToClient(wxGetMousePosition());
	const wxPoint mouseDelta = curPos - center;
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
		entities.push_back ( &entity_manager.get_progressor() );
		entities.push_back ( &player );
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
				break;
			}
		}
		// This is to imitate a lot of more mature programs that allow selection
		// in which if you don't hit anything like white space. It is deselected.
		if( !found_anything ) currentEnt = nullptr;
		// perform a dragging operation pretty much
		if(already_equal){
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
	for( auto& block : entity_manager.get_blocks() ){
		level_save << "block " << block.getSize().x() << " " << block.getSize().y() << " " << block.getPos().x() << " " << block.getPos().y() << " "
			   << block.getColor().x() << " " << block.getColor().y() << " " << block.getColor().z() << " " << block.get_type() << std::endl;
	}
	for( auto& jumping_enemy : entity_manager.get_jumping_enemies() ){
		//
	}
	for( auto& basic_enemy : entity_manager.get_basic_enemies() ){
		//
	}
	for( auto& block : entity_manager.get_background_blocks() ){
		level_save << "block " << block.getSize().x() << " " << block.getSize().y() << " " << block.getPos().x() << " " << block.getPos().y() << " "
			   << block.scrollFactor.x() << " " << block.scrollFactor.y() <<" "<< block.getColor().x() << " " << block.getColor().y() << " " << block.getColor().z() << " " << block.get_type() << std::endl;
	}
	for( auto& block : entity_manager.get_background_static_blocks() ){
		level_save << "bgrnd-static " << block.getSize().x() << " " << block.getSize().y() << " " << block.getPos().x() << " " << block.getPos().y() << " "
			   << block.getColor().x() << " " << block.getColor().y() << " " << block.getColor().z() << std::endl;//" " << block.get_type() << std::endl;
	}
	
}
void GLCanvas::save(){
	std::string path = "C:\\DEFAULT_LEVEL_NAME.lvl";
	save(path);
}

wxBEGIN_EVENT_TABLE( GLCanvas, wxGLCanvas )
	EVT_PAINT(GLCanvas::PaintScene)
	EVT_SIZE(GLCanvas::OnResize)
	EVT_MOUSE_EVENTS(GLCanvas::MouseEvents)
	EVT_KEY_DOWN(GLCanvas::KeyboardEvents)
wxEND_EVENT_TABLE()
