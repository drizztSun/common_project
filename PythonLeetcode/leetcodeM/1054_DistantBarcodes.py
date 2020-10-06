"""
1054. Distant Barcodes

In a warehouse, there is a row of barcodes, where the i-th barcode is barcodes[i].

Rearrange the barcodes so that no two adjacent barcodes are equal.  You may return any answer, and it is guaranteed an answer exists.

Example 1:

Input: [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]
Example 2:

Input: [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,2,1,2,1]


Note:

1 <= barcodes.length <= 10000
1 <= barcodes[i] <= 10000
"""


class RearrangeBarcodes:

    def doit_heap(self, barcodes):

        import heapq
        from collections import Counter

        cnt = Counter(barcodes)
        items = [(-v, k) for k, v in cnt.items()]

        heapq.heapify(items)
        res = []

        while len(items) > 1:

            v1, k1 = heapq.heappop(items)
            v1 += 1

            v2, k2 = heapq.heappop(items)
            v2 += 1

            res.extend([k1, k2])

            if v1 != 0:
                heapq.heappush(items, (v1, k1))

            if v2 != 0:
                heapq.heappush(items, (v2, k2))

        if len(items) == 1:
            res.append(items[0][1])

        return res

    def doit_sort(self, barcodes):

        if len(barcodes) < 2:
            return barcodes

        sorted_codes = sorted(barcodes)
        halfway = len(barcodes) // 2
        ans = [0] * (halfway * 2)
        ans[::2], ans[1::2] = sorted_codes[-halfway:], sorted_codes[:halfway]

        if len(barcodes) % 2 == 1:
            prev = None
            mid = sorted_codes[halfway]
            for i in range(len(ans) - 1):
                if ans[i] == mid:
                    i += 1
                elif ans[i] != prev:
                    ans.insert(i, mid)
                    break
                prev = ans[i]
        return ans


if __name__ == '__main__':

    RearrangeBarcodes().doit_heap([1, 1, 1, 2, 2])

