#include <iostream>
#include <vector>
#include <unordered_set>

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
        vector<string> grid;
        readInput(grid);

        int start = grid[0].find('S');
        vector<long long> timelineCounts(grid[0].size(), 0);
        timelineCounts[start] = 1;

        for (int lineIdx=1; lineIdx<grid.size(); lineIdx++) {
            updateTimelineLocations(grid.at(lineIdx), timelineCounts);
        }
        
        long long totalTimelines = 0;
        for (long long count : timelineCounts) {
            totalTimelines += count;
        }

        cout << totalTimelines << endl;
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

    void updateTimelineLocations(string& row, vector<long long>& timelineCounts) {
        for (int idx = 0; idx<timelineCounts.size(); idx++) {
            if (timelineCounts[idx] > 0) {
                if (row[idx] == '^') {
                    long long currCount = timelineCounts[idx];
                    timelineCounts[idx] = 0;
                    if (idx-1 >= 0) { 
                        timelineCounts[idx-1] += currCount; 
                    }
                    if (idx+1 < timelineCounts.size()) { 
                        timelineCounts[idx+1] += currCount; 
                    }
                    
                }
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