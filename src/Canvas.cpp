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

/**
 * Goes through each row left to right and creates rectangles that expands to cover each pixel in the row of the same color, resetting on color change
 * Done to reduce draw calls
 */
void Canvas::Draw() const {
  for (size_t row = 0; row < pixel_height_; row++) {
    // Start our draw rectangle at the left of the row
    Rectf draw_rect = GetPixelSizedToScreenSpace(0, row);
    // Keep track of the color of our rectangle
    RGBPixel current_color = RGBPixel::white();
    for (size_t col = 0; col < pixel_width_; col++) {
      RGBPixel const &pixel = GetPixel(col, row);
      // If we encounter a pixel a different color than the rectangle, then draw it and reset the rectangle to be that pixel's color and location
      if (pixel != current_color) {
        gl::color(current_color.GetCinderColor());
        gl::drawSolidRect(draw_rect);
        draw_rect = GetPixelSizedToScreenSpace(col, row);
        current_color = pixel;
      } else {
        // Otherwise expand the rectangle to include this pixel
        draw_rect.include(ToScreenSpace(col, row));
      }
    }
    // Draw the last rectangle
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
void Canvas::SetPixel(size_t x, size_t y, RGBPixel const &pixel) {
  if (x >= pixel_width_ | y >= pixel_height_) {
    return;
  }
  pixels_[y * pixel_width_ + x] = pixel;
}
void Canvas::SetPixelScreenSpace(float x, float y, RGBPixel const &pixel) {
  auto canvas_space = ToCanvasSpace(x, y);
  SetPixel(canvas_space.x, canvas_space.y, pixel);
}
glm::vec2 Canvas::ToScreenSpace(size_t x, size_t y) const {
  vec2 upper_left = bounds_.getUpperLeft();
  float scaling_factor_x = bounds_.getWidth() / pixel_width_;
  float scaling_factor_y = bounds_.getHeight() / pixel_height_;
  return upper_left + vec2(x * scaling_factor_x, y * scaling_factor_y);
}
glm::u64vec2 Canvas::ToCanvasSpace(float x, float y) const {

  float scaling_factor_x = bounds_.getWidth() / pixel_width_;
  float scaling_factor_y = bounds_.getHeight() / pixel_height_;
  size_t row = y / scaling_factor_y;
  size_t col = x / scaling_factor_x;
  return glm::u64vec2(col, row);
}
void Canvas::Clear() {
  pixels_.clear();
  pixels_.resize(pixel_width_ * pixel_height_, RGBPixel::white());
}
RGBPixel const &Canvas::GetPixelScreenSpace(float x, float y) const {
  auto canvas_space = ToCanvasSpace(x, y);
  return GetPixel(canvas_space.x, canvas_space.y);
}
ci::Rectf Canvas::GetPixelSizedToScreenSpace(size_t x, size_t y) const {
  return cinder::Rectf(ToScreenSpace(x, y), ToScreenSpace(x + 1, y + 1));
}
Rectf const &Canvas::GetBounds() const {
  return bounds_;
}
size_t Canvas::GetPixelWidth() const {
  return pixel_width_;
}
size_t Canvas::GetPixelHeight() const {
  return pixel_height_;
}
}
