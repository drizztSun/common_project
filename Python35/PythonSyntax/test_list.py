

def main():

    a = [0, 1, 2, 3, 4, 5, 6]

    print(a)

    print("a[:] = ", a)

    print("a[1:] = ", a[1:])

    print("a[:5] = ", a[:5])

    print("a[1:5] = ", a[1:5])

    print("a[::2] = ", a[::2])

    print("a[1::2] = ", a[1::2])

    print("a[:5:2] = ", a[:5:2])

    print("a[1:5:2] = ", a[1:5:2])

    print("a[-1:] = ", a[-1:])
    
    print("a[:-1] = ", a[:-1])

    print("a[-5: -1] = ", a[-5:-1])

    print("a[-1:-5] = ", a[-1: -5])


    # reverse sequence
    print("a[::-1] = ", a[::-1])

    print("a[-1 : -5: -1] = ", a[-1:-5:-1])


if __name__ == "__main__":

    main()