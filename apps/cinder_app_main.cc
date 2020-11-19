#include <PaintApp.h>
#include <cinder/app/RendererGl.h>

void prepareSettings(paint::PaintApp::Settings *settings) {
  settings->setTitle("Paint");
  settings->setBorderless(false);
  settings->disableFrameRate();
  cinder::gl::enableVerticalSync(true);
  settings->setHighDensityDisplayEnabled(true);
  settings->setPowerManagementEnabled(false);
  settings->setMultiTouchEnabled(true);
  settings->setWindowSize(800, 600);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(paint::PaintApp, ci::app::RendererGl, prepareSettings);
