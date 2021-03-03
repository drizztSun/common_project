/*
1190. Reverse Substrings Between Each Pair of Parentheses

You are given a string s that consists of lower case English letters and brackets. 

Reverse the strings in each pair of matching parentheses, starting from the innermost one.

Your result should not contain any brackets.

 

Example 1:

Input: s = "(abcd)"
Output: "dcba"
Example 2:

Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.
Example 3:

Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.
Example 4:

Input: s = "a(bcdefghijkl(mno)p)q"
Output: "apmnolkjihgfedcbq"
 

Constraints:

0 <= s.length <= 2000
s only contains lower case English characters and parentheses.
It's guaranteed that all parentheses are balanced.
*/
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

using std::unordered_map;
using std::stack;
using std::vector;
using std::string;


class ReverseParentheses {

    /*
        1190.Reverse-Substrings-Between-Each-Pair-of-Parentheses
        解法1：模拟
        模拟整个过程。字符串ret只记录字母，用栈来标记左右括号的配对。

        遇到左括号时，往栈推入当前ret的长度。遇到右括号时，从栈顶读取的index，它就是ret里与之配对的“虚拟的”左括号的位置。然后将index到ret末尾的字符串整体翻转。不断重复以上操作即可。

        举个例子：

        abc(def(ghi)k)
        ^   ^
        1. 第一次遇到右括号之前，ret = "abcdefghi"，栈里面的元素是[3,6]. 遇到第一个右括号时，说明ret[6,end]需要翻转，得到ret = "abcdefihg"，
        2. 第二次遇到右括号之前，ret = "abcdefihgk"，栈里面的元素是[3]. 遇到第二个右括号时，说明ret[3,end]需要翻转，得到ret = "abckghifed"，就是最终的答案。
        
        考虑到很多字母被加入ret之后又要逆序，所以时间复杂度是o(N^2)。

        解法2：反向模拟
        还是上述的例子，当我们顺着读取abc后看到跟在后面的(....)时，知道括号内def(ghi)k解析之后的结果一定最终是会反向输出的，那么索性我们就反向读取他们，即从k开始往前读。怎么找到的k呢？那就是从这个左括号对应的右括号开始往左走。

        然后，我们又碰到一个更深一级的括号，里面是ghi。同理我们知道这个更深一层的括号依然会使内部的东西最终反向输出，那么我们就索性继续反向读取它们，即从g开始往右读。怎么找到的g呢？那就是从这个右括号对应的左括号，然后开始往右走。于是就顺次ghi都读完了。

        再接着，我们碰到了右括号。此时应该干什么呢？此时这对括号读完了，应该继续之前被暂停的f。怎么快速定位到f呢？其实就是再跳回原来的左括号，但此时继续往左走。

        于是我们发现了一个规律。当你进入一层更深的括号时，就跳到括号的另一边反向读取。当你离开该层括号时，也要跳到括号的另一边反向离开。

        所谓“进入一层更深的括号”，包括(1)从左往右进入左括号，此时你需要跳转至右括号然后往左读取括号内的内容；(1)从右往做进入右括号，此时你需要跳转至左括号然后往右读取括号内的内容；

        所谓“离开该层的括号”，包括(1)从左往右进入右括号，此时你需要跳转至左括号然后往左读取括号外的内容；(1)从右往做进入左括号，此时你需要跳转至右括号然后往右读取括号外的内容；

        同上以上的顺序，我们就可以用o(N)的时间走遍整个字符串。
    */
    string doit_stack_parenthesis(string s) 
    {
        // O(n)
        int n = s.size();
        vector<int>pair(n,-1);
        stack<int>Stack;
        for (int i=0; i<n; i++)
        {
            if (s[i]=='(')
                Stack.push(i);
            else if (s[i]==')')
            {
                int j = Stack.top();
                pair[i]=j;
                pair[j]=i;
                Stack.pop();
            }
        }

        int i = 0;
        int d = 1;
        string ret;
        while (i<n)
        {
            if (isalpha(s[i]))
                ret.push_back(s[i]);
            else
            {
                i = pair[i];
                d = -d;
            }
            i += d;
        }
        return ret;
    }

