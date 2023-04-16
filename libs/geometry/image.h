#pragma once

#include <string>

#include "color.h"

namespace drone_simulation::geometry {

class Image {
 public:
  ~Image();
  Image(int width, int height);

  int getWidth() const;
  int getHeight() const;
  void clear(Color color);
  Color getPixel(int x, int y) const;
  void setPixel(int x, int y, Color color);
  void drawLine(int startX, int startY, int endX, int endY, Color color);
  int saveAs(const std::string& filename) const;

 private:
  int width;
  int height;
  unsigned char* pixels;
};

}  // namespace drone_simulation::geometry
