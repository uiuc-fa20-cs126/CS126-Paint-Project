//
// Created by Eric Pfister on 11/17/20.
//

#ifndef FINAL_PROJECT_PFISTERFACTOR_INCLUDE_CANVAS_H_
#define FINAL_PROJECT_PFISTERFACTOR_INCLUDE_CANVAS_H_
#include <cinder/gl/gl.h>
#include <vector>
namespace paint {
/**
 * Canvas object, handles holding the data for all the pixels within the program and manipulating them
 */
class Canvas {
 private:
  /**
   * Where on the window the canvas will be drawn
   */
  ci::Rectf bounds_;
  /**
   * The surface object we draw too
   */
  ci::Surface surface_;
  static ci::gl::Texture2dRef CHECKERBOARD_TEXTURE;
  ci::Rectf GetPixelSizedToScreenSpace(size_t x, size_t y) const;
 public:
  Canvas(ci::Rectf bounds, size_t pixel_width, size_t pixel_height);
  cinder::Rectf const &GetBounds() const;
  size_t GetPixelWidth() const;
  size_t GetPixelHeight() const;
  ci::Surface::Iter GetSurfaceIter(ci::Area area = ci::Area());
  bool SaveCanvasToFile(boost::filesystem::path const &p) const;
  bool LoadCanvasFromFile(boost::filesystem::path const &p);
  /**
   * Gets a pixel in canvas space, i.e. relative to the vector row/column index of the pixel
   *
   */
  ci::ColorA GetPixel(size_t x, size_t y) const;
  /**
   * Gets a pixel in screen space, i.e. relative to the window
   * Takes the input coordinates (relative to the window) and translates it to an index into the pixel array and grabs the pixel
   */
  ci::ColorA GetPixelScreenSpace(float x, float y) const;
  /**
   * Resets the canvas to all white pixels
   */
  void Clear();
  /**
   * Sets an individual pixel in canvas space
   * @param x the column of the pixel
   * @param y the row of the pixel
   * @param pixel the color to set the pixel
   */
  void SetPixel(size_t x, size_t y, ci::ColorA const &pixel);
  /**
   * Sets an individual pixel in screen space, if it exists within the canvas
   * @param x the x coordinate in screen space
   * @param y the y coordinate in screen space
   * @param pixel the color to set the pixel
   */
  void SetPixelScreenSpace(float x, float y, ci::ColorA const &pixel);
  /**
   * Converts a coordinate from screen space to canvas space
   * @param x the x coordinate in screen space
   * @param y the y coordinate in screen space
   */
  glm::u64vec2 ToCanvasSpace(float x, float y) const;
  /**
   * Converts a coordinate from screen space to canvas space
   * @param x the x coordinate in canvas space
   * @param y the y coordinate in canvas space
   */
  glm::vec2 ToScreenSpace(size_t x, size_t y) const;
  /**
   * Draws the canvas and all its pixels to the screen
   */
  void Draw() const;
};
}
#endif //FINAL_PROJECT_PFISTERFACTOR_INCLUDE_CANVAS_H_
