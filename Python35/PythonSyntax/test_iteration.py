
# Interprator is going to check, __iter__, __next__, __getitem__ in iterable objects

class Animal:
    def __init__(self, animal_list):
        self.animals_name = animal_list
    
    def __getitem__(self, index):
        return self.animals_name[index]

class non_iter:
    pass

def test_iteration():

    print(dir(list))
    print(dir(dict))
    print(dir(set))

    list_func = dir(list)
    dict_func = dir(dict)
    set_func = dir(set)

    if '__iter__' in list_func and '__getitem__' in list_func:
        for c in [1, 2, 3, 4, 5]:
            print(c)

    if '__iter__' in dict_func and '__getitem__' in dict_func:
        items = { 'a': 20, 'b': 30, 'c': 40}
        for key in items:
            print(items[key])

    if '__iter__' in set_func and '__getitem__' not in set_func:
        items = set([1, 2, 3, 4, 5, 1, 2])
        for c in items:
            print(c)

    # user-defined class
    animals = Animal(['cat', 'dog', 'human'])
    for animal in animals:
        print(animal)

    try:
        for c in non_iter():
            pass

    except TypeError as e:
        print(e)

    
        

    

if __name__ == '__main__':

    test_iteration()