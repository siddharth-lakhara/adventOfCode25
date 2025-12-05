#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
    void part1() {
        vector<string> grid;
        readGrid(grid);
        
        long paperCount = 0;
        for (int rowIdx = 0; rowIdx < grid.size(); rowIdx++) {
            string row = grid.at(rowIdx);
            for (int colIdx = 0; colIdx < row.size(); colIdx++) {
                int adjPaperCount = 0;
                if (isPaperPresent(rowIdx, colIdx, grid)) {
                    adjPaperCount = 
                      isPaperPresent(rowIdx - 1, colIdx - 1, grid) +
                      isPaperPresent(rowIdx - 1, colIdx, grid) +
                      isPaperPresent(rowIdx - 1, colIdx + 1, grid) +
                      isPaperPresent(rowIdx, colIdx - 1, grid) +
                      isPaperPresent(rowIdx, colIdx + 1, grid) +
                      isPaperPresent(rowIdx + 1, colIdx - 1, grid) +
                      isPaperPresent(rowIdx + 1, colIdx, grid) +
                      isPaperPresent(rowIdx + 1, colIdx + 1, grid);

                    if (adjPaperCount < 4) {
                        paperCount++;
                    }
                }
            }
        }

        cout << "Answer: " << paperCount << endl;
    }

    void part2() {
        vector<string> grid;
        readGrid(grid);
        
        long paperCount = 0;
        while (true) { 
            int adjPaperCount = evaluatePaperCounts(grid); 
            paperCount += adjPaperCount;
            if (adjPaperCount == 0) break; 
        }
        
        cout << "Answer: " << paperCount << endl;
    }

private:
    void readGrid(vector<string>& grid) {
        string line;
        while (getline(cin, line)) {
            grid.push_back(line);
        }
    }

    int isPaperPresent(int rowIdx, int colIdx, vector<string>& grid) {
        if ((rowIdx < 0 || rowIdx >= grid.size()) || 
            (colIdx < 0 || colIdx >= grid.at(0).size())) {
            return 0;
        }
        
        return grid.at(rowIdx).at(colIdx) != '.';
    }

    void clearGrid(vector<pair<int, int>> &papersToRemove, vector<string>& grid) {
        for (auto paperIdx : papersToRemove) {
            grid.at(paperIdx.first).at(paperIdx.second) = '.';
        }
    }

    long evaluatePaperCounts(vector<string>& grid) {
        long paperCount = 0;
        vector<pair<int, int>> papersToRemove;
        
        for (int rowIdx = 0; rowIdx < grid.size(); rowIdx++) {
            string row = grid.at(rowIdx);
            for (int colIdx = 0; colIdx < row.size(); colIdx++) {
                int adjPaperCount = 0;
                
                if (isPaperPresent(rowIdx, colIdx, grid)) {
                    adjPaperCount = 
                      isPaperPresent(rowIdx - 1, colIdx - 1, grid) +
                      isPaperPresent(rowIdx - 1, colIdx, grid) +
                      isPaperPresent(rowIdx - 1, colIdx + 1, grid) +
                      isPaperPresent(rowIdx, colIdx - 1, grid) +
                      isPaperPresent(rowIdx, colIdx + 1, grid) +
                      isPaperPresent(rowIdx + 1, colIdx - 1, grid) +
                      isPaperPresent(rowIdx + 1, colIdx, grid) +
                      isPaperPresent(rowIdx + 1, colIdx + 1, grid);
                    
                    if (adjPaperCount < 4) {
                        paperCount++;
                        papersToRemove.push_back(make_pair(rowIdx, colIdx)); 
                    }
                }
            }
        }
        
        clearGrid(papersToRemove, grid);
        
        return paperCount;
    }
};

int main() {
    Solution sol;
    sol.part2();
    // sol.part1();
    
    return 0;
}