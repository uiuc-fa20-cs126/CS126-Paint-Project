//
// Created by Eric Pfister on 11/18/20.
//

#include <draw_tools/PaintBrush.h>
namespace paint {

void PaintBrush::DrawOnCanvas(paint::Canvas &canvas, double x_center, double y_center) const {
  glm::u64vec2 canvas_space = canvas.ToCanvasSpace(x_center, y_center);
  int int_radius = radius_;
  // Create a surface iter over the rectangular area of the circle
  ci::Surface::Iter iter = canvas.GetSurfaceIter(ci::Area(canvas_space - glm::u64vec2(int_radius, int_radius),
                                                          canvas_space + glm::u64vec2(int_radius, int_radius)));
  while (iter.line()) {
    while (iter.pixel()) {
      auto x = iter.x();
      auto y = iter.y();
      if ((x - x_center) * (x - x_center) + (y - y_center) * (y - y_center) <= int_radius * int_radius) {
        iter.r() = color_.r;
        iter.g() = color_.g;
        iter.b() = color_.b;
        iter.a() = color_.a;
      }
    }
  }
}
}
