//
// Created by Eric Pfister on 11/18/20.
//

#include <draw_tools/PaintBrush.h>
using namespace ci;
namespace paint {

void PaintBrush::DrawButtonOverlay(ci::Rectf bounds) const {
  gl::color(color_);
  gl::drawSolidCircle(bounds.getLowerRight() - vec2(5, 5), 5);
}
void PaintBrush::MouseDown(Canvas &canvas, vec2 const &position) const {
  this->MouseDrag(canvas, position);
}
void PaintBrush::MouseUp(Canvas &canvas, vec2 const &position) const {

}
void PaintBrush::MouseDrag(Canvas &canvas, vec2 const &position) const {
  glm::u64vec2 canvas_space = canvas.ToCanvasSpace(position.x, position.y);
  int int_radius = radius_;
  // Create a surface iter over the rectangular area of the circle
  ci::Surface::Iter iter = canvas.GetSurfaceIter(ci::Area(canvas_space - glm::u64vec2(int_radius, int_radius),
                                                          canvas_space + glm::u64vec2(int_radius, int_radius)));
  while (iter.line()) {
    while (iter.pixel()) {
      auto x = iter.x();
      auto y = iter.y();
      if ((x - canvas_space.x) * (x - canvas_space.x) + (y - canvas_space.y) * (y - canvas_space.y)
          <= int_radius * int_radius) {
        // Convert float color value to byte color value
        iter.r() = color_.r * 255;
        iter.g() = color_.g * 255;
        iter.b() = color_.b * 255;
        iter.a() = color_.a * 255;
      }
    }
  }
}
void PaintBrush::PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) {
  // Workaround for color picker resetting color
  ColorA temp = color_;
  detail_gui->addColorPicker("Brush Color", &color_);
  color_ = temp;
  detail_gui->addSlider("Radius", &radius_, 1.0, 500.0);
}
void PaintBrush::DrawMouseOverlay(vec2 const &position) const {
  gl::color(ColorA::black());
  gl::drawStrokedCircle(position, radius_);
}
}
