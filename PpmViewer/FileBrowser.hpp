#pragma once
#include "FltkIncludes.h"
#include "FileHelpers.hpp"

#include <filesystem>
#include <string>
using namespace std;

//see https://stackoverflow.com/questions/50668814/vs2017-e0135-namespace-std-has-no-member-filesystem
//for forcing C++ 17 in VS 2019
namespace fs = std::filesystem;

enum class FileResult
{
	OPEN = 1,
	CANCEL,
	ERR
};

class FileBrowser
{
private:
	string _starting_path;
	string _file_path = "";

public:
	FileBrowser(string starting_path = "")
	{
		if (starting_path.length() == 0)
		{
			fs::path current_path{ fs::current_path() };
			string _starting_path = current_path.string();
		}
		else
		{
			_starting_path = starting_path;
		}
	}

	FileResult OpenFileBrowser()
	{
		Fl_Native_File_Chooser fnfc;
		fnfc.title("Pick a file");
		fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
		fnfc.filter("PPM\t*.ppm\n");


		vector<char> cstr(_starting_path.c_str(), _starting_path.c_str() + _starting_path.size() + 1);
		fnfc.directory(&cstr[0]);           // default directory to use

		// Show native chooser
		switch (fnfc.show())
		{
		case -1: //error
			_file_path = "";
			return FileResult::ERR;
			break;
		case  1: //cancel
			_file_path = "";
			return FileResult::CANCEL;
			break;
		default: //something selected
			_file_path = fnfc.filename();
			return FileResult::OPEN;
			break;
		}
	}

	string getSelectedFile() const
	{
		return _file_path;
	}

};