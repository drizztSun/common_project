"""
1004. Max Consecutive Ones III

# Given an array A of 0s and 1s, we may change up to K values from 0 to 1.

# Return the length of the longest (contiguous) subarray that contains only 1s.


# Example 1:

# Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
# Output: 6
# Explanation:
# [1,1,1,0,0,1,1,1,1,1,1]
# Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.

# Example 2:

# Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
# Output: 10
# Explanation:
# [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
# Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.


# Note:

# 1 <= A.length <= 20000
# 0 <= K <= A.length
# A[i] is 0 or 1

"""


class LongestOnes(object):

    """
    Approach: Sliding Window
    Intuition

    To find the longest subarray with contiguous 1's we might need to find all the subarrays first. But do we really need to do that? If we find all the subarrays we are essentially finding out so many unnecessary overlapping subarrays too.

    We can use a simple sliding window approach to solve this problem.

    In any sliding window based problem we have two pointers. One right pointer whose job is to expand the current window and then we have the left pointer whose job is to contract a given window. At any point in time only one of these pointers move and the other one remains fixed.

    The solution is pretty intuitive. We keep expanding the window by moving the right pointer. When the window has reached the limit of 0's allowed, we contract (if possible) and save the longest window till now.

    The answer is the longest desirable window.

    Algorithm

    Initialize two pointers. The two pointers help us to mark the left and right end of the window/subarray with contiguous 1's.

    left = 0, right = 0, window_size = 0

    We use the right pointer to expand the window until the window/subarray is desirable. i.e. number of 0's in the window are in the allowed range of [0, K].

    Once we have a window which has more than the allowed number of 0's, we can move the left pointer ahead one by one until we encounter 0 on the left too. This step ensures we are throwing out the extra zero.

    Complexity Analysis

    Time Complexity: O(N), where NN is the number of elements in the array. In worst case we might end up visiting every element of array twice, once by left pointer and once by right pointer.

    Space Complexity: O(1). We do not use any extra space.

    """
    def doit_twopointer_slidingwindow(self, A: list, K: int) -> int:
        left = 0

        # right to be side eat 0, left to be side out 0.
        for right in range(len(A)):
            # If we included a zero in the window we reduce the value of K.
            # Since K is the maximum zeros allowed in a window.
            K -= 1 - A[right]
            # A negative K denotes we have consumed all allowed flips and window has
            # more than allowed zeros, thus increment left pointer by 1 to keep the window size same.
            if K < 0:
                # We always remain or increase the size between left and right
                # Here left side is only place to remove 0, from this windows size
                # if meet 1, so we don't decrease K, it seems like we get one more 0, we lost 1 to replace it.
                # if there is no more K 0, means we don't need to lost anything on left side.

                # If the left element to be thrown out is zero we increase K.
                K += 1 - A[left]
                left += 1
        return right - left + 1

    def doit(self, A, K):
        """
        :type A: List[int]
        :type K: int
        :rtype: int
        """
        cnt, j = 0, -1
        ans = 0
        for i in range(len(A)):
            if A[i] == 0:
                cnt += 1

            while cnt > K:
                j += 1
                if A[j] == 0:
                    cnt -= 1

            ans = max(ans, i - j)
        return ans

    def doit(self, A, K):
        from collections import deque

        window = deque()

        for i in range(len(A)):

            next_num = A[i]
            if(K == 0 and next_num == 0 and not window):
                continue

            if(K >= 0 and next_num == 1):
                # Expand
                window.append(A[i])

            elif(K > 0 and next_num == 0):
                window.append(A[i])
                K -= 1

            else:
                # Move window
                e = window.popleft()
                if(e == 0):
                    K += 1
                if(A[i] == 0):
                    K -= 1
                window.append(A[i])

        return len(window)


if __name__ == '__main__':

    res = LongestOnes().doit(A=[1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0], K=2)

    res = LongestOnes().doit(A=[0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1], K=3)

    pass
