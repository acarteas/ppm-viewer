#pragma once
#include "FltkIncludes.h"
class PpmWindow : public Fl_Double_Window
{
private:
	Fl_Menu_Bar* _menu = nullptr;
	Fl_Menu_Item _top_bar[3] = {
		{"&File", 0, 0, 0, FL_SUBMENU},
			{"&Open",	FL_ALT + 'o', openFileCallback, 0},
			{"&Quit",	FL_ALT + 'q', quitCallback, 0},
	};

	static void openFileCallback(Fl_Widget*, void*) { exit(0); }

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