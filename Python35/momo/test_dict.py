if __name__ == "__main__":
    
 # create
    print("============TEST_DICT=================",)
    dict1 = {}
    print(dict1)

    dict2 = {'a':1,'b':2,'c':3}
    print(dict2)
    
    dict3 =  dict(n = 1, abc=3, wsad=4, abcdefg=7, a = 2)
    print(dict3)
    
    dict4 = dict3
    dict5 = dict2.copy()

    # add
    dict1['a'] = 9

    dict2.update(dict5)
    
    result = dict(dict5,**dict3) # use dictt5 and dict3 merge and get a new dict

    dict3.setdefault('n', 123456789)

    # delete
    del dict2['a'] # Remove d[key] from d. Raises a KeyError if key is not in the map.


    assert('a' not in dict2)
    
    dict5.clear()
    
    dict2.pop('b', [2]) # If key is in the dictionary, remove it and return its value, else return default. If default is not given and key is not in the dictionary, a KeyError is raised.

    dict3.popitem() 
    
    # access
    assert('n' in dict3)  #Return True if d has a key key, else False.

    print("len : ", len(dict3))

    #dict.cmp(dict4,dict3)
    
    print(dict3.items())
    for k,v in dict3.items():
        print(k,v)

def counter_list(a):
    counter_dict = {}

    for i in range(len(a)):
        if a[i] not in counter_dict:
            counter_dict[a[i]] = 1
        else:
            counter_dict[a[i]] +=1

    for k, v in counter_dict.items():
        print("key {} occurs {} times.".format(k, v))    





    
    
    a = [1, 23, 2, 7, 4, 5, 10, 2, 7, 6, 5, 2, 1, 4, 2, 2, 2]

    counter_list(a)
    
    dect = {'a':10,'b':20,'c':30}

    print(dect.get('a'))

    #create
    dect1 = {}#a clear one

    dect2 = {'a':100}# a classtic way.:D

    dect3 = dict(a= 100)
    
    dect4 = dect1 # 
    assert(id(dect4) == id(dect1))
    
    dect5 = dect2.copy()  # copy a dict
    assert(id(dect5) != id(dect2))

    # exist
    assert( 'a' in dect1)
    assert( 'sdfjskfds' not in dect1)

    # iterate
    for k,v in dect1:
        print('key {} occurs {} times '.format(k,v))

    # add
    b = 'b'
    dect1[b] = 200
    
    dect1.update({'xy': 1000, 'xz': 10000}) # put new key-value into dect1, and update key-value
    print(dect1)

    result = dict(dect1,**dect2)
    print(result)

    dect5.setdefault('c',123456789) # set 'c':123456, if 'c' does not exist, return default value(none)

    # delete
    del dect1['xy']
    dect2.clear() # clear dect2,dect2 = {} dect2 still exists
    print (dect5.pop('c'))
    print (dect3.popitem())
    del(dect4) #clear and delate dect4 ,dect4 now don't exist

    # change
    dect1['xz'] = 99999 #make it to a any new value, like int,float,str
