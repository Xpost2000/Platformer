#ifndef EDITOR_APPLICATION_WX
#define EDITOR_APPLICATION_WX
#define SDL_MAIN_HANDLED // prevent SDL2 from handling the main loop and thus prevent this conflict of wxWidgets + SDL2.
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
/*
 * I'm creating the editor using wxWidgets.
 */
#include <wx/wx.h>
#include "GLCanvas.h"
#include "RenderTimer.h"
class EditorApplication : public wxApp{
	public:
		virtual bool OnInit();
		~EditorApplication();
		/*
		 * The other functions should be inherited
		 * from the wxApp and the main loop should
		 * handle itself approprietely.
		 */
	private:
		GLCanvas* main_canvas;
		RenderTimer* timer;
		wxFrame* test_window;
};
DECLARE_APP(EditorApplication)
#endif
