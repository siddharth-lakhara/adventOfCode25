#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
    public:
    void part1() {
      vector<long> invalidRanges;

      string input;
      getline(cin, input);
      stringstream ss(input);

      string range;
      while (getline(ss, range, ',')) {
        findInvalidRange(range, invalidRanges);
        // cout << range << endl;
      }

      long long sum = findSum(invalidRanges);
      cout << "Sum: " << sum << endl;
    }

    private:
    void findInvalidRange(string range, vector<long>& invalidRanges) {
      string rangeStart;
      string rangeEnd;
      stringstream rangeStream(range);
      
      getline(rangeStream, rangeStart, '-');
      getline(rangeStream, rangeEnd, '-');

      long rangeStartLong = stol(rangeStart);
      long rangeEndLong = stol(rangeEnd);

      string check;
      if (rangeStart.size() % 2 != 0) {
        long base = (long) floor(log10(rangeStartLong));
        check = to_string((long) pow(10, base+1));
        check = check.substr(0, check.size()/2);
      } else {
        check = rangeStart.substr(0, rangeStart.size()/2);
      }

      // cout << "Check start: " << check << endl;

      while (true) {
        long possibleInvalidRange = stol(check + check);
        if (possibleInvalidRange >= rangeStartLong && possibleInvalidRange <= rangeEndLong) {
          invalidRanges.push_back(possibleInvalidRange);
        }

        if (possibleInvalidRange > rangeEndLong) {
          break;
        }
        check = to_string( stol(check) + 1 );
      }
      
    }

    long long findSum(vector<long>& invalidRanges) {
      long long sum = 0LL;
      for (long range: invalidRanges) {
        sum += range;
      }

      return sum;
    }
  };

int main() {
  Solution solution;
  solution.part1();
  
  return 0;
}