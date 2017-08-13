#include "GLCanvas.h"
#include "../Block.h"
#include <iostream>

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
	tm = std::make_shared<TextureManager>();
	tm->add_texture("tiles", "textures\\tiles.png", get_device());
	tm->add_texture("player", "textures\\test_player.png", get_device());
	sb = std::make_shared<SpriteBatcher>(dev);
	// set up matrix and stuff
	projection = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f, -1.f, 1.f);
}

void GLCanvas::PaintScene( wxPaintEvent& pnt ){
	SetCurrent(*ctx_obj);
	wxPaintDC (this);
	if(!current.loaded){
		current.load(player, entity_manager, lights);
	}
	dev->viewport(0, 0, viewPort_sz.x, viewPort_sz.y);
	dev->clearColor(1.0, 1.0, 1.0, 1.0);
	dev->clear(BufferClear::COLOR_BUFFER);
	dev->enableAlpha();
//#define IMMEDIATE_MODE_VIEWPORT_TEST
#ifdef IMMEDIATE_MODE_VIEWPORT_TEST
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(0, 0.5);
	glEnd();
#endif
	ds->use();
	ds->setTextured(false);	
	ds->setMatrices(projection, view);
	ls->use();
	ls->setTex(0);
	ls->setTextured(true);
	ls->setProj(projection);
	ls->setView(view);
	// render the lights
	for(int i = 0; i < 10; ++i ){
		ls->setLight(i, lights[i]);
	}
	tm->get_tex("tiles")->bind();
	sb->draw(Vec2(-1000), Vec4(Block::get_uv_from_type(BlockTypes::FlatColor)), Vec2(12390120), Vec4(0.0, 0.0, 0.1, 1.0));
	// THE CAMERA DOESN'T EXIST SO BACKGROUND PROPS ARE NOT DRAWN
	entity_manager.draw_progressor(*sb);	
	entity_manager.draw_blocks(*sb);
	entity_manager.draw_jumping_enemies(*sb);
	entity_manager.draw_basic_enemies(*sb);
	tm->get_tex("player")->bind();
	sb->draw( player.getPos(), player.getUvs(), player.getSize(), Vec4(1.0f) );
	sb->render();
	ls->unuse();
	ds->use();
	sb->draw( player.getPos(), player.getUvs(), player.getSize(), Vec4(1.0f, 0.0, 0.0, 1.0) );
	sb->render(true);

	
	SwapBuffers();
}

void GLCanvas::OnResize( wxSizeEvent& evnt ){
	SetSize(evnt.GetSize());
	viewPort_sz = evnt.GetSize();
	projection = glm::ortho(0.0f, static_cast<float>(viewPort_sz.x), static_cast<float>(viewPort_sz.y), 0.0f, -1.f, 1.f);
}

wxBEGIN_EVENT_TABLE( GLCanvas, wxGLCanvas )
	EVT_PAINT(GLCanvas::PaintScene)
	EVT_SIZE(GLCanvas::OnResize)
wxEND_EVENT_TABLE()
