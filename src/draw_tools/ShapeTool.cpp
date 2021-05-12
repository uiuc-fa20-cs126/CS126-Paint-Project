//
// Created by Eric Pfister on 12/8/20.
//
#include <draw_tools/ShapeTool.h>
using namespace ci;
namespace paint {
ci::SurfaceRef ShapeTool::STAR_SHAPE;
ci::SurfaceRef ShapeTool::HEART_SHAPE;
std::vector<std::string> ShapeTool::SHAPE_NAMES = {"Heart", "Star"};
void ShapeTool::MouseDown(Canvas &canvas, glm::vec2 const &position) const {

}
void ShapeTool::MouseUp(Canvas &canvas, glm::vec2 const &position) const {
  auto canvas_space = canvas.ToCanvasSpace(position.x, position.y);
  SurfaceRef shape_surface = (selected_shape_ == ShapeType::HEART) ? ShapeTool::HEART_SHAPE : ShapeTool::STAR_SHAPE;
  double scaling_factor_x = shape_surface->getWidth() / static_cast<double>(size_);
  double scaling_factor_y = shape_surface->getHeight() / static_cast<double>(size_);
  auto bounds = Area(canvas_space.x - size_ / 2,
                     canvas_space.y - size_ / 2,
                     canvas_space.x + size_ / 2,
                     canvas_space.y + size_ / 2);
  auto canvas_iter = canvas.GetSurfaceIter(bounds);
  while (canvas_iter.line()) {
    while (canvas_iter.pixel()) {
      size_t shape_x = glm::clamp((canvas_iter.x() - bounds.getX1()) * scaling_factor_x,
                                  0.0,
                                  static_cast<double>(shape_surface->getWidth() - 1));
      size_t shape_y = glm::clamp((canvas_iter.y() - bounds.getY1()) * scaling_factor_y,
                                  0.0,
                                  static_cast<double>(shape_surface->getHeight() - 1));
      auto pixel = shape_surface->getPixel(vec2(shape_x, shape_y));
      if (PaintTool::ColorDistance(pixel, ColorAT<unsigned char>::black()) < 0.05) {
        canvas_iter.r() = color_.r * 255;
        canvas_iter.g() = color_.g * 255;
        canvas_iter.b() = color_.b * 255;
        canvas_iter.a() = color_.a * 255;
      }
    }
  }
}
void ShapeTool::MouseDrag(Canvas &canvas, glm::vec2 const &position) const {

}
void ShapeTool::DrawButtonOverlay(ci::Rectf bounds) const {
  ci::gl::color(color_);
  ci::gl::drawSolidCircle(bounds.getLowerRight() - vec2(5, 5), 5);
}
void ShapeTool::PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) {
  ColorA temp = color_;
  detail_gui->addColorPicker("Brush Color", &color_);
  color_ = temp;
  detail_gui->addSlider("Size", reinterpret_cast<int *>(&size_), 1, 500);
  detail_gui->addEnum("Shape", &ShapeTool::SHAPE_NAMES, reinterpret_cast<int *>(&selected_shape_));

}
void ShapeTool::LoadShapefiles() {
  ShapeTool::HEART_SHAPE = Surface::create(loadImage("assets/shape_tool/heart.png"));
  ShapeTool::STAR_SHAPE = Surface::create(loadImage("assets/shape_tool/star.png"));
}
void ShapeTool::DrawMouseOverlay(vec2 const &position) const {
  SurfaceRef shape_surface = (selected_shape_ == ShapeType::HEART) ? ShapeTool::HEART_SHAPE : ShapeTool::STAR_SHAPE;
  gl::Texture2dRef shape = gl::Texture2d::create(*shape_surface);
  auto bounds = Rectf(position.x - size_ / 2,
                      position.y - size_ / 2,
                      position.x + size_ / 2,
                      position.y + size_ / 2);
  gl::color(ColorA::white());
  gl::draw(shape, bounds);
}
}
