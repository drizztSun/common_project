

def main():

    # blend two map objects
    x = {'a': 1, 'b': 2}
    y = {'b': 10, 'c': 3}

    print('x = {0}'.format(x))
    print('y = {0}'.format(y))

    x.update(y)
    print('x = {0}'.format(x))

    # another way to combine
    a = {'a': 1, 'b': 2}
    b = {'a': 2, 'b': 10, 'c': 3}
    
    print(dict(list(a.items()) + list(b.items())))
    

if __name__ == "__main__":

    main()
