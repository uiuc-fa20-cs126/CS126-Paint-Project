//
// Created by Eric Pfister on 12/8/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_SHAPETOOL_H_
#define PAINT_INCLUDE_DRAW_TOOLS_SHAPETOOL_H_
#include <draw_tools/PaintTool.h>
#include <cinder/gl/gl.h>
#include <cinder/Color.h>
#include "../../../../../../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/sys/_types/_size_t.h"
namespace paint {
class ShapeTool : public PaintTool {
 public:
  enum ShapeType {
    HEART,
    STAR
  };
  ShapeTool(ci::ColorA const &color, size_t size) : color_(color), selected_shape_(ShapeType::STAR), size_(size) {}
  void MouseDown(Canvas &canvas, glm::vec2 const &position) const override;
  void MouseUp(Canvas &canvas, glm::vec2 const &position) const override;
  void MouseDrag(Canvas &canvas, glm::vec2 const &position) const override;
  void DrawButtonOverlay(ci::Rectf bounds) const override;
  void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) override;
  static void LoadShapefiles();
  ShapeType GetSelectedShape() const {
    return selected_shape_;
  }
  void SetSelectedShape(ShapeType selected_shape) {
    selected_shape_ = selected_shape;
  }
  ci::ColorA const &GetColor() const {
    return color_;
  }
  void SetColor(ci::ColorA const &color) {
    color_ = color;
  }
  size_t const &GetSize() const {
    return size_;
  }
  void SetSize(size_t const &size) {
    size_ = size;
  }
 private:
  ShapeType selected_shape_;
  ci::ColorA color_;
 private:
  size_t size_;
  static ci::SurfaceRef STAR_SHAPE;
  static ci::SurfaceRef HEART_SHAPE;
  static std::vector<std::string> SHAPE_NAMES;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_SHAPETOOL_H_
