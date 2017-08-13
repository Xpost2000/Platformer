#ifndef ID_CONSTANTS_H
#define ID_CONSTANTS_H
/*
 * This file just contains the constants
 * I use for wxWidgets ( it requires integer identification )
 */
namespace ConstantId{
	const int MainWindow_ID = wxID_HIGHEST+1;
	namespace MainWindow{
		const int HelpMenu_About = wxID_HIGHEST+11;
		const int ViewMenu_Recenter = wxID_HIGHEST+12;
		const int FileMenu_Open = wxID_HIGHEST+13;
	};
};
#endif
