#ifndef EDITOR_FRAME_H
#define EDITOR_FRAME_H
#include <wx/wx.h>
#include "GLCanvas.h"
#include "RenderTimer.h"
#include "EditorAboutDialog.h"
/*
 * This is going to be the window frame that contains everything for the window :)
 */
class EditorFrame : public wxFrame{
	public:
		EditorFrame(wxWindow* parent, wxWindowID id=wxID_ANY, const wxString &title= "Editor Window", const wxPoint &pos=wxDefaultPosition, const wxSize& size = wxDefaultSize);		
		~EditorFrame(){ delete timer; }
		wxGLCanvas* RetrieveCanvas() { return canvas; }	
	protected:
		// Event Handlers
		void OnQuit( wxCommandEvent& ev );
		void OnClose ( wxCloseEvent& ev );
		void OnRecenter( wxCommandEvent& ev );
		void OnLightingBox( wxCommandEvent& ev );
		void OnAbout( wxCommandEvent& ev );
		void OnOpen( wxCommandEvent& ev );
	private:
		void RecenterCamera();
		wxGLAttributes glAttributes;
		GLCanvas* canvas;
	private:
		// Timer
		RenderTimer* timer;
		// Menu Bar.
		wxMenuBar* topBar;
		wxMenu* file;
		wxMenu* view;
		wxMenu* help;
		// Dialogs.
		EditorAboutDialog* aboutDialog;
		DECLARE_EVENT_TABLE()
};
#endif
