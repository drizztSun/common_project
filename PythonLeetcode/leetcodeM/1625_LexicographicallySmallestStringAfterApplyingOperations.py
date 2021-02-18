"""
1625. Lexicographically Smallest String After Applying Operations



You are given a string s of even length consisting of digits from 0 to 9, and two integers a and b.

You can apply either of the following two operations any number of times and in any order on s:

1. Add a to all odd indices of s (0-indexed). Digits post 9 are cycled back to 0. For example, if s = "3456" and a = 5, s becomes "3951".
2. Rotate s to the right by b positions. For example, if s = "3456" and b = 1, s becomes "6345".
Return the lexicographically smallest string you can obtain by applying the above operations any number of times on s.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. 
For example, "0158" is lexicographically smaller than "0190" because the first position they differ is at the third letter, and '5' comes before '9'.

 

Example 1:

Input: s = "5525", a = 9, b = 2
Output: "2050"
Explanation: We can apply the following operations:
Start:  "5525"
Rotate: "2555"
Add:    "2454"
Add:    "2353"
Rotate: "5323"
Add:    "5222"
​​​​​​​Add:    "5121"
​​​​​​​Rotate: "2151"
​​​​​​​Add:    "2050"​​​​​​​​​​​​
There is no way to obtain a string that is lexicographically smaller then "2050".
Example 2:

Input: s = "74", a = 5, b = 1
Output: "24"
Explanation: We can apply the following operations:
Start:  "74"
Rotate: "47"
​​​​​​​Add:    "42"
​​​​​​​Rotate: "24"​​​​​​​​​​​​
There is no way to obtain a string that is lexicographically smaller then "24".
Example 3:

Input: s = "0011", a = 4, b = 2
Output: "0011"
Explanation: There are no sequence of operations that will give us a lexicographically smaller string than "0011".
Example 4:

Input: s = "43987654", a = 7, b = 3
Output: "00553311"
 

Constraints:

2 <= s.length <= 100
s.length is even.
s consists of digits from 0 to 9 only.
1 <= a <= 9
1 <= b <= s.length - 1

"""

class LexSmallestString:

    """
        1625.Lexicographically-Smallest-String-After-Applying-Operations
        此题号称“LC史上最难周赛第二题”。从数据规模和历史经验来看，应该可以暴力解决问题，但是该怎么暴力才对呢？

        解法1：
        题目告知字符串的长度是偶数。我们的第一个发现是，如果b是偶数的话，无论怎么rotate，每次add操作总是作用在所有的奇数位上。rotate只影响数字的排列，而不影响数值的大小。
        数值的大小只取决于你做了几次add。这就提示我们，可以先尽情地add，然后再尽情地rotate，两者可以互不影响。我们可以穷尽所有add的结果，再穷尽所有rotate的结果，再找其中的最小值即可。

        再拓展一下，如果b是奇数的话，我们发现rotate一次之后，add操作其实作用在原本的偶数位上；再rotate一次之后，add操作又作用在原本的奇数位上。
        也就是说，我们可以通过rotate操作，来给所有的奇数位或者所有的偶数位加上任意的数值。奇数位上能加的数值，和偶数位上能加的数值，两者并不影响。
        同样，我们可以（分别在奇数位和偶数位上）穷尽所有add的结果，再穷尽所有rotate的结果，再找其中的最小值即可。

        关于“穷尽所有add的结果”，我们只需要尝试最多add十次。因为add a*10和add a这两个操作本质上是一样。关于“穷尽所有rotate的结果”，我们也只需要最多rotate n次，因为rotate by b和rotate by n*b的效果也是一样的。
        但更高效的方法是，我们需要rotate的次数是n/gcd(n,b).

        解法2：
        既然add和rotate可以解耦合，那么另一种思路就是先枚举rotate，再确定最优的add。

        在外层循环，我们枚举rotate的决策。然后我们查看如果b%2==1，说明我们允许对奇数位进行add操作，自然我们会选择最优的操作数使得str[0]最小。
        此外，无论b的奇偶性，我们都能对偶数位进行add操作，自然我们会选择最优的操作数使得str[1]最小。至此，奇数位和偶数位的操作次数都已经确定下来了，那么整个数也就确定下来了。      
    """
    def doit_search(self, s: str, a: int, b: int) -> str:

        from math import gcd

        n, eventimes = len(s), 10

        if b % 2 == 0:
            eventimes = 1

        target = [ord(c) - ord('0') for c in s]
        ret = s

        for i in range(eventimes):

            for j in range(10):

                t = target[:]

                for k in range(0, n, 2):
                    t[k] = (t[k] + a * i) % 10

                for k in range(1, n, 2):
                    t[k] = (t[k] + a * j) % 10

                t = [chr(c + ord('0')) for c in t]

                for k in range(0, n // gcd(n, k) + 1, 1):
                    t = t[-b:] + t[:-b]
                    ret = min(ret, ''.join(t))

        return ret