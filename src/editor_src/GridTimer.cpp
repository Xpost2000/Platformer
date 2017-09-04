#include "GridTimer.h"
#include "PropertyPanel.h"

void GridTimer::Notify(){
	ptr->IdleHandler();
	ptr->Refresh();
}
