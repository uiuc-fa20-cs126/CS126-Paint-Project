//
// Created by Eric Pfister on 11/17/20.
//
#include <PaintApp.h>
#include <draw_tools/PaintBrush.h>
#include <draw_tools/PaintBucket.h>
using namespace cinder;
namespace paint {
PaintApp::PaintApp() : canvas_(ci::Rectf(84, 0, 800, 600), 716, 600), toolbar_(ci::Rectf(0, 0, 84, 600)) {
  is_painting_ = false;
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png", new PaintBrush(10, ci::ColorA::black())),
                     "paint_brush");
  toolbar_.AddButton(ToolbarButton("assets/paint_bucket.png", new PaintBucket(ci::ColorA::black())),
                     "paint_bucket");
}
void PaintApp::update() {
  AppBase::update();
}
void PaintApp::draw() {
  AppBase::draw();
  gl::clear(Color::white());
  canvas_.Draw();
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
  if (is_painting_ && event.getWindow()->getBounds().contains(event.getPos())) {
    if (toolbar_.IsToolSelected()) {
      toolbar_.GetSelectedButton().GetTool()->MouseUp(canvas_, event.getPos());
    }
  }
}

}
