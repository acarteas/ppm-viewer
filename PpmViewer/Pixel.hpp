#pragma once
#ifndef PIXEL_H
#define PIXEL_H

#include <istream>
#include <exception>
using namespace std;

class Pixel
{
public:
	
	//if you use this, you are not allowed to keep this as is!
	//instead, I expect you to write proper getters and setters and
	//make the actual variables private!
	int red = -1;
	int green = -1;
	int blue = -1;
};

istream& operator>>(istream& stream, Pixel& pixel)
{
	stream >> pixel.red >> pixel.green >> pixel.blue;
	return stream;
}

ostream& operator<<(ostream& stream, Pixel& pixel)
{
	stream << pixel.red << " " << pixel.green << " " << pixel.blue;
	return stream;
}

#endif // !PIXEL_H
