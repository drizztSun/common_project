print('========================================MATT============================================')

# python test_dict.py
# when call this command, test_dict will be the main module
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