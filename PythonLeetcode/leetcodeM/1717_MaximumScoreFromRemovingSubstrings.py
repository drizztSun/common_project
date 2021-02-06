"""
1717. Maximum Score From Removing Substrings


You are given a string s and two integers x and y. You can perform two types of operations any number of times.

Remove substring "ab" and gain x points.
For example, when removing "ab" from "cabxbae" it becomes "cxbae".
Remove substring "ba" and gain y points.
For example, when removing "ba" from "cabxbae" it becomes "cabxe".
Return the maximum points you can gain after applying the above operations on s.

 

Example 1:

Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.
Example 2:

Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20
 

Constraints:

1 <= s.length <= 10^5
1 <= x, y <= 10^4
s consists of lowercase English letters.

"""

class MaximumGain:
    
    """
        1717.Maximum-Score-From-Removing-Substrings
        此题就是一个简单的贪心法。如果ab的收益比ba大，那么从头到尾我们就尽量删除ab。一遍走完之后，剩下的就一定只是bbbaaa的形式，那么我们就只需要再走一遍删ba了。
        如果ba的收益比ab大，我们有一个比较巧妙的处理方法。就是将s逆序，并把x和y对换。这样我们依然重用上面的代码，第一遍删ab，第二遍删ba。
    """
    def doit_greedy(self, s: str, x: int, y: int) -> int:

        if x < y:
            x, y = y, x
            s = reversed(s)

        ans = 0
        st = []
        for c in s:
            st.append(c)

            if len(st) > 1 and st[-2] == 'a' and st[-1] == 'b':
                ans += x
                st.pop()
                st.pop()

        s = ''.join(st)
        st = []
        for c in s:
            
            st.append(c)
            if len(st) > 1 and st[-2] == 'b' and st[-1] == 'a':
                ans += y
                st.pop()
                st.pop()

        return ans

    def doit_greedy(self, s: str, x: int, y: int) -> int:
        
        def search(target, c1, c2):
            st = ['.']
            ans = 0
            for c in target:
                if c == c2 and st[-1] == c1:
                    st.pop()
                    ans += 1
                    continue
                st.append(c)
            return ''.join(st), ans
        
        ans = 0
        if (x > y):
            rest, cnt1 = search(s, 'a', 'b')
            _, cnt2 = search(rest, 'b', 'a')
            ans = cnt1 * x + cnt2 * y
        else:
            rest, cnt1 = search(s, 'b', 'a')
            _, cnt2 = search(rest, 'a', 'b')
            ans = cnt1 * y + cnt2 * x
        
        return ans

        