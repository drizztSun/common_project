import math
from collections import Counter


class uniqueoccurrences:
    def way1(self, arr) -> bool:
        k = {}
        for i in arr:
            k[i] = k.get(i, 0) + 1
        n = set()
        for j in k.values():
            if j in n:
                return False
            n.add(j)
        return True

    def way2(self, arr):
        counts = Counter(arr).values()  # frequencies for each val
        return len(counts) == len(set(counts))  # checks if any frequencies are the same


if __name__ == '__main__':
    a = uniqueoccurrences().way1([1, 2, 2, 3, 4, 5, 5, 5, 6])
    print(a)
    b = uniqueoccurrences().way2([1, 2, 2, 3, 4, 5, 5, 5, 6])
    print(b)
    c = math.asin(99)
