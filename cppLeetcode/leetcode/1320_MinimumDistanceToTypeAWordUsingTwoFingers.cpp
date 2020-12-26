/*

1320. Minimum Distance to Type a Word Using Two Fingers

A B C D E F
G H I J K L
M N O P Q R
S T U V W X
Y Z



You have a keyboard layout as shown above in the XY plane, where each English uppercase letter is located at some coordinate, 
for example, the letter A is located at coordinate (0,0), the letter B is located at coordinate (0,1), the letter P is located at coordinate (2,3) and the letter Z is located at coordinate (4,1).

Given the string word, return the minimum total distance to type such string using only two fingers. The distance between coordinates (x1,y1) and (x2,y2) is |x1 - x2| + |y1 - y2|. 

Note that the initial positions of your two fingers are considered free so don't count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.

 

Example 1:

Input: word = "CAKE"
Output: 3
Explanation: 
Using two fingers, one optimal way to type "CAKE" is: 
Finger 1 on letter 'C' -> cost = 0 
Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2 
Finger 2 on letter 'K' -> cost = 0 
Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1 
Total distance = 3
Example 2:

Input: word = "HAPPY"
Output: 6
Explanation: 
Using two fingers, one optimal way to type "HAPPY" is:
Finger 1 on letter 'H' -> cost = 0
Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
Finger 2 on letter 'P' -> cost = 0
Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
Total distance = 6
Example 3:

Input: word = "NEW"
Output: 3
Example 4:

Input: word = "YEAR"
Output: 7
 

Constraints:

2 <= word.length <= 300
Each word[i] is an English uppercase letter.
*/
#include <vector>
#include <string>

using std::vector;
using std::string;

class MinimumDistanceToTypeWord {

public:

    /*
        Each char we can use left / right finger to type. Brute Force: O(2^)

        Once the best solution is found for word[0~i], it doesn't matter how er typed it, only the last positions (chars) of the two fingers matter.

        Approach: Recursion iwth memorization.

        state: (i, l, r)

        dp(i, l, r) := min cost to type word[i:n] given the postion of l/r fingers.

        c = word[i]
        dp(i, l, r) = min(dp(i+1, c, r) + cost(l, c),   // use left finger to type, right finger remains
                        dp(i+1, l, c) + cost(r, c))   // use right finger to type, left finger remains


        ans = dp(0, $, $)

        Time complexity: O(n*27^2)
        Space complexity: O(n*27^2)
    */
    int doit_dp(string word) {

        int n = word.size();
        int kRest = 26;
        vector<vector<vector<int>>> cache(n, vector<vector<int>>(27, vector<int>(27, -1)));

        auto cost = [&](int a, int b) {
            if (a == kRest || b == kRest)
                return 0;
            return abs(a/6 - b/6) + abs(a%6 - b%6);
        };

        // min cost to type word[i:n]. l, r are the last finger positions
        std::function<int(int, int, int)> search = [&](int i, int l, int r) {
            if (i == n) return 0;
            if (cache[i][l][r] != -1) return cache[i][l][r];

            int c = word[i] - 'A';
            return cache[i][l][r] = std::min(search(i+1, c, r) + cost(l, c), search(i+1, l, c) + cost(c, r));

        };

        return search(0, kRest, kRest);
    }

    /* 
        Optimization:
        Turns out we only need to record the other finger, since the last finger isalways at word[i-1]

        state: (i, o) := Min cost to type word[i:n] given the position of other finger.

        p = word[i-1]
        c = word[i]

        dp(i, o) = min(dp(i+1, o) + cost (p, c) // keep using last finger to type
                        dp(i+1, p) + cost (o, c) ) // using another finger to type

        Time complexity: O(n*27)
        Space complexity: O(n*27)
    */

    int doit_dp_topdown(string word) {

        int n = word.size();
        int kRest = 26;
        vector<vector<int>> cache(n, vector<int>(27, -1));

        auto cost = [&](int a, int b) {
            if (a == kRest || b == kRest)
                return 0;
            return abs(a/6 - b/6) + abs(a%6 - b%6);
        };

        // min cost to type word[i:n]. l, r are the last finger positions
        std::function<int(int, int)> search = [&](int i, int o) {
            if (i == n) return 0;
            if (cache[i][o] != -1) return cache[i][o];
            
            int p = i == 0 ? kRest : (word[i-1] - 'A');
            int c = word[i] - 'A';
            return cache[i][o] = std::min(search(i+1, p) + cost(o, c),  // other finger
                                          search(i+1, o) + cost(p, c));  // same finger
        };

        return search(0, kRest);
    }

    /*
        Tranitional DP, bottom up

        state: (i, j)
        dp[i][j] := min cost to type word[0:i], one finger is at word[i-1], another finger is at (char) j.

        p = word[i-1], c = word[i]

        init: dp[0][$] = 0

        Push dp[i][j] to the next stage

        dp[i+1][j] = dp[i][j] + cost(p, c) // same finger
        dp[i+1][p] = dp[i][j] + cost(j, p) // other finger

        Ans = min(dp[n])
        Time complexity: O(n*27)
        Space complexity: O(n*27) => O(27)
    */
    int doit_dp_bottomup(string word) {
        constexpr int kRest = 26;
        const int n = word.length();
        
        // dp[i][j] : min cost to type word[0:i]
        // one finger is at word[i - 1], another finger is at j.
        vector<vector<int>> dp(n + 1, vector<int>(27, INT_MAX / 2));
        
        dp[0][kRest] = 0;
        
        auto cost = [](int c1, int c2) {
            if (c1 == kRest) return 0;
            return abs(c1 / 6 - c2 / 6) + abs(c1 % 6 - c2 % 6);
        };
        
        for (int i = 0; i < n; ++i) {
            int p = i == 0 ? kRest : word[i - 1] - 'A';
            int c = word[i] - 'A';

            for (int j = 0; j <= 26; ++j) { // other finger at j, same finger at p
                dp[i + 1][j] = std::min(dp[i + 1][j], dp[i][j] + cost(p, c));  // same finger
                dp[i + 1][p] = std::min(dp[i + 1][p], dp[i][j] + cost(j, c)); // other finger
            }
        }
        
        return *min_element(begin(dp[n]), end(dp[n]));
    }

};