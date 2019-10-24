#pragma once
#ifndef PPM_DOCUMENT_HPP
#define PPM_DOCUMENT_HPP
#include <string>
#include <vector>
#include <sstream>
#include <exception>
#include "FileHelpers.hpp"
#include "Pixel.hpp"
using namespace std;

/*
Properties of PPM Document:
	1. Image format (e.g. P3)
	2. Width
	3. Height
	4. Image data (collection of Pixels)
	5. File name

Operations that we perform on PPM documents
	1. Open file
	2. Write file
	3. Manipulate pixels
	4. Draw (kind of hard)
	5. Resize image
	6. Crop
*/
class PpmDocument
{
private:
	//underscore means that the variable belongs
	//to the object
	string _format;
	int _width = 0;
	int _height = 0;
	int _color_depth = 0;
	string _file_name;
	vector<Pixel> _rgb_data;

	void checkDocumentValidity(istream& stream)
	{
		if (stream.good() == false && stream.eof() == false)
		{
			throw exception{ "Invalid PPM spec" };
		}
	}

public:

	//constructor method gets called automatically
	//whenever we create a new PpmDocument
	PpmDocument(string file_name)
	{
		open(file_name);
	}

	//do nothing constructor for when we don't
	//have a file name
	PpmDocument()
	{
	}

	void open(string file_name)
	{
		_file_name = file_name;
		vector<string> raw_data = readFile(_file_name);

		//make sure file was read successfully
		if (raw_data.size() == 0)
		{
			//TODO: throw error
		}
		else
		{
			//set object properties
			_format = raw_data[0];

			//grab width and height using istringstream
			istringstream line{ raw_data[1] };
			line >> _width;
			line >> _height;
			checkDocumentValidity(line);

			//color depth
			line = istringstream{raw_data[2]};
			line >> _color_depth;
			checkDocumentValidity(line);
			
			//process data
			for (int i = 3; i < raw_data.size(); i++)
			{
				istringstream numbers_str{ raw_data[i] };
				while (numbers_str.eof() == false)
				{
					int next_number = -1;
					Pixel p;
					numbers_str >> p;
					checkDocumentValidity(numbers_str);
					_rgb_data.push_back(p);
				}
			}
		}
	}

	int getColorDepth() const
	{
		return _color_depth;
	}

	string getFileName() const
	{
		return _file_name;
	}

	void setFileName(const string& file_name)
	{
		_file_name = file_name;
	}

	int getHeight() const
	{
		return _height;
	}

	int getWidth() const
	{
		return _width;
	}

	string getImageFormat() const
	{
		return _format;
	}

	void setImageFormat(string format)
	{
		//error checking
		if (format == "P3" || format == "P6")
		{
			_format = format;
		}
		else
		{
			//TODO: throw error 
		}
	}

	//friends are allowed to access private variables
	friend ostream& operator<<(ostream& stream, const PpmDocument& doc);
};

ostream& operator<<(ostream& stream, const PpmDocument& doc)
{
	stream << doc.getImageFormat() << endl;
	stream << doc.getWidth() << " " << doc.getHeight() << endl;
	stream << doc.getColorDepth() << endl;
	int pixel_counter = 1;
	for (auto pixel : doc._rgb_data)
	{
		stream << pixel;
		pixel_counter++;
		if (pixel_counter > doc.getWidth())
		{
			stream << endl;
			pixel_counter = 1;
		}
		else
		{
			stream << " ";
		}
	}
	return stream;
}

#endif // !PPM_DOCUMENT_HPP
