"""
1737. Change Minimum Characters to Satisfy One of Three Conditions


You are given two strings a and b that consist of lowercase letters. In one operation, you can change any character in a or b to any lowercase letter.

Your goal is to satisfy one of the following three conditions:

* Every letter in a is strictly less than every letter in b in the alphabet.
* Every letter in b is strictly less than every letter in a in the alphabet.
* Both a and b consist of only one distinct letter.

Return the minimum number of operations needed to achieve your goal.

 

Example 1:

Input: a = "aba", b = "caa"
Output: 2
Explanation: Consider the best way to make each condition true:
1) Change b to "ccc" in 2 operations, then every letter in a is less than every letter in b.
2) Change a to "bbb" and b to "aaa" in 3 operations, then every letter in b is less than every letter in a.
3) Change a to "aaa" and b to "aaa" in 2 operations, then a and b consist of one distinct letter.
The best way was done in 2 operations (either condition 1 or condition 3).
Example 2:

Input: a = "dabadd", b = "cda"
Output: 3
Explanation: The best way is to make condition 1 true by changing b to "eee".
 

Constraints:

1 <= a.length, b.length <= 10^5
a and b consist only of lowercase letters.

"""


class MinCharacters:
    
    """
        1737.Change-Minimum-Characters-to-Satisfy-One-of-Three-Conditions
        对于第一个条件，我们只需要枚举所有字母作为borderline，a中所有大于等于该字母的都要改小，b中所有小于该字母的都要改大。这样就可以保证a的每个字母都比b中的小。
        记录改动的次数，选择需要改动最少的（border line）。特别注意的是，这个borderline不能是字母'a'，因为你无法让b的所有字母比'a'还要小，这是个大坑。

        对于第二个条件，同理，反着做一遍。

        对于第三个条件，我们也只需要枚举所有字母，让a和b中所有非该字母的都做改变。记录改动的次数。

        最终答案是分别三个条件的最少改动次数里选最小的。
    """
    def doit_(self, a: str, b: str) -> int:
        
        from collections import Counter

        cntA, cntB = Counter(a), Counter(b)
        ans = float('inf')
        a = ord('a')

        for c in range(26):
            
            if c > 0:
                change = 0
                for i in range(c):
                    change += cntA.get(chr(a + i), 0)

                for i in range(c, 26):
                    change += cntB.get(chr(a + i), 0)

                ans = min(ans, change)


                change = 0
                for i in range(c):
                    change += cntB.get(chr(a + i), 0)

                for i in range(c, 26):
                    change += cntA.get(chr(a + i), 0)

                ans = min(ans, change)


            change = 0
            for i in range(26):
                if i != c:
                    change += cntA.get(chr(a + i), 0) + cntB.get(chr(a + i), 0)
            ans = min(ans, change)
            
        return ans


    def doit_(self, a: str, b: str) -> int:
        
        from collections import Counter
        
        cntA, cntB = Counter(a), Counter(b)
        
        def lessthan(A, B):
            akeys = sorted(A.keys())
            bkeys = sorted(B.keys())
            
            ans = 0
            i, j == 0, len(A)-1
            while bkeys[i] < akeys[j]: 
                if bkeys[i] == 'a' or A[akeys[j]] <= B[bkeys[i]]:
                    i += 1
                    ans += B[bkeys[i]]
                else:
                    ans += A[akeys[j]]
                    j -= 1
            return ans
        
        def equal(A, B):
            total = A + B
            return sum(total.values()) - max(total.values())
            
        return min(lessthan(cntA, cntB), lessthan(cntB, cntA), equal(cntA, cntB))