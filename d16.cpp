#include <bitset>
#include <iostream>
#include <string>
#include <vector>

std::string HexToBinString(std::string &s);

uint step1(std::string s);
ulong step2(std::string s);

uint getSubpackageLength(std::string s);
uint getLiteralPackageLength(std::string s);
uint getOperatorPackageLength(std::string s);

int main() {
  std::string s;
  std::cin >> s;
  std::string bin = HexToBinString(s);

  std::cout << step1(bin) << std::endl;
  std::cout << step2(bin) << std::endl;
}

std::string HexToBinString(std::string &s) {
  std::string result;
  for (int i = 0; i < s.size(); i++) {
    switch (s[i]) {
    case '0':
      result += "0000";
      break;
    case '1':
      result += "0001";
      break;
    case '2':
      result += "0010";
      break;
    case '3':
      result += "0011";
      break;
    case '4':
      result += "0100";
      break;
    case '5':
      result += "0101";
      break;
    case '6':
      result += "0110";
      break;
    case '7':
      result += "0111";
      break;
    case '8':
      result += "1000";
      break;
    case '9':
      result += "1001";
      break;
    case 'A':
      result += "1010";
      break;
    case 'B':
      result += "1011";
      break;
    case 'C':
      result += "1100";
      break;
    case 'D':
      result += "1101";
      break;
    case 'E':
      result += "1110";
      break;
    case 'F':
      result += "1111";
      break;
    }
  }
  return result;
}

ushort getVersion(std::string s) {
  return std::bitset<3>(s.substr(0, 3)).to_ulong();
}
ushort getTypeId(std::string s) {
  return std::bitset<3>(s.substr(3, 3)).to_ulong();
}
ushort getLengthTypeId(std::string s) { return s[6] == '0' ? 0 : 1; }

// Literal lengths
uint getLiteralDataLength(std::string s) {
  std::string data = s.substr(6, s.size() - 6);
  uint total = 0;
  for (int i = 0; i < data.size(); i += 5) {
    total += 5;
    if (data[i] == '0') {
      return total;
    }
  }
  return total;
}
uint getLiteralPackageLength(std::string s) {
  return 6 + getLiteralDataLength(s);
}

// Operator lengths
uint getOperatorDataLength0(std::string s) {
  return std::bitset<15>(s.substr(7, 15)).to_ulong();
}
uint getOperatorDataLength1(std::string s) {
  uint total = 0;
  uint packages = std::bitset<11>(s.substr(7, 11)).to_ulong();
  std::string data = s.substr(7 + 11, s.size() - (7 + 11));

  for (int i = 0; i < packages; i++) {
    total += getSubpackageLength(data.substr(total, data.size() - total));
  }
  return total;
}

uint getOperatorPackageLength(std::string s) {
  ushort t = getLengthTypeId(s);
  if (t == 0)
    return 7 + 15 + getOperatorDataLength0(s);
  else
    return 7 + 11 + getOperatorDataLength1(s);
}

// General package length
uint getSubpackageLength(std::string s) {
  ushort t = getTypeId(s);
  if (t == 4)
    return getLiteralPackageLength(s);
  else
    return getOperatorPackageLength(s);
}

// Get a list of all the sub first degree subpackages
std::vector<std::string> getSubpackages(std::string s) {
  std::vector<std::string> subpackages;
  // extract the data
  ushort t = getLengthTypeId(s);
  uint dataL = t == 0 ? getOperatorDataLength0(s) : getOperatorDataLength1(s);
  std::string data = s.substr((t == 0 ? 15 + 7 : 11 + 7), dataL);
  // Go through all the data
  int total = 0;
  do {
    // Get the subpackage
    std::string subpackage = data.substr(
        total, getSubpackageLength(data.substr(total, dataL - total)));
    subpackages.push_back(subpackage);
    total += getSubpackageLength(subpackage);
  } while (total < dataL);

  return subpackages;
}

// Value calculations
ulong getLiteralValue(std::string s) {
  std::string temp;
  uint l = getLiteralDataLength(s);
  for (int i = 0; i < l; i += 5) {
    temp += s.substr(6 + i + 1, 4);
  }
  return std::bitset<64>(temp).to_ulong();
}

uint step1(std::string s) {
  ushort v = getVersion(s);
  ushort t = getTypeId(s);
  uint total = v;

  if (t == 4) {
    return v;
  } else {
    // get subpackages
    std::vector<std::string> subpackages = getSubpackages(s);
    // print subpackages
    for (int i = 0; i < subpackages.size(); i++) {
      total += step1(subpackages[i]);
    }
  }
  return total;
}

ulong step2(std::string s) {
  ushort t = getTypeId(s);

  if (t == 4) {
    return getLiteralValue(s);
  } else {
    std::vector<std::string> subpackages = getSubpackages(s);
    switch (t) {
    case 0: {
      // SUM
      ulong sum = 0;
      for (int i = 0; i < subpackages.size(); i++) {
        sum += step2(subpackages[i]);
      }
      return sum;
    }

    case 1: {
      // PRODUCT
      ulong product = 1;
      for (int i = 0; i < subpackages.size(); i++) {
        product *= step2(subpackages[i]);
      }
      return product;
    }
    case 2: { // MINIMUM
      ulong min = __UINT32_MAX__;
      for (int i = 0; i < subpackages.size(); i++) {
        ulong x = step2(subpackages[i]);
        if (x < min) {
          min = x;
        }
      }
      return min;
    }
    case 3: { // MAXIMUM
      ulong max = 0;
      for (int i = 0; i < subpackages.size(); i++) {
        ulong x = step2(subpackages[i]);
        if (x > max) {
          max = x;
        }
      }
      return max;
    }
    case 5: { // >
      return step2(subpackages[0]) > step2(subpackages[1]);
    }
    case 6: { // <
      return step2(subpackages[0]) < step2(subpackages[1]);
    }
    case 7: { // ==
      return step2(subpackages[0]) == step2(subpackages[1]);
    }
    }
  }
  std::cout << "ERROR" << std::endl;
  return 0;
}