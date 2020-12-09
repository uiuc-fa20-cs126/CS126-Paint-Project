//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#include <Canvas.h>
#include <cinder/gl/gl.h>
#include "../blocks/PretzelGUI/src/pretzel/PretzelGui.h"
#include <cmath>
namespace paint {
class PaintTool {
 public:
  virtual void MouseDown(Canvas &canvas, ci::vec2 const &position) const = 0;
  virtual void MouseUp(Canvas &canvas, ci::vec2 const &position) const = 0;
  virtual void MouseDrag(Canvas &canvas, ci::vec2 const &position) const = 0;
  virtual void DrawButtonOverlay(ci::Rectf bounds) const = 0;
  virtual void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) = 0;
  virtual ~PaintTool() {}
  // RGB Color Distance taken from: https://stackoverflow.com/questions/4754506/color-similarity-distance-in-rgba-color-space
  static double ColorDistance(ci::ColorA c1, ci::ColorA c2) {
    return
        std::max(pow(c1.r - c2.r, 2), pow(c1.r - c2.r - c1.a + c2.a, 2)) +
            std::max(pow(c1.g - c2.g, 2), pow(c1.g - c2.g - c1.a + c2.a, 2)) +
            std::max(pow(c1.b - c2.b, 2), pow(c1.b - c2.b - c1.a + c2.a, 2));
  }
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
