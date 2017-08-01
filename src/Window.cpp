#include "Window.h"

void Window::set_fullscreen(bool val){
	fullscreen = val;
}
void Window::set_should_close(bool val){
	shld_close = val;
}
void Window::set_title(const char* title){
	this->title = std::string(title);
}
const bool Window::should_close() const{
	return shld_close;
}
void Window::set_dimensions(int w, int h){
	this->w = w;
	this->h = h;
}
void Window::set_vsync(bool val){
	vsync = val;
}
void Window::spawn(){
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w , h , flags);
}
void Window::update(){
	SDL_SetWindowTitle(window, title.c_str());
	SDL_SetWindowSize(window, w, h);	
}
void Window::refresh(){
	SDL_GL_SetSwapInterval(vsync);
	SDL_GL_SwapWindow(window);
}
