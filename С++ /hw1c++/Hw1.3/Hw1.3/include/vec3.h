#ifndef VEC3_H
#define VEC3_H

#include <string>
#include <ostream>

class vec3 {
private:
    double e[3];

public:
    vec3();
    vec3(double x, double y, double z);
    
    double x() const;
    double y() const;
    double z() const;
    double get(int idx) const;
    
    vec3& add(const vec3& v);
    vec3& sub(const vec3& v);
    vec3& scale(double t);
    double dot(const vec3& v) const;
    vec3 cross(const vec3& v) const;
    

    std::string print() const;
    double length() const;
    double length_squared() const;
};
using color = vec3;
void write_color(std::ostream& out, const color& pixel_color);
#endif // VEC3_H
