#include "GLCanvas.h"

GLCanvas::GLCanvas( wxWindow* parent, const wxGLAttributes& disp, wxWindowID id, const wxPoint & pos, const wxSize& size, long style )
: wxGLCanvas(parent, disp, id, pos, size, style){
	// I create two dummies to "work on"
	SDL_Window* dummy;
	gl_info_struct_t blank;
	// The original IDevice class was ment for SDL2 use mainly
	// other wise provided a wrapper that was typesafe for
	// OpenGL functions.
	dev = std::make_shared<GLDevice>(dummy, blank);
	ctx_obj = new wxGLContext(this);
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	glewExperimental=true;
	glewInit();
}

void GLCanvas::PaintScene( wxPaintEvent& pnt ){
	SetCurrent(*ctx_obj);
	wxPaintDC (this);
	dev->viewport(0, 0, viewPort_sz.x, viewPort_sz.y);
	dev->clearColor(1.0, 0.0, 0.0, 1.0);
	dev->clear(BufferClear::COLOR_BUFFER);
#define IMMEDIATE_MODE_VIEWPORT_TEST
#ifdef IMMEDIATE_MODE_VIEWPORT_TEST
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(0, 0.5);
	glEnd();
#endif
	SwapBuffers();
}

void GLCanvas::OnResize( wxSizeEvent& evnt ){
	SetSize(evnt.GetSize());
	viewPort_sz = evnt.GetSize();
}

wxBEGIN_EVENT_TABLE( GLCanvas, wxGLCanvas )
	EVT_PAINT(GLCanvas::PaintScene)
	EVT_SIZE(GLCanvas::OnResize)
wxEND_EVENT_TABLE()
