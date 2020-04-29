import heapq

class Heapnode:
    def __init__(self, data):
        self._data = data
        self._right = None
        self._left = None


def shift_up(k:list, i):
    if i == 0:
        return
    while i != 0:
        if k[i] > k[(i-1) // 2]:
            k[i], k[(i-1) // 2] = k[(i-1) // 2], k[i]
        else:
            break
        i = (i-1) // 2
    return k


def shift_down(a, i):
    n = len(a)-1 

    if 2*i + 1 > n:
        return

    while 2*i+1 < n:
        i = 2*i+1
        if i + 1 <= n and a[i + 1] > a[i]:
            i += 1

        if a[(i-1)//2] < a[i]:
            a[i], a[(i-1)//2] = a[(i-1)//2], a[i]
        else:
            break 
    return a            


def insert(a, x):
    """ insert a value from the heap."""
    n = len(a)-1
    n += 1
    a.append(None)
    a[n] = x
    shift_up(a, n)
    return a


def delete(a, i):
    n = len(a)-1
    x, y = a[i], a[n] 
    n -= 1 
    a.pop()
    if i == n+1:
        return a
    a[i] = y 
    if a[y] == a[x]:
        shift_up(a, i)
    else:
        shift_down(a, i)
    return a           


def delete_max(a):
    x = a[0]
    delete(a, 0)
    return x


def makeheap(arr):
    for i in range((len(arr)-1)//2, -1, -1):
        shift_down(arr,i)
    return arr

def delall(a):
    a = None


def heap_sort(a):
    b = makeheap(a)
    for j in range(len(b)-1, 1, -1):
        b[0] , b[j] = b[j], b[0]
        shift_down(b[1:j-1], 1)
    return list(b)



if __name__ == "__main__":

    a = [1, 3, 4, 2, 8, 4, 9] # 1:1 ,3:2 ,4:3, 2:4 , 8:5 ,4:6  9:7 (val:index+1)  
    

    a = makeheap(a)
    print(shift_up(a, 6))
    print(insert(a, 9))
    print(shift_down(a, 6))
    print(delete(a, 7))
    #print(delete_max(a))
    print(heap_sort([2, 9, 8, 4, 6, 1, 5, 7, 5, 3]))


    
