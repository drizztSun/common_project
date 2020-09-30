"""
692. Top K Frequent Words

Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.
"""


class TopKFrequent:

    def doit_sort(self, words, k: int):
        from collections import Counter
        return [c[0] for c in sorted(Counter(words).items(), key=lambda x: (-x[1], x[0]))][:k]

    def doit(self, words, k, ):
        from collections import Counter
        cnt = Counter(words)
        items = sorted(cnt.items(), key=lambda x: (-x[1], x[0]))[:k]
        return [c[0] for c in items]

    def doit_heap(self, words, k):
        from collections import Counter
        from heapq import heapify, heappop
        cnt = Counter(words)
        items = [(-c[1], c[0]) for c in cnt.items()]
        heapify(items)
        res = []
        while k > 0:
            res.append(heappop(items)[1])
            k -= 1
        return res