    string doit_stack_parenthesis(string s) 
    {
        string ret;
        stack<int>Stack;
        for (auto ch: s)
        {
            if (isalpha(ch))
                ret.push_back(ch);
            else if (ch=='(')
                Stack.push(ret.size());
            else
            {
                int i = Stack.top();
                Stack.pop();
                reverse(ret.begin()+i, ret.end());
            }
        }
        return ret;
    }

    string doit_stack(string s) {
        
        unordered_map<int, int> pair;
        stack<int> st;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }
        
        int i = 0;
        int d = 1;
        string ans;
        while (i < s.size()) {
            
            if (isalpha(s[i])) {
                ans.push_back(s[i]);
            } else if (pair.count(i) > 0) {
                i = pair[i];
                d = -d;
            }
            i += d;
        }
        
        return ans;
    }

    /**
     Solution 1: Brute Force
    Here is the brute force solution, which seems really easy to write.
    Nothing more to talk about.

    Time O(N^2), Space O(N)

    */
    string doit_(string s) {
        vector<int> opened;
        string res;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(')
                opened.push_back(res.length());
            else if (s[i] == ')') {
                int j = opened.back();
                opened.pop_back();
                reverse(res.begin() + j, res.end());
            } else {
                res += s[i];
            }
        }
        return res;
    }

    /*
        Solution 2: Wormholes
        Intuition
        Nice. I got a green accpeted with solution 1.
        Now before move on, let us check the solutions in the discuss.

        Hey hey hey wait, ALL solutions are BRUTE FORCE ?
        Hmmmm... why not O(N)?

        Fine fine fine, here comes an easy O(N) solution.

        Explanation
        In the first pass,
        use a stack to find all paired parentheses,
        I assume you can do this.

        Now just imgine that all parentheses are wormholes.
        As you can see in the diagram,
        the paired parentheses are connected to each other.

        image

        First it follows the left green arrrow,
        go into the left wormhole and get out from the right wormhole.
        Then it iterates the whole content between parentheses.
        Finally it follows the right arrow,
        go into the left wormhole,
        get out from the right wormhole and finish the whole trip.

        So in the second pass of our solution,
        it traverses through the paired parentheses
        and generate the result string res.

        i is the index of current position.
        d is the direction of traversing.


        Complexity
        Time O(N) for two passes
        Space O(N)
    */
    string doit_(string s) {
        int n = s.length();
        vector<int> opened, pair(n);
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(')
                opened.push_back(i);
            if (s[i] == ')') {
                int j = opened.back();
                opened.pop_back();
                pair[i] = j;
                pair[j] = i;
            }
        }
        string res;
        for (int i = 0, d = 1; i < n; i += d) {
            if (s[i] == '(' || s[i] == ')')
                i = pair[i], d = -d;
            else
                res += s[i];
        }
        return res;
    }

public:

    string doit_stack_parenthesis(string target) {

        std::function<string(int, int, bool)> dfs = [&](int i, int j, bool reversed) -> string{
            
            if (j >= i) return "";
            
            int s = i, e = j;
            
            while (i < j && target[i] != '(') i++;
            
            while (i < j && target[j] != ')') j--;
            
            if (i == j) {
                string middle = target.substr(s, e - s + 1);
                if (reversed)
                    std::reverse(begin(middle), end(middle));
                return middle;
            }
            
            string part1 = target.substr(s, i - s), part2 = target.substr(j+1, e - j);
            string middle = dfs(i+1, j-1, !reversed);
            
            if (reversed) {
                std::reverse(begin(part1), end(part1));
                std::reverse(begin(part2), end(part2));
                return part2 + middle + part1;
            }
                
            return part1 + middle + part2;
        };
        
        return dfs(0, target.length()-1, false);
    }
};