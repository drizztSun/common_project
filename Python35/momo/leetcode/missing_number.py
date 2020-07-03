class missingNumberSolution:
    def way(self, a):
        for i in range(len(a)):
            while 0 <= a[i] < len(a) and a[i] != i:
                a[a[i]], a[i]] = a[i], a[a[i]]
            i += 1
            
        i = 0
        while i < len(a) and a[i] == i:
            i += 1
        return i