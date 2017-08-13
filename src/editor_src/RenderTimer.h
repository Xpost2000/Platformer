#ifndef RENDERER_TIMER_H
#define RENDERER_TIMER_H
#include <wx/wx.h>
#include "GLCanvas.h"
/*
 * wxWidgets doesn't render constantly
 * and it only redraws when it has to.
 * (resizing is the most common case of this)
 * Sadly it doesn't redraw when the OpenGL state is changed
 * or anything so I have to make timer to do this for me.
 */
class RenderTimer : public wxTimer{
	public:
		RenderTimer(GLCanvas* ptr);
		~RenderTimer();
		void Notify();
	private:
		GLCanvas* ptr;
};
#endif
