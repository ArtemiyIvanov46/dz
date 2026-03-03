#include "gradient.h"
#include "vec3.h"
#include "transformations.hpp"
#include <iostream>

#ifndef WIDTH
#define WIDTH 480
#endif

#ifndef HEIGHT
#define HEIGHT 620
#endif

int main(){
    createGradientImage(WIDTH, HEIGHT, "/Users/rootadmin/Desktop/my_image.ppm");
}
