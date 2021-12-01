#include <iostream>
using namespace std;
string input;

int main()
{
  int increases = 0;
  int a, b, c, d;
  cin >> a;
  cin >> b;
  cin >> c;

  cin >> input;
  while (input.length() > 0)
  {
    d = stoi(input);
    if (a + b + c < b + c + d)
      increases++;
    a = b;
    b = c;
    c = d;
    input = "";
    cin >> input;
  }
  cout << increases;
  return 0;
}