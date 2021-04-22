/*
1111. Maximum Nesting Depth of Two Valid Parentheses Strings

A string is a valid parentheses string (denoted VPS) if and only if it consists of "(" and ")" characters only, and:

It is the empty string, or
It can be written as AB (A concatenated with B), where A and B are VPS's, or
It can be written as (A), where A is a VPS.
We can similarly define the nesting depth depth(S) of any VPS S as follows:

depth("") = 0
depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's
depth("(" + A + ")") = 1 + depth(A), where A is a VPS.
For example,  "", "()()", and "()(()())" are VPS's (with nesting depths 0, 1, and 2), and ")(" and "(()" are not VPS's.

 

Given a VPS seq, split it into two disjoint subsequences A and B, such that A and B are VPS's (and A.length + B.length = seq.length).

Now choose any such A and B such that max(depth(A), depth(B)) is the minimum possible value.

Return an answer array (of length seq.length) that encodes such a choice of A and B:  answer[i] = 0 if seq[i] is part of A, else answer[i] = 1.  Note that even though multiple answers may exist, you may return any of them.

 

Example 1:

Input: seq = "(()())"
Output: [0,1,1,1,1,0]
Example 2:

Input: seq = "()(())()"
Output: [0,0,0,1,1,0,1,1]
 

Constraints:

1 <= seq.size <= 10000

*/

#include <vector>
#include <string>

using std::string;
using std::vector;


class MaxDepthAfterSplit {

public:

    vector<int> doit_parenthses(string seq) {

        int c = 0; // c is differece of two parts A and B
        vector<int> res;
        
        for (auto chr: seq) {
            
            if (c == 0) {
                c++;
                res.push_back(chr=='(' ? 1 : 0);
            } else if (c == 1) {
                c--;
                res.push_back(chr==')' ? 1: 0);
            }
        }
        
        return res;
    }


    /*
        Solution 0: Alternatively Distribute Parentheses
        Basically, ( is 1 point, ) is -1 point.
        We try to keep total points of two groups even,
        by distributing parentheses alternatively.

        The good part of this solution is that,
        we actually need no extra variable to record anything.
    */
    vector<int> doit_parenthses(string seq) {
        vector<int> res(seq.length());
        for (int i = 0; i < seq.length(); ++i)
            res[i] = i & 1 ^ (seq[i] == '(');
        return res;
    }

    /*
        Complexity
        Time O(N) for one pass
        Space O(1) extra space, O(N) for output


        More
        Also provide some more easy understood ideas for this problem,
        pick the the one you like.
        (As I keep receiving complaints about the readability,
        like no parentheses in solution for problem of parentheses)


        Solution 1: Keep Two Group Even
        Count the number of open parentheses of group A and group B.
    */
    vector<int> maxDepthAfterSplit(string seq) {
        int A = 0, B = 0, n = seq.length();
        vector<int> res(n, 0);
        for (int i = 0; i < n; ++i) {
            if (seq[i] == '(') {
                if (A < B) ++A;
                else ++B, res[i] = 1;
            } else {
                if (A > B) --A;
                else --B, res[i] = 1;
            }
        }
        return res;
    }

    /*
        Solution 2: Split by Half
        Count the number of level of whole string.
        Then split it by half.
        Group 0: the part under the half height
        Group 1: the part above the half height
    */
    vector<int> maxDepthAfterSplit(string seq) {
        int depth = 0, cur = 0, n = seq.length();
        for (char c : seq)
            depth = std::max(depth, cur += c == '(' ? 1 : -1);
        vector<int> res(n, 0);
        for (int i = 0; i < n; ++i) {
            if (seq[i] == '(' && ++cur > depth / 2) res[i] = 1;
            if (seq[i] == ')' && cur-- > depth / 2) res[i] = 1;
        }
        return res;
    }
};