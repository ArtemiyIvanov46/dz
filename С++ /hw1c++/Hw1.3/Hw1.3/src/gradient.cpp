#include <iostream>
#include <string>
#include <fstream>
#include "vec3.h"
#include "gradient.h"
#include "transformations.hpp"

void createGradientImage(int WIDTH, int HEIGHT, const std::string& path) {
    std::ofstream os(path);

    os << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
    
    color red(255, 0, 0);
    color blue(0, 0, 255);
    color yellow(255, 255, 0);

    
    for (int j = 0; j < HEIGHT; j++)
    {
        std::clog << "\rScanlines remaining: " << (HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < WIDTH; i++)
        {
            color vert = gradient_vertical(red, blue, j, HEIGHT);
            color horiz = gradient_horizontal(red, yellow, i, WIDTH);
            color pixel_color = color(
            (vert.x() + horiz.x()) / 2,
            (vert.y() + horiz.y()) / 2,
            (vert.z() + horiz.z()) / 2
            );
            write_color(os, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}

