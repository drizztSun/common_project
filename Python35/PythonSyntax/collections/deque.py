from collections import deque


def main():

    print(" --- deque --- ")

    d = deque("ghi")
    for elem in d:
        print(elem.upper())


    d.append('j')
    d.appendleft('f')

    print(d)

    d.pop()
    d.popleft()

    print(list(d))

    print(d[0])
    print(d[-1])

    list(reversed(d))

    d.extend("jkl")

    d.rotate(1)

    d.rotate(-1)


    d.extendleft("abc")

    e = d.copy()

    d.clear()

    print(" --- deque --- ")

if __name__ == "__main__":
    
    main()


