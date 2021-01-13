"""
686. Repeated String Match


Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.

Notice: string "abc" repeated 0 times is "",  repeated 1 time is "abc" and repeated 2 times is "abcabc".

 

Example 1:

Input: a = "abcd", b = "cdabcdab"
Output: 3
Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
Example 2:

Input: a = "a", b = "aa"
Output: 2
Example 3:

Input: a = "a", b = "a"
Output: 1
Example 4:

Input: a = "abc", b = "wxyz"
Output: -1
 

Constraints:

1 <= a.length <= 104
1 <= b.length <= 104
a and b consist of lower-case English letters.

"""


class RepeatedStringMatch:

    """
        Approach #1: Ad-Hoc [Accepted]
        Intuition

        The question can be summarized as "What is the smallest k for which B is a substring of A * k?" We can just try every k.

        Algorithm

        Imagine we wrote S = A+A+A+.... If B is to be a substring of S, we only need to check whether some S[0:], S[1:], ..., S[len(A) - 1:] starts with B, as S is long enough to contain B, and S has period at most len(A).

        Now, suppose q is the least number for which len(B) <= len(A * q). We only need to check whether B is a substring of A * q or A * (q+1). If we try k < q, then B has larger length than A * q and therefore can't be a substring. 
        When k = q+1, A * k is already big enough to try all positions for B; namely, A[i:i+len(B)] == B for i = 0, 1, ..., len(A) - 1.

        Complexity Analysis

        Time Complexity: O(N∗(N+M)), where M, NM,N are the lengths of strings A, B. We create two strings A * q, A * (q+1) which have length at most O(M+N). When checking whether B is a substring of A, this check takes naively the product of their lengths.

        Space complexity: As justified above, we created strings that used O(M+N) space.
    """
    def doit_(self, A: str, B: str) -> int:
        q = (len(B) - 1) // len(A) + 1
        for i in range(2):
            if B in A * (q+i): return q+i
        return -1

    """
        Approach #2: Rabin-Karp (Rolling Hash) [Accepted]
        Intuition

        As in Approach #1, we've reduced the problem to deciding whether B is a substring of some A * k. Using the following technique, we can decide whether B is a substring in O(len(A) * k)O(len(A)∗k) time.

        Algorithm

        For strings SS, consider each S[i]S[i] as some integer ASCII code. Then for some prime pp, consider the following function modulo some prime modulus \mathcal{M}M:

        \text{hash}(S) = \sum_{0 \leq i < len(S)} p^i * S[i]hash(S)=∑ 
        0≤i<len(S)
        ​	
        p 
        i
        ∗S[i]

        Notably, \text{hash}(S[1:] + x) = \frac{(\text{hash}(S) - S[0])}{p} + p^{n-1} xhash(S[1:]+x)= 
        p
        (hash(S)−S[0])
        ​	
        +p 
        n−1
        x. This shows we can get the hash of every substring of A * q in time complexity linear to it's size. (We will also use the fact that p^{-1} = p^{\mathcal{M}-2} \mod \mathcal{M}p 
        −1
        =p 
        M−2
        modM.)

        However, hashes may collide haphazardly. To be absolutely sure in theory, we should check the answer in the usual way. The expected number of checks we make is in the order of 1 + \frac{s}{\mathcal{M}}1+ 
        M
        s
        ​	
        where ss is the number of substrings we computed hashes for (assuming the hashes are equally distributed), which is effectively 1.


        Complexity Analysis

        Time Complexity: O(M+N)O(M+N) (at these sizes), where M, NM,N are the lengths of strings A, B. As in Approach #1, we justify that A * (q+1) will be of length O(M + N)O(M+N), and computing the rolling hashes was linear work. We will also do a linear O(N)O(N) final check of our answer 1 + O(M) / \mathcal{M}1+O(M)/M times. In total, this is O(M+N + N(1 + \frac{M}{\mathcal{M}}))O(M+N+N(1+ 
        M
        M
        ​	
        )) work. Since M \leq 10000 < \mathcal{M} = 10^9 + 7M≤10000<M=10 
        9
        +7, we can consider this to be linear behavior.

        Space complexity: O(1)O(1). Only integers were stored with additional memory.
    """
    def doit_(self, A, B):
        def check(index):
            return all(A[(i + index) % len(A)] == x for i, x in enumerate(B))

        q = (len(B) - 1) // len(A) + 1

        p, MOD = 113, 10**9 + 7
        p_inv = pow(p, MOD-2, MOD)
        power = 1

        b_hash = 0
        for x in map(ord, B):
            b_hash += power * x
            b_hash %= MOD
            power = (power * p) % MOD

        a_hash = 0
        power = 1
        for i in range(len(B)):
            a_hash += power * ord(A[i % len(A)])
            a_hash %= MOD
            power = (power * p) % MOD

        if a_hash == b_hash and check(0): return q

        power = (power * p_inv) % MOD
        for i in range(len(B), (q+1) * len(A)):
            a_hash = (a_hash - ord(A[(i - len(B)) % len(A)])) * p_inv
            a_hash += power * ord(A[i % len(A)])
            a_hash %= MOD
            if a_hash == b_hash and check(i - len(B) + 1):
                return q if i < q * len(A) else q+1

        return -1

        