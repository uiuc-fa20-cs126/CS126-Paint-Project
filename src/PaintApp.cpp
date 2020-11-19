//
// Created by Eric Pfister on 11/17/20.
//
#include <PaintApp.h>
using namespace cinder;
namespace paint {
PaintApp::PaintApp() : canvas_(ci::Rectf(0, 0, 800, 600), 800, 600) {
  is_painting_ = false;
}
void PaintApp::update() {
  AppBase::update();
}
void PaintApp::draw() {
  AppBase::draw();
  gl::clear(Color::white());
  canvas_.Draw();
}
void PaintApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
  is_painting_ = !is_painting_;
}
void PaintApp::mouseDrag(ci::app::MouseEvent event) {
  AppBase::mouseDrag(event);
}
void PaintApp::mouseMove(ci::app::MouseEvent event) {
  AppBase::mouseMove(event);
  if (is_painting_ && event.getWindow()->getBounds().contains(event.getPos())) {
    canvas_.SetPixelScreenSpace(event.getX(), event.getY(), RGBPixel::black());
  }
}

}
