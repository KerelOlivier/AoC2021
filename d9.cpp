#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
int step1(int map[102][102]);
int step2(int map[102][102]);

int main(){
  std::string s;
  int m[102][102];

  std::fill_n(m[0], 102, 9);
  std::fill_n(m[101], 102, 9);

  for(int i = 0; i< 100; i++){
    std::cin >> s;
    m[i+1][0] = 9;
    m[i+1][101] = 9;
    for(int j = 0; j< 100; j++){
      m[i+1][j+1] = s[j] - '0';
    }
  }

  std::cout << step2(m) << std::endl;

  return 0;
}
bool isLowPoint(int map[102][102], int x, int y){
  if(map[x][y] < map[x][y-1]
  && map[x][y] < map[x][y+1] 
  && map[x][y] < map[x-1][y] 
  && map[x][y] < map[x+1][y]){
    return true;
  }
  return false;
}

int step1(int map[102][102]){

  int total = 0;
  for(int y = 1; y < 101; y++){
    for(int x = 1; x < 101 ; x++){
      if(isLowPoint(map, x, y) == true){
        total += map[x][y] + 1;
      }
    }
  }
  return total;
}

int flood(int map[102][102], bool visited[102][102], int x, int y){
  int total = 0;
  visited[x][y] = true;
  if(map[x][y] == 9){
    return 0;
  }
  total += 1;
  if(map[x][y-1] < 9 && visited[x][y-1] == false){
    total += flood(map, visited, x, y-1);
  }
  if(map[x][y+1] < 9 && visited[x][y+1] == false){
    total += flood(map, visited, x, y+1);
  }
  if(map[x-1][y] < 9 && visited[x-1][y] == false){
    total += flood(map, visited, x-1, y);
  }
  if(map[x+1][y] < 9 && visited[x+1][y] == false){
    total += flood(map, visited, x+1, y);
  }
  return total;

}

int step2(int map[102][102]){
  std::vector<int> vals;
  bool visited[102][102];
  for(int i = 0; i < 102; i++){
    for(int j = 0; j < 102; j++){
      visited[i][j] = false;
    }
  }
  for(int y = 1; y < 101; y++){
    for(int x = 1; x < 101 ; x++){
      if(isLowPoint(map, x, y) == true){
        vals.push_back(flood(map, visited, x, y));
      }
    }
  }
  //print vals
  std::sort(vals.begin(), vals.end(), std::greater<int>());

  return vals[0] * vals[1] * vals[2];
}
