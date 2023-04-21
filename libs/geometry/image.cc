#include "image.h"

#include <math.h>

#include "lodepng/lodepng.h"

namespace drone_simulation::geometry {

Image::~Image() { delete[] this->pixels; }
Image::Image(int width, int height) : width(width), height(height) {
  this->pixels = new unsigned char[width * height * 4];
}

int Image::getWidth() const { return this->width; }
int Image::getHeight() const { return this->height; }

void Image::clear(Color color) {
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      this->setPixel(x, y, color);
    }
  }
}

Color Image::getPixel(int x, int y) const {
  unsigned char* pixel = &this->pixels[(x + width * y) * 4];
  return Color(1.0 * pixel[0] / 255.0, 1.0 * pixel[1] / 255.0,
               1.0 * pixel[2] / 255.0, 1.0 * pixel[3] / 255.0);
}

void Image::setPixel(int x, int y, Color color) {
  if (x < 0) x = 0;
  if (y < 0) y = 0;
  if (x >= this->width) x = this->width - 1;
  if (y >= this->height) y = this->height - 1;
  unsigned char* pixel = &this->pixels[(x + width * y) * 4];
  pixel[0] = color.red() * 255.0;
  pixel[1] = color.green() * 255.0;
  pixel[2] = color.blue() * 255.0;
  pixel[3] = color.alpha() * 255.0;
}

void Image::drawPoint(int x, int y, Color color) {
  this->setPixel(x, y, color);
}

void Image::drawLine(int startX, int startY, int endX, int endY, Color color) {
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

int Image::saveAs(const std::string& filename) const {
  return lodepng::encode(filename, this->pixels, this->width, this->height);
}

}  // namespace drone_simulation::geometry
