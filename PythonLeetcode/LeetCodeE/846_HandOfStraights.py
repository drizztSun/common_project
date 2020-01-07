# 846. Hand of Straights

# Alice has a hand of cards, given as an array of integers.

# Now she wants to rearrange the cards into groups so that each group is size W, and consists of W consecutive cards.

# Return true if and only if she can.


# Example 1:

# Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
# Output: true
# Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
# Example 2:

# Input: hand = [1,2,3,4,5], W = 4
# Output: false
# Explanation: Alice's hand can't be rearranged into groups of 4.


# Note:

# 1 <= hand.length <= 10000
# 0 <= hand[i] <= 10^9
# 1 <= W <= hand.length

class IsNStraightHand:

    """
    Approach #1: Brute Force [Accepted]
    Intuition

    We will repeatedly try to form a group (of size W) starting with the lowest card. This works because the lowest card still in our hand must be the bottom end of a size W straight.

    Algorithm

    Let's keep a count {card: number of copies of card} as a TreeMap (or dict).

    Then, repeatedly we will do the following steps: find the lowest value card that has 1 or more copies (say with value x), and try to remove x, x+1, x+2, ..., x+W-1 from our count.
    If we can't, then the task is impossible.

    Complexity Analysis

    Time Complexity: O(N∗(N/W)), where NN is the length of hand. The (N/W) factor comes from min(count).
    In Java, the (N/W) factor becomes \log NlogN due to the complexity of TreeMap.

    Space Complexity: O(N).
    """

    def doit(self, hand, W):

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

    def doit(self, hand, W):
        import collections
        if len(hand) % W != 0:
            return False

        if W == 1:
            return True

        cnt = collections.Counter(hand)
        values = list(cnt)
        values.sort()

        tally = collections.deque([0 for _ in range(W - 1)])
        tally.append(cnt[values[0]])
        for i in range(1, len(values)):
            carry = tally.popleft()
            tally.append(cnt[values[i]] - cnt[values[i - 1]] + carry)
            if tally[-1] == 0 and (values[i] - values[i - 1] != 1):
                return False
        return True if tally[-1] == 0 else False

    """
    Step One: Sort the array (nlogn)
    Step Two: Use two pointer : O(1)
    empty_index -> refers to the first array that was not full
    next_index -> refers to the next array that was not full
    Step Three: determine whether all the arrays are full or not
    """

    def doit(self, hand, W):
        """
        :type hand: List[int]
        :type W: int
        :rtype: bool
        """
        hand.sort()
        result = [[]]

        empty_index = 0
        if W == 1:
            return True

        for height in hand:
            if not result[empty_index]:
                # it is the row in the result
                result[empty_index].append(height)
                next_index = empty_index + 1
            elif result[empty_index][-1] == height - 1:
                result[empty_index].append(height)
                next_index = empty_index + 1
                if len(result[empty_index]) == W:
                    empty_index += 1
                    if empty_index == len(result):
                        result.append([])
            elif next_index < len(result) and result[next_index][-1] == height - 1:
                result[next_index].append(height)
                next_index += 1
            else:
                result.append([])
                result[-1].append(height)

        return empty_index == len(result) or not result[empty_index]

    def doit(self, hand, W):
        from collections import Counter
        import heapq
        if len(hand) % W != 0:
            return False

        heap = list(Counter(hand).items())
        heapq.heapify(heap)

        for group in range(len(hand) // W):
            lastVal = None
            duplicates = []

            for i in range(W):
                if not heap:
                    return False

                nextVal = heapq.heappop(heap)
                if lastVal is not None and nextVal[0] != lastVal + 1:
                    return False

                if nextVal[1] > 1:
                    duplicates.append((nextVal[0], nextVal[1] - 1))

                lastVal = nextVal[0]

            for d in duplicates:
                heapq.heappush(heap, d)

        return True


if __name__ == '__main__':

    res = IsNStraightHand().doit(hand=[1, 2, 3, 6, 2, 3, 4, 7, 8], W=3)

    pass
