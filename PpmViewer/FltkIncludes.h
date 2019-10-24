#pragma once
#ifndef FLTK_INCLUDES_H
#define FLTK_INCLUDES_H

#ifdef _WIN32
#include "FL/Fl.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Export.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Button.H"
#include "FL/fl_ask.H"
#include "FL/Fl_Widget.H"
#include "FL/Fl_Double_Window.H"
#include "FL/Fl_Sys_Menu_Bar.H"
#include "FL/Fl_Menu_Item.H"
#include "FL/fl_draw.H"
#include "FL/math.h"
#include "FL/Fl_Native_File_Chooser.H"
#else
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Export.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Sys_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/math.H>
#include <FL/Fl_Native_File_Chooser.H>
#endif // _WIN32

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#endif //_MSC_VER

#endif // FLTK_INCLUDES_H