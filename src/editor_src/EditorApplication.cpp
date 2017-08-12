#include "EditorApplication.h"

/*
 * I include SDL and link it because I require SDL_Image for the ImageTexture class. Probably should've implemented it with FreeImage or something
 * but if I can get away with using on Library I suppose I should.
 */
bool EditorApplication::OnInit(){
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO); // for SDL_Surface presumably.
	IMG_Init(IMG_INIT_PNG);
	/*
	 * Alright I can procede with the other wxWidgets things.
	 */
	return true;
}

/*
 * This is so I can ensure the proper quiting of SDL.
 */ 
EditorApplication::~EditorApplication(){
	IMG_Quit();
	SDL_Quit();
}

/*
 * I'm going to let wxWidgets handle the main loop
 * since that's technically the only way to do it.
 */
IMPLEMENT_APP(EditorApplication)
