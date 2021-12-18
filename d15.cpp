#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

uint32_t step1(std::vector<std::vector<char>> map);
uint32_t step2(std::vector<std::vector<char>> map);

struct Point {
  int x, y;
  uint32_t cost = 0;
  Point(int x, int y) : x(x), y(y) {}
  Point(int x, int y, uint32_t cost) : x(x), y(y), cost(cost) {}

  bool operator<(const Point &other) const { return cost > other.cost; }
  bool operator>(const Point &other) const { return cost < other.cost; }
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Point &other) const { return !(*this == other); }
  bool operator<=(const Point &other) const {
    return *this == other || *this < other;
  }
  bool operator>=(const Point &other) const {
    return *this == other || *this > other;
  }
};

int main() {
  std::string s;
  std::vector<std::vector<char>> map;
  while (std::cin >> s) {
    std::vector<char> row;
    for (char c : s) {
      row.push_back(c);
    }
    map.push_back(row);
  }

  // print map
  for (int y = 0; y < map.size(); y++) {
    for (int x = 0; x < map[y].size(); x++) {
      std::cout << map[y][x] - '0';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << step1(map) << std::endl;
  std::cout << step2(map) << std::endl;

  return 0;
}

uint32_t step1(std::vector<std::vector<char>> map) {
  int width = map[0].size();
  int height = map.size();
  // Dijkstra's algorithm on map
  std::priority_queue<Point> q;
  std::vector<std::vector<uint32_t>> dist(
      height, std::vector<uint32_t>(width, __UINT32_MAX__));
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (y == 0 && x == 0) {
        q.emplace(x, y, 0);
      } else {
        q.emplace(x, y, __UINT32_MAX__);
      }
    }
  }
  dist[0][0] = 0;
  while (!q.empty()) {
    Point p = q.top();
    q.pop();
    if (p.x == width - 1 && p.y == height - 1) {
      return p.cost;
    }
    if (p.y > 0) {
      int alt = dist[p.x][p.y] + (map[p.y - 1][p.x] - '0');
      if (alt < dist[p.x][p.y - 1]) {
        dist[p.x][p.y - 1] = alt;
        q.emplace(p.x, p.y - 1, alt);
      }
    }
    if (p.x < width - 1) {
      int alt = dist[p.x][p.y] + (map[p.y][p.x + 1] - '0');
      if (alt < dist[p.x + 1][p.y]) {
        dist[p.x + 1][p.y] = alt;
        q.emplace(p.x + 1, p.y, alt);
      }
    }
    if (p.y < height - 1) {
      int alt = dist[p.x][p.y] + (map[p.y + 1][p.x] - '0');
      if (alt < dist[p.x][p.y + 1]) {
        dist[p.x][p.y + 1] = alt;
        q.emplace(p.x, p.y + 1, alt);
      }
    }
    if (p.x > 0) {
      int alt = dist[p.x][p.y] + (map[p.y][p.x - 1] - '0');
      if (alt < dist[p.x - 1][p.y]) {
        dist[p.x - 1][p.y] = alt;
        q.emplace(p.x - 1, p.y, alt);
      }
    }
  }

  return 0;
}

uint32_t step2(std::vector<std::vector<char>> m) {
  int w = m[0].size();
  int h = m.size();
  int width = w * 5;
  int height = h * 5;

  ushort map[height][width];
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      ushort mod = x / w + y / h;
      ushort alt = (m[y % h][x % w] - '0' + mod);
      if (alt > 9)
        alt -= 9;
      map[y][x] = alt;
    }
  }

  std::priority_queue<Point> q;
  q.emplace(0, 0);

  uint dist[height][width];
  bool isInSet[height][width];
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      dist[y][x] = __UINT32_MAX__;
      isInSet[y][x] = false;
    }
  }
  dist[0][0] = 0;
  isInSet[0][0] = true;

  while (!q.empty()) {
    Point p = q.top();
    q.pop();
    if (p.x == width - 1 && p.y == height - 1) {
      return p.cost;
    }
    if (p.y > 0) {
      int alt = dist[p.y][p.x] + map[p.y - 1][p.x];
      if (alt < dist[p.y - 1][p.x]) {
        dist[p.y - 1][p.x] = alt;
        if (!isInSet[p.y - 1][p.x]) {
          q.emplace(p.x, p.y - 1, alt);
          isInSet[p.y - 1][p.x] = true;
        }
      }
    }
    if (p.x > 0) {
      int alt = dist[p.y][p.x] + map[p.y][p.x - 1];
      if (alt < dist[p.y][p.x - 1]) {
        dist[p.y][p.x - 1] = alt;
        if (!isInSet[p.y][p.x - 1]) {
          q.emplace(p.x - 1, p.y, alt);
          isInSet[p.y][p.x - 1] = true;
        }
      }
    }
    if (p.x < width - 1) {
      int alt = dist[p.y][p.x] + map[p.y][p.x + 1];
      if (alt < dist[p.y][p.x + 1]) {
        dist[p.y][p.x + 1] = alt;
        if (!isInSet[p.y][p.x + 1]) {
          q.emplace(p.x + 1, p.y, alt);
          isInSet[p.y][p.x + 1] = true;
        }
      }
    }
    if (p.y < height - 1) {
      int alt = dist[p.y][p.x] + map[p.y + 1][p.x];
      if (alt < dist[p.y + 1][p.x]) {
        dist[p.y + 1][p.x] = alt;
        if (!isInSet[p.y + 1][p.x]) {
          q.emplace(p.x, p.y + 1, alt);
          isInSet[p.y + 1][p.x] = true;
        }
      }
    }
  }

  return 0;
}
