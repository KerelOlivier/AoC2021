#include<iostream>
#include<string>
#include<vector>
#include<queue>

std::vector<int> split(std::string s, char delimiter);
unsigned int birth(int day, int mxDay);
int main(){
int days = 256;
unsigned long tracker[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};


std::string s;
std::cin >> s;
std::vector<int> v = split(s, ',');

unsigned long total = v.size();


for(int i = 0; i < v.size(); i++){
  tracker[v[i]]++;
}

for(int i = 0; i < days; i++){
  unsigned long x = tracker[0];
  tracker[0] = tracker[1];
  tracker[1] = tracker[2];
  tracker[2] = tracker[3];
  tracker[3] = tracker[4];
  tracker[4] = tracker[5];
  tracker[5] = tracker[6];
  tracker[6] = tracker[7] + x;
  tracker[7] = tracker[8];
  tracker[8] = x;

  total += x;
   
}

  std::cout << total << std::endl;



  return 0;
}

std::vector<int> split(std::string s, char delimiter){
  std::vector<int> v;
  std::string temp = "";
  for(int i = 0; i < s.size(); i++){
    if(s[i] == delimiter){
      v.push_back(std::stoi(temp));
      temp = "";
    }else{
      temp += s[i];
    }
  }
  v.push_back(std::stoi(temp));
  return v;
}

unsigned int birth(int day, int mxDay){
  unsigned int self = 0, child = 1;
  if(day + 7 < mxDay){
    self = birth(day + 7, mxDay);
    if(day + 9 < mxDay)
      child += birth(day + 9, mxDay);
  }

  return self + child;
}