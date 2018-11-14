#include "Pixel.h"

class Image
{
    private:
        int _width, _height;
        Pixel** _image;

    public:
        Image(int, int);
        ~Image();
        Image(const Image&);
        friend std::ostream& operator << (std::ostream&, Image&);

        //getters
        int get_width() {return _width;}
        int get_height() {return _height;}

        void set_initial_state(bool seed);

        Pixel operator()(int x, int y) {return _image[x][y];}

        Image operator=(const Image&);

};