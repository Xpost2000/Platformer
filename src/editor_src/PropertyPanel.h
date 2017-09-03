#ifndef PROPERTY_PANE_H
#define PROPERTY_PANE_H
/*
 * I'm going to use panes because it might help organization.
 */
#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include "EditorFrame.h"
#include "GridTimer.h"
class PropertyPanel : public wxPanel{
	public:
		PropertyPanel( wxWindow* parent, wxWindowID id=wxID_ANY,
			       const wxPoint& pos=wxDefaultPosition,
			       const wxSize&  size=wxDefaultSize, 
			       long style=wxTAB_TRAVERSAL, 
			       const wxString& name=wxPanelNameStr);
		~PropertyPanel();
		void IdleHandler(  );
		int gridW() { return static_cast<int>(grid_w->GetValue().GetLong());}
		int gridH() { return static_cast<int>(grid_h->GetValue().GetLong());}
		int gridType() { 
			int grid_type_i = static_cast<int>( grid_type->GetValue().GetLong() );
			grid_type_i = std::min(grid_type_i, 3);
			grid_type_i = std::max(grid_type_i, 1);
			return grid_type_i;
		}
	private:
		int current_index=0;
		// I need to do this.
		wxPropertyGrid* properties;
		GridTimer* timer;
		// sub properties
		wxPGProperty* PositionX=nullptr;
		wxPGProperty* PositionY=nullptr;
		// next
		wxPGProperty* SizeX=nullptr;
		wxPGProperty* SizeY=nullptr;
		// next
		wxPGProperty* R=nullptr;
		wxPGProperty* G=nullptr;
		wxPGProperty* B=nullptr;
		// now special properties
		wxPGProperty* scroll_category=nullptr;
		wxPGProperty* scrollX=nullptr;
		wxPGProperty* scrollY=nullptr;
		wxPGProperty* blockType=nullptr;
		// Light Properties
		wxPGProperty* lIndex=nullptr;
		wxPGProperty* lPower=nullptr;	
		wxPGProperty* lR = nullptr;
		wxPGProperty* lG = nullptr;
		wxPGProperty* lB = nullptr;
		wxPGProperty* lX = nullptr;
		wxPGProperty* lY = nullptr;
		// Creation Mode Properties
		wxPGProperty* grid_type = nullptr;
		wxPGProperty* grid_w = nullptr;
		wxPGProperty* grid_h = nullptr;
		wxSize sz;
		// since this class is a friend of the editorframe
		// because I require some access to private members
		// that I don't feel like using the getters for...
		// Sue me :P
		EditorFrame* parent=nullptr;
		DECLARE_EVENT_TABLE()
};
#endif
