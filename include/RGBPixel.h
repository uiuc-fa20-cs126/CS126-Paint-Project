//
// Created by Eric Pfister on 11/18/20.
//

#ifndef PAINT_INCLUDE_PIXEL_H_
#define PAINT_INCLUDE_PIXEL_H_

#endif //PAINT_INCLUDE_PIXEL_H_

#include <cinder/gl/gl.h>
namespace paint {
class RGBPixel {
  typedef unsigned char byte;
 public:
  byte red_;
  byte green_;
  byte blue_;
  byte alpha_;

  RGBPixel(byte red, byte green, byte blue, byte alpha) : red_(red), green_(green), blue_(blue), alpha_(alpha) {}
  cinder::ColorA GetCinderColor() const;
  static RGBPixel white() {
    return RGBPixel{255, 255, 255, 255};
  }
  static RGBPixel black() {
    return RGBPixel{0, 0, 0, 255};
  }
  bool operator==(RGBPixel const &other) const;
  bool operator!=(RGBPixel const &other) const;
};
}
