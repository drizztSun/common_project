//
//  373_FindKPairswithSmallestSums.cpp
//  cppleetcode
//
//  Created by Yuxin Sun on 9/28/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

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
