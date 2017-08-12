#ifndef WX_GL_CANVAS_H
#define WX_GL_CANVAS_H
#include <wx/wx.h>
#include "../GLDevice.h"
#include <wx/glcanvas.h>

/*
 * I'm this is going to render the game scene.
 * to paint the scene I'm probably going to store the game data
 * and render the data when it's sent.
 */
#include <memory>
class GLCanvas : public wxGLCanvas{
	public:
		GLCanvas( wxWindow* parent, const wxGLAttributes& disp, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0 );
		~GLCanvas(){}
		void PaintScene( wxPaintEvent& pnt );	
		void OnResize ( wxSizeEvent& evnt );

		const std::shared_ptr<IDevice>& get_device() { return dev; }
	private:
		wxGLContext* ctx_obj;
		std::shared_ptr<IDevice> dev;
		wxSize viewPort_sz;
		DECLARE_EVENT_TABLE()
};

#endif
