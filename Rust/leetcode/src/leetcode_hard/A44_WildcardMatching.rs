/*

44. Wildcard Matching

Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false

*/

struct IsWildCastMatch (u8);

impl IsWildCastMatch {

    pub fn doit_dp(s: String, p: String) -> bool {

        let m = s.len() + 1;
        let n = p.len() + 1;
        let mut dp = vec![false; m];
        dp[0] = true;
        let s = s.as_bytes();
        let p = p.as_bytes();

        for i in 1..n {

            if p[i-1] == '*' as u8 {
                for j in 1..m {
                    dp[j] = dp[j] || dp[j-1];
                }
            } else {
                for j in (1..m).rev() {
                    dp[j] = dp[j-1] && (p[i-1] == s[j-1] || p[i-1] == '?' as u8);
                }
            }

            dp[0] = dp[0] && p[i-1] == '*' as u8;
        }

        dp[m-1]
    }

    pub fn doit(mut s: String, mut p: String) -> bool {
        let s: Vec<char> = s.drain(..).collect();
        let n = s.len();
        let mut curr: Vec<usize> = Vec::with_capacity(n + 1);
        let mut curr_wildcard: Option<usize> = None;
        let mut next: Vec<usize> = Vec::with_capacity(n + 1);
        curr.push(0);
        for c in p.drain(..) {
            if curr.is_empty() {
                return false;
            }
            match c {
                '*' => {
                    if !curr_wildcard.is_some() {
                        curr_wildcard = Some(curr[0]);
                    }
                },
                '?' => {
                    if let Some(first) = curr_wildcard {
                        if first == n {
                            return false;
                        }
                        curr_wildcard = Some(first + 1);
                    } else {
                        for i in curr.iter_mut() {
                            *i += 1;
                        }
                        if curr.last().unwrap() > &n {
                            curr.pop();
                        }
                        curr_wildcard = None;
                    }
                },
                _ => {
                    next.clear();
                    if let Some(first) = curr_wildcard {
                        for i in first..n {
                            if s[i] == c {
                                next.push(i + 1);
                            }
                        }
                    } else {
                        if curr.last() == Some(&n) {
                            curr.pop();
                        }
                        for &i in curr.iter() {
                            if s[i] == c {
                                next.push(i + 1);
                            }
                        }
                    }
                    std::mem::swap(&mut curr, &mut next);
                    curr_wildcard = None;
                }
            }
        }
        
        curr_wildcard.is_some() ||
        curr.last().map(|&x| x == n).unwrap_or(false)
    }
}

pub fn test_44_wild_card_matching() {

    IsWildCastMatch::doit(String::from("adceb"), String::from("*a*b"));

    IsWildCastMatch::doit(String::from("acdcb"), String::from("a*c?b"));
}