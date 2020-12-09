//
// Created by Eric Pfister on 11/17/20.
//
#include <Canvas.h>
#include <exception>
#include <cinder/ip/Resize.h>
using namespace cinder;

namespace paint {

gl::Texture2dRef Canvas::CHECKERBOARD_TEXTURE;
Canvas::Canvas(ci::Rectf bounds, size_t pixel_width, size_t pixel_height) {
  if (CHECKERBOARD_TEXTURE == nullptr) {
    CHECKERBOARD_TEXTURE = gl::Texture2d::create(loadImage("assets/checkerboard_pattern.png"));
  }
  bounds_ = bounds;
  if (pixel_width == 0 | pixel_height == 0) {
    throw std::invalid_argument("Pixel width or height cannot be zero");
  }
  surface_ = ci::Surface(pixel_width, pixel_height, true);
  Clear();
}

void Canvas::Draw() const {
  gl::color(Color::white());
  gl::Texture2dRef tex = gl::Texture::create(surface_);
  gl::draw(CHECKERBOARD_TEXTURE, bounds_);
  gl::draw(tex, bounds_);
}

ColorA Canvas::GetPixel(size_t x, size_t y) const {
  auto pixel_width = GetPixelWidth();
  auto pixel_height = GetPixelHeight();
  if (x >= pixel_width | y >= pixel_height) {
    throw std::invalid_argument(
        "Coordinates are out of range for canvas of size (" + std::to_string(pixel_width) + ", "
            + std::to_string(pixel_height) + ")");
  }
  return ColorA(surface_.getPixel(vec2(x, y)));
}
void Canvas::SetPixel(size_t x, size_t y, ColorA const &pixel) {
  auto pixel_width = GetPixelWidth();
  auto pixel_height = GetPixelHeight();
  if (x >= pixel_width | y >= pixel_height) {
    return;
  }
  surface_.setPixel(vec2(x, y), pixel);
}
void Canvas::SetPixelScreenSpace(float x, float y, ColorA const &pixel) {
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
  x -= bounds_.getX1();
  y -= bounds_.getY1();
  float scaling_factor_x = bounds_.getWidth() / GetPixelWidth();
  float scaling_factor_y = bounds_.getHeight() / GetPixelHeight();
  size_t row = y / scaling_factor_y;
  size_t col = x / scaling_factor_x;
  return glm::u64vec2(col, row);
}
void Canvas::Clear() {
  auto iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      auto white = ColorAT<unsigned char>::white();
      iter.r() = white.r;
      iter.g() = white.g;
      iter.b() = white.b;
      iter.a() = 0;
    }
  }
}
ColorA Canvas::GetPixelScreenSpace(float x, float y) const {
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
bool Canvas::SaveCanvasToFile(boost::filesystem::path const &p) const {
  try {
    gl::FboRef fbo = gl::Fbo::create(GetPixelWidth(), GetPixelHeight());
    fbo->bindFramebuffer();
    gl::color(Color::white());
    gl::draw(gl::Texture2d::create(surface_));
    fbo->unbindFramebuffer();
    auto texture = fbo->getColorTexture();
    std::string path = p.string();
    if (!p.has_extension()) {
      path += ".png";
    }
    writeImage(path, texture->createSource(), ImageTarget::Options(), "png");
  } catch (...) {
    return false;
  }
  return true;
}
bool Canvas::LoadCanvasFromFile(boost::filesystem::path const &p) {
  Surface copy = Surface(GetPixelWidth(), GetPixelHeight(), true);
  try {
    auto image = loadImage(p, ImageSource::Options(), "png");
    SurfaceRef loaded_surface = Surface::create(image);
    ip::resize(*loaded_surface, &copy);

  } catch (...) {
    return false;
  }
  surface_ = copy;
  return true;
}
}
