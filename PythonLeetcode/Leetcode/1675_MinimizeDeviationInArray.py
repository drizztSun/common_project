"""
1675. Minimize Deviation in Array

You are given an array nums of n positive integers.

You can perform two types of operations on any element of the array any number of times:

If the element is even, divide it by 2.
For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
If the element is odd, multiply it by 2.
For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
The deviation of the array is the maximum difference between any two elements in the array.

Return the minimum deviation the array can have after performing some number of operations.



Example 1:

Input: nums = [1,2,3,4]
Output: 1
Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
Example 2:

Input: nums = [4,1,5,20,3]
Output: 3
Explanation: You can transform the array after two operations to [4,2,5,5,3], then the deviation will be 5 - 2 = 3.
Example 3:

Input: nums = [2,10,8]
Output: 3


Constraints:

n == nums.length
2 <= n <= 105
1 <= nums[i] <= 109


"""

"""
Overview
The problem can be solved in many ways. With heap, we can directly solve it by simulation (and a little greedy idea). 
Also, with some pretreatments, we can transform it into Smallest Range Covering Elements from K Lists.

Below, we will discuss five approaches: 
1) Simulation + Heap, 
2) Pretreatment + Sorting + Sliding Window, 
3) Pretreatment + Heap + Sliding Window, 
4) Pretreatment + Heap + Pointers, and 
5) Pretreatment + Sorting + Pointers.

Generally, we recommend the first approach since it is easy to implement and has good performance. 
We provide other approaches to explore possibilities and leave them for interested readers. 
In fact, there are many different approaches to tackle this problem, and the given five approaches are not enough to cover them all.
"""


class MinimumDeviationInArray:


    """
    Algorithm

    Step 1: Initialize a max-heap evens.

    For an even number in nums, put it directly into evens; for the odd number in nums, multiply by 2 and put it into evens.
    Step 2: Maintain an integer minimum to keep tracking the smallest element in evens.

    Step 3: Take out the maximum number in evens. Use the maximum and the maintained minimum to update the minimum deviation. If the maximum number is even, divide by 2 and push into evens.

    Step 4: Repeat Step 3 until the maximum number in evens is odd.

    Step 5: Return the minimum deviation.

    Complexity Analysis

    Let NN be the length of nums, and MM be the largest number in nums. In the worst case when MM is the power of 22, there are log(M) possible values for M.
    Therefore, in the worst case, the total possible candidate number (denoted by KK) is K = N \cdot \log(M) = N\log(M)K=N⋅log(M)=Nlog(M).

    Time Complexity: O(K*log(N)) = O(N*log(M) O(Klog(N)) = O(Nlog(M)log(N)). In worst case, we need to push every candidate number into evens, and the size of evens is \mathcal{O}(N)O(N).
    Hence, the total time complexity is \mathcal{O}(K \cdot \log(N)) = \mathcal{O}(N\log(M)\log(N))O(K⋅log(N))=O(Nlog(M)log(N)).

    Space Complexity: \mathcal{O}(N)O(N), since there are at most NN elements in evens.
    """
    def doit_simulation_heap(self, nums: list) -> int:
        import heapq
        inf = float('inf')
        evens = []
        minimum = inf
        for num in nums:
            if num % 2 == 0:
                evens.append(-num)
                minimum = min(minimum, num)
            else:
                evens.append(-num*2)
                minimum = min(minimum, num*2)

        heapq.heapify(evens)
        min_deviation = inf
        while evens:
            current_value = -heapq.heappop(evens)
            min_deviation = min(min_deviation, current_value-minimum)
            if current_value % 2 == 0:
                minimum = min(minimum, current_value//2)
                heapq.heappush(evens, -current_value//2)
            else:
                # if the maximum is odd, break and return
                break
        return min_deviation

    def doit_heap(self, nums: list) -> int:
        from heapq import heappush, heappop
        candidates = []
        for c in nums:
            if c % 2 == 1:
                candidates.append([2 * c, c])
            else:
                candidates.append([])
                while c % 2 != 1:
                    candidates[-1].append(c)
                    c //= 2
                candidates[-1].append(c)

        buff, minv = [], float('inf')
        for i in range(len(candidates)):
            heappush(buff, (-candidates[i][0], i, 0))
            minv = min(minv, candidates[i][0])

        ans = float('inf')
        while buff:

            v, i, j = heappop(buff)
            ans = min(ans, -v - minv)

            if j + 1 == len(candidates[i]):
                break

            heappush(buff, (-candidates[i][j+1], i, j+1))
            minv = min(minv, candidates[i][j+1])

        return ans

    def doit_heap_2(self, nums: list) -> int:
        import math
        from heapq import heappush, heappop, heapify
        n = len(nums)
        ans = math.inf

        maxV = max(nums)

        heapify(nums)
        while True:
            ans = min(ans, maxV - nums[0])

            if nums[0] % 2 == 1:
                x = heappop(nums)
                heappush(nums, x * 2)
                maxV = max(maxV, x * 2)
            else:
                break

        nums = [-x for x in nums]
        maxV = max(nums)

        heapify(nums)
        while True:
            ans = min(ans, maxV - nums[0])
            if nums[0] % 2 == 0:
                x = heappop(nums)
                heappush(nums, x // 2)
                maxV = max(maxV, x // 2)
            else:
                break

        return ans


if __name__ == '__main__':

    MinimumDeviationInArray().doit_heap([1, 111, 113])


