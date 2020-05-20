import math


def way1(n: int) -> int:
    def isprime(a):
        for j in range(2, int(math.sqrt(a)) + 1):
            if a % j == 0:
                return False
        return True

    if n < 3:
        return 0
    n = 0
    for i in range(2, n):
        if isprime(i):
            n += 1
    return n


def way2(n):
    if n < 3:
        return 0
    primes = [True] * n
    primes[0] = primes[1] = False

    i = 1
    while i < int(n ** 0.5) + 1:
        if primes[i]:
            j = i ** 2
            while j < n:
                primes[j] = False
                j += i
        i += 1
    return sum(primes)


if __name__ == '__main__':
    print(way2(1500000))
