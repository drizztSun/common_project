/*
316. Remove Duplicate Letters

Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/

 

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"

"bcdbcda" 
"bcda"

Constraints:

1 <= s.length <= 10^4
s consists of lowercase English letters.


Intuition
First we should make sure we understand what "lexicographical order" means. Comparing strings doesn't work the same way as comparing numbers. Strings are compared from the first character to the last one. Which string is greater depends on the comparison between the first unequal corresponding character in the two strings. As a result any string beginning with a will always be less than any string beginning with b, regardless of the ends of both strings.

Because of this, the optimal solution will have the smallest characters as early as possible. We draw two conclusions that provide different methods of solving this problem in O(N)O(N):

The leftmost letter in our solution will be the smallest letter such that the suffix from that letter contains every other. This is because we know that the solution must have one copy of every letter, and we know that the solution will have the lexicographically smallest leftmost character possible.

If there are multiple smallest letters, then we pick the leftmost one simply because it gives us more options. We can always eliminate more letters later on, so the optimal solution will always remain in our search space.

As we iterate over our string, if character i is greater than character i+1 and another occurrence of character i exists later in the string, deleting character i will always lead to the optimal solution. Characters that come later in the string i don't matter in this calculation because i is in a more significant spot. Even if character i+1 isn't the best yet, we can always replace it for a smaller character down the line if possible.

Since we try to remove characters as early as possible, and picking the best letter at each step leads to the best solution, "greedy" should be going off like an alarm

*/
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::unordered_set;
using std::unordered_map;
using std::vector;
using std::string;

class RemoveDuplicateLetters {

    /*
        316.Remove-Duplicate-Letters
        总体思想是贪心法，用stack做辅助。基本方法仍然是用手头的字符尽量维持一个递增字符序列，因为递增序列意味着字典序最小。

        首先，在维护栈的过程中，遇到已经用过的字符就跳过。比如当前待处理的字符是c，而当前的栈已经有c了，意味着什么呢？因为栈在维护着一个递增序列，说明c后面的字符要比c大。如果舍弃已经用过的c，那么必将导致后续的大字符前移，使得构建的栈内的单词字典序会变小。

        接下来，如果遇到非递增的字符，则大致方向就是退栈--处理掉一些栈顶元素，使得新加入的仍能保持递增。但需要注意，如果待退栈处理的字符在后面还有出现的机会，就放心退栈，扔到后面去考虑；如果后面已经没有再出现的机会，则保留这个栈顶元素同时结束退栈。
        
        所以需要一个Hash表来实时记录每个字符剩下来还会出现几次，也就是说每遍历一个字符，就把Map[s[i]]--.

        本题和1081. Smallest Subsequence of Distinct Characters一模一样。
    */
    string removeDuplicateLetters(string s) 
    {
        string text = s;
        string str;
        unordered_map<char,int>Map;
        for (auto ch: text) Map[ch]++;
        unordered_set<char>Set; //visited
        
        for (auto ch: text)
        {
            if (Set.find(ch)!=Set.end())
            {
                Map[ch]--;
            }
            else
            {
                while (str.size()>0  && str.back()>ch && Map[str.back()]>0)
                {
                    Set.erase(str.back());
                    str.pop_back();
                }
                str.push_back(ch);
                Map[ch]--;
                Set.insert(ch);
            }
        }
        
        return str;
    }

public:
    /*
        Approach 2: Greedy - Solving with Stack
        Algorithm

        We use idea number two from the intuition. We will keep a stack to store the solution we have built as we iterate over the string, 
        and we will delete characters off the stack whenever it is possible and it makes our string smaller.

        Each iteration we add the current character to the solution if it hasn't already been used. We try to remove as many characters as possible off the top of the stack, 
        and then add the current character

        The conditions for deletion are:

        The character is greater than the current characters
        The character can be removed because it occurs later on
        At each stage in our iteration through the string, we greedily keep what's on the stack as small as possible.

        The following animation makes this more clear:

        Current
        1 / 12
        Implementation


        Complexity Analysis

        Time complexity : O(N). Although there is a loop inside a loop, the time complexity is still O(N)O(N). 
        This is because the inner while loop is bounded by the total number of elements added to the stack (each time it fires an element goes). 
        This means that the total amount of time spent in the inner loop is bounded by O(N)O(N), giving us a total time complexity of O(N)

        Space complexity : O(1). At first glance it looks like this is O(N), but that is not true! seen will only contain unique elements, 
        so it's bounded by the number of characters in the alphabet (a constant). You can only add to stack if an element has not been seen, 
        so stack also only consists of unique elements. This means that both stack and seen are bounded by constant, giving us O(1) space complexity.
    */
    string doit_stack_greedy(string s) {
        
        int last_position[256]{-1};
        for (int i = 0; i < s.length(); i++)
            last_position[s[i]] = i;
        
        vector<char> st;
        bool seen[256]{false};
        for (int i = 0; i < s.length(); i++) {
            
            if (!seen[s[i]]) {
                
                while (!st.empty() && st.back() > s[i] && last_position[st.back()] > i) {
                    seen[st.back()] = false;
                    st.pop_back();
                }
                
                st.push_back(s[i]);
                seen[s[i]] = true;
            }
        }
        
        string ans(st.begin(), st.end());
        return ans;
    }
};