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
  uint32_t cost;
  Point(int x, int y, uint32_t cost) : x(x), y(y), cost(cost) {}

  bool operator<(const Point &other) const { return cost > other.cost; }
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
    // std::cout << p.x << " " << p.y << " " << dist[p.x][p.y] << std::endl;
    if (p.x == width - 1 && p.y == height - 1) {
      return p.cost;
    }
    if (p.y > 0) {
      int alt = dist[p.x][p.y] + (map[p.y - 1][p.x] - '0');
      if (alt < dist[p.x][p.y - 1]) {
        dist[p.x][p.y - 1] = alt;
        q.emplace(p.x, p.y - 1, alt);
        // std::cout << "N: " << dist[p.x][p.y] << " " << (map[p.y - 1][p.x] -
        // '0')
        //   << " " << alt << std::endl;
      }
    }
    if (p.x < width - 1) {
      int alt = dist[p.x][p.y] + (map[p.y][p.x + 1] - '0');
      if (alt < dist[p.x + 1][p.y]) {
        dist[p.x + 1][p.y] = alt;
        q.emplace(p.x + 1, p.y, alt);
        // std::cout << "E: " << dist[p.x][p.y] << " " << (map[p.y][p.x + 1] -
        // '0')
        //   << " " << alt << std::endl;
      }
    }
    if (p.y < height - 1) {
      int alt = dist[p.x][p.y] + (map[p.y + 1][p.x] - '0');
      if (alt < dist[p.x][p.y + 1]) {
        dist[p.x][p.y + 1] = alt;
        q.emplace(p.x, p.y + 1, alt);
        // std::cout << "S: " << dist[p.x][p.y] << " " << (map[p.y + 1][p.x] -
        // '0')
        //   << " " << alt << std::endl;
      }
    }
    if (p.x > 0) {
      int alt = dist[p.x][p.y] + (map[p.y][p.x - 1] - '0');
      if (alt < dist[p.x - 1][p.y]) {
        dist[p.x - 1][p.y] = alt;
        q.emplace(p.x - 1, p.y, alt);
        // std::cout << "W: " << dist[p.x][p.y] << " " << (map[p.y][p.x - 1] -
        // '0')
        //   << " " << alt << std::endl;
      }
    }

    // std::cout << std::endl;
  }

  return 0;
}

int findShortes(std::vector<std::vector<uint>> map) {
  int minId = 0;
  int min = map[0][0];
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] < min) {
        min = map[i][j];
        minId = i;
      }
    }
  }
  return minId;
}

uint32_t step2(std::vector<std::vector<char>> map) {
  int width = map[0].size();
  int height = map.size();
  // Dijkstra's algorithm on map
  bool visited[height][width];
  std::unordered_map<uint, uint> Q;
  for (int y = 0; y < height * 5; y++) {
    for (int x = 0; x < width * 5; x++) {
      Q[y * width + x] = __UINT32_MAX__;
      visited[y][x] = false;
    }
  }
  Q[0] = 0;
  // find the minimum element in set Q

  while (!Q.empty()) {
    auto it = std::min_element(
        Q.begin(), Q.end(),
        [](decltype(Q)::value_type &l, decltype(Q)::value_type &r) -> bool {
          return l.second < r.second;
        });
    auto q = Q.extract(it);
    int row = q.key() / width;
    int col = q.key() % width;
    visited[row][col] = true;
    if (row == height * 5 - 1 && col == width * 5 - 1) {
      return q.mapped();
    }
    // if (row > 0) {
    //   uint r = row%height - 1 < 0 ? height - 1 : row%height - 1;
    //   uint c = col%width < 0;
    //   uint alt = q.mapped() + (map[r][c] - '0');

    //   if (visited[ro]) &&
    //       alt < Q[(row - 1) * width + col]) {
    //     Q[(row - 1) * width + col] = alt;
    //   }
    // }
  }
  return 0;
}
