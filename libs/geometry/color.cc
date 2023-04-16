#include "color.h"

namespace drone_simulation::geometry {

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

float Color::red() const { return this->r; }
float Color::green() const { return this->g; }
float Color::blue() const { return this->b; }
float Color::alpha() const { return this->a; }

// https://en.wikipedia.org/wiki/Relative_luminance
float Color::getLuminance() const {
  return 0.2126 * this->r + 0.7152 * this->g + 0.0722 * this->b;
}

Color Color::opaque() const { return Color(r, g, b, 1); }

Color Color::operator+(Color c) const {
  return Color(this->r + c.r, this->g + c.g, this->b + c.b, this->a + c.a);
}
Color Color::operator-(Color c) const {
  return Color(this->r - c.r, this->g - c.g, this->b - c.b, this->a - c.a);
}
Color Color::operator*(Color c) const {
  return Color(this->r * c.r, this->g * c.g, this->b * c.b, this->a * c.a);
}
Color Color::operator/(Color c) const {
  return Color(this->r / c.r, this->g / c.g, this->b / c.b, this->a / c.a);
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
  os << "r=" << c.r << ", g=" << c.g << ", b=" << c.b;
  return os;
}

}  // namespace drone_simulation::geometry
