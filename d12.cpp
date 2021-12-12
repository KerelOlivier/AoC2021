#include<iostream>
#include<string>
#include<string_view>
#include<vector>
#include<map>
#include<stack>
#include<iterator>

int step1(std::map<std::string, std::vector<std::string>> m);
int step2(std::map<std::string, std::vector<std::string>> m);

std::vector<std::string> split(std::string s);

int main(){
  std::string s;
  std::map<std::string, std::vector<std::string>> m;
  while(std::cin >> s){
    std::vector<std::string> v = split(s);
    if(m[v[0]].size() == 0){
      m[v[0]] = std::vector<std::string>{v[1]};
    }else{
      m[v[0]].push_back(v[1]);
    }
    if(m[v[1]].size() == 0){
      m[v[1]] = std::vector<std::string>{v[0]};
    }else{
      m[v[1]].push_back(v[0]);
    }
  }

  std::cout << step1(m) << std::endl;
  std::cout << step2(m) << std::endl;
}

int DFS(std::map<std::string, std::vector<std::string>> m, std::string s, std::map<std::string, bool> visited){
  if(!isupper(s[0])){
    visited[s] = true;
  }
  if(s == "end")
    return 1;
  
  // std::cout << s << std::endl;
  int total = 0;
  //Add unvisited neighbors to stack
  for(auto i : m[s]){
    if(!visited[i]){
      // std::cout << i << std::endl;
      total += DFS(m, i, visited);
    }
  }
  return total;
}

bool hasdouble(std::map<std::string, int> visited){
  for(auto i : visited){
    if(i.second > 1)
      return true;
  }
  return false;
}

int DFS(std::map<std::string, std::vector<std::string>> m, std::string s, std::map<std::string, int> visited, bool hd){
  if(!isupper(s[0])){
    visited[s]++;
    if(visited[s] > 1)
      hd = true;
  }
  if(s == "end")
    return 1;
  
  // std::cout << s << std::endl;
  int total = 0;
  //Add unvisited neighbors to stack
  for(auto i : m[s]){
    if(hd){
      if(!visited[i]){
        // std::cout << i << std::endl;
        total += DFS(m, i, visited, hd);
      }
    }else{
      if(visited[i] < 2 && i != "start"){
        // std::cout << i << std::endl;
        total += DFS(m, i, visited, hd);
      }
    }

  }
  return total;
}

int step1(std::map<std::string, std::vector<std::string>> m){
  std::map<std::string, bool> visited;
  return DFS(m, "start", visited);
}
int step2(std::map<std::string, std::vector<std::string>> m){
  std::map<std::string, int> visited;
  
  int a = DFS(m, "start", visited, false);


  return a;

}

//Split string at -
std::vector<std::string> split(std::string s){
  std::vector<std::string> v;
  std::string temp;
  for(int i = 0; i < s.size(); i++){
    if(s[i] == '-'){
      v.push_back(temp);
      temp = "";
    }
    else{
      temp += s[i];
    }
  }
  v.push_back(temp);
  return v;
}