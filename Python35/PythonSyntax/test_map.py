import operator


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

    # sort the map list
    x = {1:2, 3:4, 4:3, 2:1, 0:0}

    # sort by value
    sorted_val = sorted(x.items(), key= operator.itemgetter(1))
    sorted_val = sorted(x.items(), key= lambda x:x[1])

    # sort by key
    sorted_key = sorted(x.items(), key= operator.itemgetter(0))
    sorted_key = sorted(x.items(), key= lambda x:x[0])
    

if __name__ == "__main__":

    main()
