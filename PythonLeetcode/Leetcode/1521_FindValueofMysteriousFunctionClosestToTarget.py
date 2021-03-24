"""
1521. Find a Value of a Mysterious Function Closest to Target


Winston was given the above mysterious function func. He has an integer array arr and an integer target and he wants to find the values l and r that make the value |func(arr, l, r) - target| minimum possible.

Return the minimum possible value of |func(arr, l, r) - target|.

Notice that func should be called with the values l and r where 0 <= l, r < arr.length.



Example 1:

Input: arr = [9,12,3,7,15], target = 5
Output: 2
Explanation: Calling func with all the pairs of [l,r] = [[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]], Winston got the following results [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0]. The value closest to 5 is 7 and 3, thus the minimum difference is 2.
Example 2:

Input: arr = [1000000,1000000,1000000], target = 1
Output: 999999
Explanation: Winston called the func with all possible values of [l,r] and he always got 1000000, thus the min difference is 999999.
Example 3:

Input: arr = [1,2,4,8,16], target = 0
Output: 0


Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 10^6
0 <= target <= 10^7


"""


class ClosestToTarget:

    def doit_slidingwindow(self, arr: list, target: int) -> int:

        zeros = [0] * 26

        def remove(num, sums):
            for i in range(26):
                if num >> i & 1 == 0:
                    zeros[i] -= 1
                    if zeros[i] == 0:
                        sums |= 1 << i
            return sums

        def add(num, sums):
            for i in range(26):
                if num >> i & 1 == 0:
                    zeros[i] += 1
                    if zeros[i] == 1:
                        sums ^= 1 << i
            return sums

        res = float('inf')
        i, j, sums = 0, 0, (1 << 26) - 1

        while i < len(arr):

            sums = add(arr[i], sums)

            res = min(res, abs(sums - target))

            while sums < target:
                sums = remove(arr[j], sums)

                res = min(res, abs(sums - target))

                j += 1

            i += 1

        return res

    def doit_hashtable(self, arr: list, target: int) -> int:

        all = set()

        res = float('inf')

        for c in arr:

            tmp = set()

            for num in all:
                tmp.add(num & c)

            tmp.add(c)

            for x in tmp:
                res = min(res, abs(x - target))

            all = tmp

        return res



