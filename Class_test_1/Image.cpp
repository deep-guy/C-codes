#include "Image.h"

Image::Image(int w, int h)
{
    _width = w;
    _height = h;
    _image = new Pixel*[_height];
    for (int i = 0; i < _height; i++)
    {
        _image[i] = new Pixel[_width];
    }
    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            _image[i][j](i, j);
        }
    }
}

Image::~Image()
{
    for (int i = 0; i < _height; i++)
    {
        delete[] _image[i];
    }
    delete[] _image;
    // delete this;
}

Image::Image(const Image& obj)
{
    _width = obj._width;
    _height = obj._height;
    _image = new Pixel*[_height];
    for (int i = 0; i < _height; i++)
    {
        _image[i] = new Pixel[_width];
    }

    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            // _image[i][j] = obj._image[i][j];
            _image[i][j](obj._image[i][j].get_x(), obj._image[i][j].get_y());
            _image[i][j].set_color(obj._image[i][j].get_color_intensity());
        }
    }
}

void Image::set_initial_state(bool seed)
{
    if (seed)
    {
        for (int i = 0; i < _height; i++)
        {
            if (i % 2 == 0)
            {
                for (int j = 0; j <_width; j++)
                {
                    if (j % 2 == 0)
                        _image[i][j].set_color(1);
                    else
                        _image[i][j].set_color(0);
                }
            }
            else
            {
                for (int j = 0; j < _width; j++)
                {
                    if (j % 2 == 1)
                        _image[i][j].set_color(1);
                    else
                        _image[i][j].set_color(0);
                }
            }
        }
    }

    else
    {
        for (int i = 0; i < _height; i++)
        {
            if (i % 2 == 1)
            {
                for (int j = 0; j <_width; j++)
                {
                    if (j % 2 == 0)
                        _image[i][j].set_color(1);
                    else
                        _image[i][j].set_color(0);
                }
            }
            else
            {
                for (int j = 0; j < _width; j++)
                {
                    if (j % 2 == 1)
                        _image[i][j].set_color(0);
                    else
                        _image[i][j].set_color(1);
                }
            }
        }
    }
}

std::ostream& operator << (std::ostream& os, Image& obj)
{
    for (int i = 0; i < obj._height; i++)
    {
        for (int j = 0; j < obj._width; j++)
        {
            os << obj._image[i][j];
        }
        os << std::endl;
    }
    return os;
}

Image Image::operator=(const Image& obj)
{
    _width = obj._width;
    _height = obj._height;

    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            // _image[i][j] = obj._image[i][j];
            _image[i][j](obj._image[i][j].get_x(), obj._image[i][j].get_y());
            _image[i][j].set_color(obj._image[i][j].get_color_intensity());
        }
    }

    return *this;
}
