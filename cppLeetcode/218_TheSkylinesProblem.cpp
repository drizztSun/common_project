

#include <vector>
#include <queue>

using namespace std;


class getSkyline {

public:

	/*
		The idea is to do line sweep and just process the buildings only at the start and end points.
		The key is to use a priority queue to save all the buildings that are still “alive”.
		The queue is sorted by its height and end time (the larger height first and if equal height,
		the one with a bigger end time first). For each iteration, we first find the current process time,
		which is either the next new building start time or the end time of the top entry of the live queue.
		If the new building start time is larger than the top one end time, then process the one in the queue first
		(pop them until it is empty or find the first one that ends after the new building); otherswise,
		if the new building starts before the top one ends, then process the new building (just put them in the queue).
		After processing, output it to the resulting vector if the height changes. Complexity is the worst case O(NlogN)

		Not sure why my algorithm is so slow considering others’ Python solution can achieve 160ms, any commments?
	*/

	vector<pair<int, int>> doit(vector<vector<int>>& buildings) {

		std::priority_queue<pair<int, int>> heightQ;
		std::vector<pair<int, int>> skyline;
		int i = 0;

		while (i < buildings.size() || !heightQ.empty()) {
			int x = -1;
			if (heightQ.empty() || (i < buildings.size() && buildings[i][0] <= heightQ.top().second)) {
				x = buildings[i][0];
				while (i < buildings.size() && buildings[i][0] <= x) {
					heightQ.push(make_pair(buildings[i][2], buildings[i][1]));
					i++;
				}
			}
			else {
				x = heightQ.top().second;
				while (!heightQ.empty() && heightQ.top().second <= x) {
					heightQ.pop();
				}
			}

			int height = heightQ.empty() ? 0 : heightQ.top().first;

			if (skyline.empty() || height != skyline.back().second) {
				skyline.push_back(make_pair(x, height));
			}
		}

		return skyline;
	}
};


class Solution {
public:
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {

		vector<pair<int, int>> res;
		int cur = 0, cur_X, cur_H = -1, len = buildings.size();
		priority_queue< pair<int, int>> liveBlg; // first: height, second, end time

		while (cur<len || !liveBlg.empty())
		{ // if either some new building is not processed or live building queue is not empty
			cur_X = liveBlg.empty() ? buildings[cur][0] : liveBlg.top().second; // next timing point to process

			if (cur >= len || buildings[cur][0] > cur_X)
			{ //first check if the current tallest building will end before the next timing point
			  // pop up the processed buildings, i.e. those  have height no larger than cur_H and end before the top one
				while (!liveBlg.empty() && (liveBlg.top().second <= cur_X)) 
					liveBlg.pop();
			}
			else
			{ // if the next new building starts before the top one ends, process the new building in the vector
				cur_X = buildings[cur][0];
				while (cur<len && buildings[cur][0] == cur_X)  // go through all the new buildings that starts at the same point
				{  // just push them in the queue
					liveBlg.push(make_pair(buildings[cur][2], buildings[cur][1]));
					cur++;
				}
			}
			cur_H = liveBlg.empty() ? 0 : liveBlg.top().first; // outut the top one
			if (res.empty() || (res.back().second != cur_H)) 
				res.push_back(make_pair(cur_X, cur_H));
		}
		return res;
	}


	vector<pair<int, int>> doit(vector<vector<int>>& buildings) {

		priority_queue<pair<int, int>> rightNd;
		vector<pair<int, int>> skyline;
		size_t i = 0, x = 0;

		while (i < buildings.size() || !rightNd.empty()) {

			if (rightNd.empty() || (i < buildings.size() && buildings[i][0] <= rightNd.top().second)) {

				x = buildings[i][0];
				while (i < buildings.size() && buildings[i][0] <= x) {
					rightNd.push(make_pair(buildings[i][2], buildings[i][1]));
					i++;
				}
			}
			else {

				x = rightNd.top().second;
				while (!rightNd.empty() && rightNd.top().second <= x)
					rightNd.pop();
			}


			int height = rightNd.empty() ? 0 : rightNd.top().first;

			if (skyline.empty() || height != skyline.back().second) {
				skyline.push_back(make_pair(x, height));
			}
			
		}

		return skyline;
	}
};



void Test_218_TheSKylinesProblem()
{
	getSkyline A;

	vector<vector<int>> buildings;
	buildings.push_back(vector<int>({ 2, 9, 10 }));
	buildings.push_back(vector<int>({ 3, 7, 15 }));
	buildings.push_back(vector<int>({ 5, 12, 12 }));
	buildings.push_back(vector<int>({ 15, 20, 10 }));
	buildings.push_back(vector<int>({ 19, 24, 8 }));

	// [ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]
	auto res = A.doit(buildings);

	res = Solution().doit(buildings);

	return;
}