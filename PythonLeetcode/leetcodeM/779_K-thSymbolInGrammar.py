""""
779. K-th Symbol in Grammar


On the first row, we write a 0. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.

Given row N and index K, return the K-th indexed symbol in row N. (The values of K are 1-indexed.) (1 indexed).

Examples:
Input: N = 1, K = 1
Output: 0

Input: N = 2, K = 1
Output: 0

Input: N = 2, K = 2
Output: 1

Input: N = 4, K = 5
Output: 1

Explanation:
row 1: 0
row 2: 01
row 3: 0110
row 4: 01101001
Note:

N will be an integer in the range [1, 30].
K will be an integer in the range [1, 2^(N-1)].

"""


class KthGrammar:

    """
        0
        01
        0110
        01101001

        2**N - 1, k
        log(n)
    """
    def doit_binary_search(self, N: int, k: int) -> int:

        k -= 1
        total = 1 << (N - 1)
        last = 0
        while k > 0:

            total //= 2

            if k < total:
                cur = 0 if last == 0 else 1
            else:
                cur = 1 if last == 0 else 0

            if k >= total:
                k -= total

            last = cur

        return last

    """
        Approach 1: Brute Force
        Intuition and Algorithm
        
        We'll make each row exactly as directed in the problem statement. We only need to remember the last row.
        
        Unfortunately, the strings could have length around 1 billion, as they double on each row, so this approach is not efficient enough.
        
        
        Complexity Analysis
        
        Time Complexity: O(2^N)O(2 
        N
         ). We parse rows with lengths 2^0 + 2^1 + \cdots + 2^{N-1}2 
        0
         +2 
        1
         +⋯+2 
        N−1
         .
        
        Space Complexity: O(2^N)O(2 
        N
         ), the length of the lastrow.
    """
    def doit_brute_force(self, N, K):
        lastrow = '0'
        while len(rows) < N:
            lastrow = "".join('01' if x == '0' else '10'
                              for x in lastrow)
        return int(rows[-1][K-1])

    """
        Approach 2: Recursion (Parent Variant)
        Intuition and Algorithm
        
        Since each row is made only using information from the previous row, let's try to write the answer in terms of bits from the previous row.
        
        
        Diagram of digits with relationship to their parent
        
        In particular, if we write say "0110" which generates "01101001", then the first "0" generates the first "01" in the next row; the next digit "1" generates the next "10", the next "1" generates the next "10", and the last "0" generates the last "01".
        
        
        Diagram of digits through repeated function calls
        
        In general, the Kth digit's parent is going to be (K+1) / 2. If the parent is 0, then the digit will be the same as 1 - (K%2). If the parent is 1, the digit will be the opposite, ie. K%2.
        
        
        Complexity Analysis
        
        Time Complexity: O(N)O(N). It takes N-1N−1 steps to find the answer.
        
        Space Complexity: O(1)O(1).
    """
    def kthGrammar(self, N, K):
        if N == 1: return 0
        return (1 - K%2) ^ self.kthGrammar(N-1, (K+1)/2)


    """
        Approach 3: Recursion (Flip Variant)
        Intuition and Algorithm
        
        As in Approach #2, we could try to write the bit in terms of it's previous bit.
        
        When writing a few rows of the sequence, we notice a pattern: the second half is always the first half "flipped": namely, that '0' becomes '1' and '1' becomes '0'.
        
        We can prove this assertion by induction. The key idea is if a string XX generates YY, then a flipped string X'X 
        ′
          generates Y'Y 
        ′
         .
        
        This leads to the following algorithm idea: if K is in the second half, then we could put K -= (1 << N-2) so that it is in the first half, and flip the final answer.
        
        
        Complexity Analysis
        
        Time Complexity: O(N)O(N). It takes N-1N−1 steps to find the answer.
        
        Space Complexity: O(1)O(1).
    """
    def kthGrammar(self, N, K):
        if N == 1: return 0
        if K <= (2 ** (N - 2)):
            return self.kthGrammar(N - 1, K)
        return self.kthGrammar(N - 1, K - 2 ** (N - 2)) ^ 1

    """
        Approach 4: Binary Count
        Intuition and Algorithm
        
        As in Approach #3, the second half of every row is the first half flipped.
        
        When the indexes K are written in binary (now indexing from zero), indexes of the second half of a row are ones with the first bit set to 1.
        
        This means when applying the algorithm in Approach #3 virtually, the number of times we will flip the final answer is just the number of 1s in the binary representation of K-1.
        
        
        Complexity Analysis
        
        Time Complexity: O(\log N)O(logN), the number of binary bits in N. If \log NlogN is taken to be bounded, this can be considered to be O(1)O(1).
        
        Space Complexity: O(1)O(1). (In Python, bin(X) creates a string of length O(\log X)O(logX), which could be avoided.)
    """
    def kthGrammar(self, N, K):
        return bin(K - 1).count('1') % 2