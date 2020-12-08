//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
#include <draw_tools/PaintTool.h>
#include <cinder/gl/gl.h>
#import "../../blocks/PretzelGUI/src/pretzel/PretzelGui.h"
namespace paint {
class PaintBucket : public PaintTool {
 private:
  ci::ColorA color_;
  double ColorDistance(ci::ColorA c1, ci::ColorA c2) const;
 public:
  PaintBucket(ci::ColorA color) : color_(color) {}
  void DrawButtonOverlay(ci::Rectf bounds) const override;
  void MouseDown(Canvas &canvas, ci::vec2 const &position) const override;
  void MouseUp(Canvas &canvas, ci::vec2 const &position) const override;
  void MouseDrag(Canvas &canvas, ci::vec2 const &position) const override;
  void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) override;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
