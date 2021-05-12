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
  canvas.Clear();

  SECTION("Radius 2") {
    PaintBrush brush = PaintBrush(2, ColorA::black());
    REQUIRE(canvas.GetPixel(10, 7) == ColorA::white());
    REQUIRE(canvas.GetPixel(10, 6) == ColorA::white());
    REQUIRE(canvas.GetPixel(10, 7) == ColorA::white());
    REQUIRE(canvas.GetPixel(9, 7) == ColorA::white());
    REQUIRE(canvas.GetPixel(11, 7) == ColorA::white());
    auto screen_space = canvas.ToScreenSpace(10, 7);
    brush.MouseDown(canvas, screen_space);
    REQUIRE(canvas.GetPixel(10, 7) == ColorA::black());
    REQUIRE(canvas.GetPixel(10, 6) == ColorA::black());
    REQUIRE(canvas.GetPixel(10, 8) == ColorA::black());
    REQUIRE(canvas.GetPixel(9, 7) == ColorA::black());
    REQUIRE(canvas.GetPixel(11, 7) == ColorA::black());

    REQUIRE(canvas.GetPixel(11, 9) == ColorA::white());
    REQUIRE(canvas.GetPixel(9, 5) == ColorA::white());
  }
}