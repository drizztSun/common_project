
/*
 
 # 1035. Uncrossed Lines

 # We write the integers of A and B (in the order they are given) on two separate horizontal lines.

 # Now, we may draw connecting lines: a straight line connecting two numbers A[i] and B[j] such that:

 # A[i] == B[j];
 # The line we draw does not intersect any other connecting (non-horizontal) line.
 # Note that a connecting lines cannot intersect even at the endpoints: each number can only belong to one connecting line.

 # Return the maximum number of connecting lines we can draw in this way.


 # Example 1:


 # Input: A = [1,4,2], B = [1,2,4]
 # Output: 2
 # Explanation: We can draw 2 uncrossed lines as in the diagram.
 # We cannot draw 3 uncrossed lines, because the line from A[1]=4 to B[2]=4 will intersect the line from A[2]=2 to B[1]=2.

 # Example 2:

 # Input: A = [2,5,1,2,5], B = [10,5,2,1,5,2]
 # Output: 3

 # Example 3:

 # Input: A = [1,3,7,1,7,5], B = [1,9,2,5,1]
 # Output: 2


 # Note:

 # 1 <= A.length <= 500
 # 1 <= B.length <= 500
 # 1 <= A[i], B[i] <= 2000
 # Accepted
 
 */

#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;


class MaxUncrossedLines {

public:

    int doit(vector<int>&& A, vector<int>&& B) {

        vector<vector<int>> dp(1 + A.size(), vector<int>(1 + B.size(), 0));
        
        for (int i = 1; i <= A.size(); i++) {
            
            for (int j = 1; j <= B.size(); j++) {
                
                if (A[i-1] == B[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[A.size()][B.size()];
    }
    
    int doit1(vector<int>&& A, vector<int>&& B) {
        
        int m = A.size(), n = B.size();
        vector<int> dp(n+1, 0);
        
        for (int i = 1; i <= m; ++i){
            for (int j = n; j > 0; --j)
        
                if(A[i-1] == B[j-1]) // dp[i-1][j-1]+1
                    dp[j] = dp[j-1] + 1; //
            
            for(int j = 1; j <= n; ++j)
                dp[j] = std::max(dp[j], dp[j-1]); //max(dp[i][j-1],dp[i-1][j])
        }
        return dp[n];
    }
};

void test_1035_uncrossed_line() {
    
    auto res1 = MaxUncrossedLines().doit(vector<int>{1,4,2}, vector<int>{1,2,4});
    
    auto res2 = MaxUncrossedLines().doit(vector<int>{2,5,1,2,5}, vector<int>{10,5,2,1,5,2});
    
    auto res3 = MaxUncrossedLines().doit(vector<int>{1,3,7,1,7,5}, vector<int>{1,9,2,5,1});
    
    return;
}
