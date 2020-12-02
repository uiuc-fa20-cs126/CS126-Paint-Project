//
// Created by Eric Pfister on 11/17/20.
//

#include <Toolbar.h>
using namespace ci;
namespace paint {
void Toolbar::Draw() const {
  gl::color(ColorA::black());
  gl::drawSolidRect(bounds_);

  Rectf inner_rect = Rectf(bounds_.getUpperLeft() + vec2(5, 5), bounds_.getLowerRight() - vec2(5, 5));
  gl::color(Color::hex(0xC0C0C0));
  gl::drawSolidRect(inner_rect);
  size_t button_count = buttons_.size();
  size_t button_rect_height = inner_rect.getHeight() / button_count;
  size_t y = 0;
  for (auto const &pair : buttons_) {
    size_t vertical_spacing = (button_rect_height - inner_rect.getWidth()) / 2;
    auto rect = Rectf(inner_rect.getX1(),
                      y + vertical_spacing,
                      inner_rect.getX2(),
                      y + vertical_spacing + inner_rect.getWidth());
    pair.first.Draw(rect);
    y += button_rect_height;
  }

}
void Toolbar::AddButton(ToolbarButton const &button, paint::PaintTool *tool) {
  auto ptr = std::unique_ptr<PaintTool>(tool);
  buttons_.insert(std::make_pair(button, std::move(ptr)));
}
}
