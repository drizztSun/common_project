"""
828. Unique Letter String

# A character is unique in string S if it occurs exactly once in it.

# For example, in string S = "LETTER", the only unique characters are "L" and "R".

# Let's define UNIQ(S) as the number of unique characters in string S.

# For example, UNIQ("LETTER") =  2.

# Given a string S with only uppercases, calculate the sum of UNIQ(substring) over all non-empty substrings of S.

# If there are two or more equal substrings at different positions in S, we consider them different.

# Since the answer can be very large, retrun the answer modulo 10 ^ 9 + 7.



# Example 1:

# Input: "ABC"
# Output: 10
# Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
# Evey substring is composed with only unique letters.
# Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
# Example 2:

# Input: "ABA"
# Output: 8
# Explanation: The same as example 1, except uni("ABA") = 1.


# Note: 0 <= S.length <= 10000.

"""


class UniqueLetterString:


    """
    Approach #2: Split by Character [Accepted]
    Intuition

    As in Approach #1, we have U(x) = \sum_{c \in \mathcal{A}} U_c(x)U(x)=∑
    c∈A
    ​
     U
    c
    ​
     (x), where \mathcal{A} = \{ \text{"A"}, \text{"B"}, \dots \}A={"A","B",…} is the alphabet, and we only need to answer the following question (26 times, one for each character): how many substrings have exactly one \text{"A"}"A"?

    Algorithm

    Consider how many substrings have a specific \text{"A"}"A". For example, let's say S only has three "A"'s, at 'S[10] = S[14] = S[20] = "A"; and we want to know the number of substrings that contain S[14].
    The answer is that there are 4 choices for the left boundary of the substring (11, 12, 13, 14), and 6 choices for the right boundary (14, 15, 16, 17, 18, 19).
    So in total, there are 24 substrings that have S[14] as their unique "A".

    Continuing our example, if we wanted to count the number of substrings that have S[10], this would be 10 * 4 - note that when there is no more "A" characters to the left of S[10],
    we have to count up to the left edge of the string.

    We can add up all these possibilities to get our final answer.
    """
    def doit_(self, S):
        import collections

        index = collections.defaultdict(list)
        for i, c in enumerate(S):
            index[c].append(i)

        ans = 0
        for A in index.values():
            A = [-1] + A + [len(S)]
            for i in range(1, len(A) - 1):
                ans += (A[i] - A[i-1]) * (A[i+1] - A[i])
        return ans % (10**9 + 7)

    def doit1(self, S):
        """
        :type S: str
        :rtype: int
        """
        res = 0
        for i in range(1, len(S) + 1):
            for j in range(0, len(S) - i):
                substring = S[j : j + i]
                cnt = [0] * 256
                for c in substring:
                    cnt[int(c)] += 1

                res += sum([1 for i in range(len(cnt)) if cnt[i] == 1])
        
        return res

    """
    # In each loop, We calculate cur[i], which represent the sum of Uniq() for all substrings whose last char is S.charAt(i).
    # For example,
    # S = 'ABCBD'
    # When i = 2, cur[2] = Uniq('ABC') + Uniq('BC') + Uniq('C')
    # When i = 3, cur[3] = Uniq('ABCB') + Uniq('BCB') + Uniq('CB') + Uniq('B')

    # Notice, we append char 'B' into each previous substrings. Only in substrings 'CB' and 'B', the char 'B' can be identified as uniq. 
    # The contribution of 'B' from cur[2] to cur[3] is i - showLastPosition['B']. At the same time, in substrings 'ABCB', 'BCB', 
    # the char 'B' can‘t’ be identified as uniq any more, the previous contribution of 'B' should be removed.

    # So we have'cur[i] = cur[i - 1] - contribution[S.charAt(i)] + (i - showLastPosition[S.charAt(i)])
    # Then the new contribution[S.charAt(i)] = i - showLastPosition[S.charAt(i)]

    # The final result is the sum of all cur[i].
    """
    def doit(self, S):
        """
        :type S: str
        :rtype: int
        """
        from collections import defaultdict
        MOD = 10**9 + 7
        last, second_last = defaultdict(int), defaultdict(int) # last(i) is last pos of char 'i' + 1, and then second_last last(last(i)) + 1
        psum = tsum = 0

        for i, c in enumerate(S):
            
            psum += 1  # current single one

            psum -= (last[c] - second_last[c]) # the substring included from secondlast[i] to last[i] will have double 'c'

            psum += (i - last[c]) # count substring from current one to last one

            if last[c] > 0:
                second_last[c] = last[c]
            
            last[c] = i+1

            tsum += psum

        return tsum % MOD


if __name__ == "__main__":

    res = UniqueLetterString().doit("ABC")