//
// Created by Eric Pfister on 11/17/20.
//
#include <Canvas.h>
#include <exception>
using namespace cinder;

namespace paint {

Canvas::Canvas(ci::Rectf bounds, size_t pixel_width, size_t pixel_height) {
  bounds_ = bounds;
  if (pixel_width == 0 | pixel_height == 0) {
    throw std::invalid_argument("Pixel width or height cannot be zero");
  }
  pixel_width_ = pixel_width;
  pixel_height_ = pixel_height;
  pixels_.resize(pixel_width * pixel_height, RGBPixel::white());
}
void Canvas::Draw() const {
  for (size_t row = 0; row < pixel_height_; row++) {
    Rectf draw_rect = ToScreenSpace(0, row);
    RGBPixel current_color = RGBPixel::white();
    for (size_t col = 0; col < pixel_width_; col++) {
      RGBPixel const &pixel = GetPixel(col, row);
      if (pixel != current_color) {
        gl::color(current_color.GetCinderColor());
        gl::drawSolidRect(draw_rect);
        draw_rect = ToScreenSpace(col, row);
        current_color = pixel;
      } else {
        draw_rect.include(ToScreenSpace(col, row));
      }
    }
    gl::color(current_color.GetCinderColor());
    gl::drawSolidRect(draw_rect);
  }
}
RGBPixel const &Canvas::GetPixel(size_t x, size_t y) const {
  if (x >= pixel_width_ | y >= pixel_height_) {
    throw std::invalid_argument(
        "Coordinates are out of range for canvas of size (" + std::to_string(pixel_width_) + ", "
            + std::to_string(pixel_height_) + ")");
  }
  return pixels_[y * pixel_width_ + x];
}
ci::Rectf Canvas::ToScreenSpace(size_t x, size_t y) const {
  vec2 upper_left = bounds_.getUpperLeft();
  float scaling_factor_x = bounds_.getWidth() / pixel_width_;
  float scaling_factor_y = bounds_.getHeight() / pixel_height_;
  Rectf screen_space = Rectf(upper_left.x + x * scaling_factor_x,
                             upper_left.y + y * scaling_factor_y,
                             upper_left.x + (x + 1) * scaling_factor_x,
                             upper_left.y + (y + 1) * scaling_factor_y);
  return screen_space;
}
void Canvas::SetPixel(size_t x, size_t y, RGBPixel const &pixel) {
  if (x >= pixel_width_ | y >= pixel_height_) {
    throw std::invalid_argument(
        "Coordinates are out of range for canvas of size (" + std::to_string(pixel_width_) + ", "
            + std::to_string(pixel_height_) + ")");
  }
  pixels_[y * pixel_width_ + x] = pixel;
}
void Canvas::SetPixelScreenSpace(float x, float y, RGBPixel const &pixel) {
  float scaling_factor_x = bounds_.getWidth() / pixel_width_;
  float scaling_factor_y = bounds_.getHeight() / pixel_height_;
  size_t row = y / scaling_factor_y;
  size_t col = x / scaling_factor_x;
  SetPixel(col, row, pixel);
}
}
