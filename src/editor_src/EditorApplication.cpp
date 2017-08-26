#include "EditorApplication.h"
#include "IDConstants.h"

/*
 * I include SDL and link it because I require SDL_Image for the ImageTexture class. Probably should've implemented it with FreeImage or something
 * but if I can get away with using on Library I suppose I should.
 */
bool EditorApplication::OnInit(){
	/*
	 * I don't want this to potentially hog resources and besides
	 * there is no need for more than one copy at a time.
	 */
	if( access( ".lockfile", F_OK ) != -1 ){
		wxMessageBox( wxT("Error : More than one instance being run"), wxT("There is more than one instance"), wxICON_INFORMATION );
		exit(0);
		return false;
	}else{
	lock = fopen(".lockfile", "w");
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO); // for SDL_Surface presumably.
	IMG_Init(IMG_INIT_PNG);
	mainWindow = new EditorFrame(NULL, ConstantId::MainWindow_ID, "Editor Window Prototype", wxDefaultPosition, wxSize(1000, 730));
	mainWindow->Show(true);
	/*
	 * Alright I can procede with the other wxWidgets things.
	 */
	atexit(SDL_Quit);
	atexit(IMG_Quit);
	}
	return true;
}

/*
 * This is so I can ensure the proper quiting of SDL.
 */ 
EditorApplication::~EditorApplication(){
	fclose(lock);
	remove(".lockfile");
}

/*
 * I'm going to let wxWidgets handle the main loop
 * since that's technically the only way to do it.
 */
IMPLEMENT_APP(EditorApplication)
