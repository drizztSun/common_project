"""
1545. Find Kth Bit in Nth Binary String

Given two positive integers n and k, the binary string  Sn is formed as follows:

S1 = "0"
Si = Si-1 + "1" + reverse(invert(Si-1)) for i > 1
Where + denotes the concatenation operation, reverse(x) returns the reversed string x, 
and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).

For example, the first 4 strings in the above sequence are:

S1 = "0"
S2 = "011"
S3 = "0111001"
S4 = "011100110110001"
Return the kth bit in Sn. It is guaranteed that k is valid for the given n.

 

Example 1:

Input: n = 3, k = 1
Output: "0"
Explanation: S3 is "0111001". The first bit is "0".
Example 2:

Input: n = 4, k = 11
Output: "1"
Explanation: S4 is "011100110110001". The 11th bit is "1".
Example 3:

Input: n = 1, k = 1
Output: "0"
Example 4:

Input: n = 2, k = 3
Output: "1"
 

Constraints:

1 <= n <= 20
1 <= k <= 2n - 1


"""


class FindKthBit:

    """
        The length of n-th string should be 2 ** n - 1
        the index of middle element is mid = 2 ** (n - 1), 1-indexed,
        or mid = 2 ** (n - 1) - 1, 0-indexed
        if k == mid, then it must be '1' as definition.
        if k < mid, answer is the same as findKthBit(n - 1, k)
        if k > mid, answer is the opposite of findKthBit(n - 1, 2 * mid - k)

        Recursive Solution:
        Just do as information listed above:
    """

    def doit_(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        if n == 1:
            return '0'
        mid = 1 << (n - 1)
        if k == mid:
            return '1'
        if k < mid:
            return self.findKthBit(n - 1, k)
        return str(1 ^ int(self.findKthBit(n - 1, 2 * mid - k)))

    """
        Iterative Solution:

        1. Assuming the answer is ans = 0
        2. in each iteration, if k > mid, flip the answer once, and let k = 2 * mid - k as definition, then n will be n - 1
        3. when n == 1, the 1st element for S1 is '0'. If ans = 0, we guessed right at the beginning, so return '0'; 
            if ans = 1, we wrongly guessed the number, so return '1'. In summary, just return str(ans)
        4. If in certain iteration i, k == mid, the k-th element of Si is '1'. If ans = 1, we guessed right at the beginning, so return '0'; 
            If ans = 0, we wrongly guessed the number, so return '1'. In summary, we just return str(1 ^ ans)
    """
    def doit_(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        ans = 0
        mid = 1 << (n - 1)
        while n > 1:
            if k == mid:
                return str(1 ^ ans)
            if k > mid:
                k = 2 * mid - k
                ans = 1 - ans
            n -= 1
            mid >>= 1
        return str(ans)

    """
        Preword
        This solution involves all kinds of bit manipulation.
        So if you are beginner and not familar with bit manipulation,
        it's quite normal tht you find that I can't explain well enough.

        Like: lowbit = x & -x


        Explanation 1
        Let's define some notation:
        Odd sequence: the sequence on odd positions
        Even sequence: the sequence on even positions
        Zero-One sequence: The sequence of 1,0,1,0,1,0
        One-Zero sequence: The sequence of 1,0,1,0,1,0
        Sequence S, defined as the description.
        Magic sequence: we'll talk about that later


        Take an observation on the odd sequence of S:
        They are 0,1,0,1,0,1,0.... a Zero-One sequence. (a)
        if k >> 1 is even, return 0,
        if k >> 1 is odd, return 1,
        where k is 1-based.
        So, return k >> 1 & 1

        Take an observation of the sequence on even position:
        They are 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0
        We call this sequence as magic sequence M.
        The properties of M:
        1). It's odd sequence is a One-Zero sequence. (b)
        2). It's even sequence is still a Magic sequence (c)

        If for a even number k, it's in case c.
        We do k = k / 2, if it's even, still in case c.
        We keep doing this, until k is odd, now it's in case b.

        so for a even number k = k2 * pow(2), where k2 is odd,
        if k2 >> 1 is odd, return 1
        if k2 >> 1 is even, return 0
        we return k2 >> 1 & 1 ^ 1


        Explanation 2
        Every time we want a symmetical of k, we do k = pow(2) - k.
        For example:
        k = 215, k = 256 - 215 = 41
        k = 41 , k = 64 - 41 = 23
        k = 23 , k = 32 - 23 = 9
        k = 9 , k = 16 - 9 = 7
        k = 7 , k = 8 - 7 = 1,
        k = 1, flipped 5 times, return 0.

        In general cases,
        if k = 1 in the end, S(1) = 0
        fliped odd times, return 1
        fliped even times, return 0

        if k = pow(2) (or k = 0) in the end, S(pow(2)) = 1
        fliped odd times, return 0
        fliped even times, return 1

        So it depends how many times we will flip,
        and what's the last value.

        Assume k = x * pow(2), where x is odd.
        The number of flip time, equals to the number of 0,1 groups in x >> 1.
        If x >> 1 is odd, we'll flip odd times. 
        If x >> 1 is even, we'll flip even times.


        Complexity
        Time O(1)
        Space O(1)

    """
    def doit_(self, n: int, k: int) -> str:
        return str(k / (k & -k) >> 1 & 1 ^ k & 1 ^ 1)


    """
        Explanation
        If k is on the left part of the string, we do nothing.

        If K is right in the middle, and the middle is 1.
        We flip count times, we return count % 2 == 0 ? '1' : '0'

        If k is on the right part of the string,
        find it's symeric postion k = l + 1 - k.
        Also we increment count++.


        Complexity
        Time O(n)
        Space O(1)
    """
    def findKthBit(self, n, k):
        flip = 0
        l = 2 ** n - 1
        while k > 1:
            if k == l / 2 + 1:
                return str(1 ^ flip)
            if k > l / 2:
                k = l + 1 - k
                flip = 1 - flip
            l /= 2
        return str(flip)