

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
    del dict2['a']
    assert('a' not in dict2)




    