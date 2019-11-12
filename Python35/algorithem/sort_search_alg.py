

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
    pass


def heap_sort(a):
    pass


if __name__ == '__main__':

    print(select_sort([1, 7, 2, 6, 3, 5, 4]))

    print(insert_sort([1, 7, 2, 6, 3, 5, 4]))

    print(bubble_sort([1, 7, 2, 6, 3, 5, 4]))

    print(quick_sort([1, 7, 2, 6, 3, 5, 4]))
