//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_TOOLBARBUTTON_H_
#define PAINT_INCLUDE_TOOLBARBUTTON_H_
#include <cinder/gl/gl.h>
namespace paint {
class ToolbarButton {
 private:
  ci::gl::Texture2dRef button_image_;
 public:
  ToolbarButton(std::string const &image_path);
  void Draw(ci::Rectf const &bounds) const;
  bool operator<(ToolbarButton const &other) const {
    return button_image_->getId() < other.button_image_->getId();
  }

};
}
#endif //PAINT_INCLUDE_TOOLBARBUTTON_H_
