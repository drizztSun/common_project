# 798. Smallest Rotation with Highest Score

# Given an array A, we may rotate it by a non-negative integer K so that the array becomes A[K], A[K+1], A{K+2], ... A[A.length - 1], A[0], A[1], ..., A[K-1].
# Afterward, any entries that are less than or equal to their index are worth 1 point. 

# For example, if we have [2, 4, 1, 3, 0], and we rotate by K = 2, it becomes [1, 3, 0, 2, 4].
# This is worth 3 points because 1 > 0 [no points], 3 > 1 [no points], 0 <= 2 [one point], 2 <= 3 [one point], 4 <= 4 [one point].

# Over all possible rotations, return the rotation index K that corresponds to the highest score we could receive. 
# If there are multiple answers, return the smallest such index K.

# Example 1:
# Input: [2, 3, 1, 4, 0]
# Output: 3
# Explanation:  
# Scores for each K are listed below: 
# K = 0,  A = [2,3,1,4,0],    score 2
# K = 1,  A = [3,1,4,0,2],    score 3
# K = 2,  A = [1,4,0,2,3],    score 3
# K = 3,  A = [4,0,2,3,1],    score 4
# K = 4,  A = [0,2,3,1,4],    score 3
# So we should choose K = 3, which has the highest score.

 

# Example 2:
# Input: [1, 3, 0, 2, 4]
# Output: 0
# Explanation:  A will always have 3 points no matter how it shifts.
# So we will choose the smallest K, which is 0.
# Note:

# A will have length at most 20000.
# A[i] will be in the range [0, A.length].


class BestRotation:



    # Key point
    # Don't calculate the score for K=0, we don't need it at all.
    # (I see almost all other solutions did)
    # The key point is to find out how score changes when K++

    # Time complexity:
    # “A will have length at most 20000.”
    # I think it means you should find a O(N) solution.

    # How dosen score change when K++ ?

    # Get point
    # Each time when we rotate, we make index 0 to index N-1, then we get one more point.
    # We know that for sure, so I don't need to record it.

    # Lose point
    # (i - A[i] + N) % N is the value of K making A[i]'s index just equal to A[i].
    # For example, If A[6] = 1, then K = (6 - A[6]) % 6 = 5 making A[6] to index 1 of new array.
    # So when K=5, we get this point for A[6]
    # Then if K is bigger when K = (i - A[i] + 1) % N, we start to lose this point, making our score -= 1
    # All I have done is record the value of K for all A[i] where we will lose points.

    # A[i]=0
    # Rotation makes no change for it, becasue we alwars have 0 <= index.
    # However, it is covered in "get point" and "lose point".

    # Explanation of codes

    # Search the index where score decrease and record this changement to a list change.
    # A simple for loop to calculate the score for every K value.
    # score[K] = score[K-1] + change[K]
    # In my codes I accumulated changes so I get the changed score for every K value compared to K=0
    # Find the index of best score.
    def doit(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        N = len(A)
        diff = [1] * N

        for i in range(N):
            diff[ (i - A[i] + N + 1) % N ] -= 1

        for k in range(1, N):
            diff[k] += diff[k-1]

        return diff.index(max(diff))
         



    # O(n)
    def doit1(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        maxv, smallestK = 0, len(A)
        for k in range(len(A)):
            cnt = 0
            for i, c in enumerate(A):
                if i < k:
                    cnt += 1 if c <= len(A) - k + i else 0
                else:
                    cnt += 1 if c <= i - k else 0

            if cnt >= maxv:
                maxv = cnt
                smallestK = k

        return smallestK   




if __name__ == "__main__":

    res = BestRotation().doit([2, 3, 1, 4, 0])

    res = BestRotation().doit([1, 3, 0, 2, 4])

    pass

