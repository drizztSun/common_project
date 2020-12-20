"""
1163. Last Substring in Lexicographical Order

Given a string s, return the last substring of s in lexicographical order.



Example 1:

Input: "abab"
Output: "bab"
Explanation: The substrings are ["a", "ab", "aba", "abab", "b", "ba", "bab"]. The lexicographically maximum substring is "bab".
Example 2:

Input: "leetcode"
Output: "tcode"


Note:

1 <= s.length <= 4 * 10^5
s contains only lowercase English letters.


"""


class LastSubstringInOrder:

    """
    The goal is to find the last substring if all substrings were sorted in lexographical order.

    Lexographical Order

    1. a < b because a comes before b in alphabet
    2. if two substringss1 and s2 have the same character in the same position, the next characters in the substrings used for comparison
    3. if s1 is shorter than s2 and all the characters in s1 are in s2 , then s2 comes first s1 = aab, s2 = aaba then lexo order is s1, s2

    Key Observations

    1. The last substring in lexographical order will be a suffix of the original string. This is because of the rules of lexographical ordering.
    2. The last occurence of the largest character (z being largest possible character),is the starting point of the desired substring (last substring in lexographical order) .
    3. To get the resultant substring, take all characters from the starting point (inclusive) to the end of the orignal string. This is possible because the substring will always be a suffix as stated in point 1

    To find the last occurrence of the largest character (the starting point of the desired suffix) , a two pointer approach with an offset can be used

    below is a visual walkthrough of the approach (view along with code at bottom for better understanding)


    """

    def doit_twopointer(self, s: str) -> str:
        # k is an offset
        i, j, k = 0, 1, 0
        while i + k < len(s) and j + k < len(s):

            # s[i:..i+k]  s[j:..j+k]
            # when same largest char occurs think cacacb
            if s[i + k] == s[j + k]:
                # Here are two total equal sequence, keep adding one
                # Anything between i < p < i+k, will have s[i] > s[p]. because j scan from that part either,
                # if s[i] < s[p], i has to move forward.
                k += 1
            else:
                # ensure correct order
                # if current s[i+k] != s[j+k], we need to move smaller one, and keep bigger one.
                # the longest sequence should be 0.
                # why we need to move j or i + (k+1), not 1
                # because, we already know s[i+p] == s[j+p], if 1<= p < k, so we are gonna get the same situation, they will failed on s[i+k] != s[j+k] again.
                # so we skip and continue to find point, starting on k+1 offset.
                if s[i + k] < s[j + k]:
                    i += k + 1
                else:
                    j += k + 1

                if i == j: j += 1
                k = 0

        return s[i:]


    """
    The solution must be in one of those n suffix candidates, and the main idea here is to eliminate those candidates we are certain not the solution,
    at last, the only one left is our solution.

    Given i < j, assuming that for any p < j and p != i, s[p:] is smaller than the maximum substring (not the solution).

    For j = i+d, where d >= 1, and k >= 0, considering for any 0 <= x < k, s[i+x] == s[j+x], we have several cases to discuss.

    s[i+k] == s[j+k], we simply k++;

    s[i+k] > s[j+k], for any 0 <= p0 <= k, we have substring s[j+p0:] < s[i+p0:] = s[j-d+p0:] = s[j+p1:] < s[i+p1:] = ... and so on,
    where we have p0 = p1+d > p1 > p2...until j+pn < j, in other words s[j+p0:] < s[p:] for some p where i <= p < j,
    therefore s[j+p0:] will not be the solution, we can safely update j toj+k+1 while still holding our assumption for any p < j and p != i,
    s[p:] is not the solution;


    s[i+k] < s[j+k], for any 0 <= p0 <= k, we have substring s[i+p0:] < s[j+p0:] = s[i+d+p0:] = s[i+p1:] < s[j+p1:] = ... and so on,
    where we have p0 = p1-d < p1 < p2... until i+pn > i+k, in other words s[i+p0:] < s[p:] for some p where p > i+k,
    therefore s[i+p0:] will not be our solution, we can safely update i to max(i+k+1, j) and then update j to i+1 while holding our assumption;


    In addition, we take into account the base case where i+1 == j, and i == 0, our assumption holds by itself.

    In the end, we can regard s[j+k] == "" as a empty character when j+k == n, which falls into case two s[i+k] > s[j+k] in our discussion above,
    therefore eliminating all candidates from j to j+k, leaving the only one s[i:], hence our solution.


    """
    def doit_(self, s: str) -> str:

        pass


if __name__ == '__main__':

    LastSubstringInOrder().doit_twopointer("cacacb")

    LastSubstringInOrder().doit_twopointer("cazcazgfe")

    LastSubstringInOrder().doit_twopointer("cazzzcazgfe")










