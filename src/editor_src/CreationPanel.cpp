#include "CreationPanel.h"
#include "EditorFrame.h"

// Alright so I was planning to make a more elaborate system
// but for now I'm just going to create a bunch of buttons
// and that's about it.

CreationPanel::CreationPanel( wxWindow* window, wxWindowID id,
	                      const wxPoint& pos, const wxSize& size,
			      long style, const wxString& name)
: wxPanel(window, id, pos, size, style, name), parent(static_cast<EditorFrame*>(window)){
	wxButton *b = new wxButton(this, 12300, "Create Block", wxPoint((size.x/2)-100, pos.y+100));
	wxButton *c = new wxButton(this, 12400, "Create Static Background Block", wxPoint((size.x/2)-100, pos.y+200));
	wxButton *d = new wxButton(this, 12500, "Create Parallax Background Block", wxPoint((size.x/2)-100, pos.y+300));
	wxButton* e = new wxButton(this, 12600, "Put Progressor at (Player Pos)", wxPoint((size.x/2)-100, pos.y+400));
}
CreationPanel::~CreationPanel(){
}

// it will spawn the most generic block ever.
// to be safe I will spawn all things at player position
void CreationPanel::OnCreateBlock(wxCommandEvent& ev){
	parent->canvas->get_em().create_block(Block(parent->canvas->get_player().getPos(), Vec2(100), Vec4(1), 2));
}
void CreationPanel::OnCreateSBlock(wxCommandEvent& ev){
	parent->canvas->get_em().create_block(BackgroundBlockStatic(parent->canvas->get_player().getPos(), Vec2(100), Vec4(1), 2));
}
void CreationPanel::OnCreatePBlock(wxCommandEvent& ev){
	parent->canvas->get_em().create_block(BackgroundBlock(parent->canvas->get_player().getPos(), Vec2(100), Vec4(1), Vec2(0), 2));
}
void CreationPanel::OnRecenterProgressor(wxCommandEvent& ev){
	parent->canvas->get_em().set_progressor(Progressor(parent->canvas->get_player().getPos(), Vec2(100, 100), Vec4(1)));
}
wxBEGIN_EVENT_TABLE(CreationPanel, wxPanel)
	EVT_BUTTON( 12300, CreationPanel::OnCreateBlock )
	EVT_BUTTON( 12400, CreationPanel::OnCreateSBlock )
	EVT_BUTTON( 12500, CreationPanel::OnCreatePBlock )
	EVT_BUTTON( 12600, CreationPanel::OnRecenterProgressor )
wxEND_EVENT_TABLE()
