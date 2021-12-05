#include<iostream>
#include<string>
#include<vector>

int * split(std::string str, std::string delimiter);
void getIntermediatePoints(std::vector<int*> &res, int * p, int * q, bool diagonal);


int main(){
  std::cout << "Hello World!" << std::endl;
  std::string a;
  std::string b;
  std::string tmp;
  std::vector<int*> v;

  int mxX = 0;
  int mxY = 0;  

  int c = 0;
  while(std::cin >> a >> tmp >> b){
    int * p = split(a, ",");
    int * q = split(b, ",");
    if(p[0] == q[0] && p[1] == q[1]){
      std::cout << "c: " << c << std::endl;
      std::cout << "p: " << p[0] << "," << p[1] << std::endl;
      std::cout << "q: " << q[0] << "," << q[1] << std::endl;
    }

    mxX = std::max(std::max(mxX, p[0]), q[0]);
    mxY = std::max(std::max(mxY, p[1]), q[1]);
    getIntermediatePoints(v, p, q, true);

    c++;
  }


  //CreatePoint mapping
  int mapping[mxX+1][mxY+1];
  for(int i = 0; i < mxX+1; i++){
    for(int j = 0; j < mxY+1; j++){
      mapping[i][j] = 0;
    }
  }
  for(int i = 0; i < v.size(); i++){
    mapping[v[i][0]][v[i][1]]++;
  }
  //Find values higher than 0 in mapping
  int count = 0;
  for(int i = 0; i < mxY+1; i++){
    for(int j = 0; j < mxX+1; j++){
      std::cout << (mapping[j][i] > 0 ? std::to_string(mapping[j][i]) : ".");
      if(mapping[j][i] > 1){
        count++;
      }
    }
    std::cout << std::endl;
  }
  std::cout << "count: " << count << std::endl;

  return 0;
}

int * split(std::string str, std::string delimiter){
  int * result = new int[2];
  int pos = str.find(delimiter);
  result[0] = std::stoi(str.substr(0, pos));
  result[1] = std::stoi(str.substr(pos + delimiter.length()));
  return result;
}

void getIntermediatePoints(std::vector<int*> &res, int * p, int * q, bool diagonal){

  //Horizontal
  if(p[0] == q[0]){
    int min = std::min(p[1], q[1]);
    int max = std::max(p[1], q[1]);
    for(int i = min; i <= max; i++){
      int * tmp = new int[2];
      tmp[0] = p[0];
      tmp[1] = i;
      res.push_back(tmp);
    }
  }
  //Vertical
  else if(p[1] == q[1]){
    int min = std::min(p[0], q[0]);
    int max = std::max(p[0], q[0]);
    for(int i = min; i <= max; i++){
      int * tmp = new int[2];
      tmp[0] = i;
      tmp[1] = p[1];
      res.push_back(tmp);
    }
  }
  //diagonal line
  else if(diagonal){
    int dX = q[0] - p[0];
    int dY = q[1] - p[1];
    int sX = dX / std::abs(dX);
    int sY = dY / std::abs(dY);
    for(int i = 0; i <= std::abs(dX); i++){
      int * tmp = new int[2];
      tmp[0] = p[0] + i * sX;
      tmp[1] = p[1] + i * sY;
      res.push_back(tmp);
    }

  }
}
