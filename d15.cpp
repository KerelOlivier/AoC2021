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

uint heuristic(int x, int y, int width, int height) {
  // return manhattan distance
  return x + y;
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
      if(alt > 9) alt -= 9;
      map[y][x] = alt;
    }
  }

  // print map
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      std::cout << map[y][x];
    }
    std::cout << std::endl;
  }

  // A* algorithm on map
  std::priority_queue<Point> q;
  std::vector<std::vector<uint32_t>> dist(
      height, std::vector<uint32_t>(width, __UINT32_MAX__));
  // Add start
  q.emplace(0, 0, 0);

  uint gScore[height][width];
  uint fScore[height][width];
  bool isInSet[height][width];
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      gScore[y][x] = __UINT32_MAX__;
      fScore[y][x] = __UINT32_MAX__;
      isInSet[y][x] = false;
    }
  }
  gScore[0][0] = 0;
  fScore[0][0] = heuristic(0, 0, width, height);
  isInSet[0][0] = true;

  std::cout << "A*" << std::endl;

  while (!q.empty()) {
    Point p = q.top();
    q.pop();
    // std::cout << "Popped: " << p.x << " " << p.y << std::endl;
    if (p.x == width - 1 && p.y == height - 1) {
      return p.cost;
    }
    if (p.y > 0) {
      // std::cout << "y > 0: " << x << ", " << y << std::endl;
      int alt = gScore[p.y][p.x] + map[p.y - 1][p.x];
      if (alt < gScore[p.y - 1][p.x]) {
        gScore[p.y - 1][p.x] = alt;
        fScore[p.y - 1][p.x] = alt + heuristic(p.x, p.y - 1, width, height);
        if (!isInSet[p.y - 1][p.x]) {
          q.emplace(p.x, p.y - 1, alt);
          isInSet[p.y - 1][p.x] = true;
        }
      }
    }
    if (p.x > 0) {
      // std::cout << "x > 0: " << x << " " << y << std::endl;
      int alt = gScore[p.y][p.x] + map[p.y][p.x - 1];
      if (alt < gScore[p.y][p.x - 1]) {
        gScore[p.y][p.x - 1] = alt;
        fScore[p.y][p.x - 1] = alt + heuristic(p.x - 1, p.y, width, height);
        if (!isInSet[p.y][p.x - 1]) {
          q.emplace(p.x - 1, p.y, alt);
          isInSet[p.y][p.x - 1] = true;
        }
      }
    }
    if (p.x < width - 1) {
      // std::cout << "x < width - 1: " << x << " " << y << std::endl;
      int alt = gScore[p.y][p.x] + map[p.y][p.x + 1];
      if (alt < gScore[p.y][p.x + 1]) {
        gScore[p.y][p.x + 1] = alt;
        fScore[p.y][p.x + 1] = alt + heuristic(p.x + 1, p.y, width, height);
        if (!isInSet[p.y][p.x + 1]) {
          q.emplace(p.x + 1, p.y, alt);
          isInSet[p.y][p.x + 1] = true;
        }
      }
    }
    if (p.y < height - 1) {
      // std::cout << "y < height - 1: " << x << " " << y << std::endl;
      int alt = gScore[p.y][p.x] + map[p.y + 1][p.x];
      if (alt < gScore[p.y + 1][p.x]) {
        gScore[p.y + 1][p.x] = alt;
        fScore[p.y + 1][p.x] = alt + heuristic(p.x, p.y + 1, width, height);
        if (!isInSet[p.y + 1][p.x]) {
          q.emplace(p.x, p.y + 1, alt);
          isInSet[p.y + 1][p.x] = true;
        }
      }
    }
    // std::cout << "===========================" << std::endl;
  }

  return 0;
}
