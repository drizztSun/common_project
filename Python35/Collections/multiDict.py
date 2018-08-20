

from collections import defaultdict 
from collections import OrderedDict



def main():

    # defaultdict
    # Using list as the default_factory, it is easy to group a sequence of key-value pairs into a dictionary of lists:
    s = [('yellow', 1), ('blue', 2), ('yellow', 3), ('blue', 4), ('red', 1)]
    d = defaultdict(list)

    for i, k in s:
        d[i].append(k)

    print(sorted(d.items()))

    # defaultdict/int
    s = 'mississippi'
    d = defaultdict(int)

    for k in s:
        d[k] += 1

    print(sorted(d.items()))

    # default/function
    #def constant_factory(x):
    #    return lambda : x
    #d = defaultdict(constant_factory('<missing>')
    #d.update(name='Johen', action='ran')
    
    
    # defaultdict/set    
    s = [('red', 1), ("blue", 2), ("red", 3), ('blue', 4), ('red', 1), ('blue', 4)]
    d = defaultdict(set)

    for k, v in s:
        d[k].add(v)

    print(sorted(d.items))

        
        
    
    #  orderdict 
    # Return an instance of a dict subclass, supporting the usual dict methods. 
    # An OrderedDict is a dict that remembers the order that keys were first inserted. 
    # If a new entry overwrites an existing entry, the original insertion position is left unchanged. 
    # Deleting an entry and reinserting it will move it to the end.
    c = OrderedDict()
    c['blue'] = 100
    c['yellow'] = 200
    c['red'] = 300

    c['black'] = 400
    print(c)
     
    c.popitem(False) # FIFO
    print(c)

    c.popitem(True) # LIFO
    print(c)
    
    c.move_to_end('yellow', True) # move to the right
    print(c)

    c.move_to_end('yellow', False) # move to the left
    print(c)


    d = {'banana': 3, 'apple': 4, 'pear': 1, 'orange': 2}
    # ordered by keys
    print(OrderedDict(sorted(d.items(), key = lambda t: t[0])))

    # ordered by values
    print(OrderedDict(sorted(d.items(), key = lambda t: t[1])))

    # ordered by length of the key string
    print(OrderedDict(sorted(d.items(), key = lambda t: len(t)))

    

    
    
    pass


if __name__ == "__main__":
    
    main()


    pass