


# 380. Insert Delete GetRandom

# Design a data structure that supports all following operations in average O(1) time.

# insert(val): Inserts an item val to the set if not already present.
# remove(val): Removes an item val from the set if present.
# getRandom: Returns a random element from current set of elements. 
#    Each element must have the same probability of being returned.


class RandomizedSet(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.data_ = []
        self.pos_ = {}

    def insert(self, val):
        """
        Inserts a value to the set. Returns true if the set did not already contain the specified element.
        :type val: int
        :rtype: bool
        """
        res = False
        
        if val not in self.pos_:
            
            self.data_.append(val)

            self.pos_[val] = len(self.data_) - 1

            res = True
            
        return res

    def remove(self, val):
        """
        Removes a value from the set. Returns true if the set contained the specified element.
        :type val: int
        :rtype: bool
        """
        res = False
        
        if val in self.pos_:
            
            index, last = self.pos_[val], self.data[-1]

            self.data_[index], self.data_[-1] = last, val
            self.pos_[last] = index
            
            self.data_.pop(-1)
            self.pos_.pop(val)
            
            res = True
            
        return res
        
    def getRandom(self):
        """
        Get a random element from the set.
        :rtype: int
        """
        import random
        #return random.choice(self.data_)
        return self.data_[random.randint(0, len(self.data_)-1)]
        
        


if __name__=="__main__":


    obj =  RandomizedSet()
    
    res = obj.insert(1)
    res = obj.remove(2)
    res = obj.insert(2)
    
    res = obj.getRandom()

    res = obj.remove(1)
    res = obj.insert(2)
    
    res = obj.getRandom()
    
    # #################
    obj =  RandomizedSet()

    res = obj.insert(3)

    res = obj.insert(-2)

    res = obj.remove(2)

    res = obj.insert(1)

    res = obj.insert(-3)

    res = obj.insert(-2)

    res = obj.insert(-2)

    res = obj.remove(3)    
    
    #res = obj.remove(-1)

    res = obj.insert(-1)

    res = obj.remove(-3)

    res = obj.insert(1)

    res = obj.insert(-2)

    res = obj.insert(-2)

    res = obj.insert(-2)

    res = obj.insert(1)

    res = obj.getRandom()

    res = obj.insert(-2)

    res = obj.remove(0)
            
    res = obj.insert(-3)

    res = obj.insert(1)
    

    pass