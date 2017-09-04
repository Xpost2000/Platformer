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
		int gridBlockType() { 
		int res = static_cast<int>(grid_block_type->GetValue().GetLong());
		res = std::max(1, res);
		res = std::min(16, res);
		grid_block_type->SetValue(wxVariant(res));
		return 	res;
		}
		float gridR(){
			return grid_r->GetValue().GetDouble();
		}
		float gridG(){
			return grid_g->GetValue().GetDouble();
		}
		float gridB(){
			return grid_b->GetValue().GetDouble();
		}
		int gridType() { 
			int grid_type_i = static_cast<int>( grid_type->GetValue().GetLong() );
			grid_type_i = std::min(grid_type_i, 3);
			grid_type_i = std::max(grid_type_i, 1);
			grid_type->SetValue(wxVariant(grid_type_i));
			return grid_type_i;
		}
	private:
		int current_index=0;
		// I need to do this.
		wxPropertyGrid* properties;
		GridTimer* timer;
		// sub properties)
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
		wxPGProperty* grid_block_type=nullptr;
		wxPGProperty* grid_r = nullptr;
		wxPGProperty* grid_g = nullptr;
		wxPGProperty* grid_b = nullptr;

		wxSize sz;
		// since this class is a friend of the editorframe
		// because I require some access to private members
		// that I don't feel like using the getters for...
		// Sue me :P
		EditorFrame* parent=nullptr;
		DECLARE_EVENT_TABLE()
};
#endif
