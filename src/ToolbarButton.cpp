//
// Created by Eric Pfister on 12/1/20.
//
#include<ToolbarButton.h>
using namespace ci;
namespace paint {
ToolbarButton::ToolbarButton(std::string const &image_path, PaintTool *tool) {
  auto image_source = ci::loadImage(image_path);
  button_image_ = gl::Texture::create(image_source);
  tool_ = std::shared_ptr<PaintTool>(tool);
}
void ToolbarButton::Draw(ci::Rectf const &bounds) const {
  gl::color(Color::white());
  gl::draw(button_image_, bounds);
  tool_.get()->DrawButtonOverlay(bounds);
}
}
