/*
 
 
 # 960. Delete Columns to Make Sorted III

 # We are given an array A of N lowercase letter strings, all of the same length.

 # Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.

 # For example, if we have an array A = ["babca","bbazb"] and deletion indices {0, 1, 4}, then the final array after deletions is ["bc","az"].

 # Suppose we chose a set of deletion indices D such that after deletions, the final array has every element (row) in lexicographic order.

 # For clarity, A[0] is in lexicographic order (ie. A[0][0] <= A[0][1] <= ... <= A[0][A[0].length - 1]), A[1] is in lexicographic order (ie. A[1][0] <= A[1][1] <= ... <= A[1][A[1].length - 1]), and so on.

 # Return the minimum possible value of D.length.


 # Example 1:

 # Input: ["babca","bbazb"]
 # Output: 3
 # Explanation: After deleting columns 0, 1, and 4, the final array is A = ["bc", "az"].
 # Both these rows are individually in lexicographic order (ie. A[0][0] <= A[0][1] and A[1][0] <= A[1][1]).
 # Note that A[0] > A[1] - the array A isn't necessarily in lexicographic order.

 # Example 2:

 # Input: ["edcba"]
 # Output: 4
 # Explanation: If we delete less than 4 columns, the only row won't be lexicographically sorted.

 # Example 3:

 # Input: ["ghi","def","abc"]
 # Output: 0
 # Explanation: All rows are already lexicographically sorted.

 
  */


/*
 
 
"""
Approach 1: Dynamic Programming
Intuition and Algorithm

This is a tricky problem that is hard to build an intuition about.

First, lets try to find the number of columns to keep, instead of the number to delete. At the end, we can subtract to find the desired answer.

Now, let's say we must keep the first column C. The next column D we keep must have all rows lexicographically sorted (ie. C[i] <= D[i]),
and we can say that we have deleted all columns between C and D.

Now, we can use dynamic programming to solve the problem in this manner.
Let dp[k] be the number of columns that are kept in answering the question for input [row[k:] for row in A].
The above gives a simple recursion for dp[k].

Complexity Analysis

Time Complexity: O(N * W^2), where N is the length of A, and W is the length of each word in A.

Space Complexity: O(W).
"""

*/

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <algorithm>

class MinDeletionSizeIII {
    
public:
    
    int doit(vector<string>&& A) {
    
        int row = A.size(), col = A[0].length();
        vector<int> dp(col, 1);
        
        for (int i = col-2; i >= 0; i--) {
            
            for (int j = i+1; j < col; j++) {
                
                int cnt = 0;
                for (auto& c: A) {
                    if (c[i] > c[j])
                        break;
                    cnt++;
                }
                
                if (cnt == A.size())
                    dp[i] = std::max(dp[i], 1 + dp[j]);
            }
        }
        
        return col - *max_element(dp.begin(), dp.end());
    }


    /*
    960.Delete-Columns-to-Make-Sorted-III
    我们将每一列看做一个整体的话，本题就是求LIS序列：要求序列的元素（一列字符串）满足递增关系。这里的递增关系具体的定义是每行字符都要是递增的。

    这种LIS没有办法用贪心的I(NlogN)来实现，但是用O(N^2)的DP就可以很容易地解决。
    */
    int minDeletionSize(vector<string>& A) {
        int N = A[0].size();

        auto checkLarger = [&](int x, int y)
        {
            int M = A.size();
            for (int i=0; i<M; i++)
            {
                if (A[i][x]<A[i][y])
                    return false;
            }
            return true;
        };
        
        vector<int>dp(N,1);
        for (int i=1; i<N; i++)
            for (int j=0; j<i; j++) {
                if (checkLarger(i, j))
                    dp[i] = std::max(dp[i], dp[j] + 1);
            }

        int result = 0;
        for (int i=0; i<N; i++)
            result = std::max(result, dp[i]);
        return N-result;
    }
        

};


void test_960_delete_columns_to_make_sorted_III() {
    
    auto res1 = MinDeletionSizeIII().doit(vector<string>{"babca","bbazb"});
    
    auto res2 = MinDeletionSizeIII().doit(vector<string>{"edcba"});
    
    auto res3 = MinDeletionSizeIII().doit(vector<string>{"ghi","def","abc"});
    
    return;
}
