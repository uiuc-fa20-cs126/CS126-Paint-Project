//
// Created by Eric Pfister on 11/18/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTBRUSH_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTBRUSH_H_

#include <Canvas.h>
#include <cinder/gl/gl.h>
#include <vector>
#include <draw_tools/PaintTool.h>
namespace paint {
/**
 * Paintbrush tool, with a configurable radius and color
 */
class PaintBrush : public PaintTool {
 private:
  float radius_;
  ci::ColorA color_;
 public:
  PaintBrush(float radius, ci::ColorA const &color) : radius_(radius), color_(color) {}
  float GetRadius() const {
    return radius_;
  }
  void SetRadius(float radius) {
    radius_ = radius;
  }
  ci::ColorA const &GetColor() const {
    return color_;
  }
  void SetColor(ci::ColorA const &color) {
    color_ = color;
  }
  /**
   * Draws a circle on the canvas
   * @param canvas the canvas to draw on
   * @param x_center x center of the circle in screen space
   * @param y_center y center of the circle in screen space
   */
  void MouseDown(Canvas &canvas, ci::vec2 const &position) const override;
  /**
   * Does nothing for brush tool
   */
  void MouseUp(Canvas &canvas, ci::vec2 const &position) const override;
  /**
   * Draws a circle on the canvas
   * @param canvas the canvas to draw on
   * @param x_center x center of the circle in screen space
   * @param y_center y center of the circle in screen space
   */
  void MouseDrag(Canvas &canvas, ci::vec2 const &position) const override;
  void DrawButtonOverlay(ci::Rectf bounds) const override;
  void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) override;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTBRUSH_H_
