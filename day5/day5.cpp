#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void part1() {
        vector<pair<long, long>> ranges;
        vector<long> queries;
        readInput(ranges, queries);

        long freshIngredients = 0;
        for (long q: queries) {
            for (auto r: ranges) {
                if (q >= r.first && q <= r.second) {
                    freshIngredients++;
                    break;
                } else if (q < r.first) {
                    break;
                }
            }
        }

        cout << "Answer: " << freshIngredients << endl;
    }

    void part2() {
        vector<pair<long, long>> ranges;
        vector<long> queries;
        readAndSortRanges(ranges);

        long long total;
        for (auto r: ranges) {
            total += (long long)(r.second - r.first) + 1;
        }

        cout << "Answer: " << total << endl;
    }

private:
    void readInput(vector<pair<long, long>>& ranges, vector<long>& queries) {
        readAndSortRanges(ranges);
        readQueries(queries);
    }

    void readAndSortRanges(vector<pair<long, long>>& sortedRange) {
        vector<pair<long, long>> ranges;
        string line;
        while (getline(cin, line)) {
            if (line == "") {
                break;
            }

            long first, second;
            string rangeStr;
            stringstream rangeStream(line);
            
            getline(rangeStream, rangeStr, '-');
            first = stol(rangeStr);
            
            getline(rangeStream, rangeStr, '-');
            second = stol(rangeStr);

            ranges.push_back(make_pair(first, second));
        }

        sort(ranges.begin(), ranges.end());
        
        sortedRange.push_back(ranges.at(0));
        long sortedRangeCounter = 0;
        for (long unsortedRangeCounter = 1; unsortedRangeCounter < ranges.size(); unsortedRangeCounter++) {
            if (sortedRange.at(sortedRangeCounter).second >= ranges.at(unsortedRangeCounter).first) {
                sortedRange.at(sortedRangeCounter).second  = max(
                    ranges.at(unsortedRangeCounter).second, 
                    sortedRange.at(sortedRangeCounter).second
                );
            } else {
                sortedRange.push_back(ranges.at(unsortedRangeCounter));
                sortedRangeCounter++;
            }
        }
    }

    void readQueries(vector<long>& queries) {
        string line;
        while (getline(cin, line)) {
            queries.push_back(stol(line));
        }
    }
};

int main() {
    Solution sol;
    // sol.part1();
    sol.part2();
    
    return 0;
}