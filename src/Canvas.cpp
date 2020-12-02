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
  surface_ = ci::Surface(pixel_width, pixel_height, true);
}

/**
 * Goes through each row left to right and creates rectangles that expands to cover each pixel in the row of the same color, resetting on color change
 * Done to reduce draw calls
 */
void Canvas::Draw() const {
  gl::color(Color::white());
  gl::Texture2dRef tex = gl::Texture::create(surface_);
  gl::draw(tex);
}

ColorAT<unsigned char> Canvas::GetPixel(size_t x, size_t y) const {
  auto pixel_width = GetPixelWidth();
  auto pixel_height = GetPixelHeight();
  if (x >= pixel_width | y >= pixel_height) {
    throw std::invalid_argument(
        "Coordinates are out of range for canvas of size (" + std::to_string(pixel_width) + ", "
            + std::to_string(pixel_height) + ")");
  }
  return ColorAT<unsigned char>(surface_.getPixel(vec2(x, y)));
}
void Canvas::SetPixel(size_t x, size_t y, ColorAT<unsigned char> const &pixel) {
  auto pixel_width = GetPixelWidth();
  auto pixel_height = GetPixelHeight();
  if (x >= pixel_width | y >= pixel_height) {
    return;
  }
  surface_.setPixel(vec2(x, y), pixel);
}
void Canvas::SetPixelScreenSpace(float x, float y, ColorAT<unsigned char> const &pixel) {
  auto canvas_space = ToCanvasSpace(x, y);
  SetPixel(canvas_space.x, canvas_space.y, pixel);
}
glm::vec2 Canvas::ToScreenSpace(size_t x, size_t y) const {
  vec2 upper_left = bounds_.getUpperLeft();
  float scaling_factor_x = bounds_.getWidth() / GetPixelWidth();
  float scaling_factor_y = bounds_.getHeight() / GetPixelHeight();
  return upper_left + vec2(x * scaling_factor_x, y * scaling_factor_y);
}
glm::u64vec2 Canvas::ToCanvasSpace(float x, float y) const {

  float scaling_factor_x = bounds_.getWidth() / GetPixelWidth();
  float scaling_factor_y = bounds_.getHeight() / GetPixelHeight();
  size_t row = y / scaling_factor_y;
  size_t col = x / scaling_factor_x;
  return glm::u64vec2(col, row);
}
void Canvas::Clear() {
}
ColorAT<unsigned char> Canvas::GetPixelScreenSpace(float x, float y) const {
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
  return surface_.getWidth();
}
size_t Canvas::GetPixelHeight() const {
  return surface_.getHeight();
}
ci::Surface::Iter Canvas::GetSurfaceIter(Area area) {
  if (area == Area()) area = Area(bounds_);
  return surface_.getIter(area);
}
}
