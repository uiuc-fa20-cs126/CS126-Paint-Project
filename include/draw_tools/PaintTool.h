//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#include <Canvas.h>
#include <cinder/gl/gl.h>
namespace paint {
class PaintTool {
 public:
  virtual void DrawOnCanvas(Canvas &canvas, double x_center, double y_center) const = 0;
  virtual void DrawButtonOverlay(ci::Rectf bounds) const = 0;
  virtual ~PaintTool() {}
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
