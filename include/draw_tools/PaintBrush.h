//
// Created by Eric Pfister on 11/18/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTBRUSH_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTBRUSH_H_

#include <Canvas.h>
#include <cinder/gl/gl.h>
#include <vector>
namespace paint {
/**
 * Paintbrush tool, with a configurable radius and color
 */
class PaintBrush {
 private:
  double radius_;
  ci::ColorAT<unsigned char> color_;
 public:
  PaintBrush(double radius, ci::ColorAT<unsigned char> const &color) : radius_(radius), color_(color) {}
  /**
   * Draws a circle on the canvas
   * @param canvas the canvas to draw on
   * @param x_center x center of the circle in screen space
   * @param y_center y center of the circle in screen space
   */
  void DrawOnCanvas(Canvas &canvas, double x_center, double y_center) const;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTBRUSH_H_