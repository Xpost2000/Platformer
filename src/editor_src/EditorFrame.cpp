#include "EditorFrame.h"
#include "PropertyPanel.h"
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
	wxImage::AddHandler( new wxPNGHandler );
	glAttributes.PlatformDefaults().Depth(24).DoubleBuffer().EndList();
	canvas = new GLCanvas(this, glAttributes, wxID_ANY, pos, size);	
	property = new PropertyPanel(this, wxID_ANY);
	wxImage select("textures\\select.png", wxBITMAP_TYPE_PNG);
	wxImage create("textures\\create.png", wxBITMAP_TYPE_PNG);
	wxImage erase("textures\\erase.png",   wxBITMAP_TYPE_PNG);
	wxImage open("textures\\folder.png",   wxBITMAP_TYPE_PNG);
	wxImage save("textures\\save.png",     wxBITMAP_TYPE_PNG);
	wxImage light("textures\\lighting.png",wxBITMAP_TYPE_PNG);
	wxImage parallax("textures\\parallax.png", wxBITMAP_TYPE_PNG);
	wxImage recenter("textures\\recenter.png", wxBITMAP_TYPE_PNG);
	std::cerr << "Loading texture assests" << std::endl;
	currentDir = wxGetCwd();
	CreateStatusBar(1);
	SetStatusText("Welcome to Letter X Editor!");
	tool = new wxToolBar(this, wxID_ANY);
	timer = new RenderTimer( canvas );
	vert = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hori = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *pane_sizer = new wxBoxSizer(wxHORIZONTAL);
	using namespace ConstantId::MainWindow;
	tool->AddTool(FileMenu_Open, "Open File", open, "Open a level file");
	tool->AddTool(FileMenu_Save, "Save File", save, "Save a level file");
	tool->AddSeparator();	
	tool->AddSeparator();	
	tool->AddTool(TBMenu_Select, "Select", select, "Put editor in select mode.");
	tool->AddTool(TBMenu_Create, "Create", create, "Put editor in create mode");
	tool->AddTool(TBMenu_Delete, "Erase",  erase, "Put editor in erase mode.");
	tool->AddSeparator();	
	tool->AddSeparator();	
	tool->AddTool(ViewMenu_Lighting, "Lighting", light, "Enable Lighting");
	tool->AddTool(ViewMenu_Recenter, "Recenter", recenter, "Center camera on player");
	tool->AddTool(ViewMenu_EnableParallax, "Parallax", parallax, "Enable parallax scrolling");	
	tool->Realize();
	std::cerr << "Toolbar creation" << std::endl;
	hori->Add(tool, 0, 0);
	hori->Add(new wxStaticText(this, wxID_ANY, " Main Toolbar(Substitute for menubar above.)"));
	hori->Fit(this);
	hori->SetSizeHints(this);
	pane_sizer->Add(canvas, 1, wxEXPAND|wxALL, 0);
	pane_sizer->Add(property, 1, wxEXPAND|wxRIGHT, 0);
	pane_sizer->Fit(this);
	pane_sizer->SetSizeHints(this);
	vert->Add(hori, 0, 0);
	vert->Add(pane_sizer, 2, wxEXPAND|wxALL);
	SetAutoLayout(true);
	SetSizer(vert);
	vert->Fit(this);
	vert->SetSizeHints(this);
	timer->Start(10);
	std::cerr << "Started program timer" << std::endl;
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
	std::cerr << "Creating menubar" << std::endl;

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
	std::cerr << "Camera recentered" << std::endl;
}
void EditorFrame::OnAbout( wxCommandEvent& ev ){
//	aboutDialog = new EditorAboutDialog( this );
	NOT_IMPLEMENTED_MB("The dialog is not finished.");
	std::cerr << "About dialog : Appears" << std::endl;
}
void EditorFrame::OnOpen( wxCommandEvent& ev ){
//	NOT_IMPLEMENTED_MB("A file dialog would appear( I could easily make one but it'd have to have features eh? )");
	wxFileDialog open_file( this, wxT("Open a Level File"),
		       	 	wxGetCwd(), "",
				"Level Files (*.map)|*.map", wxFD_OPEN);
	if(open_file.ShowModal() == wxID_OK){
		canvas->get_level() = Level(open_file.GetPath().ToStdString());	
		currentLevelPath = open_file.GetPath();
		std::cerr << "Loaded level" << std::endl;
	}else{
		return;
	}
}
void EditorFrame::RecenterCamera(){
	canvas->get_camera().RecenterPlayer(canvas->get_player());
}
void EditorFrame::OnLightingBox( wxCommandEvent& ev ){
	canvas->lighting_enabled() = !canvas->lighting_enabled();
	std::cerr << "Lighting has been toggled" << std::endl;
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
	std::cerr << "Saved level file(if is valid file)" << std::endl;
}
void EditorFrame::OnParallaxBox( wxCommandEvent& ev ){
	canvas->parallax_enabled() = !canvas->parallax_enabled();
	std::cerr << "Parallax Scrolling has been toggled" << std::endl;
}
void EditorFrame::OnCopy( wxCommandEvent& ev ){
	canvas->copy_f();
}
void EditorFrame::OnPaste( wxCommandEvent& ev ){
	canvas->paste();
}
void EditorFrame::OnIdle( wxIdleEvent& ev ){
	switch(canvas->get_mode()){
		case SELECT_M:
			SetStatusText("Editor Mode : Select");
			break;
		case DELETE_M:
			SetStatusText("Editor Mode : Delete");
			break;
		case CREATE_M:
			SetStatusText("Editor Mode : Create");
			break;
	}
}

void EditorFrame::OnTB_Select( wxCommandEvent& ev ){
	canvas->get_mode() = SELECT_M;
}
void EditorFrame::OnTB_Create( wxCommandEvent& ev ){
	canvas->get_mode() = CREATE_M;
}
void EditorFrame::OnTB_Delete( wxCommandEvent& ev ){
	canvas->get_mode() = DELETE_M;
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
	EVT_MENU( ConstantId::MainWindow::TBMenu_Select, EditorFrame::OnTB_Select )
	EVT_MENU( ConstantId::MainWindow::TBMenu_Create, EditorFrame::OnTB_Create )
	EVT_MENU( ConstantId::MainWindow::TBMenu_Delete, EditorFrame::OnTB_Delete )
	EVT_IDLE( EditorFrame::OnIdle )
wxEND_EVENT_TABLE()

