/*
1578. Minimum Deletion Cost to Avoid Repeating Letters

Given a string s and an array of integers cost where cost[i] is the cost of deleting the ith character in s.

Return the minimum cost of deletions such that there are no two identical letters next to each other.

Notice that you will delete the chosen characters at the same time, in other words, after deleting a character, the costs of deleting other characters will not change.

 

Example 1:

Input: s = "abaac", cost = [1,2,3,4,5]
Output: 3
Explanation: Delete the letter "a" with cost 3 to get "abac" (String without two identical letters next to each other).
Example 2:

Input: s = "abc", cost = [1,2,3]
Output: 0
Explanation: You don't need to delete any character because there are no identical letters next to each other.
Example 3:

Input: s = "aabaa", cost = [1,2,3,4,1]
Output: 2
Explanation: Delete the first and the last character, getting the string ("aba").
 

Constraints:

s.length == cost.length
1 <= s.length, cost.length <= 10^5
1 <= cost[i] <= 10^4
s contains only lowercase English letters.

*/

#include <string>
#include <vector>


using std::vector;
using std::string;

class MinCost {

    /*
        1578.Minimum-Deletion-Cost-to-Avoid-Repeating-Letters
        本题其实只需贪心即可。在连续的相同字母中，只保留cost最大的一个，其余cost较小的都可以选择删除。
    */
    int minCost(string s, vector<int>& cost) 
    {
        int ret = 0;
        for (int i=0; i<s.size();)
        {
            int j=i;
            int maxValue = 0;
            int sum = 0;
            while (j<s.size() && s[j]==s[i])
            {
                sum += cost[j];
                maxValue = std::max(maxValue, cost[j]);
                j++;
            }
            ret += sum - maxValue;
            i = j;
        }
        return ret;

    }


public:

    int doit_greedy(string s, vector<int>& cost) {
        
        int costs = 0;
        
        for (int i = 0; i < s.length();) {
            
            int j = i+1;
            int total = cost[i], maxv = cost[i];
            
            while (j < s.length() && s[j-1] == s[j]) {
                total += cost[j];
                maxv = std::max(maxv, cost[j]);
                j++;
            } 
            
            if (j - i != 1) {
                costs += total - maxv;
            }
            i = j;
        }
        
        return costs;
    }
};