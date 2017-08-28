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
	properties->Append( new wxPropertyCategory(wxT("Size")) );
	SizeX = properties->Append( new wxFloatProperty("Width", "Width", 0) );
	SizeY = properties->Append( new wxFloatProperty("Height", "Height", 0) );
	properties->Append( new wxPropertyCategory(wxT("Color")) );
	// I should be using the color picker but since the logistics of working
	// with a crapton of conversions doesn't really seem like a good idea for
	// me again I'm going to do a one by one section creation.
	R = properties->Append( new wxFloatProperty("R", "R", 0) );
	G = properties->Append( new wxFloatProperty("G", "G", 0) );
	B = properties->Append( new wxFloatProperty("B", "B", 0) );
	scroll_category = properties->Append( new wxPropertyCategory(wxT("Scroll Factors")) );
	scrollX = properties->Append( new wxFloatProperty("Scroll X", "Scroll X", 0) );
	scrollY = properties->Append( new wxFloatProperty("Scroll Y", "Scroll Y", 0) );
	scroll_category->Enable(false);
	
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
 *
 * For now I'm going to focus on being able to display the attributes
 * I'll focus on getting it to be "edittable" tomorrow
 */
void PropertyPanel::IdleHandler( ){
	Entity* ptr = parent->canvas->get_current();
	if(ptr!=nullptr){
		PositionX->SetValue( wxVariant(ptr->getPos().x()) );
		PositionY->SetValue( wxVariant(ptr->getPos().y()) );
		SizeX->SetValue( wxVariant(ptr->getSize().x()));
		SizeY->SetValue( wxVariant(ptr->getSize().y()));

		R->SetValue( wxVariant(ptr->getColor().r()));
		G->SetValue( wxVariant(ptr->getColor().g()));
		B->SetValue( wxVariant(ptr->getColor().b()));
		if(ptr->magic == BGRNDBLOCK){
			scroll_category->Enable(true);
			BackgroundBlock* cast = (BackgroundBlock*)ptr;
			scrollX->SetValue( wxVariant(cast->scrollFactor.x()) );
			scrollY->SetValue( wxVariant(cast->scrollFactor.y()) );
		}else { scroll_category->Enable(false); }
	}
}

PropertyPanel::~PropertyPanel(){
	delete timer;
}

wxBEGIN_EVENT_TABLE( PropertyPanel, wxPanel )
//	EVT_IDLE( PropertyPanel::IdleHandler )
wxEND_EVENT_TABLE()
