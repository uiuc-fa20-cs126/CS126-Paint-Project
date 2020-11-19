//
// Created by Eric Pfister on 11/17/20.
//

#define CATCH_CONFIG_MAIN
#include <Canvas.h>
#include <catch2/catch.hpp>
#include <cinder/gl/gl.h>
using namespace paint;
Canvas canvas = Canvas(ci::Rectf(0, 0, 800, 600), 20, 15);
RGBPixel red = RGBPixel(255, 0, 0, 255);
RGBPixel blue = RGBPixel(0, 255, 0, 255);
RGBPixel green = RGBPixel(0, 0, 255, 255);
TEST_CASE("Converting between canvas and screen space") {
  // Convert to screen space
  auto screen_space_1 = canvas.ToScreenSpace(0, 0);
  auto screen_space_2 = canvas.ToScreenSpace(10, 6);
  auto screen_space_3 = canvas.ToScreenSpace(19, 14);
  // Convert back to canvas space
  auto canvas_space_1 = canvas.ToCanvasSpace(screen_space_1.x, screen_space_1.y);
  auto canvas_space_2 = canvas.ToCanvasSpace(screen_space_2.x, screen_space_2.y);
  auto canvas_space_3 = canvas.ToCanvasSpace(screen_space_3.x, screen_space_3.y);
  // Ensure they match
  REQUIRE(canvas_space_1 == glm::u64vec2(0, 0));
  REQUIRE(canvas_space_2 == glm::u64vec2(10, 6));
  REQUIRE(canvas_space_3 == glm::u64vec2(19, 14));
}
TEST_CASE("Setting a pixel") {
  SECTION("Canvas space") {
    canvas.Clear();
    REQUIRE(canvas.GetPixel(0, 0) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(10, 7) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(19, 14) == RGBPixel::white());
    canvas.SetPixel(0, 0, red);
    canvas.SetPixel(10, 7, green);
    canvas.SetPixel(19, 14, blue);
    REQUIRE(canvas.GetPixel(0, 0) == red);
    REQUIRE(canvas.GetPixel(10, 7) == green);
    REQUIRE(canvas.GetPixel(19, 14) == blue);
  }SECTION("Screen space") {
    canvas.Clear();
    REQUIRE(canvas.GetPixelScreenSpace(0, 0) == RGBPixel::white());
    REQUIRE(canvas.GetPixelScreenSpace(400, 300) == RGBPixel::white());
    REQUIRE(canvas.GetPixelScreenSpace(799, 599) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(0, 0) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(10, 7) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(19, 14) == RGBPixel::white());
    canvas.SetPixelScreenSpace(0, 0, red);
    canvas.SetPixelScreenSpace(400, 300, green);
    canvas.SetPixelScreenSpace(799, 599, blue);
    REQUIRE(canvas.GetPixelScreenSpace(0, 0) == red);
    REQUIRE(canvas.GetPixelScreenSpace(400, 300) == green);
    REQUIRE(canvas.GetPixelScreenSpace(799, 599) == blue);
    REQUIRE(canvas.GetPixel(0, 0) == red);
    REQUIRE(canvas.GetPixel(10, 7) == green);
    REQUIRE(canvas.GetPixel(19, 14) == blue);
  }
}
