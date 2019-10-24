#pragma once
#include "FltkIncludes.h"
#include "FileBrowser.hpp"
#include "PpmDocument.hpp"

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
	PpmDocument doc;

	static void openFileCallback(Fl_Widget* widget, void* params)
	{
		FileBrowser browser{};
		if (browser.OpenFileBrowser() == FileResult::OPEN)
		{
			string text = browser.getSelectedFile();
			PpmWindow* current_window = (PpmWindow*)widget;
			if (current_window != nullptr)
			{
				current_window->getActiveDocument().open(text);
			}
			
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

	PpmDocument& getActiveDocument()
	{
		return doc;
	}
};