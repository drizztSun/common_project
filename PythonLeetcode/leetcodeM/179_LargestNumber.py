"""
179. Largest Number

Given a list of non-negative integers nums, arrange them such that they form the largest number.

Note: The result may be very large, so you need to return a string instead of an integer.

 

Example 1:

Input: nums = [10,2]
Output: "210"
Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"
Example 3:

Input: nums = [1]
Output: "1"
Example 4:

Input: nums = [10]
Output: "10"
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 10^9

"""

class LargestNumber:

    def doit_sort(self, nums: list) -> str:
        import functools 

        def compare(a, b):
            return 1 if str(a) + str(b) < str(b) + str(a) else -1
    
        nums = [str(n) for n in sorted(nums, key=functools.cmp_to_key(compare))]
        ans = ''.join(nums)
        return '0' if ans.startswith('0') else ans

    def doit_sort(self, nums: list) -> str:
        
        compare = lambda x, y: x + y > y + x

        numstr = [str(c) for c in nums]

        def partition(l, h):
            
            j = l+1
            for i in range(l+1, h+1):

                if compare(numstr[i], numstr[l]):
                    numstr[i], numstr[j] = numstr[j], numstr[i]
                    j += 1

            numstr[l], numstr[j-1] = numstr[j-1], numstr[l]
            return j-1

        def quicksort(l, h):
            if l >= h:
                return

            m = partition(l, h)
            quicksort(l, m-1)
            quicksort(m+1, h)

        quicksort(0, len(numstr) - 1)
        return '0' if numstr[0].startswith('0') else ''.join(numstr)