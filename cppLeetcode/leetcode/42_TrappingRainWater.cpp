/*

42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, 

compute how much water it is able to trap after raining.

The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. 

In this case, 6 units of rain water (blue section) are being trapped. 

Thanks Marcos for contributing this image!

Example:

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6


*/
#include <algorithm>
#include <vector>
using namespace std;

class TrapWater {
public:
	int doit(vector<int>& height) {
		int N = height.size();
		vector<int> left(N, 0);
		int leftMax = 0;
		for (int i = 0; i < N; i++) {
			left[i] = leftMax;
			leftMax = std::max(leftMax, height[i]);
		}

		vector<int> right(N, 0);
		int rightMax = 0;
		for (int i = N - 1; i >= 0; i--) {
			right[i] = rightMax;
			rightMax = std::max(rightMax, height[i]);
		}

		int area = 0;
		for (auto i = 0; i < N; i++) {
			int side = std::min(right[i], left[i]);
			if (side > height[i]) {
				area += side - height[i];
			}
		}

		return area;
	}
};

void Test_42_TrappingRainWater() {

	int res1 = TrapWater().doit(vector<int>{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});

	return;
}