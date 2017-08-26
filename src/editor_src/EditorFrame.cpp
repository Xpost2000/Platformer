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
	canvas = new GLCanvas(this, glAttributes, wxID_ANY, pos, size);	
	currentDir = wxGetCwd();
	CreateStatusBar(1);
	SetStatusText("Letter X Game Editor prototype/beta");
	timer = new RenderTimer( canvas );
	timer->Start(10);
	/*
	 * I'm going to now construct the menu bar.
	 */
	topBar = new wxMenuBar();
	// Now I construct the other sub menus
	file = new wxMenu("File");
	edit = new wxMenu("Edit");
	view = new wxMenu("View");
	help = new wxMenu("Help");

	file->Append( ConstantId::MainWindow::FileMenu_Open, "Open an existing level\tAlt-O", "Opens a existing level file." );
	file->Append( ConstantId::MainWindow::FileMenu_Save, "Save a level to a file\tCtrl-S", "Save a level to a file");
	file->Append( ConstantId::MainWindow::FileMenu_Details, "Level Details", "Recieve a summary of all entities on the map.");
	file->Append( wxID_EXIT, "Exit", "Quit the program" );
//	edit->Append( ConstantId::MainWindow::EditMenu_Test, "Test map ingame \tAlt-P", "Test currently opened map ingame");
	edit->Append( ConstantId::MainWindow::EditMenu_Copy, "Copy\tCtrl-C");
	edit->Append( ConstantId::MainWindow::EditMenu_Paste, "Paste\tCtrl-V");
	view->Append( ConstantId::MainWindow::ViewMenu_Recenter, "Recenter on Player\tAlt-C", "Recenter the camera onto the player" );
	view->AppendCheckItem( ConstantId::MainWindow::ViewMenu_Lighting, "Enable Lighting\tAlt-L", "" );
	view->AppendCheckItem( ConstantId::MainWindow::ViewMenu_EnableParallax, "Enable Parallax Scorlling\tAlt-P" );
	help->Append( ConstantId::MainWindow::HelpMenu_About, "About\tF1", "" );


	// now let's append them to the menu bar so they work
	topBar->Append(file, "File");
	topBar->Append(edit, "Edit");
	topBar->Append(view, "View");
	topBar->Append(help, "Help");

	SetMenuBar(topBar);
}

void EditorFrame::OnQuit( wxCommandEvent& ev ){
	timer->Stop();
	Close();
}
void EditorFrame::OnRecenter( wxCommandEvent& ev ){
//	NOT_IMPLEMENTED_MB("The camera would be recentered(if it existed)");
	RecenterCamera();
}
void EditorFrame::OnAbout( wxCommandEvent& ev ){
//	aboutDialog = new EditorAboutDialog( this );
	NOT_IMPLEMENTED_MB("The dialog is not finished.");
}
void EditorFrame::OnOpen( wxCommandEvent& ev ){
//	NOT_IMPLEMENTED_MB("A file dialog would appear( I could easily make one but it'd have to have features eh? )");
	wxFileDialog open_file( this, wxT("Open a Level File"),
		       	 	wxGetCwd(), "",
				"Level Files (*.map)|*.map", wxFD_OPEN);
	if(open_file.ShowModal() == wxID_OK){
		canvas->get_level() = Level(open_file.GetPath().ToStdString());	

		currentLevelPath = open_file.GetPath();
	}else{
		return;
	}
}
void EditorFrame::RecenterCamera(){
	canvas->get_camera().RecenterPlayer(canvas->get_player());
}
void EditorFrame::OnLightingBox( wxCommandEvent& ev ){
	canvas->lighting_enabled() = view->IsChecked( ConstantId::MainWindow::ViewMenu_Lighting );
}
void EditorFrame::OnTestMap( wxCommandEvent& ev ){
	wxExecute(currentDir+"/Game.exe -fl " + currentLevelPath + " -res 700 500 ");
}
void EditorFrame::OnDetails( wxCommandEvent& ev ){
	NOT_IMPLEMENTED_MB("TODO Feature");
}
void EditorFrame::OnSaveLevel( wxCommandEvent& ev ) {
//	NOT_IMPLEMENTED_MB("TODO FEATURE");
	canvas->save( currentLevelPath.ToStdString() );
}
void EditorFrame::OnParallaxBox( wxCommandEvent& ev ){
	canvas->parallax_enabled() = view->IsChecked ( ConstantId::MainWindow::ViewMenu_EnableParallax );
}
void EditorFrame::OnCopy( wxCommandEvent& ev ){
	canvas->copy_f();
}
void EditorFrame::OnPaste( wxCommandEvent& ev ){
	canvas->paste();
}
// Declare the Event Table
wxBEGIN_EVENT_TABLE(EditorFrame, wxFrame)
	EVT_MENU( wxID_EXIT, EditorFrame::OnQuit )
	EVT_MENU( ConstantId::MainWindow::ViewMenu_EnableParallax, EditorFrame::OnParallaxBox)
	EVT_MENU( ConstantId::MainWindow::ViewMenu_Recenter, EditorFrame::OnRecenter )
	EVT_MENU( ConstantId::MainWindow::HelpMenu_About, EditorFrame::OnAbout )
	EVT_MENU( ConstantId::MainWindow::FileMenu_Open, EditorFrame::OnOpen)
	EVT_MENU( ConstantId::MainWindow::ViewMenu_Lighting, EditorFrame::OnLightingBox)
//	EVT_MENU( ConstantId::MainWindow::EditMenu_Test, EditorFrame::OnTestMap )	 
	EVT_MENU( ConstantId::MainWindow::FileMenu_Details, EditorFrame::OnDetails )
	EVT_MENU( ConstantId::MainWindow::FileMenu_Save, EditorFrame::OnSaveLevel )
	EVT_MENU( ConstantId::MainWindow::EditMenu_Copy, EditorFrame::OnCopy )
	EVT_MENU( ConstantId::MainWindow::EditMenu_Paste, EditorFrame::OnPaste )
wxEND_EVENT_TABLE()

