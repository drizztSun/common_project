/*
373. Find K Pairs with Smallest Sums


You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u,v) which consists of one element from the first array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:

Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]] 
Explanation: The first 3 pairs are returned from the sequence: 
             [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:

Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [1,1],[1,1]
Explanation: The first 2 pairs are returned from the sequence: 
             [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:

Input: nums1 = [1,2], nums2 = [3], k = 3
Output: [1,3],[2,3]
Explanation: All possible pairs are returned from the sequence: [1,3],[2,3]

*/

#include <stdio.h>
#include <queue>
#include <vector>

using std::vector;
using std::priority_queue;

class KSmallestPairs {
    
public:
    vector<vector<int>> doit_heap(vector<int>& nums1, vector<int>& nums2, int k) {
        
        if (nums1.empty() || nums2.empty()) {
            return {};
        }
    
        vector<vector<int>> res;
        priority_queue<std::pair<int, std::pair<int, int>>> heap;
        
        auto heappush = [&](int i, int j) {
            if (i >= 0 && i < nums1.size() && j >= 0 && j < nums2.size()) {
                heap.push({-(nums1[i] + nums2[j]), {i, j}});
            }
        };
        
        heappush(0, 0);
        
        while (!heap.empty() && res.size() < k) {
            
            auto c = heap.top().second;
            int i = c.first, j = c.second;
            res.push_back({nums1[i], nums2[j]});
            heap.pop();
            
            heappush(i, j+1);
            if (j==0)
                heappush(i+1, j);
        }
        
        return res;
    }
};

void test_373_find_Kpair_with_smallest_sum() {
    
    vector<int> a{1, 1, 2};
    vector<int> b{1, 2, 3};
    
    KSmallestPairs().doit_heap(a, b, 3);
}
