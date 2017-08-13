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
	protected:
		// Event Handlers
		void OnQuit( wxCommandEvent& ev );
		void OnRecenter( wxCommandEvent& ev );
		void OnAbout( wxCommandEvent& ev );
	private:
		wxGLAttributes glAttributes;
		GLCanvas* canvas;
	private:
		// Menu Bar.
		wxMenuBar* topBar;
		wxMenu* file;
		wxMenu* view;
		wxMenu* help;
	DECLARE_EVENT_TABLE()
};
#endif
