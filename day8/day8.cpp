#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

struct Point {
    long x;
    long y;
    long z;
};

struct SortedPoints {
    double d;
    long p1Idx;
    long p2Idx;

    bool operator < (const SortedPoints& other) const
    {
        return (d < other.d);
    }
};

class Solution {
   public:
    void part1() {
        // For example:
        // int JUNCTION_BOX_SIZE = 20;
        // int MAX_CONNECTIONS = 10;

        int JUNCTION_BOX_SIZE = 1000;
        int MAX_CONNECTIONS = 1000;
        vector<Point> points;
        readPoints(points);

        // first sort all the points
        vector<SortedPoints> sortedPoints;
        for (int p1Idx=0; p1Idx < points.size(); p1Idx++) {
            for (int p2Idx=p1Idx+1; p2Idx < points.size(); p2Idx++) {
                double d = calcDistance(points[p1Idx], points[p2Idx]);
                SortedPoints sp{d, p1Idx, p2Idx};
                sortedPoints.push_back(sp);
            }
        }
        sort(sortedPoints.begin(), sortedPoints.end());
        
        // combine the points into groups
        vector<long> junctionGroups(JUNCTION_BOX_SIZE);
        iota(junctionGroups.begin(), junctionGroups.end(), 0);
        for (int idx = 0; idx < MAX_CONNECTIONS && idx<sortedPoints.size(); idx++) {
            SortedPoints sp = sortedPoints[idx];
            long root1 = parent(sp.p1Idx, junctionGroups);
            long root2 = parent(sp.p2Idx, junctionGroups);
            if (root1 != root2) {
                junctionGroups[root2] = root1;
            }
        }

        // now find the sizes of all groups and find the 3 largest ones
        vector<long> junctionGroupSizes(JUNCTION_BOX_SIZE, 0);
        for (int i=0; i<JUNCTION_BOX_SIZE; i++) {
            long p = parent(i, junctionGroups);
            junctionGroupSizes[p]++;
        }

        std::priority_queue<long, std::vector<long>, std::greater<long>> largestJunctions;
        for (long jnSize : junctionGroupSizes) {
            if (jnSize == 0) continue;
            
            largestJunctions.push(jnSize);
            if (largestJunctions.size() > 3) {
                largestJunctions.pop();
            }
        }

        long mul = 1;
        while (!largestJunctions.empty()) {
            mul *= largestJunctions.top();
            largestJunctions.pop();
        }

        cout << "Answer: " << mul << endl;
    }

    void part2() {}

    private:
    void readPoints(vector<Point>& points) {
        string line;
        while (getline(cin, line)) {
            stringstream ss(line);
            char comma;
            long x, y, z;

            ss >> x;
            ss >> comma;
            ss >> y;
            ss >> comma;
            ss >> z;

            Point p{x, y, z};
            points.push_back(p);
        }
    }

    double calcDistance(Point p1, Point p2) {
        return sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) + pow((p1.z-p2.z),2));
    }

    long parent(long idx, vector<long>& junctionGroups) {
        if (junctionGroups[idx] != idx) {
            junctionGroups[idx] = parent(junctionGroups[idx], junctionGroups);
        }
        return junctionGroups[idx];
    }
};

int main() {
    Solution solution;
    solution.part1();
    // solution.part2();

    return 0;
}