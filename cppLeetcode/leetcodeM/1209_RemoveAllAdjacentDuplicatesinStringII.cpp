/*
1047. Remove All Adjacent Duplicates In String

Given a string S of lowercase letters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is guaranteed the answer is unique.

 

Example 1:

Input: "abbaca"
Output: "ca"
Explanation: 
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".
 

Note:

1 <= S.length <= 20000
S consists only of English lowercase letters.



1209. Remove All Adjacent Duplicates in String II

Given a string s, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made.

It is guaranteed that the answer is unique.

 

Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
 

Constraints:

1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lower case English letters.

*/
#include <string>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::string;


class RemoveAllAdjacentDuplicatesI {

public:

    /*
        Solution 1: Two Pointers
        i refers to the index to set next character in the output string.
        j refers to the index of current iteration in the input string.

        Iterate characters of S one by one by increasing j.

        If S[j] is same as the current last character S[i - 1],
        we remove duplicates by doing i -= 2.

        If S[j] is different as the current last character S[i - 1],
        we set S[i] = S[j] and increment i++.
    */
    string doit_twopointer(string s) {
        int i = 0, n = s.length();
        for (int j = 0; j < n; ++j, ++i) {
            s[i] = s[j];
            if (i > 0 && s[i - 1] == s[i]) // count = 2
                i -= 2;
        }
        return s.substr(0, i);
    }

    /*
        Solution 2: Stack
        Keep a res as a characters stack.
        Iterate characters of S one by one.

        If the next character is same as the last character in res,
        pop the last character from res.
        In this way, we remove a pair of adjacent duplicates characters.

        If the next character is different,
        we append it to the end of res.

        Complexity
        These two solution actually work in the similar way.
        Time O(N) for one pass
        Space O(N) for output
    */
    string doit_stack(string S) {
        string res = "";
        for (char& c: S)
            if (res.size() && c == res.back())
                res.pop_back();
            else
                res.push_back(c);
        return res;
    }
};

/*
1209. Remove All Adjacent Duplicates in String II


Given a string s, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made.

It is guaranteed that the answer is unique.

 

Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
 

Constraints:

1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lower case English letters.
*/
class RemoveAllAdjacentDuplicatesII {

public:

    /*
        Solution 2: Stack
        Save the character c and its count to the stack.
        If the next character c is same as the last one, increment the count.
        Otherwise push a pair (c, 1) into the stack.
        I used a dummy element ('#', 0) to avoid empty stack.
    */
    string doit_stack(string s, int k) {

        vector<std::pair<int, char>> stack = {{0, '#'}};
        for (char c: s) {
            if (stack.back().second != c) {
                stack.push_back({1, c});
            } else if (++stack.back().first == k)
                stack.pop_back();
        }
        string res;
        for (auto & p : stack) {
            res.append(p.first, p.second);
        }

        return res;
    }

    string doit_twopointer(string s, int k) {
        int i = 0, n = s.length();
        vector<int> count(n);
        for (int j = 0; j < n; ++j, ++i) {
            s[i] = s[j];
            count[i] = i > 0 && s[i - 1] == s[j] ? count[i - 1] + 1 : 1;
            if (count[i] == k) i -= k;
        }
        return s.substr(0, i);
    }

    /*
        Approach 3: Stack
        Instead of storing counts for each character, we can use a stack. When a character does not match the previous one, we push 1 to the stack. Otherwise, we increment the count on the top of the stack.

        Stack Illustration

        Algorithm

        Iterate through the string:

        If the current character is the same as the one before, increment the count on the top of the stack.

        Otherwise, push 1 to the stack.
        If the count on the top of the stack equals k, erase last k characters and pop from the stack.

        Note that, since Integer is immutable in Java, we need to pop the value first, increment it, and then push it back (if it's less than k).


        Complexity Analysis

        Time complexity: \mathcal{O}(n)O(n), where nn is a string length. We process each character in the string once.

        Space complexity: \mathcal{O}(n)O(n) for the stack.
    
    */
    string doit_stack_1(string s, int k) {
        stack<int> counts;
        for (int i = 0; i < s.size(); ++i) {
            if (i == 0 || s[i] != s[i - 1]) {
                counts.push(1);
            } else if (++counts.top() == k) {
                counts.pop();
                s.erase(i - k + 1, k);
                i = i - k;
            }
        }
        return s;
    }

    /*
        Approach 4: Stack with Reconstruction
        If we store both the count and the character in the stack, we do not have to modify the string. Instead, we can reconstruct the result from characters and counts in the stack.

        Algorithm

        1. Iterate through the string:

            If the current character is the same as on the top of the stack, increment the count.

                Otherwise, push 1 and the current character to the stack.
            If the count on the top of the stack equals k, pop from the stack.

        2. Build the result string using characters and counts in the stack.
    */
    string doit_stack(string s, int k) {
        vector<std::pair<int, char>> counts;
        for (int i = 0; i < s.size(); ++i) {
            if (counts.empty() || s[i] != counts.back().second) {
                counts.push_back({ 1, s[i] });
            } else if (++counts.back().first == k) {
                counts.pop_back();
            }
        }
        s = "";
        for (auto &p : counts) {
            s += string(p.first, p.second);
        }
        return s;
    }


    /*
        Approach 5: Two Pointers
        This method was proposed by @lee215, and we can use it to optimize string operations in approaches 2 and 3. 
        Here, we copy characters within the same string using the fast and slow pointers. 
        Each time we need to erase k characters, we just move the slow pointer k positions back.

        Two Pointers Illustration

        Algorithm

        Initialize the slow pointer (j) with zero.

        Move the fast pointer (i) through the string:

        Copy s[i] into s[j].

        If s[j] is the same as s[j - 1], increment the count on the top of the stack.

        Otherwise, push 1 to the stack.
        If the count equals k, decrease j by k and pop from the stack.

        Return j first characters of the string.
    */
    string removeDuplicates(string s, int k) {
        int j = 0;
        stack<int> counts;
        for (int i = 0; i < s.size(); ++i, ++j) {
            s[j] = s[i];
            if (j == 0 || s[j] != s[j - 1]) {
                counts.push(1);
            } else if (++counts.top() == k) {
                counts.pop();
                j -= k;
            }
        }
        return s.substr(0, j);
    }

};