#include <iostream>
#include <algorithm>
#include "Image.h"

using namespace std;

Image merge_images(Image i1, Image i2)
{
    int min_w = min(i1.get_width(), i2.get_width());
    // cout << min_w << " : Min width" << endl;
    int min_h = min(i1.get_height(), i2.get_height());
    Image i3(min_w, min_h);

    for (int i = 0; i < min_h; i++)
    {
        for (int j = 0; j < min_w; j++)
        {
            i3(i, j)(i, j);
            unsigned int color;
            if(i1(i, j).get_color_intensity() == i2(i, j).get_color_intensity())
                i3(i, j).set_color(i1(i, j).get_color_intensity());
            else
                i3(i, j).set_color(0);
        }
    }
    return i3;
}

int main()
{
    int input;
    int input_counter = 0;
    int input_array[100];
    int pair_count = 0;

    while(true)
    {
        cin >> input;
        if (input == -1)
            break;
        else
            input_array[input_counter] = input;
            input_counter++;
    }

    if (input_counter % 2 == 1)
    {
        input_counter --;
    }
    if (input_counter != 0)
    {
        if (input_counter == 2)
        {
            Image i1(input_array[0], input_array[1]);
            i1.set_initial_state(true);
            cout << i1;
        }
        else
        {
            Image i1(input_array[0], input_array[1]);
            i1.set_initial_state(true);
            Image i2(input_array[2], input_array[3]);
            i2.set_initial_state(false);
            Image ans = merge_images(i1, i2);
            input_counter -= 4;
            int array_counter = 4;
            int seed = 0;
            while (input_counter != 0)
            {
                Image temp(input_array[array_counter], input_array[array_counter + 1]);
                array_counter += 2;
                temp.set_initial_state(seed % 2 == 0);
                input_counter -= 2;
                ans = merge_images(ans, temp);
            }
            cout << ans;
        }
    }
    cout << "eof" << endl;
    return 0;
}