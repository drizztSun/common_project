
# 453. Minimum Moves to Equal Array Elements

# Given a non-empty integer array of size n, 
# find the minimum number of moves required to make all array elements equal,
# where a move is incrementing n - 1 elements by 1.

# Example:

# Input:
# [1,2,3]

# Output:
# 3

# Explanation:
# Only three moves are needed (remember each move increments two elements):

# [1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]

class minMoves(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        # Adding 1 to n - 1 elements is the same as subtracting 1 from one element,
        # w.r.t goal of making the elements in the array equal.
        # So, best way to do this is make all the elements in the array equal to the min element.
        # sum(array) - n * minimum

        return sum(nums) - len(nums) * min(nums) 



    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # First, the method of decreasing 1 instead of adding 1 for n-1 elements is brilliant.
        # But, when I was doing the contest, I was dumb, so dumb to think outside the box. And this is how I tackled it using just math logic.

        # First, traverse the array, get the sum and the minimum value.
        # If every element is equal, then min*(len) should equal to sum.
        # This part is easy to understand. So, if they are not equal, what should we do? we should keep adding 1 to the array for k times until min*(len)==sum. Then we have:

        # len*(min+k)=sum+k*(len-1).
        # ==> k=sum-min*len;

        # Looks familiar? If you do it by decreasing 1 each time, this equation should be easy to understand!
        # Some of you may have this question: how can I be sure that after adding 1 to (n-1) elements in the array,
        # the minimum value is the previous min plus one. Is it possible that the minimum value stays the same after this? The answer is no, 
        # it's not possible. As long as all elements are not same, adding 1 to (n-1) elements meaning only one element in the array is not getting a candy. 
        # And I�m sure you will choose not to give the candy to the oldest one. So, yes, every time you do that add operation, the min value adds 1.
                
        if not nums and len(nums) < 2:
            return 0

        mins, sums = nums[0], 0
        for i in range(len(nums)):
            sums += nums[i]
            mins = min(mins, nums[i])

        return sums - mins * len(nums)

if __name__=="__main__":

    res = minMoves().doit([1,2,3])