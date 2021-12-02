#include <iostream>

int step1();
int step2();

int main()
{
  std::cout << step2();
  return 0;
}
int step1()
{
  int horz = 0;
  int vert = 0;

  std::string cmd;
  int val;
  std::cin >> cmd >> val;
  while (cmd.length() > 0)
  {
    if (cmd == "forward")
      horz += val;
    if (cmd == "up")
      vert -= val;
    if (cmd == "down")
      vert += val;

    cmd = "";
    val = 0;
    std::cin >> cmd >> val;
  }
  return vert * horz;
}

int step2()
{
  int horz = 0;
  int vert = 0;
  int aim = 0;

  std::string cmd;
  int val;
  std::cin >> cmd >> val;
  while (cmd.length() > 0)
  {
    if (cmd == "forward")
    {
      horz += val;
      vert += val * aim;
    }

    if (cmd == "up")
      aim -= val;
    if (cmd == "down")
      aim += val;

    cmd = "";
    val = 0;
    std::cin >> cmd >> val;
  }
  return vert * horz;
}