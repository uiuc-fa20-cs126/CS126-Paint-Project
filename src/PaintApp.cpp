//
// Created by Eric Pfister on 11/17/20.
//
#include <PaintApp.h>
#include <draw_tools/PaintBrush.h>
using namespace cinder;
namespace paint {
PaintApp::PaintApp() : canvas_(ci::Rectf(84, 0, 800, 600), 716, 600), toolbar_(ci::Rectf(0, 0, 84, 600)) {
  is_painting_ = false;
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png", new PaintBrush(20, ci::ColorAT<unsigned char>::black())),
                     "paint_brush_black");
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png", new PaintBrush(20, ci::ColorAT<unsigned char>::white())),
                     "paint_brush_white");
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png",
                                   new PaintBrush(20, ci::ColorAT<unsigned char>::hex(0xff0000))), "paint_brush_red");
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png",
                                   new PaintBrush(20, ci::ColorAT<unsigned char>::hex(0x00ff00))), "paint_brush_green");
  toolbar_.AddButton(ToolbarButton("assets/paint_brush.png",
                                   new PaintBrush(20, ci::ColorAT<unsigned char>::hex(0x0000ff))), "paint_brush_blue");
  toolbar_.AddButton(ToolbarButton("assets/paint_bucket.png", new PaintBrush(20, ci::ColorAT<unsigned char>::black())),
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
}
void PaintApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
  if (toolbar_.GetBounds().contains(event.getPos())) {
    is_painting_ = false;
    toolbar_.OnClick(event.getPos());
    return;
  }
  if (toolbar_.IsToolSelected()) {
    if (!is_painting_) {
      toolbar_.GetSelectedButton().GetTool()->DrawOnCanvas(canvas_, event.getX(), event.getY());
    }
    is_painting_ = !is_painting_;
  }
}
void PaintApp::mouseMove(ci::app::MouseEvent event) {
  AppBase::mouseMove(event);
  if (is_painting_ && event.getWindow()->getBounds().contains(event.getPos())) {
    if (toolbar_.IsToolSelected()) {
      toolbar_.GetSelectedButton().GetTool()->DrawOnCanvas(canvas_, event.getX(), event.getY());
    }
  }
}

}
