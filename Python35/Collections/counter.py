from collections import Counter, ChainMap

# A counter tool is provided to support convenient and rapid tallies. For example:

# A Counter is a dict subclass for counting hashable objects. 
# It is an unordered collection where elements are stored as dictionary keys 
# and their counts are stored as dictionary values. Counts are allowed to be any integer value including zero or negative counts. 
# The Counter class is similar to bags or multisets in other languages.

def HowToUseCounter():

  
    # A counter tool is provided to support convenient and rapid tallies. For example:

    cnt = Counter()
    for word in ['blue', 'red', 'white', 'red', 'blue', 'blue']:
        cnt[word] += 1

    print(cnt)

    #print(os.cwd())

    #import re
    #words = re.findall(r'\w+', open('hamlet.txt').read().lower())
    #print( Counter(words).most_common(10) )


    c = Counter()
    c = Counter("abcdefgabc")
    c = Counter({'red':4, 'white': 3})
    c = Counter(cats=4, dogs=8)

    c = Counter(['eggs', 'ham', 'turkey', 'eggs', 'ham', 'sandwich', 'burger', 'sausage', 'sausage'])
    print(c)

    print(c['bacon'])
    print(c['eggs'])


    print(sorted(c.elements()))

    print(c.most_common(3))

    print(c)
    c.subtract(Counter(['egg', 'ham', 'steak']))

    print(c)
    
    print(c.items())
    print(list(c))
    print(set(c))
    print(dict(c))
    
    print(+c)
    print(-c)


    del c['eggs']
    
    print(c)


    d = Counter(a=3, b=2, c=1)
    b = Counter(a=2, b=1, c=2, d=2)

    print (d + b)
    print (d - b)
    print (d & b)   # min(d[x], b[x])
    print (d | b)   # max(d[x], b[x])

    

    pass

import builtins
# A ChainMap class is provided for quickly linking a number of mappings so they can be treated as a single unit
def HowToUseChain():
    
    #c = ChainMap({'a':1, 'b':2, 'c':3}, )

    c = ChainMap(locals(), globals(), vars(builtins))

    c = ChainMap()
    d = c.new_child()
    e = c.new_child()

    # e.

    


    pass

if __name__ == "__main__":


    HowToUseChain()

    HowToUseCounter()        

    pass