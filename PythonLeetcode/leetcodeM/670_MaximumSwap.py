"""
670. Maximum Swap


Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.

Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.
Note:
The given number is in the range [0, 108]
"""

class MaximumSwap:

    """
    Approach #2: Greedy [Accepted]
    Intuition

    At each digit of the input number in order, if there is a larger digit that occurs later, we know that the best swap must occur with the digit we are currently considering.

    Algorithm

    We will compute \text{last[d] = i}last[d] = i, the index \text{i}i of the last occurrence of digit \text{d}d (if it exists).

    Afterwards, when scanning the number from left to right, if there is a larger digit in the future, we will swap it with the largest such digit; if there are multiple such digits, we will swap it with the one that occurs the latest.

    Complexity Analysis

    Let NN be the total number of digits in the input number.

    Time Complexity: O(N)O(N).

    Every digit is considered at most once.
    Space Complexity: O(N)O(N).

    We keep each digit in the array of AA, as in the approach #1.

    The additional space used by the hashtable of last only has up to 10 values. Therefore, on this part, the space complexity is O(1)O(1).

    In total, the overall space complexity is O(N)O(N).
    """
    def doit_greedy(self, num):
        A = list(map(int, str(num)))
        last = {x: i for i, x in enumerate(A)}
        for i, x in enumerate(A):
            for d in range(9, x, -1):
                if last.get(d, -1) > i:
                    A[i], A[last[d]] = A[last[d]], A[i]
                    return int("".join(map(str, A)))
        return num

    def doit_(self, num: int) -> int:
        nums = list(map(str, str(num)))
        pos = sorted(list(range(len(nums))), key=lambda x: nums[x], reverse=True)
        
        for i in range(len(nums)):
            if i != pos[i]:
                low, high = i, pos[i]
                for j in range(pos[i], len(nums)):
                    if nums[j] == nums[high]:
                        high = j
                nums[high], nums[i] = nums[i], nums[high]
                break
        return int(''.join(nums))


if __name__ == '__main__':

    MaximumSwap().doit_(2736)