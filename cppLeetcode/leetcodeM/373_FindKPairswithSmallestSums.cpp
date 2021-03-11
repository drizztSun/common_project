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

    /*
        373.Find-K-Pairs-with-Smallest-Sums
        本题本质上非常巧妙地转换成了二维矩阵问题，同378。

        设想一个MxN的矩阵，其矩阵元素(m,n)就是num1[m]+nums2[n]，很显然这个矩阵的行、列都是递增的。于是立刻就转化成了找该矩阵第k个元素的问题。

        解法1：BFS+PQ
        用BFS的方法进行搜索。每次弹出一个PQ里最小的元素，然后新加入该元素相邻（右边和下边）的两个元素。最先弹出的k个元素就是答案。

        解法2：binary search + sorted matrix property
        此题和378. Kth Smallest Element in a Sorted Matrix非常相似。

        用binary search的方法先确定按从小到大顺序第k个元素是多少，令它为x。然后打印出matrix里面所有小于等于x的元素。注意，这样的元素可能会超过k个，也可能会小于k个。最终只要输出k个。
    */
    struct cmp
    {
        bool operator()(std::pair<int,int>a, std::pair<int,int>b)
        {
            return a.first>b.first;
        }
    };
    
    vector<vector<int>> doit_heap(vector<int>& nums1, vector<int>& nums2, int k)
    {
        priority_queue<std::pair<int,int>, vector<std::pair<int,int>>, cmp>q;
        int M=nums1.size();
        int N=nums2.size();
        vector<vector<int>>results;
        if (M==0 || N==0) return results;
        
        auto used=vector<vector<int>>(M,vector<int>(N,0));
        q.push({nums1[0]+nums2[0],0});                
        used[0][0]=1;
        
        int count=0;
        while (count<k && q.size()>0)
        {
            int m=q.top().second/N;
            int n=q.top().second%N;
            results.push_back({nums1[m],nums2[n]});
            count++;
            q.pop();
            
            if (m+1<M && used[m+1][n]==0)
            {
                q.push({nums1[m+1]+nums2[n],(m+1)*N+n});
                used[m+1][n]=1;
            }
            if (n+1<N && used[m][n+1]==0)
            {
                q.push({nums1[m]+nums2[n+1],(m)*N+n+1});
                used[m][n+1]=1;
            }             
        }
        
        return results;                
    }


    static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[0]+a[1]<b[0]+b[1];
    }
public:
    vector<vector<int>> doit_binary_search(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        int M = nums1.size();
        int N = nums2.size();
        if (M==0 || N==0) return {};
        
        auto matrix = vector<vector<int>>(M,vector<int>(N));
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
                matrix[i][j] = nums1[i]+nums2[j];
        
        int left = matrix[0][0];
        int right = matrix[M-1][N-1];
        while (left<right)
        {
            int mid = left+(right-left)/2;
            if (EqualOrSmaller(matrix, mid) < k)
                 left = mid+1;
            else
                right = mid;
        }
        
        int x = left;
        
        vector<vector<int>>results;
        int i = M-1, j = 0;
        while (i>=0 && j<N)
        {
            if (matrix[i][j]<=x)
            {
                for (int k=i; k>=0; k--)
                    results.push_back({nums1[k],nums2[j]});
                j++;
            }
            else
                i--;
        }
        
        sort(results.begin(), results.end(), cmp);
        if (k<results.size())
            results.resize(k);
        return results;
    }
    
    int EqualOrSmaller(vector<vector<int>>& matrix, int x)
    {
        int M = matrix.size();
        int N = matrix[0].size();
        int i = M-1, j = 0;
        int count = 0;
        while (i>=0 && j<N)
        {
            if (matrix[i][j]<=x)
            {
                count += i+1;
                j++;
            }
            else
                i--;
        }
        return count;        
    }
};