#ifndef EDITOR_FRAME_H
#define EDITOR_FRAME_H
#include <wx/wx.h>
#include "GLCanvas.h"
/*
 * This is going to be the window frame that contains everything for the window :)
 */
class EditorFrame : public wxFrame{
	public:
		EditorFrame(wxWindow* parent, wxWindowID id=wxID_ANY, const wxString &title= "Editor Window", const wxPoint &pos=wxDefaultPosition, const wxSize& size = wxDefaultSize);		
		wxGLCanvas* RetrieveCanvas() { return canvas; }
	private:
		wxGLAttributes glAttributes;
		GLCanvas* canvas;
};
#endif
