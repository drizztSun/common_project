

def max_consegant_length(a: str):
    
    length = 0
    length_max = 0

    for i in range(len(a)):
        if i == 0:
            length_max = 1
            length += 1 #
        elif i > 0 and a[i-1] == a[i]:
            length += 1
            if length > length_max:
                length_max = length 
           
        elif i > 0 and a[i-1] != a[i]:
           

            length = 1    
    return length_max

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

# Binary Search    
#(0) 8 low = 0 high = len(A)  
#(1) mid = (low + high) / 2 = (len(A) + 0) / 2
#(2) if A[mid] < 8, low = mid, high = high, mid = (low + high) // 2
#(3) if A[mid] > 8, low = low, high = mid, mid = (low + high) // 2  
#(4) if A[mid] == 8, or low >= high, None

# O(log(n))    
def binarySearch(A , n):
    low, high = 0, len(A)

    while low < high:

        mid = (low + high)//2
        
        if A[mid] == n:
            return mid
        
        elif A[mid] < n:
            low = mid 
        
        elif A[mid] > n:
            high = mid

    return None

# Sequency Search
# O(n)
def search(A, n):
    for i in range(len(A)):
        if A[i] == n:
            return i
    return -1

# Hash search
# O(1)
def hash_search(A, val, key):

    hash_val = key(val)

    if A[hash_val] is None:
        return ''

    return A[hash_val]

# Select Sort
# source = [4, 3, 5, 2, 1], target = [1, 2, 3, 4, 5] 
# [4, 3, 1, 2, 5]
# [2, 3, 1, 4, 5]
# [2, 1, 3, 4, 5]
# [1, 2, 3, 4, 5]
# O(n^2)
def select_sort(array):

    for i in range(len(array)-1):
        k = i
        for j in range(i+1, len(array)):
            if array[j] < array[k]:
                k = j

        if k != i:
            # array[i], array[k] = array[k], array[i]
            a = array[i]
            array[i] = array[k]
            array[k] = a

    return array

# insert sort
# [4, 3, 1, 2, 5]
# [3, 4, 1, 2, 5]
# [1, 3, 4, 2, 5]
# [1, 2, 3, 4, 5] 
# [1, 2, 3, 4, 5]
# O(n^2)
def insert_sort(arr):

    for i in range(1, len(arr)):

        for j in range(i, 0, -1):

            if arr[j] <= arr[j-1]:
                arr[j], arr[j-1] = arr[j-1], arr[j]
            else:
                break
    return arr

def bubble_sort(arr):
    for i in range(len(arr)-1):  
        for j in range(len(arr)-i-1):  
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr
    # a = [1, 3, 7,8], b = [2, 4, 5, 6]
def merge2(a, b):
    c = []
    i, j = 0, 0
    while i < len(a) or j < len(b):

        if i == len(a) or (j != len(b) and a[i] > b[j]):
            c.append(b[j])
            j += 1

        elif j == len(b) or a[i] <= b[j]:
            c.append(a[i])
            i += 1

    return c

def merge(a:list, i:int, j:int, k:int):

    s1, s2 = i, j
    c = []

    while s1 < j and s2 < k:
        if a[s1] > a[s2]:
            c.append(a[s2])
            s2 += 1
        elif a[s1]<= a[s2]:
            c.append(a[s1])
            s1 += 1

    if s1 < j:
        c.extend(a[s1:j])
    elif s2 < k:
        c.extend(a[s2:k])

    a[i:k] = c[:]


'''
def bottom_up_sort(arr):
    t = 1
    s = 1
    while t < l(arr):
        s, t, i = t, 2*s, 0
        while i + t <= l(arr):
            merge(merge(arr,i+1),merge(i+s,i+t))
            i += t
        if i + s < l(arr):
              merge(arr,i+1,i+s,l(arr))
        pass
'''


if __name__ == '__main__':

    print(merge2(a = [1, 3, 7, 8], b = [2, 4, 5, 6]))

    print(merge2([2, 4, 5, 6], [1, 3, 7, 8]))

    A = [1, 5, 2, 3]
    print(merge(A, 0, 2, 4))

    array = [1, 5, 2, 7, 9, 0, -4, 57, 12345]
    print(select_sort(array))

    array = [9, 5, 2, 7, 1, 0, -4, 57, 12345]
    print(insert_sort(array))

    arr = [8,6,5,4,2,8,4,9,3,7,3,6,4,56,4,6,6,3,5,-7,0]
    print(bubble_sort(arr))

    l = [5, 4, 3, 2, 1]
    print(bubble_sort(l))



    array = [9, 5, 2, 7, 1, 0, -4, 57, 12345]
    #print(bottom_up_sort(array))
    pass