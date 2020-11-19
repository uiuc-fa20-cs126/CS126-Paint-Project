//
// Created by Eric Pfister on 11/18/20.
//
#include <draw_tools/PaintBrush.h>
#include <catch2/catch.hpp>
#include <cinder/gl/gl.h>
using namespace paint;
using namespace cinder;
TEST_CASE("Paint brush draws a circle correctly") {
  Canvas canvas = Canvas(Rectf(0, 0, 800, 600), 20, 15);

  SECTION("Radius 1") {
    PaintBrush brush = PaintBrush(1, RGBPixel::black());
    REQUIRE(canvas.GetPixel(10, 7) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(10, 6) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(10, 7) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(9, 7) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(11, 7) == RGBPixel::white());
    auto screen_space = canvas.ToScreenSpace(10, 7);
    brush.DrawOnCanvas(canvas, screen_space.x, screen_space.y);
    REQUIRE(canvas.GetPixel(10, 7) == RGBPixel::black());
    REQUIRE(canvas.GetPixel(10, 6) == RGBPixel::black());
    REQUIRE(canvas.GetPixel(10, 8) == RGBPixel::black());
    REQUIRE(canvas.GetPixel(9, 7) == RGBPixel::black());
    REQUIRE(canvas.GetPixel(11, 7) == RGBPixel::black());

    REQUIRE(canvas.GetPixel(11, 9) == RGBPixel::white());
    REQUIRE(canvas.GetPixel(9, 5) == RGBPixel::white());
  }
}