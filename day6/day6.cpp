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

    void part2() {
        vector<string> grid;
        readInputs2(grid);
        
        vector<vector<string>> operations;
        readOperations(grid, operations);

        vector<long> results;
        for (auto op : operations) {
            long result;
            if (op[0] == "+") {
               result = performAddition2(op);
            } else {
               result = performMultiplication2(op);
            }
            results.push_back(result);
        }

        long sumOfOperation = accumulate(results.begin(), results.end(), 0L);
        cout << sumOfOperation << endl;
    }

   private:
    void readInputs2(vector<string>& grid) {
        string row;
        while (getline(cin, row)) {
            grid.push_back(row);
        }
    }

    void readOperations(vector<string>& grid, vector<vector<string>>& operations) {
        string opRow = grid.at(grid.size()-1);
        int opRowIdx = opRow.size()-1;
        while (opRowIdx >= 0) {
            int opEndIdx = opRowIdx;
            while (opRow.at(opRowIdx) == ' ') {
                opRowIdx--;
            }
            int opStartIdx = opRowIdx;
            operations.push_back(parseOperation(opStartIdx, opEndIdx, grid));

            // go to next set of operations
            opRowIdx -= 2;
        }
    }

    vector<string> parseOperation(int startIdx, int endIdx, vector<string>& grid) {
        vector<string> operation;
        operation.push_back( (string){ grid.at(grid.size()-1).at(startIdx) } );
        
        for (int colIdx = startIdx; colIdx <= endIdx; colIdx++) {
            string num = "";
            for (int rowIdx = 0; rowIdx < grid.size()-1; rowIdx++) {
                char ch = grid[rowIdx][colIdx];
                if (ch != ' ') {
                    num += ch;
                }
                
            }
            operation.push_back(num);
        }

        return operation;
    }

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

    long performAddition2(vector<string> operation) {
        long sum = 0;
        for (int idx = 1; idx<operation.size(); idx++) {
            sum += stol(operation.at(idx));
        }

        return sum;
    }
    
    long performMultiplication2(vector<string> operation) {
        long multiply = 1;
        for (int idx = 1; idx<operation.size(); idx++) {
            multiply *= stol(operation.at(idx));
        }

        return multiply;
    }

};

int main() {
    Solution solution;
    // solution.part1();
    solution.part2();

    return 0;
}