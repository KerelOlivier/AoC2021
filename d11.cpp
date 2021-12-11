#include<iostream>
#include<string>

int step1(ushort map[10][10]);
int step2(ushort map[10][10]);

int main(){
  std::string s;
  ushort map[10][10];
  ushort map2[10][10];
  for(int i = 0; i < 10; i++){
    std::cin >> s;
    for(int j = 0; j < 10; j++){
      map[i][j] = s[j] - '0';
      map2[i][j] = s[j] - '0';      
    }
  }
  
  std::cout << step1(map) << std::endl;
  std::cout << step2(map2) << std::endl;
  return 0;
}

int printMap(ushort map[10][10]){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      std::cout << map[i][j];
    }
    std::cout << std::endl;
  }
  return 0;
}

void increaseEnergy(ushort map[10][10]){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      map[i][j]++;
    }
  }
}

int flash(ushort map[10][10], int r, int c){
  int flashes =0;
  if(map[r][c] == 0){
    return 0;
  }
  if(map[r][c] >= 10){
    map[r][c] = 0;
    flashes++;
    //call flash on 8 neighbours
    if(r-1 >= 0){
      if(map[r-1][c] > 0){
        map[r-1][c]++;
        flashes += flash(map, r-1, c);
      }
      if(c-1 >= 0){
        if(map[r-1][c-1] > 0){
          map[r-1][c-1]++;
          flashes += flash(map, r-1, c-1);
        }
      }
      if(c+1 < 10){
        if(map[r-1][c+1] > 0){
          map[r-1][c+1]++;
          flashes += flash(map, r-1, c+1);
        }
      }      
    }
    if(r+1 < 10){
      if(map[r+1][c] > 0){
        map[r+1][c]++;
        flashes += flash(map, r+1, c);
      }
      if(c-1 >= 0){
        if(map[r+1][c-1] > 0){
          map[r+1][c-1]++;
          flashes += flash(map, r+1, c-1);
        }
      }
      if(c+1 < 10){
        if(map[r+1][c+1] > 0){
          map[r+1][c+1]++;
          flashes += flash(map, r+1, c+1);
        }
      }      
    }
    if(c-1 >= 0){
      if(map[r][c-1] > 0){
        map[r][c-1]++;
        flashes += flash(map, r, c-1);
      }
    }
    if(c+1 < 10){
      if(map[r][c+1] > 0){
        map[r][c+1]++;
        flashes += flash(map, r, c+1);
      }
    }



  }
  return flashes;
}

int step1(ushort map[10][10]){
  int flashes = 0;
  for(int i =0 ; i < 100; i++){
    increaseEnergy(map);
    for(int r = 0; r < 10; r++){
      for(int c = 0; c < 10; c++){        
        flashes += flash(map, r, c);
      }
    }
  }
  return flashes;
}

int step2(ushort map[10][10]){
  int flashes = 0;
  int step = 0;
  while(flashes != 100){
    flashes =0 ;
    increaseEnergy(map);
    for(int r = 0; r < 10; r++){
      for(int c = 0; c < 10; c++){        
        flashes += flash(map, r, c);
      }
    }
    step++;
  }
  return step;
}