#include "GLCanvas.h"
#include "../Block.h"
#include <iostream>

GLCanvas::GLCanvas( wxWindow* parent, const wxGLAttributes& disp, wxWindowID id, const wxPoint & pos, const wxSize& size, long style )
: wxGLCanvas(parent, disp, id, pos, size, style){
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
	tm = std::make_shared<TextureManager>();
	tm->add_texture("test", "textures\\tiles.png", get_device());
	sb = std::make_shared<SpriteBatcher>(dev);
	// set up matrix and stuff
	projection = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f, -1.f, 1.f);
}

void GLCanvas::PaintScene( wxPaintEvent& pnt ){
	SetCurrent(*ctx_obj);
	wxPaintDC (this);
	dev->viewport(0, 0, viewPort_sz.x, viewPort_sz.y);
	dev->clearColor(0.0, 0.0, 0.1, 1.0);
	dev->clear(BufferClear::COLOR_BUFFER);
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
	ds->setTex(0);
	ds->setTextured(true);
	ds->setMatrices(projection, view);
	tm->get_tex("test")->bind();
	sb->draw(Vec2(300, 200), Vec4(Block::get_uv_from_type(BlockTypes::BasicBox)), Vec2(400, 400), Vec4(1.0));
	sb->draw(Vec2(100, 200), Vec4(Block::get_uv_from_type(BlockTypes::Box)), Vec2(200, 400), Vec4(0.4));
	sb->draw(Vec2(300, 200), Vec4(Block::get_uv_from_type(BlockTypes::Floor)), Vec2(400, 100), Vec4(0.2));
	sb->render();
	ds->unuse();
	
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