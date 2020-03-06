import math



def binary_search(a, s):

    l, h = 0, len(a)

    while l < h:

        mid = l + (h-l) // 2

        if a[mid] == s:
            return mid
        elif a[mid] > s:
            h = mid
        else:
            l = mid + 1

    return -1


def select_sort(a):

    for i in range(len(a)-1):
        m = 0
        for j in range(len(a) - i):
            if a[m] < a[j]:
                m = j
        a[m], a[len(a) - i - 1] = a[len(a) - i - 1], a[m]

    return a


def insert_sort(a):

    for i in range(1, len(a)):
        m = a[i]
        for j in reversed(range(i)):
            if a[j] > m:
                a[j + 1] = a[j]
            else:
                a[j + 1] = m
                break

    return a


def bubble_sort(a):

    for i in reversed(range(len(a))):
        for j in range(i):
            if a[j+1] < a[j]:
                a[j], a[j+1] = a[j+1], a[j]
    return a


def quick_sort(a):

    # O(n)
    def quick_insert(a, s, e):
        j = s
        for i in range(s+1, e):
            if a[s] > a[i]:
                a[j+1], a[i] = a[i], a[j+1]
                j = j+1
        a[s], a[j] = a[j], a[s]
        return j

    def quick_sort_with_insert(a, s, e):
        if e - s <= 1:
            return

        k = quick_insert(a, s, e)
        quick_sort_with_insert(a, s, k)
        quick_sort_with_insert(a, k+1, e)

    quick_sort_with_insert(a, 0, len(a))
    return a



def merge_sort(a):

    def merge(a, i, j, step):
        s, e1, e2 = i, j, min(j + step, len(a))
        b = []
        while i < e1 and j < e2:
            if a[i] < a[j]:
                b.append(a[i])
                i += 1
            else:
                b.append(a[j])
                j += 1

        if j == e1:
            return

        if i == e1:
            b.extend(a[j:e2])
        else:
            b.extend(a[i:e1])

        a[s:e2] = b

    step = 1
    while step < len(a):
        i = 0
        while i < len(a):
            if i + step < len(a):
                merge(a, i, i + step, step)
            i += step * 2
        step *= 2

    return a


def heap_sort(a):
    pass


if __name__ == '__main__':

    for i in range(12):
        print('%d in pos: %d' % (i, binary_search([1, 3, 5, 7, 9, 11], i)))

    print(select_sort([1, 7, 2, 6, 3, 5, 4]))

    print(insert_sort([1, 7, 2, 6, 3, 5, 4]))

    print(bubble_sort([1, 7, 2, 6, 3, 5, 4]))

    print(quick_sort([1, 7, 2, 6, 3, 5, 4]))

    print(merge_sort([1, 7, 2, 6, 3, 5, 4]))


    arr= [12, 24, 23, 56, 1, 3, 10, 4, 6, 45]

    quick_sort(arr)

    print(arr)
