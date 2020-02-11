

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


if __name__ == '__main__':
    
    array = [1, 5, 2, 7, 9, 0, -4, 57, 12345]
    print(select_sort(array)) 

    array = [9, 5, 2, 7, 1, 0, -4, 57, 12345]
    print(insert_sort(array))

    pass