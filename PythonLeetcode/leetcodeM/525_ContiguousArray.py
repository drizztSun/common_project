"""
525. Contiguous Array

Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.
"""


class FindMaxLength:


    # O(n2)
    def doit_brute_force(self, nums):

        res = 0
        for s in range(len(nums)):
            zeros, ones = 0, 0
            for e in range(s, len(nums)):

                if nums[e] == 0:
                    zeros += 1
                else:
                    ones += 1

                if zeros == ones:
                    res = max(res, e - s)
        return res

    """
    Approach #2 Using Extra Array [Accepted]
    Algorithm
    
    In this approach, we make use of a countcount variable, which is used to store the relative number of ones and zeros encountered so far while traversing the array. 
    The countcount variable is incremented by one for every \text{1}1 encountered and the same is decremented by one for every \text{0}0 encountered.
    
    We start traversing the array from the beginning. If at any moment, the countcount becomes zero, it implies that we've encountered equal number of zeros and 
    nes from the beginning till the current index of the array(ii). Not only this, another point to be noted is that if we encounter the same countcount twice while traversing the array, 
    it means that the number of zeros and ones are equal between the indices corresponding to the equal countcount values. The following figure illustrates the observation for the sequence [0 0 1 0 0 0 1 1]:
    
    In the above figure, the subarrays between (A,B), (B,C) and (A,C) (lying between indices corresponing to count = 2count=2) have equal number of zeros and ones.

    Another point to be noted is that the largest subarray is the one between the points (A, C). Thus, if we keep a track of the indices corresponding 
    to the same countcount values that lie farthest apart, we can determine the size of the largest subarray with equal no. of zeros and ones easily.

    Now, the countcount values can range between \text{-n}-n to \text{+n}+n, with the extreme points corresponding to the complete array being filled with 
    all 0's and all 1's respectively. Thus, we make use of an array arrarr(of size \text{2n+1}2n+1to keep a track of the various countcount's encountered so far. 
    We make an entry containing the current element's index (ii) in the arrarr for a new countcount encountered everytime. Whenever, we come across the same countcount value later while traversing the array, 
    we determine the length of the subarray lying between the indices corresponding to the same countcount values.
    """
    def doit_array(self, nums):
        pos = [0 for _ in range(len(nums))]
        profix = {0: -1}
        maxv = 0

        for i in range(len(nums)):
            pos[i] = 1 if nums[i] == 1 else -1
            if i > 0:
                pos[i] += pos[i - 1]

            if pos[i] not in profix:
                profix[pos[i]] = i
            else:
                maxv = max(maxv, i - profix[pos[i]])

        return maxv
    
    """
    Approach #3 Using HashMap [Accepted]
    Algorithm

    This approach relies on the same premise as the previous approach. But, we need not use an array of size \text{2n+1}2n+1, since it isn't necessary that we'll encounter all the countcount values possible.
    Thus, we make use of a HashMap mapmap to store the entries in the form of (index, count)(index,count). We make an entry for a countcount in the mapmap whenever the countcount is encountered first,
    and later on use the correspoding index to find the length of the largest subarray with equal no. of zeros and ones when the same countcount is encountered again.

    The following animation depicts the process:
    """

    def doit_hashmap(self, nums: list[int]) -> int:
        ## the number of 0s and 1s will be the same between 2 points where the count is the same
        ## use a dictionary !
        counts = {}
        counts[0] = [-1, -1]

        count = 0
        max_len = 0

        for i, c in enumerate(nums):
            count += -1 if c == 0 else 1

            if count in counts:
                ## add finishing index
                counts[count][1] = i
            else:
                counts[count] = [i, i]

        for key in counts.keys():
            max_len = max(max_len, counts[key][1] - counts[key][0])

        return max_len