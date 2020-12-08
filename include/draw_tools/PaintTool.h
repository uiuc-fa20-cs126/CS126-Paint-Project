//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#include <Canvas.h>
#include <cinder/gl/gl.h>
#import "../blocks/PretzelGUI/src/pretzel/PretzelGui.h"
namespace paint {
class PaintTool {
 public:
  virtual void MouseDown(Canvas &canvas, ci::vec2 const &position) const = 0;
  virtual void MouseUp(Canvas &canvas, ci::vec2 const &position) const = 0;
  virtual void MouseDrag(Canvas &canvas, ci::vec2 const &position) const = 0;
  virtual void DrawButtonOverlay(ci::Rectf bounds) const = 0;
  virtual void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) = 0;
  virtual ~PaintTool() {}
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
