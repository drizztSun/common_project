"""
1234. Replace the Substring for Balanced String

You are given a string containing only 4 kinds of characters 'Q', 'W', 'E' and 'R'.

A string is said to be balanced if each of its characters appears n/4 times where n is the length of the string.

Return the minimum length of the substring that can be replaced with any other string of the same length to make the original string s balanced.

Return 0 if the string is already balanced.

 

Example 1:

Input: s = "QWER"
Output: 0
Explanation: s is already balanced.
Example 2:

Input: s = "QQWE"
Output: 1
Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is balanced.
Example 3:

Input: s = "QQQW"
Output: 2
Explanation: We can replace the first "QQ" to "ER". 
Example 4:

Input: s = "QQQQ"
Output: 3
Explanation: We can replace the last 3 'Q' to make s = "QWER".
 

Constraints:

1 <= s.length <= 10^5
s.length is a multiple of 4
s contains only 'Q', 'W', 'E' and 'R'.


"""


class BalancedString:

    """
        Intuition
        We want a minimum length of substring,
        which leads us to the solution of sliding window.
        Specilly this time we don't care the count of elements inside the window,
        we want to know the count outside the window.


        Explanation
        One pass the all frequency of "QWER".
        Then slide the windon in the string s.

        Imagine that we erase all character inside the window,
        as we can modyfy it whatever we want,
        and it will always increase the count outside the window.

        So we can make the whole string balanced,
        as long as max(count[Q],count[W],count[E],count[R]) <= n / 4.


        Important
        Does i <= j + 1 makes more sense than i <= n.
        Strongly don't think, and i <= j + 1 makes no sense.

        Answer the question first:
        Why do we need such a condition in sliding window problem?

        Actually, we never need this condition in sliding window solution
        (Check all my other solutions link at the bottom).

        Usually count the element inside sliding window,
        and i won't be bigger than j because nothing left in the window.

        The only reason that we need a condition is in order to prevent index out of range.
        And how do we do that? Yes we use i < n

        Does i <= j + 1 even work?
        When will i even reach j + 1?
        Does i <= j + 1 work better than i <= j?

        Please upvote for this important tip.
        Also let me know if there is any unclear, glad to hear different voices.
        But please, have a try, and show the code if necessary.

        Some people likes to criticize without even a try,
        and solve the problem by talking.
        Why talk to me? Talk to the white board.


        Complexity
        Time O(N), one pass for counting, one pass for sliding window
        Space O(1)
    """
    def doit_slidingwindow(self, s):
        import collections
        count = collections.Counter(s)
        res = n = len(s)
        i = 0
        for j, c in enumerate(s):
            count[c] -= 1
            while i < n and all(n // 4 >= count[c] for c in 'QWER'):
                res = min(res, j - i + 1)
                count[s[i]] += 1
                i += 1
        return res

    def doit_slidingwindow(self, s: str) -> int:
        from collections import Counter
        counter = Counter(s)
        n, start, larger = len(s), 0, 0
        ret = n
        
        for val in counter.values():
            if val > n//4:
                larger += 1
                
        if larger == 0: return 0
        
        for end, val in enumerate(s):
            
            counter[val] -= 1
            if counter[val] == n//4:
                larger -= 1
            
            while start <= end and larger == 0:
                ret = min(ret, end - start + 1)
                counter[s[start]] += 1
                if counter[s[start]] == n // 4 + 1:
                    larger += 1
                start += 1
        return ret

    def doit_(self, s: str) -> int:
        
        if len(s) % 4 != 0: return -1
        
        ave = len(s) // 4
        cnt = {'Q': 0, 'E': 0, 'W': 0, 'R': 0}
        for c in s: 
            cnt[c] += 1
        
        length, t1, t2 = 0, {}, {}
        for c in cnt:
            if cnt[c] > ave:
                t1[c] = cnt[c] - ave
                length += cnt[c] - ave
            elif cnt[c] < ave:
                t2[c] = ave - cnt[c]
                
        if length == 0: return 0
        
        def minimum_length(target):

            from collections import defaultdict
            
            i, ans, size, cnt = 0, len(s), 0, defaultdict(int)

            for j in range(len(s)):

                if s[j] in target:
                    cnt[s[j]] += 1
                    size += 1

                    while cnt[s[j]] > target[s[j]]:
                        if s[i] in target:
                            cnt[s[i]] -= 1
                            size -= 1
                        i += 1
                    
                if length == size:
                    ans = min(ans, j - i + 1)
                    
            return ans
        
        return min(minimum_length(t1), minimum_length(t2))


if __name__ == '__main__':

    BalancedString().doit_("QEQRWRRWWWRQQQWQQEQEQREWRQEQRQQRRQEW")

    BalancedString().doit_("WWEQERQWQWWRWWERQWEQ")