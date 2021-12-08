#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
struct data
{
  std::string d[10];
  std::string h[4];

};

void print(data d)
{
  for(int i=0;i<10;i++)
  {
    std::cout<<d.d[i]<<" ";
  }
  std::cout<< "| ";
  for(int i=0;i<4;i++)
  {
    std::cout<<d.h[i]<<" ";
  }
  std::cout<<std::endl;
}

int step1(std::vector<data> v);
int step2(std::vector<data> v);

int main(){
  std::vector<data> v;
  std::string s;
  while(std::cin >> s){
    data d;
    d.d[0] = s;

    for(int i = 1; i < 10; i++){
      std::cin >> d.d[i];
    }
    std::cin >> s;
    for(int i = 0; i < 4; i++){
      std::cin >> d.h[i];
    }
    v.push_back(d);
  }

  std::cout << "step 1: " << step1(v) << std::endl;
  std::cout << "step 2: " << step2(v) << std::endl;


  return 0;
}

int step1(std::vector<data> v){
  int total = 0;
  for(int i = 0; i < v.size(); i++){
    for(int j = 0; j < 4; j++){
      int l = v[i].h[j].length();
      if(l == 2 || l == 3 || l == 4 || l == 7){
        total++;
      }
    }
  }
  return total;
}

int calcOutput(data d){
  ushort freq[7] = {0,0,0,0,0,0,0};
  char map[7];

  std::string four;

  for(int i = 0; i < 10; i++){
    if(d.d[i].length() == 4) four = d.d[i];
    for(int j = 0; j< d.d[i].length(); j++){
      freq[d.d[i][j]-'a']++;
    }      
  }
  for(int i =0; i < 7; i++){
    switch (freq[i]){
      case 4:
        map[i] = 'e';
        break;
      case 6:
        map[i] = 'b';
        break;
      case 9: 
        map[i] = 'f';
        break;
      case 8:
        if(four.find('a' + i) != std::string::npos){
          map[i] = 'c';
        }
        else{
          map[i] = 'a';
        }
        break;
      case 7:
        if(four.find('a' + i) != std::string::npos){
          map[i] = 'd';
        }
        else{
          map[i] = 'g';
        }
        break;
    }
  }

  std::string res;
  for(int i = 0; i < 4; i++){
    std::string s;
    for(int j = 0; j < d.h[i].length(); j++){
      s += map[d.h[i][j]-'a'];
    }
    std::sort(s.begin(), s.end());

    if(s == "abcefg") res += '0';
    else if(s == "cf") res += '1';
    else if(s == "acdeg") res += '2';
    else if(s == "acdfg") res += '3';
    else if(s == "bcdf") res += '4';
    else if(s == "abdfg") res += '5';
    else if(s == "abdefg") res += '6';
    else if(s == "acf") res += '7';
    else if(s == "abcdefg") res += '8';
    else res += '9';
  }


  return std::stoi(res);
}

int step2(std::vector<data> v){
  int total = 0;
  for(int i = 0; i < v.size(); i++){
    int out = calcOutput(v[i]);
    std::cout << out << std::endl;
    total += out;
  }
  return total;
}


