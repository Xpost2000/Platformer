#include "RenderTimer.h"

RenderTimer::RenderTimer(GLCanvas* ptr):
ptr(ptr), wxTimer(){
}
RenderTimer::~RenderTimer(){
}

// this function is called when the timer is "reset"
// or reaches the target.
void RenderTimer::Notify(){
	// I want to seperate my logic m8.
	ptr->LogicRefresh();
	// This will enforce a repaint.
	ptr->Refresh();
}
