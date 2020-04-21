/*
 
 943. Find the Shortest Superstring
 
 
 # 943. Find the Shortest Superstring

 # Given an array A of strings, find any smallest string that contains each string in A as a substring.
 #
 # We may assume that no string in A is substring of another string in A.
 #
 #
 # Example 1:
 #
 # Input: ["alex","loves","leetcode"]
 # Output: "alexlovesleetcode"
 # Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
 # Example 2:
 #
 # Input: ["catg","ctaagt","gcta","ttca","atgcatc"]
 # Output: "gctaagttcatgcatc"
 #

 """


 Approach 1: Dynamic Programming
 Intuition

 We have to put the words into a row, where each word may overlap the previous word. This is because no word is contained in any word.

 Also, it is sufficient to try to maximize the total overlap of the words.

 Say we have put some words down in our row, ending with word A[i]. Now say we put down word A[j] as the next word,
 where word j hasn't been put down yet. The overlap increases by overlap(A[i], A[j]).

 We can use dynamic programming to leverage this recursion. Let dp(mask, i) be the total overlap
 after putting some words down (represented by a bitmask mask), for which A[i] was the last word put down.
 Then, the key recursion is dp(mask ^ (1<<j), j) = max(overlap(A[i], A[j]) + dp(mask, i)), where the jth bit is not set in mask,
 and i ranges over all bits set in mask.

 Of course, this only tells us what the maximum overlap is for each set of words. We also need to remember
 each choice along the way (ie. the specific i that made dp(mask ^ (1<<j), j) achieve a minimum) so that we can reconstruct the answer.

 Algorithm

 Our algorithm has 3 main components:

 1） Precompute overlap(A[i], A[j]) for all possible i, j.
 2） Calculate dp[mask][i], keeping track of the "parent" i for each j as described above.
 3） Reconstruct the answer using parent information.

 Please see the implementation for more details about each section.


 Complexity Analysis
 Time Complexity: O(N^2 (2^N + W)), where NN is the number of words, and WW is the maximum length of each word.
 Space Complexity: O(N (2^N + W)).
 """
 
 */

#include <vector>
using std::vector;

#include <string>
using std::string;

class ShortestSuperstring {
    
public:
    string doit(vector<string>&& A) {
        
        int N = A.size();
        vector<vector<int>> overlaps(N, vector<int>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                if (i != j) {
                    int len = A[i].length();
                    
                    if (len > A[j].length())
                        len = A[j].length();
                    
                    for (; len >= 0; len--) {
                        if (A[i].substr(A[i].length() - len, len) == A[j].substr(0, len)){
                            overlaps[i][j] = len;
                            break;
                        }
                    }
                }
        }
        
        int max_bits = 1 << N;
        vector<vector<int>> dp(max_bits, vector<int>(N, 0));
        vector<vector<int>> parent(max_bits, vector<int>(N, -1));
       
        for (int mask = 1; mask < max_bits; mask++) {
            for (int j = 0; j < N; j++) {
                
                if ((mask >> j)  & 1) {
                    int pmask = mask ^ (1 << j);
                    
                    if (pmask == 0)
                        continue;
                    
                    for (int l = 0; l < N; l++) {
                        if ((pmask >> l) & 1) {
                            int res = dp[pmask][l] + overlaps[l][j];
                            if (res > dp[mask][j]) {
                                dp[mask][j] = res;
                                parent[mask][j] = l;
                            }
                        }
                    }
                }
            }
        }
        
        
        vector<int> path;
        int c = -1;
        for (int i = 0; i < N; i++) {
            if (c == -1 || dp.back()[i] > dp.back()[c]) {
                c = i;
            }
        }
        
        int mask = (1 << N) - 1;
        while (c != -1) {
            path.push_back(c);
            int nc = parent[mask][c];
            mask = mask ^ (1 << c);
            c = nc;
        }
        
        std::reverse(path.begin(), path.end());
        vector<bool> seen(N, false);
        for (auto c : path) {
            seen[c] = true;
        }
        
        for (int i = 0; i < N; i++)
            if (!seen[i])
                path.push_back(i);
        
        string ans = A[path[0]];
        for (int i = 1; i < path.size(); i++) {
            int n = overlaps[path[i-1]][path[i]];
            ans += A[path[i]].substr(n, A[path[i]].length() - n);
        }
        
        return ans;
    }
};


void test_943_find_shortest_superstring() {
    
    auto res1 = ShortestSuperstring().doit(vector<string>{"catg","ctaagt","gcta","ttca","atgcatc"}); // "gctaagttcatgcatc"
    
    auto res2 = ShortestSuperstring().doit(vector<string>{"alex","loves","leetcode"});
    
    
    
}
