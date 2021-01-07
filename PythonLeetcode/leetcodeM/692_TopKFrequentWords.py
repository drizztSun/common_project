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
from collections import Counter


class TopKFrequent:


    """
        Approach #1: Sorting [Accepted]
        Intuition and Algorithm

        Count the frequency of each word, and sort the words with a custom ordering relation that uses these frequencies. Then take the best k of them.

        Complexity Analysis

        Time Complexity: O(N \log{N})O(NlogN), where NN is the length of words. We count the frequency of each word in O(N)O(N) time, then we sort the given words in O(N \log{N})O(NlogN) time.

        Space Complexity: O(N)O(N), the space used to store our candidates.
    """
    def doit_sort(self, words, k):
        count = collections.Counter(words)
        candidates = count.keys()
        candidates.sort(key = lambda w: (-count[w], w))
        return candidates[:k]

    """
        Approach #2: Heap [Accepted]
        Intuition and Algorithm

        Count the frequency of each word, then add it to heap that stores the best k candidates. Here, "best" is defined with our custom ordering relation, 
        which puts the worst candidates at the top of the heap. At the end, we pop off the heap up to k times and reverse the result so that the best candidates are first.

        In Python, we instead use heapq.heapify, which can turn a list into a heap in linear time, simplifying our work.

        Complexity Analysis

        Time Complexity: O(N \log{k})O(Nlogk), where NN is the length of words. We count the frequency of each word in O(N)O(N) time, then we add NN words to the heap, each in O(\log {k})O(logk) time. 
        Finally, we pop from the heap up to kk times. As k \leq Nk≤N, this is O(N \log{k})O(Nlogk) in total.

        In Python, we improve this to O(N + k \log {N})O(N+klogN): our heapq.heapify operation and counting operations are O(N)O(N), and each of kk heapq.heappop operations are O(\log {N})O(logN).

        Space Complexity: O(N), the space used to store our count.
    """
    def topKFrequent(self, words, k):
        count = collections.Counter(words)
        heap = [(-freq, word) for word, freq in count.items()]
        heapq.heapify(heap)
        return [heapq.heappop(heap)[1] for _ in range(k)]

    #O(n*log(n))
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


