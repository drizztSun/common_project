# 466. Count The Repetitions

# Define S = [s,n] as the string S which consists of n connected strings s.
# For example, ["abc", 3] ="abcabcabc".

# On the other hand, we define that string s1 can be obtained from string s2
# if we can remove some characters from s2 such that it becomes s1.

# For example,
# 'abc' can be obtained from 'abdbec' based on our definition, but it can not be obtained from 'acbbe'

# You are given two non-empty strings s1 and s2 (each at most 100 characters long) and
# two integers 0  < n1 < 106 and 1 < n2 < 106.
# Now consider the strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2].
# Find the maximum integer M such that [S2,M] can be obtained from S1.

# Example:

# Input:
# s1="acb", n1=4
# s2="ab", n2=2

# Return:
# 2

"""

Approach #1 Brute force [Time Limit Exceeded]
Intuition

According to the question, we need to find mm such that [S2,m][S2,m] is the largest subsequence that can be found in S1S1.
S2S2 is essentially [s2,n2][s2,n2] and S1S1 is [s1,n1][s1,n1] and so, we can find the number of times s2s2 repeats in [s1,n1][s1,n1], say \text{repeat_count}.
And the number of times S2S2 repeats in S1S1 is therefore \text{(repeat_count/n2)}. Simple.

Algorithm

1) Initialize \text{index=0}index=0 and \text{repeat_count=0}. \text{index}index represents the current index in s2s2 to be checked against s1s1 and \text{repeat_count} represents the number of times s2s2 repeats in S1S1.
2) Iterate over the variable i from 0 to n1-1:
    Iterate over the variable jj from 00 to \text{size(s1)}-1size(s1)−1:
        If \text{s1[j] }s1[j]  is equal to \text{s2[index]}s2[index], increment \text{index}index.
        If indexindex is equal to size(s2)size(s2), this implies that s2s2 has completed one repartition and hence set \text{index=0}index=0 and increment the \text{repeat_count}.
3) Return \text{(repeat_count / n2)} since, S2 is {[s2,n2]}.

Complexity Analysis

Time complexity: O(n1*size(s1))O(n1∗size(s1)).
    We iterate over the entire length of string s1s1 for n1n1 times.
Space complexity: O(1)O(1) extra space for \text{index}index and \text{repeat_count}.



Approach #2 A better brute force [Accepted]
Intuition

In Approach #1, we simply checked for repetition over the entire [s1,n1][s1,n1]. However, n1n1 could be quiet large and thus, is inefficient to iterate over complete S1S1.
We can take advantage of the fact that s1s1 is repeating and hence, we could find a pattern of repetition of s2s2 in S1S1.
Once, we get the repetition pattern, we can easy calculate how many times the pattern repeats in n2n2 in O(1)O(1).

But what's the pattern!

In approach #1, we kept \text{index}index which tells the index to search in s2s2.
We try to see in the below illustration if this \text{index}index repeats itself after some fixed iterations of s1s1 or not and if so, then how can we leverage it.


After finding the repitition pattern, we can calculate the sum of repeating pattern, part before repitition and part left after repitition as the result in O(1)O(1).

But will this repitition always take place?

Yes! By Pigeonhole principle, which states that if nn items are put into mm containers, with n > mn>m, then at least one container must contain more than one item.
So, according to this, we are sure to find 2 same indexindex after scanning at max \text{size(s2)}size(s2) blocks of s1s1.

Algorithm

1) Intialize count=0 and index=0, which are same as in Approach #1.
2) Initialize 2 arrays, say indexr and countr of size (size(s2)+1), initialized with 0. The size (size(s2)+1) is based on the Pigeonhole principle as discussed above.
        The 2 arrays specifies the index and count at the start of each s1s1 block.
3) Iterate over i from 0 to n1-1:
        Iterate over j from 0 to size(s1)−1:

            If s1[j]==s2[index], increment index.
            If index is equal to size(s2), set index=0 and increment count.
        Set countr[i]=count and indexr[i]=index

        Iterate over k from 0 to i−1:

            If we find the repitition, i.e. current index=indexr[k], we calculate the count for block before the repitition starts,
            the repeating block and the block left after repitition pattern, which can be calculated as:
\begin{align} \text{prev_count} &= \text{countr}[k] \\ \text{pattern_count} &= (\text{countr}[i] - \text{countr}[k]) * \frac{n1 - 1 - k}{i - k} \\ \text{remain_count} &= \text{countr}\left[k + \left(n1 - 1 - k\right) \% \left(i - k \right)\right] - \text{countr}[k] \end{align}

            Sum the 3 counts and return the sum divided by n2n2, since \text{S2 = [s2,n2]}S2 = [s2,n2]

4) If no repetition is found, return countr[n1-1]/n2.

"""


class GetMaxRepetitions:

    def doit(self, s1, n1, s2, n2):
        """
        :type s1: str
        :type n1: int
        :type s2: str
        :type n2: int
        :rtype: int
        """
        start = {}
        s1_round, s2_round, s2_index = 0, 0, 0

        while s1_round < n1:

            s1_round += 1
            for c in s1:
                if c == s2[s2_index]:
                    s2_index += 1

                    if s2_index == len(s2):
                        s2_round += 1
                        s2_index = 0

            if s2_index in start:

                prev_s1_round, prev_s2_round = start[s2_index]

                circle_s1_round, circle_s2_round = s1_round - \
                    prev_s1_round, s2_round - prev_s2_round

                res = (n1 - prev_s1_round) / circle_s1_round * circle_s2_round

                left_s1_round = (
                    n1 - s1_round) % circle_s1_round + prev_s1_round

                for key, val in start.items():
                    if val[0] == left_s1_round:
                        res += val[1]
                        break

                return res / n2

            else:
                start[s2_index] = (s1_round, s2_round)

        return s2_round / n2


if __name__ == "__main__":

    res = GetMaxRepetitions().doit1("acb", 4, "ab", 2)

    pass
