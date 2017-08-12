#include "RenderTimer.h"

RenderTimer::RenderTimer(wxGLCanvas* ptr):
ptr(ptr), wxTimer(){
}
RenderTimer::~RenderTimer(){
	wxTimer::Stop();
}

// this function is called when the timer is "reset"
// or reaches the target.
void RenderTimer::Notify(){
	// This will enforce a repaint.
	ptr->Refresh();
}
