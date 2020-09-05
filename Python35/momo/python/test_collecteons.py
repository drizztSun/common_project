from collections import Counter

def test_counter():
    a = Counter(a = 10, b = 3, f = 2)
    print(list(a.elements()))

    print(Counter('aaabbbcccdef').most_common(3))


    b= Counter(a = 20, b = 10, c = 5)
    c = Counter(a = 10, b = 5, c = 2)
    b.subtract(c)
    print(b)

    d = Counter(a = 1, b = 2, c= 3, d = 4)
    print(sum(d.values()))

    d.clear()
    print(d)
    
    e = Counter(a = 5, b = 6, c = 8, d = 10)
    


    return


if __name__ == "__main__":
    test_counter()