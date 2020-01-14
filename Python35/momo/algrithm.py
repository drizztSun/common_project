

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
    def __init__(self, t):
        self._t = t
        self._max_min = max_min2(self._t)
        self._count = {}
        for i in range(len(self._t)):
            # self._count[i] = self._count.get(i, 0) + 1
            if self._t[i] not in self._count:
                self._count[self._t[i]] = 0
            self._count[self._t[i]] += 1

    @classmethod
    def MAX(clr):
        return 0

    def update(self, t):
        self._t = t
        self._max_min = max_min2(self._t)
        self._count = {}
        for i in range(len(self._t)):
            self._count[i] = self._count.get(i,0) +1
       


    def max(self):
        return self._max_min[0]

    def min(self):
        return self._max_min[1]
    
    def count(self,n):

        return self._count[n]

def max_consegant_length(a: str):
    
    length = 0
    length_max = 0

    for i in range(len(a)):
        if i == 0:
            length_max = 1
            length += 1
        elif i > 0 and a[i-1] == a[i]:
            length += 1
            if length > length_max:
                length_max = length 
           
        elif i > 0 and a[i-1] != a[i]:
           

            length = 1    
    return length_max





    



if __name__ == "__main__":


    t = Counter([1, 2, 2, 2, 3, 4, 5, 6, 6, 6])
    
    print(t.max()) # 6

    t.update([6, 2, 3, 4])

    print(t.min()) # 1

    print(t.count(1)) # 1

    print(t.count(2)) # 3


    a = [1,2,3,-9,25374,123456,-98]
    print(max_min2(a))

    a = []
    print(max_min(a))

    a = [2]
    print(max_min(a))

    print(max_consegant_length("xxxxyyyybbbbbbbb")) # 8

    print(max_consegant_length("aaabbbbbbbccc")) # 7
