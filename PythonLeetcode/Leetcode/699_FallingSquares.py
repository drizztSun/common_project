"""
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

"""
import bisect


class FallingSquares:

    def fallingSquares(self, positions):
        import bisect

        heights = [0, 0] 
        axis = [0, float('inf')]
        res = [0]

        for start, high in positions:

            pos1 = bisect.bisect_right(axis, start)
            pos2 = bisect.bisect_left(axis, start + high)

            new_h= max(heights[pos1-1:pos2]) + high
            axis[pos1: pos2] = [start, start + high]

            heights[pos1: pos2] = [new_h, heights[pos2 - 1]] 
            res.append(max(res[-1], new_h)) 

        return res[1:]


    def doit_segmenttree(self, positions):
        """
        :type positions: List[List[int]]
        :rtype: List[int]
        """
        # compress positions into consecutive indices
        all_pos = set()
        for p in positions:
            all_pos.add(p[0])
            all_pos.add(p[0] + p[1])
        
        pos_ind = {}
        for i, pos in enumerate(sorted(all_pos)):
            pos_ind[pos] = i
        
        n = len(pos_ind)
        segtree = [0] * (4 * n)
        lazy = [0] * (4 * n)
        
        def _insert(left, right, h, root, start, end):
            if lazy[root] != 0:
                if start != end:
                    lazy[root*2] = max(lazy[root*2], lazy[root])
                    lazy[root*2 + 1] = max(lazy[root*2+1], lazy[root])
                segtree[root] = max(segtree[root], lazy[root])
                lazy[root] = 0          
            
            if left > end or right < start:
                return
            
            if start == end:
                segtree[root] = max(segtree[root], h)
                return 
            
            if left <= start and right >= end:
                segtree[root] = max(segtree[root], h)
                lazy[root*2] = max(lazy[root*2], h)
                lazy[root*2 + 1] = max(lazy[root*2+1], h)
                return
            
            mid = (start + end) // 2
            _insert(left, right, h, root*2, start, mid)
            _insert(left, right, h, root*2 + 1, mid + 1, end)
            segtree[root] = max(segtree[2*root], segtree[2*root + 1], h)
            return
        
        def _query(left, right, root, start, end):
            if lazy[root] != 0:
                if start != end:
                    lazy[root*2] = max(lazy[root*2], lazy[root])
                    lazy[root*2 + 1] = max(lazy[root*2+1], lazy[root])
                segtree[root] = max(segtree[root], lazy[root])
                lazy[root] = 0
                
            if left > end or right < start:
                return 0
            
            if start == end: 
                return segtree[root]
            
            if left <= start and right >= end:
                return segtree[root]
            
            mid = (start + end) // 2
            return max(_query(left, right, root*2, start, mid), _query(left, right, root*2+1, mid + 1, end))
        
        def insert(left, right, h):
            _insert(left, right, h, 1, 0, n-1)
        
        def query(left, right):
            return _query(left, right, 1, 0, n-1)
        
        res = []
        accu_max = 0
        for p in positions:
            left_raw, h = p
            right_raw = left_raw + h
            left = pos_ind[left_raw]
            right = pos_ind[right_raw] - 1
            cur_max = query(left, right)
            new_max = cur_max + h
            accu_max = max(accu_max, new_max)
            res.append(accu_max)
            insert(left, right, new_max)
        return res

    """
    Approach 4: Segment Tree with Lazy Propagation
    Intuition

    If we were familiar with the idea of a segment tree (which supports queries and updates on intervals), we can immediately crack the problem.

    Algorithm

    Segment trees work by breaking intervals into a disjoint sum of component intervals, whose number is at most log(width).
    The motivation is that when we change an element, we only need to change log(width) many intervals that aggregate on an interval containing that element.

    When we want to update an interval all at once, we need to use lazy propagation to ensure good run-time complexity. This topic is covered in more depth here.

    With such an implementation in hand, the problem falls out immediately.

    Complexity Analysis

    Time Complexity: O(NlogN), where NN is the length of positions. This is the run-time complexity of using a segment tree.

    Space Complexity: O(N), the space used by our tree.
    """
    class SegmentTree(object):
        def __init__(self, N, update_fn, query_fn):
            self.N = N
            self.H = 1
            while 1 << self.H < N:
                self.H += 1

            self.update_fn = update_fn
            self.query_fn = query_fn
            self.tree = [0] * (2 * N)
            self.lazy = [0] * N

        def _apply(self, x, val):
            self.tree[x] = self.update_fn(self.tree[x], val)
            if x < self.N:
                self.lazy[x] = self.update_fn(self.lazy[x], val)

        def _pull(self, x):
            while x > 1:
                x /= 2
                self.tree[x] = self.query_fn(self.tree[x * 2], self.tree[x * 2 + 1])
                self.tree[x] = self.update_fn(self.tree[x], self.lazy[x])

        def _push(self, x):
            for h in range(self.H, 0, -1):
                y = x >> h
                if self.lazy[y]:
                    self._apply(y * 2, self.lazy[y])
                    self._apply(y * 2 + 1, self.lazy[y])
                    self.lazy[y] = 0

        def update(self, L, R, h):
            L += self.N
            R += self.N
            L0, R0 = L, R
            while L <= R:
                if L & 1:
                    self._apply(L, h)
                    L += 1
                if R & 1 == 0:
                    self._apply(R, h)
                    R -= 1
                L /= 2
                R /= 2
            self._pull(L0)
            self._pull(R0)

        def query(self, L, R):
            L += self.N
            R += self.N
            self._push(L)
            self._push(R)
            ans = 0
            while L <= R:
                if L & 1:
                    ans = self.query_fn(ans, self.tree[L])
                    L += 1
                if R & 1 == 0:
                    ans = self.query_fn(ans, self.tree[R])
                    R -= 1
                L /= 2
                R /= 2
            return ans

        def doit_segement_tree(self, positions):
            # Coordinate compression
            # index = ...

            tree = FallingSquares.SegmentTree(len(index), max, max)
            best = 0
            ans = []
            for left, size in positions:
                L, R = index[left], index[left + size - 1]
                h = tree.query(L, R) + size
                tree.update(L, R, h)
                best = max(best, h)
                ans.append(best)

            return ans

    """
        Approach 3: Block (Square Root) Decomposition
    Intuition

    Whenever we perform operations (like update and query) on some interval in a domain, we could segment that domain with size WW into blocks of size \sqrt{W}
    W
    ​
     .

    Then, instead of a typical brute force where we update our array heights representing the board, we will also hold another array blocks, where blocks[i] represents the B = \lfloor \sqrt{W} \rfloorB=⌊
    W
    ​
     ⌋ elements heights[B*i], heights[B*i + 1], ..., heights[B*i + B-1]. This allows us to write to the array in O(B)O(B) operations.

    Algorithm

    Let's get into the details. We actually need another array, blocks_read. When we update some element i in block b = i / B, we'll also update blocks_read[b]. If later we want to read the entire block, we can read from here (and stuff written to the whole block in blocks[b].)

    When we write to a block, we'll write in blocks[b]. Later, when we want to read from an element i in block b = i / B, we'll read from heights[i] and blocks[b].

    Our process for managing query and update will be similar. While left isn't a multiple of B, we'll proceed with a brute-force-like approach, and similarly for right. At the end, [left, right+1) will represent a series of contiguous blocks: the interval will have length which is a multiple of B, and left will also be a multiple of B.

    Complexity Analysis

    Time Complexity: O(N\sqrt{N})O(N
    N
    ​
     ), where NN is the length of positions. Each query and update has complexity O(\sqrt{N})O(
    N
    ​
     ).

    Space Complexity: O(N)O(N), the space used by heights.

    """
    def doit_1(self, positions):
        #Coordinate compression
        #index = ...

        W = len(index)
        B = int(W**.5)
        heights = [0] * W
        blocks = [0] * (B+2)
        blocks_read = [0] * (B+2)

        def query(left, right):
            ans = 0
            while left % B and left <= right:
                ans = max(ans, heights[left], blocks[left / B])
                left += 1
            while right % B != B-1 and left <= right:
                ans = max(ans, heights[right], blocks[right / B])
                right -= 1
            while left <= right:
                ans = max(ans, blocks[left / B], blocks_read[left / B])
                left += B
            return ans

        def update(left, right, h):
            while left % B and left <= right:
                heights[left] = max(heights[left], h)
                blocks_read[left / B] = max(blocks_read[left / B], h)
                left += 1
            while right % B != B-1 and left <= right:
                heights[right] = max(heights[right], h)
                blocks_read[right / B] = max(blocks_read[right / B], h)
                right -= 1
            while left <= right:
                blocks[left / B] = max(blocks[left / B], h)
                left += B

        best = 0
        ans = []
        for left, size in positions:
            L = index[left]
            R = index[left + size - 1]
            h = query(L, R) + size
            update(L, R, h)
            best = max(best, h)
            ans.append(best)

        return ans


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

    res = FallingSquares().doit([[4,9],[8,8],[6,8],[8,2],[1,2]])

    res = FallingSquares().doit([[1, 2], [2, 3], [6, 1]])

    res = FallingSquares().doit([[100, 100], [200, 100]])

    pass


