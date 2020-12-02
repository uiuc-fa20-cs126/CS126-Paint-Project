//
// Created by Eric Pfister on 11/17/20.
//
#include <PaintApp.h>
#include <draw_tools/PaintBrush.h>
using namespace cinder;
namespace paint {
PaintApp::PaintApp() : canvas_(ci::Rectf(0, 0, 800, 600), 800, 600), toolbar_(ci::Rectf(0, 0, 84, 600)) {
  is_painting_ = false;
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png"), new PaintBrush(20, ci::ColorAT<unsigned char>::black()));
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png"), new PaintBrush(20, ci::ColorAT<unsigned char>::black()));
}
void PaintApp::update() {
  AppBase::update();
}
void PaintApp::draw() {
  AppBase::draw();
  gl::clear(Color::white());
  canvas_.Draw();
  toolbar_.Draw();
}
void PaintApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
  is_painting_ = !is_painting_;
}
void PaintApp::mouseMove(ci::app::MouseEvent event) {
  AppBase::mouseMove(event);
  if (is_painting_ && event.getWindow()->getBounds().contains(event.getPos())) {
  }
}

}
