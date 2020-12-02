//
// Created by Eric Pfister on 12/1/20.
//

#include <draw_tools/PaintBucket.h>
#include <queue>
using namespace std;
using namespace glm;
namespace paint {

void PaintBucket::DrawOnCanvas(paint::Canvas &canvas, double x_center, double y_center) const {
  auto canvas_space = canvas.ToCanvasSpace(x_center, y_center);
  auto start_color = canvas.GetPixelScreenSpace(x_center, y_center);
  vector<bool> visited = vector<bool>(canvas.GetPixelWidth() * canvas.GetPixelHeight(), false);
  std::queue<glm::u64vec2> to_visit;
  visited[canvas_space.y * canvas.GetPixelWidth() + canvas_space.x] = true;
  to_visit.push(canvas_space);
  vector<glm::u64vec2> adjacent = vector<glm::u64vec2>(4);
  while (!to_visit.empty()) {
    auto front = to_visit.front();
    canvas.SetPixel(front.x, front.y, color_);
    visited[front.x * canvas.GetPixelWidth() + front.y] = true;
    to_visit.pop();
    adjacent[0] = glm::clamp(front - glm::u64vec2(1, 0),
                             u64vec2(0, 0),
                             u64vec2(canvas.GetPixelWidth() - 1, canvas.GetPixelHeight() - 1));
    adjacent[1] = glm::clamp(front + glm::u64vec2(1, 0),
                             u64vec2(0, 0),
                             u64vec2(canvas.GetPixelWidth() - 1, canvas.GetPixelHeight() - 1));
    adjacent[2] = glm::clamp(front - glm::u64vec2(0, 1),
                             u64vec2(0, 0),
                             u64vec2(canvas.GetPixelWidth() - 1, canvas.GetPixelHeight() - 1));
    adjacent[3] = glm::clamp(front + glm::u64vec2(0, 1),
                             u64vec2(0, 0),
                             u64vec2(canvas.GetPixelWidth() - 1, canvas.GetPixelHeight() - 1));
    for (auto &adj : adjacent) {
      double color_distance = ColorDistance(start_color, canvas.GetPixel(adj.x, adj.y));
      if (!visited[adj.y * canvas.GetPixelWidth() + adj.x] && color_distance < 0.05) {
        to_visit.push(adj);
      }
    }

  }
}
void PaintBucket::DrawButtonOverlay(ci::Rectf bounds) const {

}
// RGB Color Distance taken from: https://stackoverflow.com/questions/4754506/color-similarity-distance-in-rgba-color-space
double PaintBucket::ColorDistance(ci::ColorAT<unsigned char> c1, ci::ColorAT<unsigned char> c2) const {
  return
      std::max(pow(c1.r - c2.r, 2), pow(c1.r - c2.r - c1.a + c2.a, 2)) +
          std::max(pow(c1.g - c2.g, 2), pow(c1.g - c2.g - c1.a + c2.a, 2)) +
          std::max(pow(c1.b - c2.b, 2), pow(c1.b - c2.b - c1.a + c2.a, 2));
}
}
