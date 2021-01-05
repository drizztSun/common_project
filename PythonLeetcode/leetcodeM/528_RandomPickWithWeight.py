"""
528. Random Pick with Weight

You are given an array of positive integers w where w[i] describes the weight of ith index (0-indexed).

We need to call the function pickIndex() which randomly returns an integer in the range [0, w.length - 1].
pickIndex() should return the integer proportional to its weight in the w array.

For example, for w = [1, 3], the probability of picking the index 0 is 1 / (1 + 3) = 0.25 (i.e 25%) while the probability of picking the index 1 is 3 / (1 + 3) = 0.75 (i.e 75%).

More formally, the probability of picking index i is w[i] / sum(w).



Example 1:

Input
["Solution","pickIndex"]
[[[1]],[]]
Output
[null,0]

Explanation
Solution solution = new Solution([1]);
solution.pickIndex(); // return 0. Since there is only one single element on the array the only option is to return the first element.
Example 2:

Input
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
Output
[null,1,1,1,1,0]

Explanation
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // return 1. It's returning the second element (index = 1) that has probability of 3/4.
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 0. It's returning the first element (index = 0) that has probability of 1/4.

Since this is a randomization problem, multiple answers are allowed so the following outputs can be considered correct :
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......
and so on.


Constraints:

1 <= w.length <= 10000
1 <= w[i] <= 10^5
pickIndex will be called at most 10000 times.

"""
import random
import bisect


class RandomPickWithWeight:

    def __init__(self, w):
        """
        :type w: List[int]
        """
        self.w = w
        for i in range(1, len(w)):
            self.w[i] += self.w[i - 1]

    def pickIndex(self):
        """
        :rtype: int
        """
        r = random.randint(1, self.w[-1])
        return bisect.bisect_left(self.w, r)


class RandomPickWithWeight:

    def __init__(self, w):
        """
        :type w: List[int]
        """
        self.prefix_sums = []
        prefix_sum = 0
        for weight in w:
            prefix_sum += weight
            self.prefix_sums.append(prefix_sum)
        self.total_sum = prefix_sum

    def pickIndex(self) -> int:
        """
        :rtype: int
        """
        target = self.total_sum * random.random()
        # run a linear search to find the target zone
        for i, prefix_sum in enumerate(self.prefix_sums):
            if target < prefix_sum:
                return i

"""
Approach 2: Prefix Sums with Binary Search
Intuition

As we promised before, we could improve the above approach by replacing the linear search with the binary search, which then can reduce the time complexity of the pickIndex() function from \mathcal{O}(N)O(N) to \mathcal{O}(\log{N})O(logN).

As a reminder, the condition to apply binary search on a list is that the list should be sorted, either in ascending or descending order. For the list of prefix sums that we search on, this condition is guaranteed, as we discussed before.

Algorithm

We could base our implementation largely on the previous approach. In fact, the only place we need to modify is the pickIndex() function, where we replace the linear search with the binary search.

As a reminder, there exist built-in functions of binary search in almost all programming languages. If one comes across this problem during the interview, it might be acceptable to use any of the built-in functions.

On the other hand, the interviewers might insist on implementing a binary search by hand. It would be good to prepare for this request as well.

There are several code patterns to implement a binary search algorithm, which we cover in the Explore card of Binary Search algorithm. One can refer to the card for more details.

Complexity Analysis

Let NN be the length of the input list.

Time Complexity

For the constructor function, the time complexity would be O(N), which is due to the construction of the prefix sums.

For the pickIndex() function, this time its time complexity would be O(logN), since we did a binary search on the prefix sums.

Space Complexity

For the constructor function, the space complexity remains \mathcal{O}(N)O(N), which is again due to the construction of the prefix sums.

For the pickIndex() function, its space complexity would be \mathcal{O}(1)O(1), since it uses constant memory. Note, here we consider the prefix sums that it operates on, as the input of the function.


"""

class RandomPickWithWeight:

    def __init__(self, w):
        """
        :type w: List[int]
        """
        self.prefix_sums = []
        prefix_sum = 0
        for weight in w:
            prefix_sum += weight
            self.prefix_sums.append(prefix_sum)
        self.total_sum = prefix_sum

    def pickIndex(self) -> int:
        """
        :rtype: int
        """
        target = self.total_sum * random.random()
        # run a binary search to find the target zone
        low, high = 0, len(self.prefix_sums)
        while low < high:
            mid = low + (high - low) // 2
            if target > self.prefix_sums[mid]:
                low = mid + 1
            else:
                high = mid
        return low