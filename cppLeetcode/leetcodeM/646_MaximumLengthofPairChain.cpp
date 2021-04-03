/*
646. Maximum Length of Pair Chain


You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.

Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be formed in this fashion.

Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given pairs. You can select pairs in any order.

Example 1:
Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]
Note:
The number of given pairs will be in the range [1, 1000].


*/
#include <vector>
#include <algorithm>

using std::vector;



class LongestChain {


    /*
            646.Maximum-Length-of-Pair-Chain
    此题本质和 435.Non-overlapping-Intervals 一模一样
    */
     static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[1]<b[1];
    }

    int findLongestChain(vector<vector<int>>& pairs) 
    {
        sort(pairs.begin(), pairs.end(), cmp);
        int i=0, count = 0;
        while (i<pairs.size())
        {
            int j = i;
            while (j<pairs.size() && pairs[j][0]<=pairs[i][1])
                j++;
            count++;
            i = j;
        }
        return count;
    }

public:

    /*
        Approach #2: Greedy [Accepted]
        Intuition
        We can greedily add to our chain. Choosing the next addition to be the one with the lowest second coordinate is at least better than a choice with a larger second coordinate.

        Algorithm
        Consider the pairs in increasing order of their second coordinate. We'll try to add them to our chain. If we can, by the above argument we know that it is correct to do so.

        Complexity Analysis
        Time Complexity: O(NlogN) where NN is the length of S. The complexity comes from the sorting step, but the rest of the solution does linear work.
        Space Complexity: O(N). The additional space complexity of storing cur and ans, but sorting uses O(N)O(N) space. Depending on the implementation of the language used, sorting can sometimes use less space.
    */
    int doit_greedy(vector<vector<int>>& pairs) {

        std::sort(begin(pairs), end(pairs), [&](auto& a, auto&& b) {
           return a[1] < b[1]; 
        });
        
        
        int length = 0, end = INT_MIN;
        
        for (auto& c : pairs) {
            
            if (c[0] > end) {
                length++;
                end = c[1];
            }
        }
        
        return length;  
    }

    /*
        Approach #1: Dynamic Programming [Accepted]
        Intuition

        If a chain of length k ends at some pairs[i], and pairs[i][1] < pairs[j][0], we can extend this chain to a chain of length k+1.

        Algorithm

        Sort the pairs by first coordinate, and let dp[i] be the length of the longest chain ending at pairs[i]. When i < j and pairs[i][1] < pairs[j][0], we can extend the chain, and so we have the candidate answer dp[j] = max(dp[j], dp[i] + 1).


        Complexity Analysis

        Time Complexity: O(N^2) where NN is the length of pairs. There are two for loops, and N^2N 
        2
        dominates the sorting step.

        Space Complexity: O(N) for sorting and to store dp.
    */
    int doit_dp(vector<vector<int>>& pairs) {
        
        int n = pairs.size(), length = 0;
        std::sort(begin(pairs), end(pairs));
        
        vector<int> dp(n, 1);
        
        for (int i = 1; i < n; i++) {
            
            for(int j = 0; j < i; j++) {
                
                if (pairs[i][0] > pairs[j][1])
                    dp[i] = std::max(dp[i], dp[j]+1);    
            }
            
            length = std::max(length, dp[i]);
        }
        
        return length;
    }
};