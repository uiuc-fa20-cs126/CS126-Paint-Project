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
/**
 * Application class for paint
 */
class PaintApp : public ci::app::App {
 private:
  /**
   * The canvas that holds the current picture and any pixels
   */
  Canvas canvas_;
  /**
   * A boolean indicating if we're in painting mode, toggled by clicking the screen once
   * Due to a bug in cinder, I cannot use the mouseDrag event as it doesn't work (atleast on my Mac) unless the mouse moves really slowly
   */
  bool is_painting_;
 public:
  PaintApp();
  /**
   * Called every frame to do application logic
   */
  void update() override;
  /**
   * Called when it is time to draw content to the screen
   */
  void draw() override;
  /**
   * Called on mouse button down
   */
  void mouseDown(ci::app::MouseEvent event) override;
  /**
   * Called on mouse movement, inside or outside the window
   */
  void mouseMove(ci::app::MouseEvent event) override;
};
}
