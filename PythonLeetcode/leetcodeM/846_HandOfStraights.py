"""
846. Hand of Straights

Alice has a hand of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size W, and consists of W consecutive cards.

Return true if and only if she can.

Note: This question is the same as 1296: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/

 

Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.

 

Constraints:

1 <= hand.length <= 10000
0 <= hand[i] <= 10^9
1 <= W <= hand.length
"""


class HandOfStraights:

    def doit_search(self, hand: list, W: int) -> bool:
        from collections import Counter
        from heapq import heapify, heappop, heappush
        if len(hand) % W != 0:
            return False
        
        heap = list(Counter(hand).items())
        heapify(heap)
                            
        for group in range(len(hand) // W):
            lastVal = None
            duplicates = []
            for i in range(W):
                if not heap:
                    return False
                nextVal = heappop(heap)
                if lastVal is not None and nextVal[0] != lastVal + 1:
                    return False
                if nextVal[1] > 1:
                    duplicates.append((nextVal[0], nextVal[1] - 1))
                lastVal = nextVal[0]

            for d in duplicates:
                heappush(heap, d)
        
        return True

    """
        Approach #1: Brute Force [Accepted]
        Intuition

        We will repeatedly try to form a group (of size W) starting with the lowest card. This works because the lowest card still in our hand must be the bottom end of a size W straight.

        Algorithm

        Let's keep a count {card: number of copies of card} as a TreeMap (or dict).

        Then, repeatedly we will do the following steps: find the lowest value card that has 1 or more copies (say with value x), 
        and try to remove x, x+1, x+2, ..., x+W-1 from our count. If we can't, then the task is impossible.

        Complexity Analysis

        Time Complexity: O(N∗(N/W)), where N is the length of hand. The (N/W) factor comes from min(count). 
        In Java, the (N/W) factor becomes logN due to the complexity of TreeMap.

        Space Complexity: O(N).
    """
    def doit_search(self, hand: list, W: int) -> bool:

        if len(hand) % W != 0:
            return False

        cnt = {}
        for c in hand:
            cnt[c] = cnt.get(c, 0) + 1

        while cnt:
            c = min(cnt)
            for i in range(c, c + W):
                if cnt.get(i, 0) == 0:
                    return False
                cnt[i] -= 1
                if cnt[i] == 0:
                    del cnt[i]

        return True
        