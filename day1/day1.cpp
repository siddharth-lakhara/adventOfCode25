#include <iostream>
using namespace std;

class Solution {
    public:
    int solvePart1() {
      int count = 0;
      int pos = 50;
      string instruction;

      while (getline(cin, instruction)) {
        int multiplier = instruction.at(0) == 'L' ? -1 : 1;
        int adder = stoi(instruction.substr(1));
        
        pos = (pos + multiplier*adder)%100;

        if (pos == 0) {
          count++;
        }
      }

      cout << count << endl;
      return count;
    }

    int solvePart2() {
      int count = 0;
      int pos = 50;
      string instruction;

      while (getline(cin, instruction)) {
        int multiplier = instruction.at(0) == 'L' ? -1 : 1;
        int adder = stoi(instruction.substr(1));
        
        int delta = (multiplier*adder);
        pos += delta;
        count += abs(pos/100);

        pos %= 100;
        if (pos < 0) {
          pos = 100+pos;
          count++;
        }

        if (pos == 0 && delta < 0) {
          count++;
        }
      }

      cout << count << "\n";
      return count;
    }

};

int main() {
  Solution solution;
  // solution.solvePart1();
  solution.solvePart2();

  return 0;
}