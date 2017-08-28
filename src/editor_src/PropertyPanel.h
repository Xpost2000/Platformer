#ifndef PROPERTY_PANE_H
#define PROPERTY_PANE_H
/*
 * I'm going to use panes because it might help organization.
 */
#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include "EditorFrame.h"
class PropertyPanel : public wxPanel{
	public:
		PropertyPanel( wxWindow* parent, wxWindowID id=wxID_ANY,
			       const wxPoint& pos=wxDefaultPosition,
			       const wxSize&  size=wxDefaultSize, 
			       long style=wxTAB_TRAVERSAL, 
			       const wxString& name=wxPanelNameStr);
		~PropertyPanel();
	private:
		// since this class is a friend of the editorframe
		// because I require some access to private members
		// that I don't feel like using the getters for...
		// Sue me :P
		EditorFrame* parent=nullptr;
};
#endif
