//
// Created by Eric Pfister on 11/17/20.
//
#include <PaintApp.h>
#include <draw_tools/PaintBrush.h>
#include <draw_tools/PaintBucket.h>
#include <draw_tools/ShapeTool.h>
#include <draw_tools/Eraser.h>
using namespace cinder;
namespace paint {
PaintApp::PaintApp() : canvas_(ci::Rectf(84, 0, 800, 600), 716, 600), toolbar_(ci::Rectf(0, 0, 84, 600)) {
  is_painting_ = false;
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png", new PaintBrush(10, ci::ColorA::black())),
                     "paint_brush");
  toolbar_.AddButton(ToolbarButton("assets/paint_bucket.png", new PaintBucket(ci::ColorA::black())),
                     "paint_bucket");
  toolbar_.AddButton(ToolbarButton("assets/shape_tool.png", new ShapeTool(ci::ColorA::black(), 10)), "shape_tool");
  toolbar_.AddButton(ToolbarButton("assets/eraser.png", new Eraser(10)), "eraser");
}
void PaintApp::update() {
  AppBase::update();
}
void PaintApp::draw() {
  AppBase::draw();
  gl::clear(Color::white());
  canvas_.Draw();
  if (toolbar_.IsToolSelected()) {
    toolbar_.GetSelectedButton().GetTool()->DrawMouseOverlay(this->getWindow()->getMousePos());
  }
  toolbar_.Draw();
  if (detail_gui != nullptr) detail_gui->draw();
}
void PaintApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
  if (detail_gui != nullptr && detail_gui->getGlobalBounds().contains(event.getPos())) {
    is_painting_ = false;
    return;
  }
  if (toolbar_.GetBounds().contains(event.getPos())) {
    is_painting_ = false;
    toolbar_.OnClick(event.getPos(), detail_gui);
    return;
  }
  if (toolbar_.IsToolSelected()) {
    is_painting_ = !is_painting_;
    if (is_painting_) {
      toolbar_.GetSelectedButton().GetTool()->MouseDown(canvas_, event.getPos());
    }
  }
}
void PaintApp::mouseMove(ci::app::MouseEvent event) {
  AppBase::mouseMove(event);
  if (detail_gui != nullptr && detail_gui->getGlobalBounds().contains(event.getPos())) return;
  if (is_painting_ && event.getWindow()->getBounds().contains(event.getPos())) {
    if (toolbar_.IsToolSelected()) {
      toolbar_.GetSelectedButton().GetTool()->MouseDrag(canvas_, event.getPos());
    }
  }
}
void PaintApp::mouseUp(ci::app::MouseEvent event) {
  if (detail_gui != nullptr && detail_gui->getGlobalBounds().contains(event.getPos())) return;
  if (toolbar_.GetBounds().contains(event.getPos())) return;
  if (event.getWindow()->getBounds().contains(event.getPos())) {
    if (toolbar_.IsToolSelected()) {
      toolbar_.GetSelectedButton().GetTool()->MouseUp(canvas_, event.getPos());
    }
  }
}
void PaintApp::keyDown(ci::app::KeyEvent event) {
  if (!event.isControlDown() && !event.isMetaDown()) return;
  switch (event.getChar()) {
    case 's': {
      is_painting_ = false;
      boost::filesystem::path save_path = getSaveFilePath();
      canvas_.SaveCanvasToFile(save_path);
      break;
    }
    case 'l': {

      break;
    }
    default: {

      break;
    }
  }
}

}
