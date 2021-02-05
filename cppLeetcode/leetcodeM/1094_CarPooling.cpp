/*
1094. Car Pooling

You are driving a vehicle that has capacity empty seats initially available for passengers.  The vehicle only drives east (ie. it cannot turn around and drive west.)

Given a list of trips, trip[i] = [num_passengers, start_location, end_location] contains information about the i-th trip: the number of passengers that must be picked up, 
and the locations to pick them up and drop them off.  The locations are given as the number of kilometers due east from your vehicle's initial location.

Return true if and only if it is possible to pick up and drop off all passengers for all the given trips. 

 

Example 1:

Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false
Example 2:

Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true
Example 3:

Input: trips = [[2,1,5],[3,5,7]], capacity = 3
Output: true
Example 4:

Input: trips = [[3,2,7],[3,7,9],[8,3,9]], capacity = 11
Output: true
 
 

Constraints:

trips.length <= 1000
trips[i].length == 3
1 <= trips[i][0] <= 100
0 <= trips[i][1] < trips[i][2] <= 1000
1 <= capacity <= 100000

*/
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using std::priority_queue;
using std::map;
using std::vector;

class CarPooling {

public:

    /*
        Approach 1: Time Stamp
        Intuition

        A simple idea is to go through from the start to end, and check if the actual capacity exceeds capacity.

        To know the actual capacity, we just need the number of passengers changed at each timestamp.

        We can save the number of passengers changed at each time, sort it by timestamp, and finally iterate it to check the actual capacity.

        Algorithm

        We will initialize a list to store the number of passengers changed and the corresponding timestamp and then sort it.

        Note that in Java, we do not have a nice API to do this. However, we can use a TreeMap, which can help us to sort during insertion. You can use a PriorityQueue instead.

        Finally, we just need to iterate from the start timestamp to the end timestamp and check if the actual capacity meets the condition.

        Complexity Analysis

        Assume NN is the length of trips.

        Time complexity: O(Nlog(N)) since we need to iterate over trips and sort our timestamp. Iterating costs O(N), and sorting costs O(Nlog(N)), and adding together we have O(N)+O(Nlog(N))=O(Nlog(N)).

        Space complexity: O(N) since in the worst case we need \mathcal{O}(N)O(N) to store timestamp.
    */
    bool doit_sort(vector<vector<int>>& trips, int capacity) {

        vector<std::pair<int, int>> buff;
        for (const auto& c: trips) {
            buff.push_back({c[1], c[0]});
            buff.push_back({c[2], -c[0]});
        }

        std::sort(begin(buff), end(buff), [](const auto& a, const auto& b) {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
        });

        int seats = 0;
        for (const auto& c: buff) {
            seats += c.second;
            if (seats > capacity) return false;
        }

        return true;
    }

    bool doit_heap(vector<vector<int>>& trips, int capacity) {

        std::sort(begin(trips), end(trips), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });

        priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> heap; 

        int seats = 0;
        for (const auto& cur : trips) {

            int cnt = cur[0], start = cur[1], stop = cur[2];

            while (!heap.empty() && heap.top().first <= start) {
                seats -= heap.top().second;
                heap.pop();
            }

            seats += cnt;

            if (seats > capacity) return false;

            heap.push({stop, cnt});
        }

        return true;
    }

    /*
        Approach 2: Bucket Sort
        Intuition

        Note that in the problem there is a interesting constraint:

        0 <= trips[i][1] < trips[i][2] <= 1000
        What pops into the mind is Bucket Sort, which is a sorting algorithm in \mathcal{O}(N)O(N) time but requires some prior knowledge for the range of the data.

        We can use it instead of the normal sorting in this method.

        What we do is initial 1001 buckets, and put the number of passengers changed in corresponding buckets, and collect the buckets one by one.

        Algorithm

        We will initial 1001 buckets, iterate trip, and save the number of passengers changed at i mile in the i-th bucket.
    */

    bool doit_sweepline(vector<vector<int>>& trips, int capacity) {

        int stops = 2000;
        vector<int> timelines(stops, 0);
        for (auto& c : trips) {
            timelines[c[1]] += c[0];
            timelines[c[2]] -= c[0];
        }

        int seats = 0;
        for (int i = 0; i < timelines.size(); i++) {
            seats += timelines[i];
            if (seats > capacity) return false;
        }
        return true;
    }
};