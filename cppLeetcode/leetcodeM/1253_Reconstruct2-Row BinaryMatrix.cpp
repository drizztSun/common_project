/*
1253. Reconstruct a 2-Row Binary Matrix

Given the following details of a matrix with n columns and 2 rows :

The matrix is a binary matrix, which means each element in the matrix can be 0 or 1.
The sum of elements of the 0-th(upper) row is given as upper.
The sum of elements of the 1-st(lower) row is given as lower.
The sum of elements in the i-th column(0-indexed) is colsum[i], where colsum is given as an integer array with length n.
Your task is to reconstruct the matrix with upper, lower and colsum.

Return it as a 2-D integer array.

If there are more than one valid solution, any of them will be accepted.

If no valid solution exists, return an empty 2-D array.

 

Example 1:

Input: upper = 2, lower = 1, colsum = [1,1,1]
Output: [[1,1,0],[0,0,1]]
Explanation: [[1,0,1],[0,1,0]], and [[0,1,1],[1,0,0]] are also correct answers.
Example 2:

Input: upper = 2, lower = 3, colsum = [2,2,1,1]
Output: []
Example 3:

Input: upper = 5, lower = 5, colsum = [2,1,2,0,1,0,1,2,0,1]
Output: [[1,1,1,0,1,0,0,1,0,0],[1,0,1,0,0,0,1,1,0,1]]
 

Constraints:

1 <= colsum.length <= 10^5
0 <= upper, lower <= colsum.length
0 <= colsum[i] <= 2

*/
#include <vector>
#include <numeric>

using std::vector;


class ReconstructMatrix {

    /*
        1253.Reconstruct-a-2-Row-Binary-Matrix
        容易知道，当colsum==0时，上下两行都要赋值0；当colsum==2时，上下两行都要赋值1.那么当colsum==1时，我们是否该任意给上一行或下一行赋值1呢？

        这时有一个比较保守但有效的策略，那就是用upper和lower来统计上/下行分别还有多少个1还没有被使用。如果upper>lower，那么就优先给上一行赋值1，反之就优先给下一行赋值1.这样做是为了应对colsum==2的情况，保证上下行都尽量能存留有足够的1.举个例子，如果upper远多于lower，那么等lower降至0的时候，再碰到colsum==2的情况时就没有可行解了，之前全部的尝试都要作废。

        如果采用了上述的保守的贪心策略，但最终还是遇到了colsum==2且lower为0的情况，那么说明了这个题就没有解，直接返回空就行了。

        另外，本题有两个细节要注意。（1）当upper>=lower时，仍要检查upper是否大于0才可以给上一行赋值1. 反之同理。（2）当colsum全部走过一遍之后，仍需要保证此时upper==0 && lower==0 才能说明有解，也就是说初始状态下需要满足sum(colsum)==upper+lower。
    */
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) 
    {
        vector<int>a;
        vector<int>b;
        
        for (auto x: colsum)
        {
            if (x==2)
            {
                if (upper==0 || lower==0)
                    return {};
                a.push_back(1);
                b.push_back(1);
                upper--;
                lower--;
            }
            else if (x==0)
            {
                a.push_back(0);
                b.push_back(0);
            }
            else
            {
                if (upper>=lower && upper>0)
                {
                    a.push_back(1);
                    b.push_back(0);
                    upper--;
                }
                else if (lower>=upper && lower>0)
                {
                    a.push_back(0);
                    b.push_back(1);
                    lower--;
                }
                else
                    return {};
            }
        }
        
        if (upper!=0 || lower!=0)
            return {};
        else
            return {a,b};
    }

public:

    vector<vector<int>> doit_greedy(int upper, int lower, vector<int>& colsum) {
        
        int n = colsum.size();
        
        if (upper + lower != std::accumulate(begin(colsum), end(colsum), 0)) return {};
        
        vector<vector<int>> ans(2, vector<int>(n, 0));
        
        for (int i = 0; i < colsum.size(); i++) {
            
            if (colsum[i] == 0) continue;
            
            if (colsum[i] == 2) {
                
                if (upper == 0 || lower == 0) return {};
                
                ans[0][i] = ans[1][i] = 1;
                upper--;
                lower--;
            } else {
                if (upper >= lower) {
                    ans[0][i] = 1;
                    if (upper == 0) return {};
                    upper--;
                    
                } else {
                    ans[1][i] = 1;
                    
                    if (lower == 0) return {};
                    lower--;                
                }
            }
        }

        return ans;   
    }
};