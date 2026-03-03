// transformations.cpp
#include "transformations.hpp"
#include <algorithm>

color gradient_vertical(const color& color_start, const color& color_end, int y, int HEIGHT) {
    double t = double(y) / (HEIGHT - 1);  // t от 0 до 1
    
    double r = (1 - t) * color_start.x() + t * color_end.x();
    double g = (1 - t) * color_start.y() + t * color_end.y();
    double b = (1 - t) * color_start.z() + t * color_end.z();
    
    return color(r, g, b);
}

color gradient_horizontal(const color& color_start, const color& color_end, int x, int WIDTH) {
    double t = double(x) / (WIDTH - 1);  // t от 0 до 1
    
    double r = (1 - t) * color_start.x() + t * color_end.x();
    double g = (1 - t) * color_start.y() + t * color_end.y();
    double b = (1 - t) * color_start.z() + t * color_end.z();
    
    return color(r, g, b);
}

color invert_color(const color& c) {
    return color(255 - c.x(), 255 - c.y(), 255 - c.z());
}

color color2bw(const color& c) {
    double gray = 0.299 * c.x() + 0.587 * c.y() + 0.114 * c.z();
    return color(gray, gray, gray);
}
