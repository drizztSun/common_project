
/*
10. Regular Expression Matching

Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/

struct IsMatch (u8);

impl IsMatch {

    // (DP)
    pub fn doit_dp(s: String, p: String) -> bool {

        let M = p.len()+1;
        let N = s.len()+1;
        let mut dp = vec![vec![false; M]; N];
        dp[0][0] = true;

        let s = s.as_bytes();
        let p = p.as_bytes();

        for j in 1..M {
            dp[0][j] = j > 1 && p[j-1] == '*' as u8 && dp[0][j-2];
        }


        for i in 1..N {

            for j in 1..M {

                if p[j-1] != '*' as u8 {
                    dp[i][j] = dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.' as u8);
                } else {
                    dp[i][j] = dp[i][j-2] || (s[i-1] == p[j-2] || p[j-2] == '.' as u8) && dp[i-1][j];
                }
            }
        }

        dp[N-1][M-1]
    }
}

pub fn test_10_regular_expressing_matching() {

    IsMatch::doit_dp(String::from("mississippi"), String::from("mis*is*p*."));

    IsMatch::doit_dp(String::from("aab"), String::from("c*a*b"));
}