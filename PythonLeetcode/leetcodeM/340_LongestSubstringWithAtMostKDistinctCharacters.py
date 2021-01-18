"""
340. Longest Substring with At Most K Distinct Characters


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


class LengthOfLongestSubstringKDistinct:

    def doit_slidingwindow(self, s: str, k: int) -> int:

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

    """
            Approach 2: Sliding Window + Ordered Dictionary.
        How to achieve \mathcal{O}(N)O(N) time complexity

        Approach 1 with a standard hashmap couldn't ensure \mathcal{O}(N)O(N) time complexity.

        To have \mathcal{O}(N)O(N) algorithm performance, one would need a structure, which provides four operations in \mathcal{O}(1)O(1) time :

        Insert the key

        Get the key and check if the key exists

        Delete the key

        Return the first or last added key/ value

        The first three operations in \mathcal{O}(1)O(1) time are provided by the standard hashmap, and the forth one - by linked list.

        There is a structure called ordered dictionary, it combines behind both hashmap and linked list. In Python this structure is called OrderedDict and in Java LinkedHashMap.

        Ordered dictionary is quite popular for interviews. for example, check out the Implementing a LRU Cache question by Google.

        Algorithm

        Let's use ordered dictionary instead of standard hashmap to trim the algorithm from approach 1 :

        Return 0 if the string is empty or k is equal to zero.
        Set both pointers to the beginning of the string left = 0 and right = 0 and initialize max substring length max_len = 1.
        While right pointer is less than N:
        If the current character s[right] is already in the ordered dictionary hashmap -- delete it, to ensure that the first key in hashmap is the leftmost character.
        Add the current character s[right] in the ordered dictionary and move right pointer to the right.
        If ordered dictionary hashmap contains k + 1 distinct characters, remove the leftmost one and move the left pointer so that sliding window contains again k distinct characters only.
        Update max_len.
        Implementation

        Complexity Analysis

        Time complexity : O(N) since all operations with ordered dictionary : insert/get/delete/popitem (put/containsKey/remove) are done in a constant time.

        Space complexity : O(k) since additional space is used only for an ordered dictionary with at most k + 1 elements.
    """

    def doit_slidingwindow(self, s: str, k: int) -> int:
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
                _, del_idx = hashmap.popitem(last = False)
                # move left pointer of the slidewindow
                left = del_idx + 1

            max_len = max(max_len, right - left)

        return max_len