"""
Binary searchable elements

Binary search is a search algorithm usually used on a sorted sequence to quickly find an element with a given value. 
In this problem we will evaluate how binary search performs on data that isn't necessarily sorted. 

An element is said to be binary searchable if an element can be found provided the pivot is chosen everytime as the middle element - like in a regular binary search.
We need to find total number of elements which are binary searchable.

Example 1:

[2, 1, 3, 4, 6, 5] - 3 is searchable, 2 is searchable, 1 not searchable, 6 is searchable, 4 is seachable, 5 is not searchable 
Output: 4
Example 2:

Input: [1, 3, 2]
Output: 2
Explanation: 3 and 1 are searchable - you look for 3 - find it in the middle, look for 1 - you search the left half....search for 2, you look for it in the left half but didn't find.
"""

def binary_searchable_elements(nums):

    s = [(0, len(nums), -float("infinity"), float("infinity"))]
    res = []

    while s:

        left, right, lower_bound, upper_bound = s.pop()

        if left > right:
            continue

        mid = left + (right - left) / 2

        if lower_bound < nums[mid] < upper_bound:
            res.append(nums[mid])

        s.append((left, mid, lower_bound, min(upper_bound, nums[mid])))
        s.append((mid+1, right, max(nums[mid], lower_bound), upper_bound))

    return res


if __name__ == '__main__':

    binary_searchable_elements([2, 1, 3, 4, 6, 5])

    binary_searchable_elements([1, 3, 2])