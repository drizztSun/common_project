/*
 
 # 955. Delete Columns to Make Sorted II

 # We are given an array A of N lowercase letter strings, all of the same length.

 # Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.

 # For example, if we have an array A = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3},
 # then the final array after deletions is ["bef","vyz"].

 # Suppose we chose a set of deletion indices D such that after deletions,
 # the final array has its elements in lexicographic order (A[0] <= A[1] <= A[2] ... <= A[A.length - 1]).

 # Return the minimum possible value of D.length.

 # Example 1:

 # Input: ["ca","bb","ac"]
 # Output: 1
 # Explanation:
 # After deleting the first column, A = ["a", "b", "c"].
 # Now A is in lexicographic order (ie. A[0] <= A[1] <= A[2]).
 # We require at least 1 deletion since initially A was not in lexicographic order, so the answer is 1.

 # Example 2:

 # Input: ["xc","yb","za"]
 # Output: 0
 # Explanation:
 # A is already in lexicographic order, so we don't need to delete anything.
 # Note that the rows of A are not necessarily in lexicographic order:
 # ie. it is NOT necessarily true that (A[0][0] <= A[0][1] <= ...)

 # Example 3:

 # Input: ["zyx","wvu","tsr"]
 # Output: 3
 # Explanation:
 # We have to delete every column.
 
 
 */

#include <vector>
using std::vector;

#include <string>
using std::string;

class MinDeletionSize {

public:
    /*
     Approach 2: Greedy with Optimizations
     Explanation

     It is also possible to implement the solution in Approach 1 without using as much time and space.

     The key idea is that we will record the "cuts" that each column makes.
     In our first example from Approach 1 with A = ["axx","ayy","baa","bbb","bcc"] (and R defined as in Approach 1),
     the first column cuts our condition from R[0] <= R[1] <= R[2] <= R[3] <= R[4] to R[0] <= R[1] and R[2] <= R[3] <= R[4].
     
     That is, the boundary "a" == column[1] != column[2] == "b" has 'cut' one of the conditions for R out.

     At a high level, our algorithm depends on evaluating whether adding a new column will keep all the rows sorted.
     By maintaining information about these cuts, we only need to compare characters in the newest column.
     */
    int doit(vector<string>&& A) {
        
        size_t N = A.size();
        vector<bool> cur(N-1, false);
        int ans = 0;
        
        for (size_t i = 0; i < A[0].size(); i++) {
            
            int cnt = 0;
            for (size_t j = 0; j < A.size()-1; j++) {
                if (cur[j] || A[j][i] <= A[j+1][i])
                    cnt++;
                else
                    break;
            }
            
            if (cnt == A.size()-1) {
                for (size_t j = 0; j < A.size()-1; j++)
                    if (!cur[j] && A[j][i] < A[j+1][i])
                        cur[j] = true;
            } else
                ans++;
        }
    
        return ans;
    }
};

void test_955_delete_columns_to_make_sortedII() {
    
    auto res1 = MinDeletionSize().doit(vector<string>{"ca","bb","ac"});
    
    auto res2 = MinDeletionSize().doit(vector<string>{"xc","yb","za"});
    
    auto res3 = MinDeletionSize().doit(vector<string>{"zyx","wvu","tsr"});
    
    return;
}
