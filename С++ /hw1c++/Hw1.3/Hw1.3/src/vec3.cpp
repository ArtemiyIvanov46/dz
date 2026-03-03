#include "vec3.h"
#include <cmath>
#include <sstream>
#include <iomanip>

vec3::vec3() {};

    vec3::vec3 (double x, double y, double z) :  e{x, y, z} {}

    double vec3::x() const {
        return e[0];
    }
    double vec3::y() const {
        return e[1];
    }
    double vec3::z() const {
        return e[2];
    }
    double vec3::get(int i) const {
        return e[i];
    }
    vec3& vec3::add(const vec3& v) {
        e[0]+=v.e[0];
        e[1]+=v.e[1];
        e[2]+=v.e[2];
        return *this;
    }
    vec3& vec3::sub(const vec3& v) {
        e[0]-=v.e[0];
        e[1]-=v.e[1];
        e[2]-=v.e[2];
        return *this;
    }
    vec3& vec3::scale(double v) {
        e[0]*=v;
        e[0]*=v;
        e[0]*=v;
        return *this;
    }
    double vec3::dot(const vec3& v) const {
        return e[0]*v.e[0]+e[1]*v.e[1]+e[2]*v.e[2];
    }
    vec3 vec3::cross(const vec3& v) const {
        return vec3(
            e[1] * v.e[2] - e[2] * v.e[1],
            e[2] * v.e[0] - e[0] * v.e[2],
            e[0] * v.e[1] - e[1] * v.e[0]
        );
    }
    std::string vec3::print() const {
        std::ostringstream oss;
        oss << "(" << e[0] << "," << e[1] << "," << e[2] << ")";
        return oss.str();
    }
    double vec3::length() const {
        return std::sqrt(length_squared());
    }
    double vec3::length_squared() const {
        return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
    }
    void write_color(std::ostream& out, const color& pixel_color) {
        out << static_cast<int>(pixel_color.x()) << ' '
            << static_cast<int>(pixel_color.y()) << ' '
            << static_cast<int>(pixel_color.z()) << '\n';
    }
