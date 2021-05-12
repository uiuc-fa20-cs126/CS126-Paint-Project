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
  for (auto const &pair: buttons_) {
    Rectf tool_bounds = GetBoundsForTool(pair.first);
    if (selected_tool_ == pair.first) {
      gl::color(Color::hex(0x778899));
      gl::drawSolidRect(tool_bounds);
    }
    pair.second.Draw(tool_bounds);
  }

}
void Toolbar::AddButton(ToolbarButton const &button, std::string const &name) {
  buttons_.insert(make_pair(name, button));
}
void Toolbar::OnClick(glm::ivec2 mouse_pos, pretzel::PretzelGuiRef &detailed_tool_window) {
  for (auto &button : buttons_) {
    if (GetBoundsForTool(button.first).contains(mouse_pos)) {
      if (selected_tool_ == button.first) {
        selected_tool_ = "";
        detailed_tool_window = nullptr;
      } else {
        selected_tool_ = button.first;
        detailed_tool_window = pretzel::PretzelGui::create("Tool Settings");
        detailed_tool_window->setPos(vec2(600, 0));
        detailed_tool_window->setSize(vec2(100, 250));
        button.second.GetTool()->PopulateDetailedGUI(detailed_tool_window);
      }
      break;
    }
  }
}
ToolbarButton &Toolbar::GetButton(std::string const &name) {
  return buttons_.at(name);
}
ToolbarButton &Toolbar::GetSelectedButton() {
  return GetButton(selected_tool_);
}
ci::Rectf Toolbar::GetBoundsForTool(std::string const &tool_name) const {
  auto button = buttons_.find(tool_name);
  if (button == buttons_.end()) return ci::Rectf();
  size_t tool_index = std::distance(buttons_.begin(), button);
  Rectf inner_rect = Rectf(bounds_.getUpperLeft() + vec2(5, 5), bounds_.getLowerRight() - vec2(5, 5));
  size_t button_count = buttons_.size();
  size_t button_rect_height = inner_rect.getHeight() / button_count;
  size_t y = button_rect_height * tool_index;
  size_t vertical_spacing = (button_rect_height - inner_rect.getWidth()) / 2;
  Rectf rect = Rectf(inner_rect.getX1(),
                     y + vertical_spacing,
                     inner_rect.getX2(),
                     y + vertical_spacing + inner_rect.getWidth());
  return rect;
}
bool Toolbar::IsToolSelected() const {
  return selected_tool_ != "";
}
Rectf const &Toolbar::GetBounds() const {
  return bounds_;
}
}
