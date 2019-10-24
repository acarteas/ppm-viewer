#pragma once
#include "FltkIncludes.h"
class PpmWindow : public Fl_Double_Window
{
private:
	Fl_Menu_Bar* _menu = nullptr;
	Fl_Menu_Item _top_bar[5] = {
		{"&File", 0, 0, 0, FL_SUBMENU},
		{"Open", FL_CTRL + 'o', openFileCallback, 0},
		{"Quit",	FL_CTRL + FL_F + 4, quitCallback, 0},
	{0}
	};

	static void openFileCallback(Fl_Widget*, void*) 
	{ 
		Fl_Native_File_Chooser fnfc;
		fnfc.title("Pick a file");
		fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
		fnfc.filter("Text\t*.txt\n"
			"C Files\t*.{cxx,h,c}");
		fnfc.directory("/var/tmp");           // default directory to use
		// Show native chooser
		switch (fnfc.show()) {
		case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
		case  1: printf("CANCEL\n");                      break;  // CANCEL
		default: printf("PICKED: %s\n", fnfc.filename()); break;  // FILE CHOSEN
		}
	}

	static void quitCallback(Fl_Widget*, void*) { exit(0); }


public:
	PpmWindow(int x, int y, int w, int h, const char* l)
		: Fl_Double_Window(x, y, w, h, l)
	{
		_menu = new Fl_Menu_Bar(0, 0, w, 30);
		_menu->menu(_top_bar);
	}

	~PpmWindow()
	{
		delete _menu;
		_menu = nullptr;
	}
};