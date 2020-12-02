//
// Created by Eric Pfister on 11/17/20.
//

#include <Toolbar.h>
using namespace ci;
void paint::Toolbar::Draw() const {
  gl::color(ColorA::black());
  gl::drawSolidRect(bounds_);

  Rectf inner_rect = Rectf(bounds_.getUpperLeft() + vec2(5, 5), bounds_.getLowerRight() - vec2(5, 5));
  gl::color(Color::hex(0xC0C0C0));
  gl::drawSolidRect(inner_rect);
}
