/*
1641. Count Sorted Vowel Strings

Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.

A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.

 

Example 1:

Input: n = 1
Output: 5
Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
Example 2:

Input: n = 2
Output: 15
Explanation: The 15 sorted strings that consist of vowels only are
["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.
Example 3:

Input: n = 33
Output: 66045
 

Constraints:

1 <= n <= 50 

*/
#include <vector>

using std::vector;

class CountSortedVowelStrings {

public:
    
    /*
        Approach 2: Decoding the Pattern, Using Recursion
        Intuition

        If we observe, the problem follows a specific pattern. For any given nn and number of \text{vowels}vowels , the number of combinations is always equal to the sum of following,

        Number of combinations for previous nn i.e n-1n−1 and same number of vowelsvowels
        Number of combinations for vowels-1vowels−1 and same nn.
        The following figure illustrates this idea using an example.

        img

        Thus, the recurrence relation can be written as,

        countVowelStrings (n, vowels) = isSum(n - 1, vowels) + isSum(n, vowels - 1)
        Algorithm

        We start with given nn and vowels as 55. {a, e, i, o, u}.
        Recursively calculate the result for every nn and \text{vowels}vowels using above recurrence relation.
        We must backtrack on the following base cases,
        If n = 1n=1, we have only one position left. Here, we must return the current number of vowels.

        Example, if n = 1n=1 and \text{vowels} = 3vowels=3. As there could be 3 combinations a, e, i, the result would be 3.

        If \text{vowels} = 1vowels=1, we must return 11.

        Example, if n=3n=3, and only 1 vowel u is left, there could be only one combination uuu.

        Implementation


        Complexity Analysis

        Time Complexity : \mathcal{O}(n^{5})O(n 
        5
        ), as for a given nn and 55 vowels (a, e, i, o, u), there are roughly n^{5}n 
        5
        possible candidates (Refer time complexity of Approach 1).This gives us time complexity as \mathcal{O}(n^{5})O(n 
        5
        ).

        Space Complexity: \mathcal{O}(n)O(n). This space will be used to store the recursion stack. As the maximum depth of recursion would be \max(n,5)max(n,5), the space required for internal call stack would roughly \mathcal{O}(n)O(n).
    
    */
    
    int doit_recursive(int n) {

        std::function<int(int, int)> countVowelStringUtil = [&](int n, int vowels) {
            if (n == 1)
                return vowels;
            if (vowels == 1)
                return 1;
            return countVowelStringUtil(n - 1, vowels) + countVowelStringUtil(n, vowels - 1);
        };

        return countVowelStringUtil(n, 5);
    }

    /*
        Approach 3: Using Recursion + Memoization, Top Down Dynamic Programming
        Intuition

        If you have solved problems on Dynamic Programming before, it is pretty easy to optimize the Approach 2 using Memoization. In the above approach, the problem can be broken down into subproblems. On drawing the recursion tree, it is evident that the same subproblems are computed multiple times.

        img

        In the above recursion tree, we could see that subproblems (2, 4), (2, 3) and (1, 2) are computed multiple times and the result would be always the same. The problem has Overlapping Subproblem and can be solved using Dynamic Programming.

        Algorithm

        We could have stored the results of our computation for the first time and used it later. This technique of computing once and returning the stored value is called Memoization.

        As we must store results for every nn and \text{vowels}vowels, we use a two dimensional array \text{memo}memo of size n \cdot 5n⋅5 and follow the following steps for each recursive call :

        Check in the memo if we have already calculated results for a given nn and \text{vowels}vowels and return the result stored in the memo.
        Save the results of any calculations to \text{memo}memo.
        Since arrays are 0-indexed, we initialize the array of size (n + 1, 5 + 1) and use the range 1..n and 1..5 for easier understanding and keeping it consistent with the previous approach.

       

        Implementation


        Complexity Analysis

        Time Complexity : \mathcal{O}(n)O(n), as for every nn and \text{vowels}vowels we calculate result only once, the total number of nodes in the recursion tree would be n \cdot 5n⋅5, which is roughly equal to nn.

        Space Complexity : \mathcal{O}(n)O(n), as we use a 2D array \text{memo}memo of size n \cdot 5n⋅5 and the size of internal call stack would also be nn (As explained in Approach 2), the space complexity would be \mathcal{O}(n+n) = \mathcal{O}(n+n)O(n+n)=O(n+n).
            
    */

    int doit_dp_topdown(int n) {
        vector<vector<int>> memo(n+1, vector<int>(6, 0));
        std::function<int(int, int)> countVowelStringUtil = [&](int n, int vowels) {
            if (n == 1)
                return vowels;
            if (vowels == 1)
                return 1;
            if (memo[n][vowels] != 0)
                return memo[n][vowels];
            int res = countVowelStringUtil(n - 1, vowels) + countVowelStringUtil(n, vowels - 1);
            memo[n][vowels] = res;
            return res;
        };

        return countVowelStringUtil(n, 5, memo);
    }

    /*
        Approach 4: Bottom Up Dynamic Programming, Tabulation
        Intuition

        This is another approach to solve the Dynamic Programming problems. We use the iterative approach and store the result of subproblems in bottom-up fashion also known as Tabulation. We store the results of previous computations in tabular format and use those results for the next computations.

        Algorithm

        We maintain a 2D array , \text{dp}dp of size n \cdot 5n⋅5 where, \text{dp[n][vowels]}dp[n][vowels] denotes the total number of combinations for given nn and number of \text{vowels}vowels. Using the recurrence relation established in Approach 2, we could iteratively calculate the value for \text{dp[n][vowels]}dp[n][vowels] as,

        dp[n][vowels] = dp[n - 1][vowels] + dp[n][vowels - 1]
        As this is the Bottom Up approach to solve the problem, we must initialize the table for the base cases. The base cases are the same as in Approach 2.

        If n = 1n=1, the number of combinations are always equal to number of \text{vowels}vowels. Hence, we initialize all the values of \text{dp[1][vowels]}dp[1][vowels] with \text{vowels}vowels.
        If vowels = 1vowels=1, the number of combinations are always equal to 1. Hence, we initialize all the values of \text{dp[n][1]}dp[n][1] with 11.
        Implementation

         dp[n][vowels] = dp[n - 1][vowels] + dp[n][vowels - 1]

        Complexity Analysis

        Time Complexity : \mathcal{O}(n)O(n), as we iterate 5 \cdot n5⋅n times to fill the \text{dp}dp array, the time complexity is approximately \mathcal{O}(5 \cdot n) =\mathcal{O}(n)O(5⋅n)=O(n).

        Space Complexity : \mathcal{O}(n)O(n), as we use a 2D array of size n \cdot 5n⋅5, the space complexity would be \mathcal{O}(n)O(n).
    */
    int doit_dp_bottomup(int n) {

        vector<vector<int>> dp(n + 1, vector<int>(6, 0));
        
        for (int vowels = 1; vowels <= 5; vowels++)
            dp[1][vowels] = vowels;
        
        for (int nValue = 2; nValue <= n; nValue++) {
            dp[nValue][1] = 1;
            for (int vowels = 2; vowels <= 5; vowels++) {
                dp[nValue][vowels] =
                    dp[nValue][vowels - 1] + dp[nValue - 1][vowels];
            }
        }
        return dp[n][5];
    }

    int doit_math(int n) {

        return (n+4) * (n+3) * (n+2) * (n+1) / 24;
    }

        
};
