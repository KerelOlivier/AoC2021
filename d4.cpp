#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

int step1(std::vector<int**> bingoCards, std::vector<int> drawNumbers);
int step2(std::vector<int**> bingoCards, std::vector<int> drawNumbers);
std::vector<int> readDraws(std::string s);
int** readBingoCard();

int main(){
  std::string draws;
  std::cin >> draws;
  std::vector<int> drawNumbers = readDraws(draws);
  std::vector<int**> bingoCards;
  int ** card;
  while(card = readBingoCard()){
    bingoCards.push_back(card);
  }

  std::cout << "bingocount: " << bingoCards.size() << std::endl;
  std::cout << "drawcount: " << drawNumbers.size() << std::endl;

  // std::cout << "step1: " << step1(bingoCards, drawNumbers) << std::endl;
  std::cout << "step2: " << step2(bingoCards, drawNumbers) << std::endl;
  return 0;
}

std::vector<int> readDraws(std::string s){
  std::vector<int> ret;
  std::string tmp;
  for(int i = 0; i < s.size(); i++){
    if(s[i] == ','){
      ret.push_back(std::stoi(tmp));
      tmp = "";
    }else{
      tmp += s[i];
    }
  }
  ret.push_back(std::stoi(tmp));
  return ret;
}
int ** readBingoCard(){
  std::string s;
  int** ret = new int*[5];
  for(int i = 0; i < 5; i++){
    ret[i] = new int[5];
    for(int j = 0; j < 5; j++){
      if(!(std::cin >> s)) return NULL;
      ret[i][j] = std::stoi(s);
    }
  }

  return ret;
}

int crossOff(int** card, int val){
  for(int x = 0; x < 5; x++){
    for(int y = 0; y < 5; y++){
      if(card[x][y] == val){
        card[x][y] = -1;
      }
    }
  }
  return 0;
}

bool hasBingo(int** card){
  for(int x = 0; x < 5; x++){
    int row = 0;
    int col = 0;
    for(int y = 0; y < 5; y++){
      if(card[x][y] == -1)col++;
      if(card[y][x] == -1)row++;
    }
    if(row == 5 || col == 5)return true;
  }
  return false;
}

int getScore(int** card){
  int score = 0;
  for(int x = 0; x < 5; x++){
    for(int y = 0; y < 5; y++){
      if(card[x][y] != -1)score+= card[x][y];
    }
  }
  return score;
}
int step1(std::vector<int**> bingoCards, std::vector<int> drawNumbers){
  for(int i = 0; i < drawNumbers.size(); i++){
    for(int j = 0; j < bingoCards.size(); j++){
      crossOff(bingoCards[j], drawNumbers[i]);
      if(hasBingo(bingoCards[j]))return getScore(bingoCards[j]) * drawNumbers[i];
    }
  }
  return 0;
}
int step2(std::vector<int**> bingoCards, std::vector<int> drawNumbers){
  bool used[bingoCards.size()];
  int leftOver = bingoCards.size();
  for(int i = 0; i < drawNumbers.size(); i++){
    for(int j = 0; j < bingoCards.size(); j++){
      if(used[j] == true){
        continue;
      }
      crossOff(bingoCards[j], drawNumbers[i]);
      if(hasBingo(bingoCards[j])){
        used[j] = true;
        leftOver--;
        if(leftOver == 0)return getScore(bingoCards[j]) * drawNumbers[i];
      }
    }
  }
  return 0;
}