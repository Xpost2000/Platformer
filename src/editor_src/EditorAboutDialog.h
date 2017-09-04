#ifndef EDITOR_ABOUT_DIALOG_H
#define EDITOR_ABOUT_DIALOG_H
#include <wx/wx.h>

// it is a custom dialog. Well it's actually more like a window
// but it's technically a dialog.
// TODO: FINISH
class EditorAboutDialog : public wxDialog {
	public:
	EditorAboutDialog(wxWindow* parent,
			  const wxPoint& pos=wxDefaultPosition, 
			  long style=wxDEFAULT_DIALOG_STYLE);
	~EditorAboutDialog();
	private:
	DECLARE_EVENT_TABLE()
};

#endif
