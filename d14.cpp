#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

ulong step1(std::map<std::string, char> m, std::string input);
ulong step2(std::map<std::string, char> m, std::string input);

int main() {
  std::string input;
  std::string s;
  std::cin >> input;
  std::map<std::string, char> m;
  while (std::cin >> s) {
    std::string out;
    std::cin >> out;
    std::cin >> out;
    m.insert(std::make_pair(s, out[0]));
  }
  std::cout << m.size() << std::endl;
  std::cout << step2(m, input) << std::endl;
  return 0;
}

void calcDuo(std::map<std::string, char> m, ushort depth, std::string s,
             std::map<std::string, std::vector<ulong>> &memo, ulong res[26]) {
  char mid = m[s];
  res[mid - 'A']++;
  if (depth == 1) {
    return;
  }

  // check if s already exists
  std::string hash = s + (char)(depth + 48);
  if (memo.find(hash) != memo.end()) {
    for (int i = 0; i < 26; i++) {
      res[i] += memo[hash][i];
    }
    return;
  }
  // not already known

  std::vector<ulong> v(26, 0);
  for (int i = 0; i < 26; i++) {
    v[i] = res[i];
  }

  // Calculate it of the siblings
  calcDuo(m, depth - 1, std::string(1, s[0]) + mid, memo, res);
  calcDuo(m, depth - 1, std::string(1, mid) + s[1], memo, res);

  // save to memo
  for (int i = 0; i < 26; i++) {
    v[i] = res[i] - v[i];
  }
  memo.insert(std::make_pair(hash, v));
  return;
}

ulong *calc(std::map<std::string, char> m, int depth, std::string input) {
  std::map<std::string, std::vector<ulong>> memo;
  ulong *res = new ulong[26];
  std::fill(res, res + 26, 0);

  for (int i = 0; i < input.size() - 1; i++) {
    res[input[i] - 'A']++;
    std::string s = input.substr(i, 2);
    calcDuo(m, depth, s, memo, res);
  }
  res[input[input.size() - 1] - 'A']++;

  // print res
  ulong count = 0;
  for (int i = 0; i < 26; i++) {
    count += res[i];
    std::cout << (char)(i + 'A') << ": " << res[i] << std::endl;
  }
  std::cout << "count: " << count << std::endl;

  return res;
}

ulong step1(std::map<std::string, char> m, std::string input) {

  ulong *res = calc(m, 10, input);
  ulong max = res[0];
  ulong min = 100000000;
  for (int i = 0; i < 26; i++) {
    if (res[i] > 0) {
      max = std::max(max, res[i]);
      min = std::min(min, res[i]);
    }
  }
  std::cout << "max: " << max << std::endl;
  std::cout << "min: " << min << std::endl;
  return max - min;
}
ulong step2(std::map<std::string, char> m, std::string input) {

  ulong *res = calc(m, 40, input);
  ulong max = res[0];
  ulong min = 1099511627776;
  for (int i = 0; i < 26; i++) {
    if (res[i] > 0) {
      max = std::max(max, res[i]);
      min = std::min(min, res[i]);
    }
  }
  std::cout << "max: " << max << std::endl;
  std::cout << "min: " << min << std::endl;
  return max - min;
}
