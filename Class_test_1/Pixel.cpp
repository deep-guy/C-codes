#include "Pixel.h"

Pixel::Pixel(int x = 0, int y = 0)
{
    _x = x;
    _y = y;
    _color_intensity = 0;
}

Pixel::Pixel(){}

Pixel::~Pixel()
{
    // delete this;
}

Pixel::Pixel(const Pixel& obj)
{
    _x = obj._x;
    _y = obj._y;
    _color_intensity = obj._color_intensity;
}

std::ostream& operator << (std::ostream& os, Pixel& obj)
{
    if (obj._color_intensity == 1)
        os << "o ";
    else
        os << "+ ";
    
    return os;
}

void Pixel::operator()(int x, int y)
{
    _x = x;
    _y = y;
}

Pixel Pixel::operator = (const Pixel& obj)
{
    _x = obj._x;
    _y = obj._y;
    _color_intensity = obj._color_intensity;
    return (*this);
}


