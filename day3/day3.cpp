#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

// "987 654321111111"

class Solution {
    public:
    void part1() {
      long sum = 0;
      string input;
      while (getline(cin, input)) {
        sum += link2Batteries(input);
      }

      cout << "Answer: " << sum << endl;
    }

    void part2() {
      long long sum = 0;
      string input;
      while (getline(cin, input)) {
        sum += (long long) link12Batteries(input);
      }

      cout << "Answer: " << sum << endl;
    }

    private:
    long link2Batteries(string input) {
      int idx = input.size()-1;
      int right = input.at(idx--) - '0';
      int left = input.at(idx--) - '0';

      while (idx >= 0) {
        int curr = input.at(idx) - '0';
        if (curr >= left) {
          int old_left = left;
          left = curr;

          if (old_left >= right) {
            right = old_left;
          }
        }

        idx--;
      }

      return (long)(left*10 + right);
    }

    long link12Batteries(string input) {
      // int idx = input.size()-1;
      int batteries_size = 12;
      vector<int> batteries(batteries_size);
      
      char num;
      int idx = 0;
      stringstream ss(input.substr(input.size()-batteries_size, batteries_size));
      while (ss >> num) {
        batteries[idx] = num-'0';
        idx++;
      }

      idx = input.size()-batteries_size-1;
      while (idx >= 0) {
        int curr = input.at(idx) - '0';
        if (curr >= batteries[0]) {
          shift_batteries(batteries, curr);
        }
        idx--;
      }

      long sum = 0;
      for (int b: batteries) {
        sum = sum*10 + (long) b;
      }
      return sum;
    }

    void shift_batteries(vector<int>& batteries, int curr) {
      int idx = 0;
      int shifter = curr;

      for (; idx<batteries.size(); idx++) {
        if (shifter >= batteries[idx]) {
          int temp = batteries[idx];
          batteries[idx] = shifter;
          shifter = temp;
        } else {
          break;
        }
      }
    }

  };

int main() {
  Solution solution;
  // solution.part1();
  solution.part2();
  
  return 0;
}