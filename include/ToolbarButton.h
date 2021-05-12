//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_TOOLBARBUTTON_H_
#define PAINT_INCLUDE_TOOLBARBUTTON_H_
#include <cinder/gl/gl.h>
#include <draw_tools/PaintTool.h>
namespace paint {
/**
 * A class that represents a button on the toolbar and its associated tool
 */
class ToolbarButton {
 private:
  /**
   * The button icon to draw
   */
  ci::gl::Texture2dRef button_image_;
  /**
   * The tool this button will activate when selected
   */
  std::shared_ptr<PaintTool> tool_;
 public:
  ToolbarButton(std::string const &image_path, PaintTool *tool);
  std::shared_ptr<PaintTool> const &GetTool() const {
    return tool_;
  }
  void Draw(ci::Rectf const &bounds) const;
  /**
   * Implemented so we can store in a map, just compares the OpenGL texture ID's
   */
  bool operator<(ToolbarButton const &other) const {
    return button_image_->getId() < other.button_image_->getId();
  }

};
}
#endif //PAINT_INCLUDE_TOOLBARBUTTON_H_
