#include "EditorAboutDialog.h"

EditorAboutDialog::EditorAboutDialog( wxWindow* parent,
	       			      const wxPoint& pos,
				      long style)
: wxDialog(parent, wxID_ANY, "About Letter X Editor", pos, wxSize(300, 710), style){
	Show( true );
	// sample text
	// brit spelling.
	CentreOnParent();
}

EditorAboutDialog::~EditorAboutDialog(){
}

wxBEGIN_EVENT_TABLE( EditorAboutDialog, wxDialog )
wxEND_EVENT_TABLE()
