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
/**
 * Draws a shape to the screen
 */
class ShapeTool : public PaintTool {
 public:
  /**
   * The type of shapes we can draw
   */
  enum ShapeType {
    HEART,
    STAR
  };
  ShapeTool(ci::ColorA const &color, size_t size) : color_(color), selected_shape_(ShapeType::STAR), size_(size) {}
  void MouseDown(Canvas &canvas, glm::vec2 const &position) const override;
  void MouseUp(Canvas &canvas, glm::vec2 const &position) const override;
  void MouseDrag(Canvas &canvas, glm::vec2 const &position) const override;
  void DrawMouseOverlay(ci::vec2 const &position) const override;
  void DrawButtonOverlay(ci::Rectf bounds) const override;
  void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) override;
  /**
   * Loads the shape files into static textures
   */
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
  /**
   * The current shape to paint
   */
  ShapeType selected_shape_;
  /**
   * The color of the filled shape
   */
  ci::ColorA color_;
 private:
  size_t size_;
  /**
   * The star shape texture
   */
  static ci::SurfaceRef STAR_SHAPE;
  /**
   * The heart shape texture
   */
  static ci::SurfaceRef HEART_SHAPE;
  /**
   * Names of the shapes to display on the tool window selection
   */
  static std::vector<std::string> SHAPE_NAMES;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_SHAPETOOL_H_
