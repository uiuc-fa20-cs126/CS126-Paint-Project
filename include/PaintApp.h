//
// Created by Eric Pfister on 11/17/20.
//

#ifndef FINAL_PROJECT_PFISTERFACTOR_INCLUDE_PAINTAPP_H_
#define FINAL_PROJECT_PFISTERFACTOR_INCLUDE_PAINTAPP_H_

#endif //FINAL_PROJECT_PFISTERFACTOR_INCLUDE_PAINTAPP_H_
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>
#include <Canvas.h>
namespace paint {
class PaintApp : public ci::app::App {
 private:
  Canvas canvas_;
  bool is_painting_;
 public:
  PaintApp();
  void update() override;
  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void mouseMove(ci::app::MouseEvent event) override;
};
}
