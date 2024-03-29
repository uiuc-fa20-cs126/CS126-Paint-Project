//
// Created by Eric Pfister on 12/8/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_ERASER_H_
#define PAINT_INCLUDE_DRAW_TOOLS_ERASER_H_
#include <draw_tools/PaintTool.h>
namespace paint {
/**
 * Eraser tool
 * Basically a paint brush but with a transparent color
 */
class Eraser : public PaintTool {
 private:
  /**
   * The radius of the brush circle
   */
  float radius_;
 public:
  Eraser(float radius) : radius_(radius) {};
  void MouseDown(Canvas &canvas, glm::vec2 const &position) const override;
  void MouseUp(Canvas &canvas, glm::vec2 const &position) const override;
  void MouseDrag(Canvas &canvas, glm::vec2 const &position) const override;
  void DrawMouseOverlay(ci::vec2 const &position) const override;
  void DrawButtonOverlay(ci::Rectf bounds) const override;
  void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) override;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_ERASER_H_
