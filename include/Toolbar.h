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
  std::map<ToolbarButton, std::unique_ptr<PaintTool>> buttons_;
  ci::Rectf bounds_;
 public:
  Toolbar(ci::Rectf bounds) : bounds_(bounds) {}
  void Draw() const;

};
}
#endif //FINAL_PROJECT_PFISTERFACTOR_INCLUDE_TOOLBAR_H_
