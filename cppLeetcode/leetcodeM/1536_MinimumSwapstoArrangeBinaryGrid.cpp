/*
1536. Minimum Swaps to Arrange a Binary Grid

Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.

A grid is said to be valid if all the cells above the main diagonal are zeros.

Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.

The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).

 

Example 1:


Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
Output: 3
Example 2:


Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
Output: -1
Explanation: All rows are similar, swaps have no effect on the grid.
Example 3:


Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
Output: 0
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 200
grid[i][j] is 0 or 1

*/
#include <vector>
#include <list>

using std::list;
using std::vector;


class MinSwaps {

public:

    /*
        1536.Minimum-Swaps-to-Arrange-a-Binary-Grid
        本题先进行一下转换。将每行末尾的零的个数统计一下，得到数组zeros，即zeros[i]表示第i行末尾的零的个数。我们的目标是将zeros通过adjacent swap操作，变成一个数组target，其中target[i]>=n-1-i. 求最小的操作数。

        我们首先考虑target[0]，它的要求最高（需要有n-1个零）。我们考察所有的行，看看有哪些满足条件。加入有a和b两行满足条件，即zeros[a]>=n-1，zeros[b]>=n-1，那么我们应该选择将哪一行挪到第0行的位置上来呢？我们不妨举个例子：

        X X X a X b X
        如果我们选择将第b行提到最前面，那么需要操作5次得到

        b X X X a X X   (1)
        如果我们选择将第a行提到最前面，那么需要操作3次得到

        a X X X X b X   (2)
        别停，我们如果对(2)继续操作1次（将b前移一位）能得到

        a X X X b X X   (3)
        我们比较一下(1)和(3)。我们发现对于第0行的处理，两种方案都满足条件。唯一的区别是，第一种方案第4行是zeros[a]，第二种方案第4行是zeros[b]。
        
        但是由于zeros[a]和zeros[b]都是大于等于n-1的，而除了target[0]之外的target[i]的要求都不到n-1，
        
        所以这两行（a和b）对于以后的安排而言都是“溢价”的，即“价值”是没有区别的。但是第一种方案需要5次操作，第二种方案只需要4次操作。

        所以我们得到一个贪心的结论：当我们处理target[i]时需要找某个zeros[j]>=n-1-i时，只要从i开始往后顺次查找第一个满足zeros[j]>=n-1-i的位置即可。然后将j所对应的行提前到第i行。然后处理target[i+1]，不断重复。
    */


    int doit_greedy(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        vector<int>zeros(n);
        for (int i=0; i<n; i++)
        {
            int count = 0;
            for (int j=n-1; j>=0; j--)
            {
                if (grid[i][j]!=0)
                    break;
                count++;
            }
            zeros[i] = count;            
        }
        
        int count = 0;
        for (int i=0; i<n-1; i++)
        {
            int num = n-1-i;
            int j = i;
            for (; j<n; j++)
            {
                if (zeros[j]>=num)
                    break;
            }
            if (j==n) return -1;
            count += j-i;
            int temp = zeros[j];
            for (int k=j; k>i; k--)
                zeros[k] = zeros[k-1];
            zeros[i] = temp;
        }
        
        return count;
    }

    int doit_greedy(vector<vector<int>>& grid) {

        int n = grid.size(), res = 0;
        list<int> cnt0;
        for(const auto& v:grid) 
            cnt0.push_back(find(v.rbegin(), v.rend(), 1) - v.rbegin());
        
        for(int i=0;i<n;i++){
            int j=0;
            for(auto it = cnt0.begin(); it !=cnt0.end(); ++it, ++j){
                if(*it >= n-i-1){
                    res += j;
                    cnt0.erase(it);
                    break;
                }
            }

            if(j==n-i) return -1;
        }

        return res;
    }

    int doit_greedy(vector<vector<int>>& grid) {
        
        int n=grid.size();
        vector<int> arr(n,0);
        
        for(int i=0;i<n;i++) {
            int count=0;
            for(int j=n-1;j>=0 && grid[i][j]==0;j--)
                count++;
            
            arr[i]=count;
        }
        int res=0;
        
        for(int i=0;i<n;i++) {
            int k=i,req=n-1-k;
            
            while(k<n && arr[k]<req)
                k++;
            
            if(k==n)
                return -1;
            
            res+=(k-i);
            //arr[k] = -1;
            
            while(k>i) {
                arr[k]=arr[k-1];
                k--;
            }
        }
        
        return res;
    }
};