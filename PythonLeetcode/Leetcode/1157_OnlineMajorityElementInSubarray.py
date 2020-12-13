"""
1157. Online Majority Element In Subarray

Implementing the class MajorityChecker, which has the following API:

MajorityChecker(int[] arr) constructs an instance of MajorityChecker with the given array arr;
int query(int left, int right, int threshold) has arguments such that:
0 <= left <= right < arr.length representing a subarray of arr;
2 * threshold > right - left + 1, ie. the threshold is always a strict majority of the length of the subarray
Each query(...) returns the element in arr[left], arr[left+1], ..., arr[right] that occurs at least threshold times, or -1 if no such element exists.



Example:

MajorityChecker majorityChecker = new MajorityChecker([1,1,2,2,1,1]);
majorityChecker.query(0,5,4); // returns 1
majorityChecker.query(0,3,3); // returns -1
majorityChecker.query(2,3,2); // returns 2


Constraints:

1 <= arr.length <= 20000
1 <= arr[i] <= 20000
For each query, 0 <= left <= right < len(arr)
For each query, 2 * threshold > right - left + 1
The number of queries is at most 10000




"""
from collections import defaultdict, Counter
from copy import deepcopy
from bisect import bisect_left, bisect_right


class MajorityChecker:

    def __init__(self, arr):

        # key   : number
        # value : list of indices for number
        self.num_idx_dict = defaultdict(list)

        # Append index to corresoinding number's dictionary
        for idx, number in enumerate(arr):
            self.num_idx_dict[number].append(idx)

        # With descending order of number of occurrences
        self.candidates = sorted(self.num_idx_dict, key=lambda x: len(self.num_idx_dict[x]), reverse=True)

    def query(self, left, right, threshold):

        for number in self.candidates:

            # Longest occurrences is smaller than threhsold, then no solution
            if len(self.num_idx_dict[number]) < threshold:
                return -1

            left_idx = bisect_left(self.num_idx_dict[number], left)
            right_idx = bisect_right(self.num_idx_dict[number], right)

            if right_idx - left_idx >= threshold:
                return number

        return -1


class Node(object):
    '''
    Node of the segment tree.

    self.val = [i,j] where i and j are lower and upper bound indices in array (arr)
    self.count = Counter(arr[i:j+1])  <-- keeps track of the frequency of each value in the range [i,j] inclusive
    '''

    def __init__(self, val):
        self.val = val
        self.count = None


class Segment_Tree(object):
    def __init__(self, arr):
        self.arr = arr
        self.root = self.build(0, len(arr) - 1)

    def build(self, i, j):
        '''
        constructs segment tree where each node has:

            1. a value of the index range [i,j] (inclusive) that it covers
            2. a counter for how many times each number appears in the range [i,j]j

        *Note, self.root will look like:

            self.root.val = [0, len(arr) - 1]
            self.root.count = Counter(arr)
        '''

        if i == j:
            node = Node([i, i])
            node.count = Counter([self.arr[i]])
            return node

        node = Node([i, j])
        k = (i + j) >> 1
        node.left = self.build(i, k)
        node.right = self.build(k + 1, j)

        node.count = node.left.count + node.right.count

        return node

    def find_most_common(self, l, r, threshold):
        '''
        returns a tuple of (most common element, frequency) in the range l, r
        where 0 <= l <= r < self.arr.length

        This is done as a subtraction process:

            1. res = self.root.count.copy()  <-- equivalent to Counter(arr)
            2. subtract values from res for ranges that are not included in l, r
            3. During this process, if the most frequent value in res ever occurs
               less than treshold times, then trigger the sentinel to quit out
            4. If a range [i,j] on the tree is completely contained within [l,r] inclusive
               then do not subtract the values in A[i:j+1] from the result
        '''

        res = self.root.count.copy()

        sentinel = False  # 3

        def helper(node):
            nonlocal res, l, r, sentinel, threshold

            if sentinel: return None  # 3

            if (not res) or max(res.values()) < threshold:  # 3
                # there is no solution so set res = {} and escape recursive function
                sentinel = True
                res = {}
                return None

            i, j = node.val
            if (j < l) or (i > r):  # 2
                # this node has only values that are OUTSIDE of [left,right] so subtract them from res
                res -= node.count
                return None

            if (l <= i) and (j <= r):  # 4
                # this node has only values that are INSIDE of [left,right] so keep the values
                return None

            helper(node.left)
            helper(node.right)

        helper(self.root)
        most_common = max(res, key=lambda k: res[k]) if res else (-1, -1)

        return (most_common, res[most_common]) if res else most_common


class MajorityCheckerSegmentTree:

    def __init__(self, arr: list:
        self.tree = Segment_Tree(arr)

    def query(self, left: int, right: int, threshold: int) -> int:
        # Find the value (val) that occurs the most frequently in range [left,right]
        val, freq = self.tree.find_most_common(left, right, threshold)
        return val if freq >= threshold else -1


class MajorityCheckerTLE:

    def __init__(self, arr: list):

        tmp = defaultdict(int)
        self._buff = [deepcopy(tmp)]

        for c in arr:
            tmp[c] += 1
            self._buff.append(deepcopy(tmp))

    def query(self, left: int, right: int, threshold: int) -> int:

        for k, v in self._buff[right + 1].items():
            if v - self._buff[left][k] >= threshold:
                return k

        return -1


if __name__ == '__main__':

    obj = MajorityChecker([1,1,2,2,1,1])
    obj.query(0, 5, 4)
    obj.query(0, 3, 3)
    obj.query(2, 3, 2)