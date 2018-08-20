# 699. Falling Squares

# On an infinite number line (x-axis), we drop given squares in the order they are given.

# The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point
# being positions[i][0] and sidelength positions[i][1].

# The square is dropped with the bottom edge parallel to the number line, and from a higher height than
# all currently landed squares. We wait for each square to stick before dropping the next.

# The squares are infinitely sticky on their bottom edge, and will remain fixed to any positive length surface
# they touch (either the number line or another square).
# Squares dropped adjacent to each other will not stick together prematurely.


# Return a list ans of heights. Each height ans[i] represents the current highest height of any square we have dropped,
# after dropping squares represented by positions[0], positions[1], ..., positions[i].

# Example 1:
# Input: [[1, 2], [2, 3], [6, 1]]
# Output: [2, 5, 5]
# Explanation:

# After the first drop of positions[0] = [1, 2]:
# _aa
# _aa
# -------
# The maximum height of any square is 2.


# After the second drop of positions[1] = [2, 3]:
# __aaa
# __aaa
# __aaa
# _aa__
# _aa__
# --------------
# The maximum height of any square is 5.  
# The larger square stays on top of the smaller square despite where its center
# of gravity is, because squares are infinitely sticky on their bottom edge.


# After the third drop of positions[1] = [6, 1]:
# __aaa
# __aaa
# __aaa
# _aa
# _aa___a
# --------------
# The maximum height of any square is still 5.

# Thus, we return an answer of [2, 5, 5].


# Example 2:
# Input: [[100, 100], [200, 100]]
# Output: [100, 100]
# Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.

# Note:

# 1 <= positions.length <= 1000.
# 1 <= positions[i][0] <= 10^8.
# 1 <= positions[i][1] <= 10^6.


import bisect

class FallingSquares:

    def doit1(self, positions):
        """
        :type positions: List[List[int]]
        :rtype: List[int]
        """
        heights = {}
        ans = []

        for left, side in positions:

            right = left + side

            nearby = [h for h in heights.keys() if not (h[0] >= right or h[1] <= left)]

            if len(nearby) > 0:
                h = max(heights[s] for s in nearby) + side
            else:
                h = side

            heights[(left, right)] = h

            if len(ans) == 0:
                ans.append(h)
            else:
                ans.append(max(ans[-1], h))

        return ans

    def doit(self, positions):
        """
        :type positions: List[List[int]]
        :rtype: List[int]
        """
        import bisect

        pos = [0]
        heights = [0]
        res = []
        max_h = 0

        for left, side in positions:

            i = bisect.bisect_right(pos, left)
            j = bisect.bisect_left(pos, left + side)

            h = max(heights[i - 1:j] or [0]) + side

            pos[i:j] = [left, left + side]
            heights[i:j] = [h, heights[j - 1]]

            max_h = max(max_h, h)
            res.append(max_h)

        return res


if __name__ == "__main__":

    res = FallingSquares().doit([[1, 2], [2, 3], [6, 1]])

    res = FallingSquares().doit([[100, 100], [200, 100]])

    pass


