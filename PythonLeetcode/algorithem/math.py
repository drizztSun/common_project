def isprime(n):
    for d in range(2, int(n**0.5)+1):
        if n % d == 0:
            return False
    return n > 1