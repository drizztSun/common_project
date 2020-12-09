/*
 1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows
 
 
 You are given an m * n matrix, mat, and an integer k, which has its rows sorted in non-decreasing order.

 You are allowed to choose exactly 1 element from each row to form an array. Return the Kth smallest array sum among all possible arrays.

 Example 1:

 Input: mat = [[1,3,11],[2,4,6]], k = 5
 Output: 7
 Explanation: Choosing one element from each row, the first k smallest sum are:
 [1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.

 Example 2:

 Input: mat = [[1,3,11],[2,4,6]], k = 9
 Output: 17
 Example 3:

 Input: mat = [[1,10,10],[1,4,5],[2,3,6]], k = 7
 Output: 9
 Explanation: Choosing one element from each row, the first k smallest sum are:
 [1,1,2], [1,1,3], [1,4,2], [1,4,3], [1,1,6], [1,5,2], [1,5,3]. Where the 7th sum is 9.

 Example 4:

 Input: mat = [[1,1,10],[2,2,9]], k = 7
 Output: 12


 Constraints:

 m == mat.length
 n == mat.length[i]
 1 <= m, n <= 40
 1 <= k <= min(200, n ^ m)
 1 <= mat[i][j] <= 5000
 mat[i] is a non decreasing array.
 */

#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;

class KthSmallest {
    
public:
    
    
    vector<int> kSmallestPairs(const vector<int>& nums1, const vector<int>& nums2, int k) {
       const int M = nums1.size();
       const int N = nums2.size();
       auto cmp = [&](const auto& lhs, const auto& rhs) {
           return nums1[lhs.first] + nums2[lhs.second] > nums1[rhs.first] + nums2[rhs.second];
       };
       priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);
       vector<int> ans;
       // i < k ?
       // k is param or fixed number ?
       for (int i = 0; i < M && i < k; ++i)
           pq.push({i, 0});

       // why somewhere --k
       while (k-- && !pq.empty()) {
           auto top = pq.top();
           pq.pop();
           ans.push_back(nums1[top.first] + nums2[top.second]);

           if (top.second + 1 < N)
               pq.push({top.first, top.second + 1});
       }

       return ans;
   }

   int doit_heap_1(vector<vector<int>>& mat, int k) {
       vector<int> ans = mat[0];
       for (int i = 1; i < mat.size(); ++i)
           ans = kSmallestPairs(ans, mat[i], k);

       // ans.back(), ans.size() ?
       return ans.back();
   }
    
    int doit_heap(vector<vector<int>>&& mat, int k) {
        
        auto M = mat.size(), N = mat[0].size();
        auto total = 0;
        int res = 0;
        
        for (auto i = 0; i < M; i++) {
            total += mat[i][0];
        }
        
        vector<int> index(N, 0);
        priority_queue<std::pair<int, std::pair<int, vector<int>>>> qu;
        qu.push({-total, {0, index}});
        
        while (!qu.empty() && k > 0) {
            
            auto c = qu.top();
            auto total = c.first, row = c.second.first;
            vector<int> index = c.second.second;
            res = total;
            qu.pop();
            
            for (auto j = row; j < N; j++) {
                
                index[j]++;
                
                if (index[j] < N) {
                    qu.push({total - mat[j][index[j]] + mat[j][index[j]-1], {j, index}});
                }
                index[j]--;
            }
            
            k--;
        }
        
        return -res;
    }
    
    int search(vector<vector<int>>& mat, int target, int i, int sum, int k) {
        
        if (target < sum)
            return 0;
        
        if (i == mat.size())
            return 1;
        
        int ans = 0;
        
        for (int j = 0; j < mat[i].size(); j++) {
            
            int cnt = search(mat, target, i+1, sum + mat[i][j], k-ans);
            
            if (cnt == 0)
                break;
            
            ans += cnt;
            if (ans > k)
                break;
        }
        
        return ans;
    }
    
    int doit_binary_search(vector<vector<int>>&& mat, int k){
        
        auto M = mat.size(), N = mat[0].size();
        int ans = 0;
        
        int left = 0, right = 0;
        for (int i = 0; i < M; i++) {
            left += mat[i][0];
            right += mat[i][N-1];
        }
        
        while (left <= right) {
            
            int mid = left + (right - left) / 2;
            
            int cnt = search(mat, mid, 0, 0, k);
            
            if (cnt >= k) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return ans;
    }
    
};


void test_1439_find_the_kth_smallest_sum_of_matrix_with_sorted_rows() {
    
    KthSmallest().doit_heap(vector<vector<int>>{{1, 10, 10}, {1, 4, 5}, {2, 3, 6}}, 7);
    
}
