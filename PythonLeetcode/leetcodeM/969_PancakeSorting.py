"""
# 969. Pancake Sorting

# Given an array A, we can perform a pancake flip: We choose some positive integer k <= A.length,
# then reverse the order of the first k elements of A.
# We want to perform zero or more pancake flips (doing them one after another in succession) to sort the array A.

# Return the k-values corresponding to a sequence of pancake flips that sort A.
# Any valid answer that sorts the array within 10 * A.length flips will be judged as correct.


# Example 1:

# Input: [3,2,4,1]
# Output: [4,2,4,3]
# Explanation:
# We perform 4 pancake flips, with k values 4, 2, 4, and 3.
# Starting state: A = [3, 2, 4, 1]
# After 1st flip (k=4): A = [1, 4, 2, 3]
# After 2nd flip (k=2): A = [4, 1, 2, 3]
# After 3rd flip (k=4): A = [3, 2, 1, 4]
# After 4th flip (k=3): A = [1, 2, 3, 4], which is sorted.

# Example 2:

# Input: [1,2,3]
# Output: []
# Explanation: The input is already sorted, so there is no need to flip anything.
# Note that other answers, such as [3, 3], would also be accepted.
"""


class PancakeSort:

    """

    """
    def doit_(self, A: List[int]) -> List[int]:
        """ sort like bubble-sort
            sink the largest number to the bottom at each round
        """
        def flip(sublist, k):
            i = 0
            while i < k / 2:
                sublist[i], sublist[k-i-1] = sublist[k-i-1], sublist[i]
                i += 1

        ans = []
        value_to_sort = len(A)
        while value_to_sort > 0:
            # locate the position for the value to sort in this round
            index = A.index(value_to_sort)

            # sink the value_to_sort to the bottom,
            #   with at most two steps of pancake flipping.
            if index != value_to_sort - 1:
                # flip the value to the head if necessary
                if index != 0:
                    ans.append(index+1)
                    flip(A, index+1)
                # now that the value is at the head, flip it to the bottom
                ans.append(value_to_sort)
                flip(A, value_to_sort)

            # move on to the next round
            value_to_sort -= 1

        return ans

    """
    Approach 1: Sort Largest to Smallest
    Intuition

    We can place the largest element (in location i, 1-indexed) by flipping i to move the element to the first position, then A.length to move it to the last position.
    Afterwards, the largest element is in the correct position, so we no longer need to pancake-flip by A.length or more.

    We can repeat this process until the array is sorted. Each move will use 2 flips per element.

    Algorithm

    First, sort the locations from largest value of A to smallest value of A.

    For each element (from largest to smallest) with location i, we will first simulate where this element actually is,
    based on the pancake flips we have done. For a pancake flip f, if i <= f, then the element has moved from location i to f+1 - i.

    After, we flip by i then N-- to put this element in the correct position.
    Complexity Analysis

    Time Complexity: O(N^2), where N is the length of A.

    Space Complexity: O(N).
    """
    def doit(self, A):

        ans = []
        N = len(A)
        B = sorted(range(1, N + 1), key=lambda i: -A[i - 1])

        for i in B:

            for f in ans:

                if i <= f:
                    i = f + 1 - i

            ans.extend([i, N])

            N -= 1

        return ans

    def doit(self, A):

        res = []
        for x in range(len(A), 1, -1):
            i = A.index(x)
            res.extend([i + 1, x])
            A = A[:i:-1] + A[:i]
        return res

    """
        for case [3,2,4,1], we can flip to [1, 2, 3, 4] like below ways. 
        We finsh from n ~ 1. Each time, if number n is not in index n-1, it will be a target to do. Saying number n is on the pos k,
        Since we only can flip from 0 ~ k, that means  flip[0:k], then n will be on pos[0],  like [3, 2, 4, 1] => [4, 2, 3, 1]
        Thne n is getting into index 0, then we need to flip[0:n], so n will reach to its position. [4, 2, 3, 1] => [1, 3, 2, 4]

        then we go over the array back to forth, then finish each number i. if i is already in ith pos, then no need to change,
        or if num i in j, it need to do flip[0:j] and then flip[0:i] 
    """
    def doit_sort(self, A: list) -> list:
        def flip(sublist, k):
            i = 0
            while i < k // 2:
                sublist[i], sublist[k - i - 1] = sublist[k - i - 1], sublist[i]
                i += 1
        ans = []
        value_to_sort = len(A)
        while value_to_sort > 0:
            index = A.index(value_to_sort)
            if index != value_to_sort - 1:
                if index != 0:
                    ans.append(index + 1)
                    flip(A, index + 1)
                    
                ans.append(value_to_sort)
                flip(A, value_to_sort)
            value_to_sort -= 1
            
        return ans


if __name__ == "__main__":

    res = PancakeSort().doit([3, 2, 4, 1])  # [4,2,4,3]

    res = PancakeSort().doit([1, 2, 3])  # []

    res = PancakeSort().doit([3, 1, 2])

    pass
