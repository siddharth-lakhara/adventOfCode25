#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
   public:
    void part1() {
        vector<vector<string>> grid;
        readInputs(grid);
        int idx = 0;

        vector<long> results;
        for (auto operation : grid.at(grid.size() - 1)) {
            long result;
            if (operation == "+") {
               result = performAddition(grid, idx);
            } else {
               result = performMultiplication(grid, idx);
            }
            idx++;
            results.push_back(result);
        }

        long sumOfOperation = accumulate(results.begin(), results.end(), 0L);
        cout << sumOfOperation << endl;
    }

   private:
    void readInputs(vector<vector<string>>& grid) {
        string row;
        while (getline(cin, row)) {
            stringstream ss(row);
            string cols;
            vector<string> rowVect;

            while (ss >> cols) {
                rowVect.push_back(cols);
            }
            grid.push_back(rowVect);
        }
    }
    
    long performAddition(vector<vector<string>>& grid, int idx) {
        long sum = 0;
        for (int rowIdx = 0; rowIdx < grid.size() - 1; rowIdx++) {
            sum += stol(grid.at(rowIdx).at(idx));
        }

        return sum;
    }
    
    long performMultiplication(vector<vector<string>>& grid, int idx) {
        long multiply = 1;
        for (int rowIdx = 0; rowIdx < grid.size() - 1; rowIdx++) {
            multiply *= stol(grid.at(rowIdx).at(idx));
        }

        return multiply;
    }
};

int main() {
    Solution solution;
    solution.part1();

    return 0;
}