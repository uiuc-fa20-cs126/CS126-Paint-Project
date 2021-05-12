//
// Created by Eric Pfister on 11/17/20.
//

#ifndef FINAL_PROJECT_PFISTERFACTOR_INCLUDE_TOOLBAR_H_
#define FINAL_PROJECT_PFISTERFACTOR_INCLUDE_TOOLBAR_H_
#include <Toolbar.h>
#include <ToolbarButton.h>
#include <draw_tools/PaintTool.h>
#include <map>
#include <cinder/gl/gl.h>
#include <memory>
namespace paint {
class Toolbar {
 private:
  /**
   * A map between button names and their object
   */
  std::map<std::string, ToolbarButton> buttons_;
  /**
   * The boundaries of the toolbar on the screen
   */
  ci::Rectf bounds_;
  /**
   * The currently selected tool on the toolbar
   * Empty if no selected tool
   */
  std::string selected_tool_;
  /**
   * Returns the boundaries for a tool button icon on the toolbar
   * @param tool_name the tool whose boundaries we wish to find
   */
  ci::Rectf GetBoundsForTool(std::string const &tool_name) const;
 public:
  Toolbar(ci::Rectf bounds) : bounds_(bounds), selected_tool_("") {}
  /**
   * Draws the toolbar to the screen
   */
  void Draw() const;
  /**
   * Adds a button to the toolbar
   * @param button the toolbar button object
   * @param name the name of the tool
   */
  void AddButton(ToolbarButton const &button, std::string const &name);
  /**
   * Called when the user clicks on the toolbar
   * @param mouse_pos the position of the mouse
   * @param detailed_tool_window a reference to the detailed tool gui window
   */
  void OnClick(glm::ivec2 mouse_pos, pretzel::PretzelGuiRef &detailed_tool_window);
  cinder::Rectf const &GetBounds() const;
  ToolbarButton &GetButton(std::string const &name);
  ToolbarButton &GetSelectedButton();
  bool IsToolSelected() const;

};
}
#endif //FINAL_PROJECT_PFISTERFACTOR_INCLUDE_TOOLBAR_H_
