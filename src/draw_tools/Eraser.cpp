//
// Created by Eric Pfister on 12/8/20.
//
#include <draw_tools/Eraser.h>

namespace paint {

void Eraser::MouseDown(Canvas &canvas, glm::vec2 const &position) const {
  this->MouseDrag(canvas, position);
}
void Eraser::MouseUp(Canvas &canvas, glm::vec2 const &position) const {

}
void Eraser::MouseDrag(Canvas &canvas, glm::vec2 const &position) const {
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
        iter.r() = 0;
        iter.g() = 0;
        iter.b() = 0;
        iter.a() = 0;
      }
    }
  }
}
void Eraser::DrawButtonOverlay(ci::Rectf bounds) const {

}
void Eraser::PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) {
  detail_gui->addSlider("Radius", &radius_, 1.0, 500);

}
}
