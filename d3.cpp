#include<iostream>
#include<bitset>
#include<queue>
#include<cmath>
int step1();
int step2();
int main()
{
  // std::cout << step1() << std::endl;
  std::cout << step2() << std::endl;
  return 0;
}

int step1(){
  std:: string s;
  int c = 0;
  int count[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  while(std::cin >> s){
    c++;
    for(int i = 0; i < s.length(); i++){
      if(s[i] == '1'){
        count[i]++;
      }
    }
  }

  int gamma =0;
  int epsilon = 0;
  //Determine epsilon and gamma values
  for(int i = 11; i >=0; i--){
    std::cout << (c - count[i] < c/2) << " ";
    gamma += c - count[i] < c/2 ? 0 << 11-i : 1 << 11-i;
  }
  epsilon = gamma ^ 0xfff;
  return epsilon*gamma;


}
int getNthBitcount(int n, std::queue<std::string> &q){
  int c = 0;
  int count = q.size();
  for(int i = 0; i <count; i++){
    if(q.front()[n] == '1'){
      c++;
    }
    q.push(q.front());
    q.pop();
    
  }
  // std::cout << c << std::endl;
  return c;
}

int step2(){
  //Read in values
  std::string s;
  std::queue<std::string> values;
  int c = 0;
  int count[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  while(std::cin >> s){
    c++;
    values.push(s);
    for(int i = 0; i < s.length(); i++){
      if(s[i] == '1'){
        count[i]++;
      }
    }
  }

  std::queue<std::string> a(values);
  std::queue<std::string> b(values);
  std::cout << "A: " << a.size() << std::endl;
  std::cout << "B: " << b.size() << std::endl;

  int oxygen = -1;
  int co2 = -1;

  //Determine life support values
  for(int i = 0; i < values.front().length(); i++){
    int sa = a.size();
    int sb = b.size();
    int a_count = getNthBitcount(i, a);
    int b_count =  getNthBitcount(i, b);
    char most = getNthBitcount(i, a) >= std::ceil(sa/2.0f)? '1' : '0';
    char least = getNthBitcount(i, b) < std::ceil(sb/2.0f)? '1' : '0';
    std::cout << "count: " << a_count << " " << b_count << std::endl;
    std::cout << "sizes: " << sa << " " << sb << std::endl;
    std::cout << "most/least: " << most << " " << least << std::endl;

    // std::cout << "least common: " << leastCommon[i] << std::endl;
    //Find oxygen
    for(int x = 0; oxygen < 0 && x < sa; x++){
      if(a.front()[i] == most){
        a.push(a.front());
      }
      a.pop();
      if(a.size() == 1) oxygen = std::bitset<12>(a.front()).to_ullong();
    }
    //Find CO2
    for(int y = 0; co2 <0 && y < sb; y++){
      if(b.front()[i] == least){
        b.push(b.front());
      }
      b.pop();
      if(b.size() == 1) co2 = std::bitset<12>(b.front()).to_ullong();
    }
  }

  std::cout << "a, size: " << a.size() << std::endl;
  std::cout << "b, size: " << b.size() << std::endl;
  while(!a.empty()){
    std::cout << a.front() << std::endl;
    a.pop();
  }
  while(!b.empty()){
    std::cout << b.front() << std::endl;
    b.pop();
  }

  std::cout << "oxygen: " << oxygen << std::endl;
  std::cout << "co2: " << co2 << std::endl;
  return oxygen * co2;
}

