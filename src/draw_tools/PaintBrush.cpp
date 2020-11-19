//
// Created by Eric Pfister on 11/18/20.
//

#include <draw_tools/PaintBrush.h>
namespace paint {

void PaintBrush::DrawOnCanvas(paint::Canvas &canvas, double x_center, double y_center) const {
  glm::u64vec2 canvas_space = canvas.ToCanvasSpace(x_center, y_center);
  int int_radius = radius_;
  for (int y = -int_radius; y <= int_radius; y++) {
    for (int x = -int_radius; x <= int_radius; x++) {
      if (x * x + y * y <= int_radius * int_radius) {
        canvas.SetPixel(canvas_space.x + x, canvas_space.y + y, color_);
      }
    }
  }
}
}
