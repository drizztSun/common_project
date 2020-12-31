"""
340 Longest Sub String With At Most K Distinct Characters

Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.


Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.
Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.


Constraints:

1 <= s.length <= 5 * 104
0 <= k <= 50

"""


class KthDistinctChar:

    def doit_slidingwindow(self, s, k):
        """
        type: str
        type: int
        rtype: int
        """
        # j is front pointer, i is back pointer
        counter = [0] * 256
        i = numChars = 0
        best = 0

        for j in range(len(s)):

            if counter[ord(s[j])] == 0:
                numChars += 1

            counter[ord(s[j])] += 1

            while i < len(s) and numChars > k:
                counter[ord(s[i])] -= 1
                if counter[ord(s[i])] == 0:
                    numChars -= 1
                i += 1

            best = max(best, j - i + 1)

        return best

    def doit_1(self, s, k):
        """
        type: str
        type: int
        rtype: int
        """
        from collections import defaultdict
        n = len(s)
        if k == 0 or n == 0:
            return 0

        # sliding window left and right pointers
        left, right = 0, 0
        # hashmap character -> its rightmost position
        # in the sliding window
        hashmap = defaultdict()
        max_len = 1

        while right < n:
            # add new character and move right pointer
            hashmap[s[right]] = right
            right += 1

            # slidewindow contains 3 characters
            if len(hashmap) == k + 1:
                # delete the leftmost character
                del_idx = min(hashmap.values())
                del hashmap[s[del_idx]]
                # move left pointer of the slidewindow
                left = del_idx + 1

            max_len = max(max_len, right - left)

        return max_len

    def doit_2(self, s: 'str', k: 'int') -> 'int':
        from collections import OrderedDict
        n = len(s)
        if k == 0 or n == 0:
            return 0

        # sliding window left and right pointers
        left, right = 0, 0
        # hashmap character -> its rightmost position
        # in the sliding window
        hashmap = OrderedDict()

        max_len = 1

        while right < n:
            character = s[right]
            # if character is already in the hashmap -
            # delete it, so that after insert it becomes
            # the rightmost element in the hashmap
            if character in hashmap:
                del hashmap[character]
            hashmap[character] = right
            right += 1

            # slidewindow contains k + 1 characters
            if len(hashmap) == k + 1:
                # delete the leftmost character
                _, del_idx = hashmap.popitem(last=False)
                # move left pointer of the slidewindow
                left = del_idx + 1

            max_len = max(max_len, right - left)

        return max_len


if __name__ == "__main__":

    res = KthDistinctChar().doit("eceba", 2)