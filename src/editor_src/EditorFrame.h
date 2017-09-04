#ifndef EDITOR_FRAME_H
#define EDITOR_FRAME_H
#include <wx/wx.h>
#include "GLCanvas.h"
#include "RenderTimer.h"
#include "EditorAboutDialog.h"
/*
 * This is going to be the window frame that contains everything for the window :)
 */
class PropertyPanel;
class CreationPanel;
class EditorFrame : public wxFrame{
	public:
		friend class PropertyPanel;
		friend class CreationPanel;
		friend class GLCanvas;
		EditorFrame(wxWindow* parent, wxWindowID id=wxID_ANY, const wxString &title= "Editor Window", const wxPoint &pos=wxDefaultPosition, const wxSize& size = wxDefaultSize);		
		~EditorFrame(){ delete timer; }
		GLCanvas* RetrieveCanvas() { return canvas; }	
	protected:
		// Event Handlers
		void OnQuit( wxCommandEvent& ev );
		void OnClose ( wxCloseEvent& ev );
		void OnRecenter( wxCommandEvent& ev );
		void OnTestMap( wxCommandEvent& ev );
		void OnLightingBox( wxCommandEvent& ev );
		void OnParallaxBox ( wxCommandEvent& ev );
		void OnSaveLevel( wxCommandEvent& ev );
		void OnSaveAs( wxCommandEvent& ev );
		void OnCopy( wxCommandEvent& ev );
		void OnPaste( wxCommandEvent& ev );
		void OnAbout( wxCommandEvent& ev );
		void OnDetails( wxCommandEvent& ev );
		void OnOpen( wxCommandEvent& ev );
		void OnIdle( wxIdleEvent& ev );
		void OnTB_Select( wxCommandEvent& ev );
		void OnTB_Create( wxCommandEvent& ev );
		void OnTB_Delete( wxCommandEvent& ev );
	private:
		void RecenterCamera();
		wxGLAttributes glAttributes;
		GLCanvas* canvas;
		PropertyPanel* property;
		CreationPanel* creation;
	private:
		bool file_open=false;
		// Timer
		RenderTimer* timer;
		// Menu Bar.
		wxBoxSizer* vert;
		wxToolBar* tool;
		wxMenuBar* topBar;
		wxMenu* file;
		wxMenu* edit;
		wxMenu* view;
		wxMenu* help;
		wxString currentDir;
		wxString currentLevelPath;
		// Dialogs.
		EditorAboutDialog* aboutDialog;
		DECLARE_EVENT_TABLE()
};
#endif
