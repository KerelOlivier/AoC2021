#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

int step1(std::vector<std::string> v);
ulong step2(std::vector<std::string> v);

int main(){
  std::vector<std::string> v;
  std::string s;
  //Read in data
  while(std::cin >> s){
    v.push_back(s);
  }

  std::cout << step1(v) << std::endl;
  std::cout << step2(v) << std::endl;


  return 0;
}

int getScore(char c){
  if(c == ')') return 3;
  if(c == ']') return 57;
  if(c == '}') return 1197;
  if(c == '>') return 25137;
  return 0;
}

int calcError(std::string s){
  std::stack<char> stack;
  for(int i = 0; i < s.size(); i++){
    if(s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == '<'){
      stack.push(s[i]);
    }else{
      char c = stack.top();
      if(c == '(' && s[i] != ')') return getScore(s[i]);
      if(c == '[' && s[i] != ']') return getScore(s[i]);
      if(c == '{' && s[i] != '}') return getScore(s[i]);
      if(c == '<' && s[i] != '>') return getScore(s[i]);
      stack.pop();
    }
  }
  return 0;
}

int step1(std::vector<std::string> v){
  int total = 0;
  for(int i = 0; i < v.size(); i++){
    total += calcError(v[i]);
  }
  return total;
}

int getACScore(char c){
  if(c == '(') return 1;
  if(c == '[') return 2;
  if(c == '{') return 3;
  if(c == '<') return 4;
  return 0;
}

ulong calcACScore(std::string s){
  std::stack<char> stack;
  for(int i = 0; i < s.size(); i++){
    //Dicard corrupted lines
    if(s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == '<'){
      stack.push(s[i]);
    }else{
      char c = stack.top();
      if(c == '(' && s[i] != ')') return 0;
      if(c == '[' && s[i] != ']') return 0;
      if(c == '{' && s[i] != '}') return 0;
      if(c == '<' && s[i] != '>') return 0;
      stack.pop();
    }
  }
  ulong total = 0;
  while(!stack.empty()){
    std::cout << stack.top();
    total *=5;
    total += getACScore(stack.top());
    stack.pop();
  }
  std::cout << " =>" << total << std::endl;
  return total;
}

ulong step2(std::vector<std::string> v){
  std::vector<ulong> scores;
  for(int i = 0; i < v.size(); i++){
    ulong score = calcACScore(v[i]);
    if(score > 0) scores.push_back(score);
  }
  std::sort(scores.begin(), scores.end());
  // for(int i = 0; i < scores.size(); i++){
  //   std::cout << scores[i] << " ";
  // }
  // std::cout << std::endl;
  //print scores size
  std::cout << scores.size() << std::endl;
  int mid = (scores.size())/2;
  return scores[mid];
}