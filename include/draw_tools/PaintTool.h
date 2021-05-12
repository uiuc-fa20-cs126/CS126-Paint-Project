//
// Created by Eric Pfister on 12/1/20.
//

#ifndef PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#define PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
#include <Canvas.h>
#include <cinder/gl/gl.h>
#include "../blocks/PretzelGUI/src/pretzel/PretzelGui.h"
#include <cmath>
namespace paint {
/**
 * Parent class for all tools that paint on the canvas
 */
class PaintTool {
 public:
  /**
   * Called when a user left clicks their mouse in the canvas window
   * @param canvas the canvas to draw on
   * @param position the position of the mouse click, relative to the cinder window
   */
  virtual void MouseDown(Canvas &canvas, ci::vec2 const &position) const = 0;
  /**
   * Called when a user releases left click on their mouse in the canvas window
   * @param canvas the canvas to draw on
   * @param position the position of the mouse click, relative to the cinder window
   */
  virtual void MouseUp(Canvas &canvas, ci::vec2 const &position) const = 0;
  /**
   * Called when a user drags the mouse
   * @param canvas the canvas to draw on
   * @param position the current position of the mouse, relative to the cinder window
   */
  virtual void MouseDrag(Canvas &canvas, ci::vec2 const &position) const = 0;
  /**
   * Called when time to draw the toolbar button icon, allows drawing dynamic information (such as color, radius) to the button icon
   * @param bounds the bounds of the toolbar button icon on the screen
   */
  virtual void DrawButtonOverlay(ci::Rectf bounds) const = 0;
  /**
   * Called every frame to draw a mouse overlay for the tool
   * @param position the position of the mouse
   */
  virtual void DrawMouseOverlay(ci::vec2 const &position) const = 0;
  /**
   * Called when tool is selected to populate the tool property window with gui elements to configure the tool
   * Add stuff like sliders or color pickers here
   * @param detail_gui the tool gui window
   */
  virtual void PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) = 0;
  virtual ~PaintTool() {}
  /**
   * Calculates the RGB color distance between two colors
   * Taken from: https://stackoverflow.com/questions/4754506/color-similarity-distance-in-rgba-color-space
   * @param c1 the first color
   * @param c2 the second color
   * @return the distance between these color points in RGB color space
   */
  //
  static double ColorDistance(ci::ColorA c1, ci::ColorA c2) {
    return
        std::max(pow(c1.r - c2.r, 2), pow(c1.r - c2.r - c1.a + c2.a, 2)) +
            std::max(pow(c1.g - c2.g, 2), pow(c1.g - c2.g - c1.a + c2.a, 2)) +
            std::max(pow(c1.b - c2.b, 2), pow(c1.b - c2.b - c1.a + c2.a, 2));
  }
};
}
#endif //PAINT_INCLUDE_DRAW_TOOLS_PAINTTOOL_H_
