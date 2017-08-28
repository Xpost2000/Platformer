#include "PropertyPanel.h"

PropertyPanel::PropertyPanel(
			    wxWindow* parent,
			    wxWindowID id,
			    const wxPoint& pos,
			    const wxSize& size,
			    long style,
			    const wxString& name)
: wxPanel(parent, id, pos, size, style, name), parent(static_cast<EditorFrame*>(parent)){
	sz = size;
	properties = new wxPropertyGrid(this, -1, pos, size);
	properties->Append( new wxPropertyCategory(wxT("All Properties")));
	properties->Append( new wxPropertyCategory(wxT("Position")) );
	PositionX = properties->Append( new wxFloatProperty("X", "X", 0) );
	PositionY = properties->Append( new wxFloatProperty("Y", "Y", 0));
	properties->Show(true);
	timer = new GridTimer(this);
	timer->Start(10);
}
/*
 * Essentially I make a few preset property grids
 * and swap pointers with the current one if the magic number is
 * different.
 *
 * either that or I just reconstruct it based on certain things.
 * for now I'll pick the reconstruction route.
 *
 * EDIT: Alright you know what. I'm going to do this.
 * I'm going to make every possible property visible.
 * But enable or disable them based on if it is usable.
 */
void PropertyPanel::IdleHandler( ){
	Entity* ptr = parent->canvas->get_current();
	if(ptr!=nullptr){
		PositionX->SetValue( wxVariant(ptr->getPos().x()) );
		PositionY->SetValue( wxVariant(ptr->getPos().y()) );
	}
}

PropertyPanel::~PropertyPanel(){
	delete timer;
}

wxBEGIN_EVENT_TABLE( PropertyPanel, wxPanel )
//	EVT_IDLE( PropertyPanel::IdleHandler )
wxEND_EVENT_TABLE()
