# 1004. Max Consecutive Ones III

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

class LongestOnes(object):

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
        """
        :type A: List[int]
        :type K: int
        :rtype: int
        """
        # O(n), O(1)
        i = 0
        for j in range(len(A)):
            K -= 1-A[j]
            if K < 0:
                K += 1-A[i]
                i += 1
        return j-i + 1

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

    res = LongestOnes().doit(
        A=[0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1], K=3)

    pass
