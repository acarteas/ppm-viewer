#pragma once
#include "PpmDocument.hpp"
class ImageEffect
{
public:
	virtual void applyEffect(PpmDocument& doc) = 0;
};