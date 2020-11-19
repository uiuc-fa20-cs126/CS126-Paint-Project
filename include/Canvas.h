//
// Created by Eric Pfister on 11/17/20.
//

#ifndef FINAL_PROJECT_PFISTERFACTOR_INCLUDE_CANVAS_H_
#define FINAL_PROJECT_PFISTERFACTOR_INCLUDE_CANVAS_H_

#endif //FINAL_PROJECT_PFISTERFACTOR_INCLUDE_CANVAS_H_
#include <RGBPixel.h>
#include <cinder/gl/gl.h>
#include <vector>
namespace paint {
class Canvas {
 private:
  ci::Rectf bounds_;
  size_t pixel_width_;
  size_t pixel_height_;
  std::vector<RGBPixel> pixels_;
  ci::Rectf ToScreenSpace(size_t x, size_t y) const;
 public:
  Canvas(ci::Rectf bounds, size_t pixel_width, size_t pixel_height);
  RGBPixel const &GetPixel(size_t x, size_t y) const;
  void SetPixel(size_t x, size_t y, RGBPixel const &pixel);
  void SetPixelScreenSpace(float x, float y, RGBPixel const &pixel);
  void Draw() const;
};
}