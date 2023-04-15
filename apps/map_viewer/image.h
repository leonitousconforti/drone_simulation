#pragma once

#include <cmath>
#include <string>

#include "libs/geometry/color.h"
#include "lodepng/lodepng.h"

using Color = drone_simulation::geometry::Color;

class Image {
 public:
  ~Image() { delete[] this->pixels; }
  Image(int width, int height) : width(width), height(height) {
    this->pixels = new unsigned char[width * height * 4];
  }

  int getWidth() const { return width; }
  int getHeight() const { return height; }

  void clear(Color color) {
    for (int x = 0; x < this->width; x++) {
      for (int y = 0; y < this->height; y++) {
        setPixel(x, y, color);
      }
    }
  }

  Color getPixel(int x, int y) const {
    unsigned char* pixel = &this->pixels[(x + width * y) * 4];
    return Color(1.0 * pixel[0] / 255.0, 1.0 * pixel[1] / 255.0,
                 1.0 * pixel[2] / 255.0, 1.0 * pixel[3] / 255.0);
  }

  void setPixel(int x, int y, Color color) {
    unsigned char* pixel = &this->pixels[(x + width * y) * 4];
    pixel[0] = color.red() * 255.0;
    pixel[1] = color.green() * 255.0;
    pixel[2] = color.blue() * 255.0;
    pixel[3] = color.alpha() * 255.0;
  }

  void drawLine(int startX, int startY, int endX, int endY, Color color) {
    float dist = std::sqrt((endX - startX) * (endX - startX) +
                           (endY - startY) * (endY - startY));

    float dx = 1.0 * (endX - startX) / dist;
    float dy = 1.0 * (endY - startY) / dist;

    float x = startX;
    float y = startY;

    for (int i = 0; i < dist; i++) {
      this->setPixel(x, y, color);
      x += dx;
      y += dy;
    }
  }

  int saveAs(const std::string& filename) const {
    return lodepng::encode(filename, pixels, width, height);
  }

 private:
  int width;
  int height;
  unsigned char* pixels;
};
