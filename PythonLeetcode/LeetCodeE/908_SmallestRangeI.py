# 908. Smallest Range I

# Given an array A of integers, for each integer A[i] we may choose any x with -K <= x <= K, and add x to A[i].

# After this process, we have some array B.

# Return the smallest possible difference between the maximum value of B and the minimum value of B.

 

# Example 1:

# Input: A = [1], K = 0
# Output: 0
# Explanation: B = [1]
# Example 2:

# Input: A = [0,10], K = 2
# Output: 6
# Explanation: B = [2,8]
# Example 3:

# Input: A = [1,3,6], K = 3
# Output: 0
# Explanation: B = [3,3,3] or B = [4,4,4]
 

# Note:

# 1 <= A.length <= 10000
# 0 <= A[i] <= 10000
# 0 <= K <= 10000


class SmallestRangeI:


# Approach 1: Mathematical
# Intuition and Algorithm

# Let A be the original array, and B be the array after all our modifications. 
# Towards trying to minimize max(B) - min(B), let's try to minimize max(B) and maximize min(B) separately.

# The smallest possible value of max(B) is max(A) - K, as the value max(A) cannot go lower. 
# Similarly, the largest possible value of min(B) is min(A) + K. 
# So the quantity max(B) - min(B) is at least ans = (max(A) - K) - (min(A) + K).

# We can attain this value (if ans >= 0), by the following modifications:

# If A[i] \leq \min(A) + KA[i]≤min(A)+K, then B[i] = \min(A) + KB[i]=min(A)+K
# Else, if A[i] \geq \max(A) - KA[i]≥max(A)−K, then B[i] = \max(A) - KB[i]=max(A)−K
# Else, B[i] = A[i]B[i]=A[i].

# Complexity Analysis

# Time Complexity: O(N)O(N), where NN is the length of A.
# Space Complexity: O(1)O(1). 


    def doit(self, A: 'List[int]', K: 'int') -> 'int':
        return max(0, max(A) - min(A) - 2*K)


if __name__ == "__main__":

    res = SmallestRangeI().doit(A = [1], K = 0)

    res = SmallestRangeI().doit(A = [0,10], K = 2)

    res = SmallestRangeI().doit(A = [1,3,6], K = 3)