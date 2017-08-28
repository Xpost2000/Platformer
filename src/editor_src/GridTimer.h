#ifndef GRID_TIMER_H
#define GRID_TIMER_H
// Header only timer file
#include <wx/wx.h>
class PropertyPanel;
class GridTimer : public wxTimer{
	public:
		GridTimer( PropertyPanel* ptr ) : ptr(ptr), wxTimer() {  }
		~GridTimer() {}
		void Notify();
	private:
		PropertyPanel* ptr;
};

#endif
