//
// Created by Eric Pfister on 11/17/20.
//

#ifndef FINAL_PROJECT_PFISTERFACTOR_INCLUDE_CANVAS_H_
#define FINAL_PROJECT_PFISTERFACTOR_INCLUDE_CANVAS_H_
#include <RGBPixel.h>
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
   * Width of the canvas, in pixels
   */
  size_t pixel_width_;
  /**
   * Height of the canvas, in pixels
   */
  size_t pixel_height_;
  /**
   * One dimensional array of a 2D canvas
   */
  std::vector<RGBPixel> pixels_;
  /**
   * Gets a screen spaced rectangle to draw a pixel given a canvas space coordinate
   * Used in drawing
   */
  ci::Rectf GetPixelSizedToScreenSpace(size_t x, size_t y) const;
 public:
  Canvas(ci::Rectf bounds, size_t pixel_width, size_t pixel_height);
  cinder::Rectf const &GetBounds() const;
  size_t GetPixelWidth() const;
  size_t GetPixelHeight() const;
  /**
   * Gets a pixel in canvas space, i.e. relative to the vector row/column index of the pixel
   *
   */
  RGBPixel const &GetPixel(size_t x, size_t y) const;
  /**
   * Gets a pixel in screen space, i.e. relative to the window
   * Takes the input coordinates (relative to the window) and translates it to an index into the pixel array and grabs the pixel
   */
  RGBPixel const &GetPixelScreenSpace(float x, float y) const;
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
  void SetPixel(size_t x, size_t y, RGBPixel const &pixel);
  /**
   * Sets an individual pixel in screen space, if it exists within the canvas
   * @param x the x coordinate in screen space
   * @param y the y coordinate in screen space
   * @param pixel the color to set the pixel
   */
  void SetPixelScreenSpace(float x, float y, RGBPixel const &pixel);
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
