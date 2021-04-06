/*
844. Backspace String Compare


Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
Follow up:

Can you solve it in O(N) time and O(1) space?

*/

#include <string>
#include <stack>

using std::stack;
using std::string;


class BackspaceCompare {

    /*
        844.Backspace-String-Compare
        此题的考点是用o(n)时间和o(1)空间．这就提示我们做in-place的修改．

        我们可以尝试用双指针的方法，将有效的字符都移动到字符串的前面去。具体的做法是快指针j扫每个元素，如果遇到了正常的字符，则str[i]=str[j]，同时慢指针i自增1。如果遇到了退格键，那么将慢指针i退一个即可。最终i指针的位置就代表了这个字符串最终有多长。
    */
    bool backspaceCompare(string S, string T) 
    {
        int i = convert(S);
        int j = convert(T);
        return S.substr(0,i)==T.substr(0,j);
    }

    int convert(string& str)
    {
        int i=0;
        for (int j=0; j<str.size(); j++)
        {
            if (str[j]!='#')
            {
                str[i] = str[j];
                i++;
            }
            else
            {
                i = std::max(0, i-1);
            }                
        }
        return i;
    }


public:

    bool doit_stack(string S, string T) {

        auto filter = [](const string& target) {
            stack<char> st;
            for(auto c: target) {
                if (c == '#') {
                    if (!st.empty())
                        st.pop();
                } else
                    st.push(c);
            }

            return st;
        };
        
        return filter(S) == filter(T);
    }

    
    bool doit_str(string S, string T) {
        
        int i = 0, j = 0;
        int ds = 0, dt = 0;
        
        while (i < S.length() && j < T.length()) {
            
            
            
            
        }
        
        return i == S.length() && j == T.length();
    }
};