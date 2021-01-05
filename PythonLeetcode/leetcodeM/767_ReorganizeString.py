"""
767. Reorganize String

Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.

If possible, output any possible result.  If not possible, return the empty string.

Example 1:

Input: S = "aab"
Output: "aba"
Example 2:

Input: S = "aaab"
Output: ""
Note:

S will consist of lowercase letters and have length in range [1, 500].
"""
import heapq


class ReorganizeString:

    """
    Approach #1: Sort by Count [Accepted]
    Intuition

    If we should make no two 'a's adjacent, it is natural to write "aXaXaXa..." where "X" is some letter. For now, let's assume that the task is possible (ie. the answer is not "".)

    Let's sort the string S, so all of the same kind of letter occur in continuous blocks. Then when writing in the following interleaving pattern, like S[3], S[0], S[4], S[1], S[5], S[2], adjacent letters never touch. (The specific interleaving pattern is that we start writing at index 1 and step by 2; then start from index 0 and step by 2.)

    The exception to this rule is if N is odd, and then when interleaving like S[2], S[0], S[3], S[1], S[4], we might fail incorrectly if there is a block of the same 3 letters starting at S[0] or S[1]. To prevent failing erroneously in this case, we need to make sure that the most common letters all occur at the end.

    Finally, it is easy to see that if N is the length of the string, and the count of some letter is greater than (N+1) / 2, the task is impossible.

    Algorithm

    Find the count of each character, and use it to sort the string by count.

    If at some point the number of occurrences of some character is greater than (N + 1) / 2, the task is impossible.

    Otherwise, interleave the characters in the order described above.

    Complexity Analysis

    Time Complexity: O(A(N+logA)), where NN is the length of SS, and A is the size of the alphabet. In Java, our implementation is O(N+AlogA). If A is fixed, this complexity is O(N).

    Space Complexity: O(N). In Java, our implementation is O(N+A).
    """
    def doit_sort(self, S):
        N = len(S)
        A = []
        for c, x in sorted((S.count(x), x) for x in set(S)):
            if c > (N+1)/2: return ""
            A.extend(c * x)
        ans = [None] * N
        ans[::2], ans[1::2] = A[N/2:], A[:N/2]
        return "".join(ans)

    """
    Approach #2: Greedy with Heap [Accepted]
    Intuition
    
    One consequence of the reasoning in Approach #1, is that a greedy approach that tries to write the most common letter (that isn't the same as the previous letter written) will work.
    
    The reason is that the task is only impossible if the frequency of a letter exceeds (N+1) / 2. Writing the most common letter followed by the second most common letter keeps this invariant.
    
    A heap is a natural structure to repeatedly return the current top 2 letters with the largest remaining counts.
    
    Approach
    
    We store a heap of (count, letter). [In Python, our implementation stores negative counts.]
    
    We pop the top two elements from the heap (representing different letters with positive remaining count), and then write the most frequent one that isn't the same as the most recent one written. After, we push the correct counts back onto the heap.
    
    Actually, we don't even need to keep track of the most recent one written. If it is possible to organize the string, the letter written second can never be written first in the very next writing.
    
    At the end, we might have one element still on the heap, which must have a count of one. If we do, we'll add that to the answer too.
    
    Proof of Invariant
    
    Complexity Analysis

    Time Complexity: O(NlogA)), where NN is the length of SS, and A is the size of the alphabet. If A is fixed, this complexity is O(N).
    
    Space Complexity: O(A). If A is fixed, this complexity is O(1).
    """
    def doit_heap(self, S):
        pq = [(-S.count(x), x) for x in set(S)]
        heapq.heapify(pq)
        if any(-nc > (len(S) + 1) / 2 for nc, x in pq):
            return ""

        ans = []
        while len(pq) >= 2:
            nct1, ch1 = heapq.heappop(pq)
            nct2, ch2 = heapq.heappop(pq)
            # This code turns out to be superfluous, but explains what is happening
            # if not ans or ch1 != ans[-1]:
            #    ans.extend([ch1, ch2])
            # else:
            #    ans.extend([ch2, ch1])
            ans.extend([ch1, ch2])
            if nct1 + 1:
                heapq.heappush(pq, (nct1 + 1, ch1))
            if nct2 + 1:
                heapq.heappush(pq, (nct2 + 1, ch2))

        return "".join(ans) + (pq[0][1] if pq else '')

    def doit_heap(self, S):
        from collections import Counter
        from heapq import heapify, heappop

        buff = Counter(S)
        pq = [(-v, k) for k, v in buff.items()]
        heapify(pq)

        res = ''
        while pq:
            c = heappop(pq)

            if not pq:
                if c[0] < -1:
                    return ''                               

                res += c[1] 
                continue

            s = heappop(pq)
            res += c[1] + s[1]
            
            if c[0] != -1:
                heapq.heappush(pq, (c[0] + 1, c[1]))
                
            if s[0] != -1:
                heapq.heappush(pq, (s[0] + 1, s[1]))

        return res