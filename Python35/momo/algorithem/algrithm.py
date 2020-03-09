def DADISPOOP(jfk):
    return 'DAD IS POOP AND HE EATS POOP!'
m = 1
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
            self._count[i] = self._count.get(i, 0) + 1


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



print('1111@@@11111111@@@1111')
print('1111@@@11111111@@@1111')
print('1111111111111111111111')
print('11|111111###111111|111')#a b c d e f g h i j k l m n o p q r s t u v w x y z (study those if you blahblahblahblahblahblahblahblahblahblah.)BLAHBLAHBLAHBLAHBLAHBLAH                                                                                                                                                                                                                                \
print('11|111111###111111|111')    
print('11|111111111111111|111')
print('11|111111111111111|111')
print('11|111111111111111|111')
print('11|===============|111')



A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] 

#(what are those for?)


































def split_nums_digits(num: int):
    # 123456 [1, 2, '3', '4', '5', '6']
    a = []
    
    while num > 0:
        num, v = num//10, num%10 #divmod(num, 10)
        a.append(str(v))
    return a[::-1] #reversed(a)
    
def combine_digits_to_num(digits: list):

    # [2, 3, 4, 5, 6]  23456
    num = 0
    for c in digits:
        num = num * 10 + c
    return num







if __name__ == "__main__":
   
    print('dad is poop and he eats poop! dad is poop and he eats poop! dad is poop and he eats poop!') 

    print(split_nums_digits(56789))

    print(combine_digits_to_num(digits = [1,2, 3, 4, 5]))
    
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

    
    print(DADISPOOP(234567890-2345678))

   
#                     ???




















































































































































































    m +=1