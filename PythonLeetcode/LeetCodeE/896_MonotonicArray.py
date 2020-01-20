# 896. Monotonic Array

# An array is monotonic if it is either monotone increasing or monotone decreasing.

# An array A is monotone increasing if for all i <= j, A[i] <= A[j].
# An array A is monotone decreasing if for all i <= j, A[i] >= A[j].

# Return true if and only if the given array A is monotonic.



# Example 1:

# Input: [1,2,2,3]
# Output: true

# Example 2:

# Input: [6,5,4,4]
# Output: true

# Example 3:

# Input: [1,3,2]
# Output: false

# Example 4:

# Input: [1,2,4,5]
# Output: true

# Example 5:

# Input: [1,1,1]
# Output: true


# Note:

# 1 <= A.length <= 50000
# -100000 <= A[i] <= 100000

class IsMonotonic:


    """
    Approach 1: Two Pass
    Intuition

    An array is monotonic if it is monotone increasing, or monotone decreasing.
    Since a <= b and b <= c implies a <= c, we only need to check adjacent elements to determine if the array is monotone increasing (or decreasing, respectively).
    We can check each of these properties in one pass.

    Algorithm

    To check whether an array A is monotone increasing, we'll check A[i] <= A[i+1] for all i. The check for monotone decreasing is similar.

    Complexity Analysis

    Time Complexity: O(N), where NN is the length of A.

    Space Complexity: O(1).

    """

    def doit(self, A):

        increasing = True
        decreasing = True

        for i in range(len(A)-1):
            if A[i] > A[i+1]:
                increasing = False
                break

        for i in range(len(A)-1):
            if A[i] < A[i+1]:
                decreasing = False
                break

        return increasing || decreasing

    def doit(self, A):

        status = -1
        
        for i in range(len(A)-1):
            
            if A[i] == A[i+1]:
                continue
                
            if status == - 1:
                status = A[i] < A[i+1]
            elif status != (A[i] < A[i+1]):
                return False
            
        return True
