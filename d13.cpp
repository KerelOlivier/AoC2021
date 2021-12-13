#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string s, char delimiter);
int step1(std::vector<std::vector<bool>> grid, std::vector<std::string> folds);
int step2(std::vector<std::vector<bool>> grid, std::vector<std::string> folds);

struct point {
  int x;
  int y;
};

void printGrid(std::vector<std::vector<bool>> grid, int x, int y) {
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      std::cout << (grid[j][i] ? "#" : ".");
    }
    std::cout << std::endl;
  }
}

int main() {
  std::vector<point> points;
  std::vector<std::string> folds;
  std::string s;
  int mxX = 0;
  int mxY = 0;

  while (std::cin >> s) {
    // if s start with a number, it is a number
    if (s[0] >= '0' && s[0] <= '9') {
      std::vector<std::string> tmp = split(s, ',');
      point p;
      p.x = std::stoi(tmp[0]);
      p.y = std::stoi(tmp[1]);
      mxX = std::max(mxX, p.x);
      mxY = std::max(mxY, p.y);
      points.push_back(p);
    } else {
      std::cin >> s;
      std::cin >> s;
      folds.push_back(s);
    }
  }

  std::vector<std::vector<bool>> grid(mxX + 1,
                                      std::vector<bool>(mxY + 1, false));

  // fill grid with points
  for (auto p : points) {
    grid[p.x][p.y] = true;
  }

  printGrid(grid, mxX + 1, mxY + 1);
  std::cout << std::endl;
  // std::cout << step1(grid, folds) << std::endl;
  std::cout << step2(grid, folds) << std::endl;
}

std::vector<std::vector<bool>> fold(std::vector<std::vector<bool>> grid,
                                    std::string foldDir, int foldLine) {

  int width = grid.size();
  int height = grid[0].size();
  if (foldDir == "y") {
    int l = std::max(foldLine, height - foldLine - 1);
    std::vector<std::vector<bool>> newGrid(width, std::vector<bool>(l, false));
    for (int y = 0; y < l; y++) {
      for (int x = 0; x < width; x++) {
        newGrid[x][l - y - 1] =
            (grid[x][foldLine - y - 1] | grid[x][foldLine + y + 1]);
      }
    }
    std::cout << std::endl;
    return newGrid;
  } else {
    int l = std::max(foldLine, width - foldLine - 1);
    std::vector<std::vector<bool>> newGrid(l, std::vector<bool>(height, false));
    for (int x = 0; x < l; x++) {
      for (int y = 0; y < height; y++) {
        newGrid[l - x - 1][y] =
            (grid[foldLine - x - 1][y] | grid[foldLine + x + 1][y]);
      }
    }
    return newGrid;
  }
}

int step1(std::vector<std::vector<bool>> grid, std::vector<std::string> folds) {
  std::vector<std::string> f = split(folds[0], '=');
  std::vector<std::vector<bool>> g = fold(grid, f[0], std::stoi(f[1]));
  printGrid(g, g.size(), g[0].size());
  int count = 0;
  // count true in g
  for (int i = 0; i < g.size(); i++) {
    for (int j = 0; j < g[0].size(); j++) {
      if (g[i][j])
        count++;
    }
  }
  return count;
}
int step2(std::vector<std::vector<bool>> grid, std::vector<std::string> folds) {
  std::vector<std::string> f;
  for(int i = 0; i < folds.size(); i++) {
    f = split(folds[i], '=');
    grid = fold(grid, f[0], std::stoi(f[1]));
  }
  printGrid(grid, grid.size(), grid[0].size());
  return 0;
}
// function to split a string on a delimiter
std::vector<std::string> split(std::string s, char delimiter) {
  std::vector<std::string> v;
  std::string temp;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != delimiter) {
      temp += s[i];
    } else {
      v.push_back(temp);
      temp = "";
    }
  }
  v.push_back(temp);
  return v;
}
