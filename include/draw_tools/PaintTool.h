//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
namespace paint {
class PaintTool {
  virtual void DrawOnCanvas(Canvas &canvas, double x_center, double y_center) const = 0;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
