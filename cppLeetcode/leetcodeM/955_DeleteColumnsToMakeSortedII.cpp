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
    int doit_greedy(vector<string>&& A) {
        
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

    /*
        955.Delete-Columns-to-Make-Sorted-II
        我们考虑第一列。如果有任何相邻两行字符的关系是降序的，就意味着第一列我们必须删除。如果没有出现逆序，那么我们就可以保留第一列。

        假设我们可以保留第一列，那么我们考虑第二列时，在判断相邻两行字符串A[i-1][0:1]和A[i][0:1]的关系时，如何高效地判断是否存在逆序呢？我们注意到，如果A[i-1][0]<A[i][0]，那么无论A[i-1][1]和论A[i][1]的关系如何，这两个字符串总是升序关系的。
        如果A[i-1][0]==A[i][0]，那么这两个字符串的关系就取决于A[i-1][1]和A[i][1]。至于A[i-1][0]>A[i][0]，那是不可能出现的，因为我们之前所做的任何删除列的操作就是为了保证每行的字符串是增序的。

        所以我们维护一个数组p，p[i]=1表示第i行的字符串已经大于第i-1行的字符串，否则表示目前为止第i行的字符串完全等于第i-1行的字符串。这样我们只需要根据上一轮的p[i]、和这一列A[i-1][j]与A[i][j]两个字符的关系，就能判断是否维持了增序，并且记得更新p[i]。具体的是：

        1. 如果p[i]=1，那么已经增序，不用判断。
        2. 如果p[i]=0，且A[i-1][j]==A[i][j]，那么继续维持p[i]=0
        3. 如果p[i]=0，且A[i-1][j]<A[i][j]，那么可以更新p[i]=1
        4. 如果p[i]=0，且A[i-1][j]>A[i][j]，那么整个第j列都不能保留，同时p也不更新。
    */
    int doit_greedy(vector<string>& A) 
    {
        int m = A.size();
        int n = A[0].size();
        vector<int>p(m, 0);
        int ret = 0;
        for (int j=0; j<n; j++)
        {
            vector<int>p2 = p;
            int flag = true;
            for (int i=1; i<m; i++)
            {
                if (p[i]==1) continue;
                if (p[i]==0)
                {
                    if (A[i][j]>A[i-1][j])
                        p2[i] = 1;
                    else if (A[i][j]<A[i-1][j])
                    {
                        flag = false;
                        break;
                    }                        
                }
            }
            if (flag==true)
                p = p2;
            else
                ret++;
        }
        return ret;

    }
};

void test_955_delete_columns_to_make_sortedII() {
    
    auto res1 = MinDeletionSize().doit(vector<string>{"ca","bb","ac"});
    
    auto res2 = MinDeletionSize().doit(vector<string>{"xc","yb","za"});
    
    auto res3 = MinDeletionSize().doit(vector<string>{"zyx","wvu","tsr"});
    
    return;
}
