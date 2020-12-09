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
  std::map<std::string, ToolbarButton> buttons_;
  ci::Rectf bounds_;
 private:
  std::string selected_tool_;
  ci::Rectf GetBoundsForTool(std::string const &tool_name) const;
 public:
  Toolbar(ci::Rectf bounds) : bounds_(bounds), selected_tool_("") {}
  void Draw() const;
  void AddButton(ToolbarButton const &button, std::string const &name);
  void OnClick(glm::ivec2 mouse_pos);
  cinder::Rectf const &GetBounds() const;
  ToolbarButton &GetButton(std::string const &name);
  ToolbarButton &GetSelectedButton();
  bool IsToolSelected() const;

};
}
#endif //FINAL_PROJECT_PFISTERFACTOR_INCLUDE_TOOLBAR_H_
