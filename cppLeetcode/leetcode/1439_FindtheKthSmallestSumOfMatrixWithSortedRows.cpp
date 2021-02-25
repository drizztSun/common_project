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
#include <set>
#include <functional>

using std::set;
using std::vector;
using std::priority_queue;

class KthSmallest {
    
public:


    int doit_binary_search(vector<vector<int>>&& mat, int k){
        
        auto M = mat.size(), N = mat[0].size();
        int ans = 0;
        
        int left = 0, right = 0;
        for (int i = 0; i < M; i++) {
            left += mat[i][0];
            right += mat[i][N-1];
        }

        std::function<int(int, int, int, int)> search = [&](int target, int i, int sum, int k) {
        
            if (target < sum)
                return 0;
            
            if (i == mat.size())
                return 1;
            
            int ans = 0;
            
            for (int j = 0; j < mat[i].size(); j++) {
                
                int cnt = search(target, i+1, sum + mat[i][j], k-ans);
                
                if (cnt == 0)
                    break;
                
                ans += cnt;
                if (ans > k)
                    break;
            }
            
            return ans;
        };

        
        while (left <= right) {
            
            int mid = left + (right - left) / 2;
            
            int cnt = search(mid, 0, 0, k);
            
            if (cnt >= k) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return ans;
    }

    /*
        1439.Find-the-Kth-Smallest-Sum-of-a-Matrix-With-Sorted-Rows
        我们注意到，虽然array的组合有m^n个，但本题中的K不超过200.这说明我们是可以暴力找到第K大sum的array的！

        我们的初始状态是sum最小的array，也就是每行取第一个元素。然后基于这个array，分别将每行的元素替换为该行的下一个，这样就可以扩展出m个array...将所有拓展出的array放在一个PQ里，然后每次弹出的是sum最小的array，继续拓展...可见，此题本质上是就N sorted list的归并排序。

        注意的是，我们在本题采用的数据结构是set而不是PQ，是因为考虑到去重的问题。要警惕某种array的组合，可能会由不同的array拓展而来，我们不能重复加入进PQ，必须做visited标记。如果用有序的set可以同时起到去重的作用，一举两得。
    */
    int doit_heap(vector<vector<int>>& mat, int k) 
    {
        int m = mat.size();
        int n = mat[0].size();
        int sum = 0;

        for (int i=0; i<m; i++) 
            sum+=mat[i][0];
        
        set<std::pair<int,vector<int>>>Set;
        Set.insert({sum, vector<int>(m,0)});
        int count = 0;
        
        while (Set.size()>0)
        {
            auto [val, idx] = *Set.begin();
            Set.erase(Set.begin());
            count++;
        
            if (count==k) return val;
            
            for (int i=0; i<m; i++)
            {
                if (idx[i]<n-1)
                {
                    auto idx2 = idx;
                    auto val2= val;
                    val2 += mat[i][idx2[i]+1] - mat[i][idx2[i]];
                    idx2[i]++;
                    Set.insert({val2, idx2});                    
                }
            }
        }
        
        return -1;
    }

    int doit_heap(vector<vector<int>>&& mat, int k) {
        
        auto M = mat.size(), N = mat[0].size();
        auto total = 0;
        int res = 0;
        
        for (auto i = 0; i < M; i++) {
            total += mat[i][0];
        }
        
        vector<int> index(M, 0);
        priority_queue<std::pair<int, std::pair<int, vector<int>>>> qu;
        qu.push({-total, {0, index}});
        
        while (!qu.empty() && k > 0) {
            
            auto c = qu.top();
            auto total = c.first, row = c.second.first;
            vector<int> index = c.second.second;
            res = total;
            qu.pop();
            
            for (auto j = row; j < M; j++) {
                
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

    int doit_heap_1(vector<vector<int>>& mat, int k) {
        vector<int> ans = mat[0];

        std::function<vector<int>(const vector<int>&, const vector<int>&, int) > kSmallestPairs = [](const vector<int>& nums1, const vector<int>& nums2, int k) {
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
        };

       for (int i = 1; i < mat.size(); ++i)
           ans = kSmallestPairs(ans, mat[i], k);

       return ans.back();
    }  
};