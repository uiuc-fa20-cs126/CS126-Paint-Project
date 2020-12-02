//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
#include <draw_tools/PaintTool.h>
#include <cinder/gl/gl.h>
namespace paint {
class PaintBucket : public PaintTool {
 private:
  ci::ColorAT<unsigned char> color_;
  double ColorDistance(ci::ColorAT<unsigned char> c1, ci::ColorAT<unsigned char> c2) const;
 public:
  PaintBucket(ci::ColorAT<unsigned char> color) : color_(color) {}
  void DrawOnCanvas(Canvas &canvas, double x_center, double y_center) const override;
  void DrawButtonOverlay(ci::Rectf bounds) const override;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
