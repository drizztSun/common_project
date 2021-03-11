/*
378. Kth Smallest Element in a Sorted Matrix

Given an n x n matrix where each of the rows and columns are sorted in ascending order, return the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

 

Example 1:

Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
Example 2:

Input: matrix = [[-5]], k = 1
Output: -5
 

Constraints:

n == matrix.length
n == matrix[i].length
1 <= n <= 300
-10^9 <= matrix[i][j] <= -10^9
All the rows and columns of matrix are guaranteed to be sorted in non-degreasing order.
1 <= k <= n^2
*/

#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::priority_queue;


class KthSmallestInSortedMatrix {

public:
    
    int doit_heap(vector<vector<int>>& matrix, int k) {

        priority_queue<std::pair<int, std::pair<int, int>>> heap;
        
        auto push = [&](int i, int j) {
            if (i < matrix.size() && j < matrix[0].size())
                heap.push({-matrix[i][j], {i, j}});
        };
        
        push(0, 0);
        int ans = 0;

        while (!heap.empty() && k > 0) {
            
            auto item = heap.top();
            auto c = item.second;
        
            ans = item.first;
            int x = c.first, y = c.second;
            heap.pop();
            k--;
            
            push(x, y+1);
            
            if (y==0)
                push(x+1, y);
        }
        
        return -ans;
    }
    
    // O(m*(logn)^2)
    int doit_binary_search(vector<vector<int>>& matrix, int k) {
     
        int size = matrix.size(), l = matrix[0][0], r = matrix[size-1][size-1];
        
        while(l < r) {
            
            int smaller = 0, m = l+((r-l)>>1);
            
            for(int i = 0; i < size; ++i) {
               smaller += std::upper_bound(matrix[i].begin(), matrix[i].end(), m) - matrix[i].begin();
            }
            
            if (smaller < k)
                l = m + 1;
            else 
                r = m;
        }

        return r;
    }

    /*

    378. Kth Smallest Element in a Sorted Matrix
    解法１
    矩阵的规律是：如果matrix[i][j]不是最小的，则matrix[i+1][j]和matrix[i][j+1]就都不用考虑。或者matrix[i][j]是最小的，则matrix[i+1][j]和matrix[i][j+1]就能进如考虑范围。

    所以类似BFS的算法，设计一个小顶堆的Priority_queue，每次出列最小值之后，将最小值邻接的matrix[i+1][j]和matrix[i][j+1]加入这个队列会自动排序。当出列k个数之后就是答案。

    类似的题目：373

    解法2
    以上的解法在新的测试集下会非常慢．更优的方法是binary search.

    显然，答案的上限是matrix[0][0],下限是matrix[N-1][N-1]．对于这个区间的任意一个ｘ，我们可以计算出这个矩阵里小于等于ｘ的元素有多少，定义为smallerOrEqual(x)．
    如果smallerOrEqual(x)<k，说明这个ｋ太小了不是想要的答案，应该往上调整，所以left=x+1.反之smallerOrEqual(x)>=k，说明ｋ可能是答案，但可以再缩小一点试一试，因此right=x．　（当然，更直接一点，其实如果直接得到smallerOrEqual(x)==k的话就已经说明ｋ就是答案了）

    那么如果写这个smallerOrEqual(x)呢？这个思路其实和 240. Search a 2D Matrix II 非常相似．对于这种行列都排序的矩阵，我们可以从左下角（其实右上角也可以）出发，遇到matrix[i][j]<=x，说明从(i,j)之上的整列都smallerOrEqual(x)，于是就可以往右移动一列．　
    否则的话，我们就往上移动一行．　这样直至我们走出这个矩阵，走过的路径就自动将矩阵划分为了左上和右下两个部分，就是以smallerOrEqual(x)为分界的．
    */

    struct cmp
    {
        bool operator()(std::pair<int,int>a, std::pair<int,int>b)
        {
            return a.first>=b.first;
        }
    };
    
    int doit_heap_1(vector<vector<int>>& matrix, int k) 
    {
        int M=matrix.size();
        int N=matrix[0].size();
        
        auto visited=vector<vector<int>>(M,vector<int>(N,0));
        visited[0][0]=1;
        
        priority_queue<std::pair<int,int>,vector<std::pair<int,int>>, cmp>q;
        q.push({matrix[0][0],0});
        int count=0;
        int result;
        
        while (count<k)
        {
            int i=q.top().second/N;
            int j=q.top().second%N;
            int t=q.top().first;
            q.pop();
            count++;
            if (count==k)
                result=t;
            
            if (i+1<M && j<N && visited[i+1][j]==0)
            {
                q.push({matrix[i+1][j],(i+1)*N+j});
                visited[i+1][j]=1;
            }
            if (i<M && j+1<N && visited[i][j+1]==0)
            {
                q.push({matrix[i][j+1],(i)*N+j+1});
                visited[i][j+1]=1;
            }
        }
        
        return result;
    }

    int doit_binary_search_1(vector<vector<int>>& matrix, int k) 
    {
        int N = matrix.size();
        int left = matrix[0][0];
        int right = matrix[N-1][N-1];

        auto equalOrSmaller = [&](int x) {

            int i = N-1, j=0, count = 0;
            
            while (i >= 0 && j < N)
            {
                if (matrix[i][j] <= x)
                {
                    count += (i+1);
                    j++;
                }
                else
                    i--;                
            }
            return count;
        };

        while (left<right)
        {
            int mid = left + (right - left) / 2;
            
            if (equalOrSmaller(mid) < k)
                left = mid+1;
            else
                right = mid;
        }
        return left;
    }
    
    
};
