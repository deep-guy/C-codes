#include <iostream>
#include <stdlib.h>

#ifndef PIXEL_H_
#define PIXEL_H_

class Pixel
{
    private:    
        int _x, _y;
        unsigned int _color_intensity;

    public:
        Pixel(int, int);
        Pixel();
        ~Pixel();
        Pixel(const Pixel&);
        friend std::ostream& operator << (std::ostream&, Pixel&);


        //getters
        int get_x() {return _x;}
        int get_y() {return _y;}
        unsigned int get_color_intensity() {return _color_intensity;}

        //setters
        void set_color(unsigned int x) {_color_intensity = x;}

        // Assignment, input and output overloading
        void operator()(int x, int y);
        Pixel operator=(const Pixel&);




};

#endif
