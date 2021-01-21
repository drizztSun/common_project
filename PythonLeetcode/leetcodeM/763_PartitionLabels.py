"""
763. Partition Labels


A string S of lowercase English letters is given. 
We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

 

Example 1:

Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
 

Note:

S will have length in range [1, 500].
S will consist of lowercase English letters ('a' to 'z') only.


"""


class PartitionLabels:

    """
        O(n*log(n))
    """
    def doit_sort(self, S: str) -> list:
        
        letter_range = {}
        for i in range(len(S)):
            if S[i] not in letter_range:
                letter_range[S[i]] = [i, i]
            else:
                letter_range[S[i]][1] = i

        vals = [c for c in letter_range.values()]
        vals.sort(key=lambda a: a[0])

        res = []
        s, e = vals[0]
        for i, v in enumerate(vals):
            if v[0] > e:
                res.append((s, e))
                s, e = v[0], v[1]
            elif v[1] > e:
                e = v[1]

            if i == len(vals) - 1:
                res.append((s, e))

        return [e - s + 1 for s, e in res]

    """
        Approach 1: Greedy
        Intuition

        Let's try to repeatedly choose the smallest left-justified partition. Consider the first label, say it's 'a'. The first partition must include it, and also the last occurrence of 'a'. 
        However, between those two occurrences of 'a', there could be other labels that make the minimum size of this partition bigger. 
        For example, in "abccaddbeffe", the minimum first partition is "abccaddb". 
        
        This gives us the idea for the algorithm: For each letter encountered, process the last occurrence of that letter, extending the current partition [anchor, j] appropriately.

        Algorithm

        We need an array last[char] -> index of S where char occurs last. Then, let anchor and j be the start and end of the current partition. 
        If we are at a label that occurs last at some index after j, we'll extend the partition j = last[c]. 
        If we are at the end of the partition (i == j) then we'll append a partition size to our answer, and set the start of our new partition to i+1.


        Complexity Analysis

        Time Complexity: O(N), where NN is the length of SS.

        Space Complexity: O(1) to keep data structure last of not more than 26 characters.
    """
    def doit_greedy(self, S):
        last = {c: i for i, c in enumerate(S)}
        j = anchor = 0
        ans = []
        for i, c in enumerate(S):
            j = max(j, last[c])
            if i == j:
                ans.append(i - anchor + 1)
                anchor = i + 1
            
        return ans