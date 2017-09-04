#ifndef CREATION_PANEL_H
#define CREATION_PANEL_H
#include<wx/wx.h>

class EditorFrame;
class CreationPanel : public wxPanel{
	friend class EditorFrame;
	public:
		CreationPanel(wxWindow* parent, wxWindowID id=wxID_ANY,
			      const wxPoint& pos=wxDefaultPosition,
			      const wxSize& size=wxDefaultSize,
			      long style=wxTAB_TRAVERSAL,
			      const wxString& name=wxPanelNameStr);
		~CreationPanel();
		void OnCreateBlock(wxCommandEvent& ev);
		void OnCreateSBlock(wxCommandEvent& ev);
		void OnCreatePBlock(wxCommandEvent& ev);
		void OnRecenterProgressor(wxCommandEvent& ev);
	private:
	EditorFrame* parent;
	wxDECLARE_EVENT_TABLE();
};

#endif
