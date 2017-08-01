#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>
#include <string>
class Window{
	public:
		Window(int w, int h, std::string title, bool fullscreen=false): w(w), h(h), title(title), fullscreen(fullscreen){
			if(fullscreen){ flags |= SDL_WINDOW_FULLSCREEN; }
		}
		Window(const Window&) = delete;
		~Window(){
			SDL_DestroyWindow(window);
		}
		// most of the setting functions only work before creation
		void set_fullscreen(bool);
		void set_should_close(bool);
		void set_title(const char*);
		void set_vsync(bool);
		void set_dimensions(int , int );
		const bool should_close() const;
		void spawn();
		void update();
		void refresh();
		SDL_Window* get_handle() { return window; }
	private:
		std::string title;
		bool vsync;
		uint32_t flags=SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL;
		int w, h;
		bool shld_close=false;
		bool fullscreen=false;
		SDL_Window* window = nullptr;
};
#endif 
