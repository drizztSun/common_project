

#O(log(n))
def max_min2(a):
    if len(a) == 1:
        return a[0], a[0]

    b1, s1 = max_min2(a[0: len(a)//2])
    b2,s2 = max_min2(a[len(a)//2: len(a)])

    maxv = b1 if b1 > b2 else b2
    minv = s1 if s1 < s2 else s2

    return maxv, minv


#O(n)
def max_min(a):
    if len(a)==0:
        return 'ERROR(no intger in list.)'

    big,small = a[0],a[0]

    for i in range(1,len(a)):
        if a[i]>big:
            big = a[i]

        if a[i]<small:
            small = a[i]

    return 'Max : {0}, Min: {1}'.format(big, small)

#
# Counter
# Calculate max and min of list
# Calculate amount of each number
class Counter:

    def __init__(self, t:list):
        self._t = t



    def max(self):
        maxv, minv = max_min2(self._t)
        return maxv

    def min(self):
        maxv, minv = max_min2(self._t)
        return minv

    def count(self, n: int):
        a = 0
        for i in range(len(self._t)):
            if self._t[i] == n:
                a = a + 1
        return a


if __name__ == "__main__":


    t = Counter([1, 2, 2, 2, 3, 4, 5, 6, 6, 6])

    print(t.max()) # 6

    print(t.min()) # 1

    print(t.count(1)) # 1

    print(t.count(2)) # 3



    a = [1,2,3,-9,25374,123456,-98]
    print(max_min2(a))

    a = []
    print(max_min(a))

    a = [2]
    print(max_min(a))