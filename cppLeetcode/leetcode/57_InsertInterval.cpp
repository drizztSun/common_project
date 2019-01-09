/*

57. Insert Interval


Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]

Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].


*/


// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};



#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:

	vector<Interval> doit(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval> res;
		bool insert = true;
		for (auto& x : intervals) {

			if (x.end < newInterval.start) {
				res.push_back(x);
			}
			else if (x.start > newInterval.end) {
				if (insert) {
					res.push_back(newInterval);
					insert = false;
				}
				res.push_back(x);
			}
			else {
				newInterval.start = min(newInterval.start, x.start);
				newInterval.end = max(newInterval.end, x.end);
			}
		}

		if (insert)
			res.push_back(newInterval);

		return res;
	}


	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {

		int N = intervals.size();

		int lo = 0, hi = N - 1;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (intervals[mid].start <= newInterval.start) {
				lo = mid;
			}
			else {
				hi = mid - 1;
			}
		}
		int s = lo;

		lo = s, hi = N - 1;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (intervals[mid].end <= newInterval.end)
				lo = mid;
			else
				hi = mid - 1;
		}
		int e = lo;


		return vector<Interval>{};
	}
};
