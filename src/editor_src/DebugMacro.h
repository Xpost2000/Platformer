#ifndef DEBUG_MB_MACRO
#define DEBUG_MB_MACRO
#include <wx/wx.h>
#include <cassert>
#define DEBUG_MB( message )\
	wxMessageBox( #message, wxT("DEBUG MESSAGE SHOULD NOT APPEAR"), wxICON_ERROR )
#define NOT_IMPLEMENTED_MB(message)\
	wxMessageBox( #message, wxT("Feature doesn't exist yet"), wxICON_INFORMATION )
#define ERROR_MB( message , condition )\
	wxMessageBox( #message, wxT("Program Error. (Assertion performed)"), wxICON_ERROR )\
	assert( condition )
#endif
