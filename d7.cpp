#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

std::vector<int> split(std::string s, char deliminator);
ulong totalDist(std::vector<int> v, int target);
int main(){
  std::string s;
  std::cin >> s;
  std::vector<int> v = split(s, ',');
  std::sort(v.begin(), v.end());
  
  int x = 2;
  int prev= totalDist(v, 0);
  int curr = totalDist(v, 1);
  while(curr <= prev){
    prev = curr;
    x++;
    curr = totalDist(v, x);
  }
  std::cout << x << " => " << curr << "," << prev << std::endl;

  


  

}
std::vector<int> split(std::string s, char deliminator){
  std::vector<int> v;
  int start = 0;
  int end = 0;
  while(end < s.size()){
    if(s[end] == deliminator){
      v.push_back(std::stoi(s.substr(start, end-start)));
      start = end+1;
    }
    end++;
  }
  v.push_back(std::stoi(s.substr(start, end-start)));
  return v;
}

int dist(int a, int b){
  return (std::abs(a - b) * (std::abs(a - b) +1))/2;
}
ulong totalDist(std::vector<int> v, int target){
  int total = 0;
  for(int i = 0; i < v.size(); i++){
    total += dist(v[i], target);
  }
  return total;
}