//
// Created by Eric Pfister on 12/1/20.
//

#include <draw_tools/PaintBucket.h>
#include <queue>
using namespace std;
using namespace glm;
namespace paint {

void PaintBucket::DrawButtonOverlay(ci::Rectf bounds) const {
  ci::gl::color(color_);
  ci::gl::drawSolidCircle(bounds.getLowerRight() - vec2(5, 5), 5);
}
void PaintBucket::MouseDown(Canvas &canvas, vec2 const &position) const {

}
// BFS Implementation
void PaintBucket::MouseUp(Canvas &canvas, vec2 const &position) const {
  auto canvas_space = canvas.ToCanvasSpace(position.x, position.y);
  auto start_color = canvas.GetPixelScreenSpace(position.x, position.y);
  std::set<uint64> visited = std::set<uint64>();
  std::queue<glm::u64vec2> to_visit;
  to_visit.push(canvas_space);
  vector<glm::u64vec2> adjacent = vector<glm::u64vec2>(4);
  while (!to_visit.empty() && visited.size() <= canvas.GetPixelWidth() * canvas.GetPixelHeight()) {
    auto front = to_visit.front();
    do {
      front = to_visit.front();
      to_visit.pop();
    } while (!to_visit.empty() && visited.count(front.y * canvas.GetPixelWidth() + front.x) == 1);
    canvas.SetPixel(front.x, front.y, color_);
    visited.insert(front.y * canvas.GetPixelWidth() + front.x);
    adjacent = GetAdjacent(front, canvas.GetPixelWidth(), canvas.GetPixelHeight());
    for (auto &adj : adjacent) {
      double color_distance = PaintTool::ColorDistance(start_color, canvas.GetPixel(adj.x, adj.y));
      if (visited.count(adj.y * canvas.GetPixelWidth() + adj.x) == 0 && color_distance < 0.05) {
        to_visit.push(adj);
      }
    }
  }
}
void PaintBucket::MouseDrag(Canvas &canvas, vec2 const &position) const {

}
void PaintBucket::PopulateDetailedGUI(pretzel::PretzelGuiRef &detail_gui) {
  ci::ColorA temp = color_;
  detail_gui->addColorPicker("Fill Color", &color_);
  color_ = temp;
}
vector<u64vec2> PaintBucket::GetAdjacent(u64vec2 const &pos, size_t width, size_t height) const {
  vector<u64vec2> adjacent;
  if (pos.x > 0) {
    adjacent.push_back(pos - u64vec2(1, 0));
  }
  if (pos.y > 0) {
    adjacent.push_back(pos - u64vec2(0, 1));
  }
  if (pos.x < width - 1) {
    adjacent.push_back(pos + u64vec2(1, 0));
  }
  if (pos.y < height - 1) {
    adjacent.push_back(pos + u64vec2(0, 1));
  }
  return adjacent;
}
}
