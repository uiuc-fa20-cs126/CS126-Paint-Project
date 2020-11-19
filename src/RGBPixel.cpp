//
// Created by Eric Pfister on 11/18/20.
//

#include <RGBPixel.h>

namespace paint {
cinder::ColorA RGBPixel::GetCinderColor() const {
  uint32_t packed = (alpha_ << 24) | (red_ << 16) | (green_ << 8) | blue_;
  return cinder::ColorA::hexA(packed);
}
bool RGBPixel::operator==(RGBPixel const &other) const {
  return red_ == other.red_ && green_ == other.green_ && blue_ == other.blue_ && alpha_ == other.alpha_;
}
bool RGBPixel::operator!=(RGBPixel const &other) const {
  return !(*this == other);
}
}