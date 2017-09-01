#ifndef CREATION_PANEL_H
#define CREATION_PANEL_H
#include<wx/wx.h>

class CreationPanel : public wxPanel{
	public:
		CreationPanel(wxWindow* parent, wxWindowID id=wxID_ANY,
			      const wxPoint& pos=wxDefaultPosition,
			      const wxSize& size=wxDefaultSize,
			      long style=wxTAB_TRAVERSAL,
			      const wxString& name=wxPanelNameStr);
		~CreationPanel();
	private:
};

#endif
