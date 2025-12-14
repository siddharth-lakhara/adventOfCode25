#include <iostream>
#include <vector>
#include <unordered_set>
// #include <sstream>
// #include <numeric>

using namespace std;

class Solution {
   public:
    void part1() {
        vector<string> grid;
        readInput(grid);

        int start = grid[0].find('S');
        vector<int> beamLocations(grid[0].size(), 0);
        beamLocations[start] = 1;

        int totalBeamCount = 0;
        for (int lineIdx=1; lineIdx<grid.size(); lineIdx++) {
            totalBeamCount += updateBeamLocations(grid.at(lineIdx), beamLocations);
        }

        cout << totalBeamCount << endl;
    }

    void part2() {
    }

   private:
    void readInput(vector<string>& grid) {
        string line;
        while (getline(cin, line)) {
            grid.push_back(line);
        }
    }

    int updateBeamLocations(string& row, vector<int>& beamLocations) {
        int newBeams = 0;
        
        for (int idx = 0; idx<beamLocations.size(); idx++) {
            if (beamLocations[idx] == 1) {
                if (row[idx] == '^') {
                    newBeams++;
                    
                    beamLocations[idx] = 0;
                    if (idx-1 >= 0 && beamLocations[idx-1] == 0 && row[idx-1] == '.') { 
                        beamLocations[idx-1] = 1; 
                    }
                    if (idx+1 < beamLocations.size() && beamLocations[idx+1] == 0 && row[idx+1] == '.') { 
                        beamLocations[idx+1] = 1; 
                    }
                }
            }
        }

        return newBeams;
    }
};

int main() {
    Solution solution;
    solution.part1();
    // solution.part2();

    return 0;
}