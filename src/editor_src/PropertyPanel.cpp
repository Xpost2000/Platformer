#include "PropertyPanel.h"

PropertyPanel::PropertyPanel(
			    wxWindow* parent,
			    wxWindowID id,
			    const wxPoint& pos,
			    const wxSize& size,
			    long style,
			    const wxString& name)
: wxPanel(parent, id, pos, size, style, name){
	wxStaticText* stuff = new wxStaticText(this, wxID_ANY,
					       "Sample Text");
	stuff->Show(true);
}

PropertyPanel::~PropertyPanel(){
}
