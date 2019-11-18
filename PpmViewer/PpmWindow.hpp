#pragma once
#include "FltkIncludes.h"
#include "FileBrowser.hpp"
#include "PpmDocument.hpp"
#include "EffectFactory.hpp"

#include <cmath>
using namespace std;


class PpmWindow : public Fl_Double_Window
{
private:
	Fl_Menu_Bar* _menu = nullptr;
	Fl_Menu_Item _top_bar[8] = {
		{"&File", 0, 0, 0, FL_SUBMENU},
		{"Open", FL_CTRL + 'o', openFileCallback, this},
		{"Quit",	FL_CTRL + FL_F + 4, quitCallback, 0},
		{0}, //this ends a menu group; end of File dropdown
		{"&Effects", 0, 0, 0, FL_SUBMENU},
		{"Remove Red", 0, applyEffect, (void*)ImageEffectType::RemoveRed},
		{"Remove Green", 0, applyEffect, (void*)ImageEffectType::RemoveGreen},
		{0} //end of Effects dropdown
	};
	Fl_RGB_Image* _image = nullptr;
	PpmDocument* _doc = nullptr;
	Fl_Box* _image_box = nullptr;
	static const int MENU_HEIGHT = 30;
	static const int MIN_WIDTH = 200;

	static void openFileCallback(Fl_Widget* widget, void* params)
	{
		FileBrowser browser{};
		if (browser.OpenFileBrowser() == FileResult::OPEN)
		{
			string text = browser.getSelectedFile();
			PpmWindow* current_window = (PpmWindow*)params;
			if (current_window != nullptr)
			{
				current_window->setActiveDocument(new PpmDocument{ text });
				current_window->loadImage();
				current_window->redraw();
			}

		}
	}

	static void quitCallback(Fl_Widget*, void*)
	{
		exit(0);
	}

	static void applyEffect(Fl_Widget* widget, void* params)
	{
		//from https://www.fltk.org/articles.php?L379+I0+TFAQ+P1+Q
		Fl_Widget* p = widget->parent();
		while (p->parent()) p = p->parent();
		PpmWindow* window = (PpmWindow*)p;
		ImageEffectType effect_type = (ImageEffectType)(int)params;
		ImageEffect* effect = EffectFactory::createEffect(effect_type);
		effect->applyEffect(*window->getActiveDocument());
		window->loadImage();
		window->redraw();
		delete effect;
	}

public:
	PpmWindow(int x, int y, int w, int h, const char* l)
		: Fl_Double_Window(x, y, w, h, l)
	{
		_menu = new Fl_Menu_Bar(0, 0, w, MENU_HEIGHT);
		_menu->menu(_top_bar);
		_image_box = new Fl_Box{ 0, 0, w, h };
	}

	~PpmWindow()
	{
		delete _menu;
		_menu = nullptr;
	}

	void loadImage()
	{
		if (_image != nullptr)
		{
			delete _image;
		}
		_image = new Fl_RGB_Image(&_doc->getRawBytes()[0], _doc->getWidth(), _doc->getHeight(), 3);
		_image_box->image(_image);

		//resize
		int width = max(MIN_WIDTH, _doc->getWidth());
		size(width, _doc->getHeight() + MENU_HEIGHT);
		_image_box->size(width, _doc->getHeight());
		_image_box->position(0, MENU_HEIGHT);

	}

	void setActiveDocument(PpmDocument* doc)
	{
		if (_doc != nullptr)
		{
			delete _doc;
		}
		_doc = doc;
	}

	PpmDocument* getActiveDocument()
	{
		return _doc;
	}
};