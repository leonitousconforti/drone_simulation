#pragma once

#include <iostream>

namespace drone_simulation::geometry {

struct Color {
 public:
  Color(float r, float g, float b, float a);

  float red() const;
  float green() const;
  float blue() const;
  float alpha() const;

  Color opaque() const;
  float getLuminance() const;

  Color operator+(Color c) const;
  Color operator-(Color c) const;
  Color operator*(Color c) const;
  Color operator/(Color c) const;

  friend std::ostream& operator<<(std::ostream& os, const Color& c);

 private:
  float r, g, b, a;
};

}  // namespace drone_simulation::geometry
