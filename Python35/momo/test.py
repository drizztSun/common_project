def fibon(n):
    a = b = 1
    for i in range(n):
        yield a
        a, b = b, a + b

if __name__ == '__main__':

    for x in fibon(10):
        print(x)