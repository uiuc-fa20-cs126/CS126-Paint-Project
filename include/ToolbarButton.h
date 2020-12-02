//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_TOOLBARBUTTON_H_
#define PAINT_INCLUDE_TOOLBARBUTTON_H_
#include <cinder/gl/gl.h>
#include <draw_tools/PaintTool.h>
namespace paint {
class ToolbarButton {
 private:
  ci::gl::Texture2dRef button_image_;
  std::shared_ptr<PaintTool> tool_;
 public:
  ToolbarButton(std::string const &image_path, PaintTool *tool);
  std::shared_ptr<PaintTool> const &GetTool() const {
    return tool_;
  }
  void Draw(ci::Rectf const &bounds) const;
  bool operator<(ToolbarButton const &other) const {
    return button_image_->getId() < other.button_image_->getId();
  }

};
}
#endif //PAINT_INCLUDE_TOOLBARBUTTON_H_
