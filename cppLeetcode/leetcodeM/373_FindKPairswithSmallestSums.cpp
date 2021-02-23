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

    /*
        378. Kth Smallest Element in a Sorted Matrix
        解法１
        矩阵的规律是：如果matrix[i][j]不是最小的，则matrix[i+1][j]和matrix[i][j+1]就都不用考虑。或者matrix[i][j]是最小的，则matrix[i+1][j]和matrix[i][j+1]就能进如考虑范围。

        所以类似BFS的算法，设计一个小顶堆的Priority_queue，每次出列最小值之后，将最小值邻接的matrix[i+1][j]和matrix[i][j+1]加入这个队列会自动排序。当出列k个数之后就是答案。

        类似的题目：373

        解法2
        以上的解法在新的测试集下会非常慢．更优的方法是binary search.

        显然，答案的上限是matrix[0][0],下限是matrix[N-1][N-1]．对于这个区间的任意一个ｘ，我们可以计算出这个矩阵里小于等于ｘ的元素有多少，定义为smallerOrEqual(x)．如果smallerOrEqual(x)<k，说明这个ｋ太小了不是想要的答案，
        应该往上调整，所以left=x+1.反之smallerOrEqual(x)>=k，说明ｋ可能是答案，但可以再缩小一点试一试，因此right=x．　（当然，更直接一点，其实如果直接得到smallerOrEqual(x)==k的话就已经说明ｋ就是答案了）

        那么如果写这个smallerOrEqual(x)呢？这个思路其实和 240. Search a 2D Matrix II 非常相似．对于这种行列都排序的矩阵，我们可以从左下角（其实右上角也可以）出发，遇到matrix[i][j]<=x，说明从(i,j)之上的整列都smallerOrEqual(x)，于是就可以往右移动一列．　
        否则的话，我们就往上移动一行．　这样直至我们走出这个矩阵，走过的路径就自动将矩阵划分为了左上和右下两个部分，就是以smallerOrEqual(x)为分界的．

        这个性质非常好用，请大家多多练习．（从左下角出发或者从右上角出发）．
    */
    struct cmp
    {
        bool operator()(std::pair<int,int>a, std::pair<int,int>b)
        {
            return a.first>b.first;
        }
    };
    
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        priority_queue<std::pair<int,int>,vector<std::pair<int,int>>,cmp>q;
        int M=nums1.size();
        int N=nums2.size();
        vector<pair<int, int>>results;
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

};

void test_373_find_Kpair_with_smallest_sum() {
    
    vector<int> a{1, 1, 2};
    vector<int> b{1, 2, 3};
    
    KSmallestPairs().doit_heap(a, b, 3);
}
