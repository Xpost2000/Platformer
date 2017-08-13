#include "EditorFrame.h"
#include "DebugMacro.h"
#include "IDConstants.h"

/*
 * This constructor only handles creation everything else
 * is handled on it's own events.
 */
EditorFrame::EditorFrame(wxWindow* parent, wxWindowID id,
			 const wxString& title,
			 const wxPoint& pos,
			 const wxSize& size)
: wxFrame(parent, id, title, pos, size){
	glAttributes.PlatformDefaults().Depth(24).DoubleBuffer().EndList();
	canvas = new GLCanvas(this, glAttributes);	
	CreateStatusBar(1);
	SetStatusText("Letter X Game Editor prototype/alpha");
	timer = new RenderTimer( RetrieveCanvas() );
	timer->Start(10);
	/*
	 * I'm going to now construct the menu bar.
	 */
	topBar = new wxMenuBar();
	// Now I construct the other sub menus
	file = new wxMenu("File");
	view = new wxMenu("View");
	help = new wxMenu("Help");

	file->Append( ConstantId::MainWindow::FileMenu_Open, "Open an existing level\tAlt-O", "Opens a existing level file." );
	file->Append( wxID_EXIT, "Exit", "Quit the program" );
	view->Append( ConstantId::MainWindow::ViewMenu_Recenter, "Recenter on Player", "Recenter the camera onto the player" );
	help->Append( ConstantId::MainWindow::HelpMenu_About, "About\tF1", "" );


	// now let's append them to the menu bar so they work
	topBar->Append(file, "File");
	topBar->Append(view, "View");
	topBar->Append(help, "Help");

	SetMenuBar(topBar);
}

void EditorFrame::OnQuit( wxCommandEvent& ev ){
	timer->Stop();
	Close();
}
void EditorFrame::OnRecenter( wxCommandEvent& ev ){
	NOT_IMPLEMENTED_MB("The camera would be recentered(if it existed)");
}
void EditorFrame::OnAbout( wxCommandEvent& ev ){
	NOT_IMPLEMENTED_MB("An about dialog would appear.");
}
void EditorFrame::OnOpen( wxCommandEvent& ev ){
	NOT_IMPLEMENTED_MB("A file dialog would appear( I could easily make one but it'd have to have features eh? )");
}
// Declare the Event Table
wxBEGIN_EVENT_TABLE(EditorFrame, wxFrame)
	EVT_MENU( wxID_EXIT, EditorFrame::OnQuit )
	EVT_MENU( ConstantId::MainWindow::ViewMenu_Recenter, EditorFrame::OnRecenter )
	EVT_MENU( ConstantId::MainWindow::HelpMenu_About, EditorFrame::OnAbout )
	EVT_MENU( ConstantId::MainWindow::FileMenu_Open, EditorFrame::OnOpen)
wxEND_EVENT_TABLE()

