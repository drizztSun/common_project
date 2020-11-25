"""
878. Nth Magical Number

A positive integer is magical if it is divisible by either A or B.

Return the N-th magical number.  Since the answer may be very large, return it modulo 10^9 + 7.



Example 1:

Input: N = 1, A = 2, B = 3
Output: 2
Example 2:

Input: N = 4, A = 2, B = 3
Output: 6
Example 3:

Input: N = 5, A = 2, B = 4
Output: 10
Example 4:

Input: N = 3, A = 6, B = 4
Output: 8


Note:

1 <= N <= 10^9
2 <= A <= 40000
2 <= B <= 40000
"""


class NthMagicalNumber:


    """
    Approach 1: Mathematical
    Intuition and Algorithm

    Let's try to count to the NN-th magical number mathematically.

    First, the pattern of magical numbers repeats. Let LL be the least common multiple of AA and BB. If X \leq LX≤L is magical, then X + LX+L is magical,
    because (for example) A | XA∣X and A | LA∣L implies A | (X + L)A∣(X+L), and similarly if BB were the divisor.

    There are M = \frac{L}{A} + \frac{L}{B} - 1M=
    A
    L
    ​
     +
    B
    L
    ​
     −1 magical numbers less than or equal to LL: \frac{L}{A}
    A
    L
    ​
      of them are divisible by AA, \frac{L}{B}
    B
    L
    ​
      of them are divisible by BB, and 11 of them is divisible by both. So instead of counting one at a time, we can count by MM at a time.

    Now, suppose N = M*q + rN=M∗q+r (with r < Mr<M). The first L*qL∗q numbers contain M*qM∗q magical numbers, and within the next numbers (L*q + 1, L*q + 2, \cdots)(L∗q+1,L∗q+2,⋯) we want to find rr more magical ones.

    For this task, we can use brute force. The next magical number (less L*qL∗q) will either be AA or BB. If for example it is AA, then the next number will either be 2*A2∗A or BB, and so on.

    If the rr-th such magical number is YY, then the final answer is L*q + YL∗q+Y. Care must also be taken in the case that rr is 00.

    Complexity Analysis

    Time Complexity: O(A+B), assuming a model where integer math operations are O(1).
    The calculation of q * L is O(1). The calculation of the rr-th magical number after q*M is O(M) which is O(A+B).

    Space Complexity: O(1).

    """
    def doit_math(self, N: int, A: int, B: int) -> int:
        from fractions import gcd
        MOD = 10**9 + 7

        L = A / gcd(A, B) * B
        M = L / A + L / B - 1
        q, r = divmod(N, M)

        if r == 0:
            return q * L % MOD

        heads = [A, B]
        for _ in range(r - 1):
            if heads[0] <= heads[1]:
                heads[0] += A
            else:
                heads[1] += B

        return (q * L + min(heads)) % MOD

    """
    
    Approach 2: Binary Search
Intuition

The number of magical numbers less than or equal to xx is a monotone increasing function in xx, so we can binary search for the answer.

Algorithm

Say L = \text{lcm}(A, B)L=lcm(A,B), the least common multiple of AA and BB; and let f(x)f(x) be the number of magical numbers less than or equal to xx. A well known result says that L = \frac{A * B}{\text{gcd}(A, B)}L= 
gcd(A,B)
A∗B
​	
 , and that we can calculate the function \gcdgcd. For more information on least common multiples and greatest common divisors, please visit Wikipedia - Lowest Common Multiple.

Then f(x) = \lfloor \frac{x}{A} \rfloor + \lfloor \frac{x}{B} \rfloor - \lfloor \frac{x}{L} \rfloorf(x)=⌊ 
A
x
​	
 ⌋+⌊ 
B
x
​	
 ⌋−⌊ 
L
x
​	
 ⌋. Why? There are \lfloor \frac{x}{A} \rfloor⌊ 
A
x
​	
 ⌋ numbers A, 2A, 3A, \cdotsA,2A,3A,⋯ that are divisible by AA, there are \lfloor \frac{x}{B} \rfloor⌊ 
B
x
​	
 ⌋ numbers divisible by BB, and we need to subtract the \lfloor \frac{x}{L} \rfloor⌊ 
L
x
​	
 ⌋ numbers divisible by AA and BB that we double counted.

Finally, the answer must be between 00 and N * \min(A, B)N∗min(A,B).
Without loss of generality, suppose A \geq BA≥B, so that it remains to show

\lfloor \frac{N * \min(A, B)}{A} \rfloor + \lfloor \frac{N * \min(A, B)}{B} \rfloor - \lfloor \frac{N * \min(A, B)}{\text{lcm}(A, B)} \rfloor \geq N⌊ 
A
N∗min(A,B)
​	
 ⌋+⌊ 
B
N∗min(A,B)
​	
 ⌋−⌊ 
lcm(A,B)
N∗min(A,B)
​	
 ⌋≥N

\Leftrightarrow \lfloor \frac{N*A}{A} \rfloor + \lfloor \frac{N*A}{B} \rfloor - \lfloor \frac{N*A*\gcd(A, B)}{A*B} \rfloor \geq N⇔⌊ 
A
N∗A
​	
 ⌋+⌊ 
B
N∗A
​	
 ⌋−⌊ 
A∗B
N∗A∗gcd(A,B)
​	
 ⌋≥N

\Leftrightarrow \lfloor \frac{N*A}{B} \rfloor \geq \lfloor \frac{N*\gcd(A, B)}{B} \rfloor⇔⌊ 
B
N∗A
​	
 ⌋≥⌊ 
B
N∗gcd(A,B)
​	
 ⌋

\Leftrightarrow A \geq \gcd(A, B)⇔A≥gcd(A,B)

as desired.

Afterwards, the binary search on ff is straightforward. For more information on binary search,



    Complexity Analysis

    Time Complexity: O(log(N∗min(A,B))).
    
    Space Complexity: O(1).
    """
    def doit_binary_search(self, N, A, B):
        from fractions import gcd
        MOD = 10**9 + 7
        L = A / gcd(A,B) * B

        def magic_below_x(x):
            # How many magical numbers are <= x?
            return x / A + x / B - x / L

        lo = 0
        hi = N * min(A, B)
        while lo < hi:
            mi = (lo + hi) / 2
            if magic_below_x(mi) < N:
                lo = mi + 1
            else:
                hi = mi

        return lo % MOD

    def doit_binary_search_1(self, N: int, A: int, B: int) -> int:
        import math

        L = A // math.gcd(A, B) * B
        MOD = 10 ** 9 + 7

        def numbsers(x):
            return x // A + x // B - x // L

        lo = 0
        hi = N * min(A, B)

        while lo < hi:

            mid = (lo + hi) // 2

            if numbsers(mid) >= N:
                hi = mid
            else:
                lo = mid + 1

        return lo % MOD