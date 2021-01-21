/*
131. Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.

 

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
Example 2:

Input: s = "a"
Output: [["a"]]
 

Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.
*/
#include <vector>
#include <string>

using std::vector;
using std::string;


class PalindromePartition {

public:


    /*
        Approach 2: Backtracking with Dynamic Programming
        Intuition

        This approach uses a similar Backtracking algorithm as discussed in Approach 1. But, the previous approach performs one extra iteration to determine if a given substring is a palindrome or not. 
        Here, we are repeatedly iterating over the same substring multiple times and the result is always the same. There are Overlapping Subproblems and we could further optimize the approach by using dynamic programming to determine if a string is a palindrome in constant time. Let's understand the algorithm in detail.

        Algorithm

        A given string ss starting at index \text{start}start and ending at index \text{end}end is a palindrome if following conditions are satisfied :

        The characters at \text{start}start and \text{end}end indexes are equal.
        The substring starting at index \text{start}+1start+1 and ending at index \text{end}-1end−1 is a palindrome.
        img

        Let NN be the length of the string. To determine if a substring starting at index \text{start}start and ending at index \text{end}end is a palindrome or not, we use a 2 Dimensional array \text{dp}dp of size N \cdot NN⋅N where,

        \text{dp[start][end]} = \text{true}dp[start][end]=true , if the substring beginning at index \text{start}start and ending at index \text{end}end is a palindrome.

        Otherwise, \text{dp[start][end] }== \text{false}dp[start][end] ==false.

        Also, we must update the \text{dp}dp array, if we find that the current string is a palindrome.

        Implementation


        Complexity Analysis

        Time Complexity : \mathcal{O}(N \cdot 2^{N})O(N⋅2 
        N
        ), where NN is the length of string ss. In the worst case, there could be 2^{N}2 
        N
        possible substrings and it will take \mathcal{O}(N)O(N) to generate each substring using substr as in Approach 1. However, we are eliminating one additional iteration to check if substring is a palindrome or not.

        Space Complexity: \mathcal{O}(N \cdot N)O(N⋅N), where NN is the length of the string ss. The recursive call stack would require NN space as in Approach 1. Additionally we also use 2 dimensional array \text{dp}dp of size N \cdot NN⋅N .

        This gives us total space complexity as \mathcal{O}(N \cdot N)O(N⋅N) + \mathcal{O}(N)O(N) = \mathcal{O}(N \cdot N)O(N⋅N)
    
    */


    vector<vector<string>> doit_backtracking(string s) {
        
        int len = s.length();
        vector<vector<bool>> dp (len, vector <bool> (len, false));
        vector<vector<string>> result;
        vector<string> currentList;
        
        std::function<void(int)> dfs = [&](int start) {
            if (start >= s.length()) 
                result.push_back(currentList);
            
            for (int end = start; end < s.length(); end++) {
                if (s[start] == s[end] && (end - start <= 2 || dp[start + 1][end - 1])) {
                    dp[start][end] = true;
                    currentList.push_back(s.substr(start, end - start + 1));
                    dfs(end + 1);
                    currentList.pop_back();
                }
            }
        };
        
        dfs(0);
        return result;
    }

    /*
        Approach 1: Backtracking
        Intuition

        The idea is to generate all possible substrings of a given string and expand each possibility if is a potential candidate. The first thing that comes to our mind is Depth First Search. In Depth First Search, we recursively expand potential candidate until the defined goal is achieved. After that, we backtrack to explore the next potential candidate.

        Backtracking incrementally build the candidates for the solution and discard the candidates (backtrack) if it doesn't satisfy the condition.

        The backtracking algorithms consists of the following steps:

        Choose: Choose the potential candidate. Here, our potential candidates are all substrings that could be generated from the given string.

        Constraint: Define a constraint that must be satisfied by the chosen candidate. In this case, the constraint is that the string must be a palindrome.

        Goal: We must define the goal that determines if have found the required solution and we must backtrack. Here, our goal is achieved if we have reached the end of the string.

        Algorithm

        In the backtracking algorithm, we recursively traverse over the string in depth-first search fashion. For each recursive call, the beginning index of the string is given as \text{start}start.

        Iteratively generate all possible substrings beginning at \text{start}start index. The \text{end}end index increments from \text{start}start till the end of the string.

        For each of the substring generated, check if it is a palindrome.

        If the substring is a palindrome, the substring is a potential candidate. Add substring to the \text{currentList}currentList and perform a depth-first search on the remaining substring. If current substring ends at index \text{end}end, \text{end}+1end+1 becomes the \text{start}start index for the next recursive call.

        Backtrack if \text{start}start index is greater than or equal to the string length and add the \text{currentList}currentList to the result.

        Current
        1 / 10
        Implementation


        Complexity Analysis

        Time Complexity : \mathcal{O}(N \cdot 2^{N})O(N⋅2 
        N
        ), where NN is the length of string ss. This is the worst-case time complexity when all the possible substrings are palindrome.
        Example, if = s = aaa, the recursive tree can be illustrated as follows:

        img

        Hence, there could be 2^{N}2 
        N
        possible substrings in the worst case. For each substring, it takes \mathcal{O}(N)O(N) time to generate substring and determine if it a palindrome or not. This gives us time complexity as \mathcal{O}(N \cdot 2^{N})O(N⋅2 
        N
        )

        Space Complexity: \mathcal{O}(N)O(N), where NN is the length of the string ss. This space will be used to store the recursion stack. For s = aaa, the maximum depth of the recursive call stack is 3 which is equivalent to NN.
    */

    vector<vector<string>> doit_backtracking(string s) {
        vector<vector<string>> result;
        vector<string> currentList;

        auto  isPalindrome = [&](int low, int high) {
            while (low < high) {
                if (s[low++] != s[high--]) return false;
            }
            return true;
        };

        std::function<void(int)> dfs = [&](int start) {
            if (start >= s.length()) result.push_back(currentList);
            for (int end = start; end < s.length(); end++) {
                if (isPalindrome(start, end)) {
                    // add current substring in the currentList
                    currentList.push_back(s.substr(start, end - start + 1));
                    dfs(end + 1);
                    // backtrack and remove the current substring from currentList
                    currentList.pop_back();
                }
            }
        };

        dfs(0);
        return result;
    }
};