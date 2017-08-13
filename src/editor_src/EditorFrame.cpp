#include "EditorFrame.h"

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
	canvas = new GLCanvas(this, glAttributes);
	
	CreateStatusBar(1);
	SetStatusText("Letter X Game Editor prototype/alpha");
}
