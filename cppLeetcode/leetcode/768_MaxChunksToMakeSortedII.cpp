/*

# 768. Max Chunks To Make Sorted II

# Given an array arr of integers (not necessarily distinct),
# we split the array into some number of "chunks" (partitions),
# and individually sort each chunk.
# After concatenating them, the result equals the sorted array.

# What is the most number of chunks we could have made?

# Example 1:

# Input: arr = [5,4,3,2,1]
# Output: 1
# Explanation:
# Splitting into two or more chunks will not return the required result.
# For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.

# Example 2:

# Input: arr = [2,1,3,4,4]
# Output: 4
# Explanation:
# We can split into two chunks, such as [2, 1], [3, 4, 4].
# However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.
# Note:

# arr will have length in range [1, 2000].
# arr[i] will be an integer in range [0, 10**8].



*/

#include <vector>

using namespace std;


class MaxChunksToSorted {
public:
	int doit(vector<int>&& arr) {
		size_t length = arr.size();
		vector<int> leftMax(length), rightMin(length);
	
		leftMax[0] = arr[0];
		for (auto i = 1; i < arr.size(); i++) {
			if (leftMax[i - 1] > arr[i])
				leftMax[i] = leftMax[i - 1];
			else
				leftMax[i] = arr[i];
		}

		rightMin[length - 1] = arr[length - 1];
		for (auto i = length - 2; i >= 0; i--) {
			if (rightMin[i + 1] < arr[i])
				rightMin[i] = rightMin[i + 1];
			else
				rightMin[i] = arr[i];
		}

		int maxChunks = 0;
		for (auto i = 0; i < arr.size()-1; i++) {
			if (leftMax[i] <= rightMin[i + 1])
				maxChunks++;
		}

		return maxChunks + 1;
	}
};


void Test_768_MaxChunksToMakeSortedII() {

	MaxChunksToSorted().doit(vector<int>{5, 4, 3, 2, 1});

	MaxChunksToSorted().doit(vector<int>{2, 1, 3, 4, 4});

	return;
}
