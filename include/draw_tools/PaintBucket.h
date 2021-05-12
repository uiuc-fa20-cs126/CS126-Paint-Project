//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
#include <draw_tools/PaintTool.h>
#include <cinder/gl/gl.h>
#import "../../blocks/PretzelGUI/src/pretzel/PretzelGui.h"
namespace paint {
/**
 * Fills in an area with a specific color
 */
class PaintBucket : public PaintTool {
 private:
  ci::ColorA color_;
  float tolerance_;
  /**
   * Gets adjacent positions to the passed in position, constrained between 0 and width/height
   * @param pos the position whose neighbors we wish to find
   * @param width the x upper bound of the area this position lies in
   * @param height the y upper bound of the area this position lies in
   * @return a vector containing adjacent points to pos
   */
  std::vector<glm::u64vec2> GetAdjacent(glm::u64vec2 const &pos, size_t width, size_t height) const;
 public:
  PaintBucket(ci::ColorA color) : color_(color), tolerance_(0.05) {}
  void DrawMouseOverlay(ci::vec2 const &position) const override;
  void DrawButtonOverlay(ci::Rectf bounds) const override;
  void MouseDown(Canvas &canvas, ci::vec2 const &position) const override;
  void MouseUp(Canvas &canvas, ci::vec2 const &position) const override;
  void MouseDrag(Canvas &canvas, ci::vec2 const &position) const override;
  void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) override;
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTBUCKET_H_
