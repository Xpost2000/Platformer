#include "PropertyPanel.h"
#include "EditorFrame.h"

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
	properties->Append( new wxPropertyCategory(wxT("All Properties + Lights")));
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
	blockType = properties->Append( new wxIntProperty("Block Type", "Block Type", 0) );
	scroll_category = properties->Append( new wxPropertyCategory(wxT("Scroll Factors")) );
	scrollX = properties->Append( new wxFloatProperty("Scroll X", "Scroll X", 0) );
	scrollY = properties->Append( new wxFloatProperty("Scroll Y", "Scroll Y", 0) );
	scroll_category->Enable(false);
	properties->Append( new wxPropertyCategory(wxT("Light Properties")) );
	lIndex = properties->Append( new wxIntProperty("Light Index", "Light Index", current_index));
	lPower = properties->Append( new wxFloatProperty("Light Power", "Light Power", 0) );
	lR = properties->Append( new wxFloatProperty("Light R", "Light R", 0) );
	lG = properties->Append( new wxFloatProperty("Light G", "Light G", 0) );
	lB = properties->Append( new wxFloatProperty("Light B", "Light B", 0) );
	lX = properties->Append( new wxFloatProperty("Light X", "Light X", 0) );
	lY = properties->Append( new wxFloatProperty("Light Y", "Light Y", 0) );
	properties->Append( new wxPropertyCategory(wxT("Creation Mode Properties")) );
	grid_type = properties->Append( new wxIntProperty("Block Type(Grid)", "Block Type For Grid", 1) );
	
	grid_w = properties->Append( new wxIntProperty("Grid Width", "Grid Width", 10) );
	grid_h = properties->Append( new wxIntProperty("Grid Height", "Grid Height", 10) );
	grid_block_type = properties->Append( new wxIntProperty("Grid Actual Block type", "Actual Block Type", 1) );
	grid_r = properties->Append( new wxFloatProperty("Grid R", "Grid R", 0) );
	grid_g = properties->Append( new wxFloatProperty("Grid G", "Grid G", 0) );
	grid_b = properties->Append( new wxFloatProperty("Grid B", "Grid B", 0) );



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
	// technically speaking ptr is not going to work.
	int as_int = static_cast<int>(blockType->GetValue().GetLong());
	as_int = std::max(1, as_int);
	as_int = std::min(16, as_int);
	if(parent->canvas->get_current() == nullptr){
		PositionX->SetValue( wxVariant(0) ); PositionX->Enable(false);
		PositionY->SetValue( wxVariant(0) ); PositionY->Enable(false);
		SizeX->SetValue( wxVariant(0) ); SizeX->Enable(false);
		SizeY->SetValue( wxVariant(0) ); SizeY->Enable(false);
		R->SetValue( wxVariant(0) ); R->Enable(false);
		G->SetValue( wxVariant(0) ); G->Enable(false);
		B->SetValue( wxVariant(0) ); B->Enable(false);
		scroll_category->Enable(false);
		scrollX->SetValue( wxVariant(0) ); scrollX->Enable(false);
		scrollY->SetValue( wxVariant(0) ); scrollY->Enable(false);
		blockType->SetValue( wxVariant(1) ); blockType->Enable(false);
	}
	if( lIndex->GetValue().GetLong() != current_index ){
	current_index = static_cast<int>(lIndex->GetValue().GetLong());
	current_index = std::max(0, current_index);
	current_index = std::min(9, current_index);
	lIndex->SetValue( wxVariant(current_index) );
	Light& light = parent->canvas->get_lights()[current_index];
	lPower->SetValue( wxVariant(light.strength) );
	lR->SetValue( wxVariant(light.color.r()) );
	lG->SetValue( wxVariant(light.color.g()) );
	lB->SetValue( wxVariant(light.color.b()) );
	lX->SetValue( wxVariant(light.pos.x()) );
	lY->SetValue( wxVariant(light.pos.y()) );
	}
	// sadly lights are pretty odd so I have to update it when entities get updated :(
	if(ptr!=nullptr && parent->canvas->should_update){
		PositionX->SetValue( wxVariant(ptr->getPos().x()) ); PositionX->Enable(true);
		PositionY->SetValue( wxVariant(ptr->getPos().y()) ); PositionY->Enable(true);
		if(ptr->magic != PLAYER){
		SizeX->SetValue( wxVariant(ptr->getSize().x())); SizeX->Enable(true);
		SizeY->SetValue( wxVariant(ptr->getSize().y())); SizeY->Enable(true);
		R->SetValue( wxVariant(ptr->getColor().r())); R->Enable(true);
		G->SetValue( wxVariant(ptr->getColor().g())); G->Enable(true);
		B->SetValue( wxVariant(ptr->getColor().b())); B->Enable(true);
		if(ptr->magic != PROGRESSOR){
		Block* cast = (Block*)ptr;
		blockType->SetValue( wxVariant(cast->get_type()) );
		blockType->Enable(true);
		}
		}
		if(ptr->magic == BGRNDBLOCK){
			scroll_category->Enable(true);
			BackgroundBlock* cast = (BackgroundBlock*)ptr;
			scrollX->SetValue( wxVariant(cast->scrollFactor.x()) ); scrollX->Enable(true);
			scrollY->SetValue( wxVariant(cast->scrollFactor.y()) ); scrollY->Enable(true);
		}else { scroll_category->Enable(false); }

	} else if ( ptr!=nullptr && parent->canvas->should_update==false ){
		ptr->getPos().x()=PositionX->GetValue().GetDouble();
		ptr->getPos().y()=PositionY->GetValue().GetDouble();
		if(ptr->magic != PLAYER){
		ptr->getSize().x()=SizeX->GetValue().GetDouble();
		ptr->getSize().y()=SizeY->GetValue().GetDouble();
		ptr->getColor().r()=R->GetValue().GetDouble();
		ptr->getColor().g()=G->GetValue().GetDouble();
		ptr->getColor().b()=B->GetValue().GetDouble();
		Block* cast = (Block*)ptr;
		cast->get_type() = as_int;
		}
		if(ptr->magic == BGRNDBLOCK){
			BackgroundBlock* cast = (BackgroundBlock*)ptr;
			cast->scrollFactor.x() = scrollX->GetValue().GetDouble();
			cast->scrollFactor.y() = scrollY->GetValue().GetDouble();
		}
		update_cur_light();
	} else if ( parent->canvas->should_update==false  ){
		update_cur_light();
	}
}

void PropertyPanel::update_cur_light(){
	Light& light = parent->canvas->get_lights()[current_index];
	light.strength = lPower->GetValue().GetDouble();
	light.color.r() = lR->GetValue().GetDouble();
	light.color.g() = lG->GetValue().GetDouble();
	light.color.b() = lB->GetValue().GetDouble();
	light.pos.x() = lX->GetValue().GetDouble();
	light.pos.y() = lY->GetValue().GetDouble();

}

PropertyPanel::~PropertyPanel(){
	delete timer;
}

wxBEGIN_EVENT_TABLE( PropertyPanel, wxPanel )
//	EVT_IDLE( PropertyPanel::IdleHandler )
wxEND_EVENT_TABLE()
