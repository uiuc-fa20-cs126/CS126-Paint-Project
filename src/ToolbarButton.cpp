//
// Created by Eric Pfister on 12/1/20.
//
#include<ToolbarButton.h>
using namespace ci;
namespace paint {
ToolbarButton::ToolbarButton(std::string const &image_path) {
  auto image_source = ci::loadImage(image_path);
  button_image_ = gl::Texture::create(image_source);
}
void ToolbarButton::Draw(ci::Rectf area) const {
  gl::color(Color::white());
  gl::draw(button_image_, area);
}
}
