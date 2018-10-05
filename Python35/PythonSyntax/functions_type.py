

# a will store the status among different function call. like [], [5], [7]
def foo(a = []):
    print(a)
    a.append(5)
    return a

def main():

    print(id(foo())) # [] a [5]

    print(id(foo())) # [5] a [5, 5]

    print(id(foo())) # [5, 5] a [5, 5, 5]
    
    print(id(foo([1]))) # [5, 5]

    print(id(foo())) # [5, 5, 5] a [5, 5, 5, 5]

    print(id(foo())) # [5, 5, 5, 5] a [5, 5, 5, 5, 5]
    


if __name__ == "__main__":
    
    main()
