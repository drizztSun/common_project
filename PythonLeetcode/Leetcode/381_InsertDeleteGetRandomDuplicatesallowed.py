


# 381. Insert Delete GetRandom O(1) - Duplicates allowed

# Design a data structure that supports all following operations in average O(1) time.

# Note: Duplicate elements are allowed.
# insert(val): Inserts an item val to the collection.
# remove(val): Removes an item val from the collection if present.
# getRandom: Returns a random element from current collection of elements.
# The probability of each element being returned is linearly related to the number of same value the collection contains.
# Example:

# // Init an empty collection.
# RandomizedCollection collection = new RandomizedCollection();

# // Inserts 1 to the collection. Returns true as the collection did not contain 1.
# collection.insert(1);

# // Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
# collection.insert(1);

# // Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
# collection.insert(2);

# // getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
# collection.getRandom();

# // Removes 1 from the collection, returns true. Collection now contains [1,2].
# collection.remove(1);

# // getRandom should return 1 and 2 both equally likely.
# collection.getRandom();



class RandomizedCollection(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.pos_, self.data_ = {}, []

    def insert(self, val):
        """
        Inserts a value to the collection. Returns true if the collection did not already contain the specified element.
        :type val: int
        :rtype: bool
        """
        self.data_.append(val)

        res = val in self.pos_
        if not res:
            self.pos_[val] = []

        self.pos_[val].append(len(self.data_)-1)

        return res

    def remove(self, val):
        """
        Removes a value from the collection. Returns true if the collection contained the specified element.
        :type val: int
        :rtype: bool
        """
        if val not in self.pos_ or not self.pos_[val]:
            return False

        last = self.data_[-1]

        if val != last:
            pos = self.pos_[val].pop()
            self.data_[pos] = last
            self.pos_[last].remove(len(self.data_)-1)
            self.pos_[last].append(pos)
            self.data_.pop()
            if not self.pos_[val]:
                del self.pos_[val]
        else:
            self.pos_[self.data_.pop()].remove(len(self.data_))

        return True
        

    def getRandom(self):
        """
        Get a random element from the collection.
        :rtype: int
        """
        import random
        return random.choice(self.data_)

# Your RandomizedCollection object will be instantiated and called as such:
# obj = RandomizedCollection()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()

import collections
class RandomizedCollection(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        
        # tests: removing when there are only one element left in list  ["RandomizedCollection","insert","remove","insert"]
        #                                                               [[],[1],[1],[1]]
        #        num to remove = num at last idx  ["RandomizedCollection","insert","insert","insert","insert","insert","remove"]
        #                                         [[],[4],[3],[4],[2],[4],[4]]
        
        # self.nums keep track of all present numbers
        self.nums = []

        # self.d has the numbers as key, sets as values. sets contain the positions of a number in the list self.nums
        self.d = collections.defaultdict(set)
        

    def insert(self, val):
        """
        Inserts a value to the collection. Returns true if the collection did not already contain the specified element.
        :type val: int
        :rtype: bool
        """
        # keep the index of the number in the list
        self.d[val].add(len(self.nums))
        self.nums.append(val)

        # if the len of the list is 1, it means there is only one of this number -> it's the one we just add -> no duplicate
        return len( self.d[val] ) == 1
        

    def remove(self, val):
        """
        Removes a value from the collection. Returns true if the collection contained the specified element.
        :type val: int
        :rtype: bool
        """
        # In defaultdicts, key error wont be induced if a key doesnt already exist. it will simply return False. 
        # If self.d[key] is empty, it'll also return False
        
        if self.d[val]:

            idx = self.d[val].pop()

            if len(self.nums) > 1:

                self.d[self.nums[-1]].add(idx)
                self.d[self.nums[-1]].remove(len(self.nums) - 1)
                self.nums[idx] = self.nums[-1]

            self.nums.pop()

            return True

        return False
        

    def getRandom(self):
        """
        Get a random element from the collection.
        :rtype: int
        """
        return random.choice(self.nums)



if __name__=="__main__":
    
    obj = RandomizedCollection()

    obj.insert(1)
    obj.insert(2)
    obj.insert(1)
    obj.remove(1)

    res = obj.getRandom()

    obj.insert(4)
    obj.insert(3)
    obj.insert(4)
    obj.insert(5)
    obj.insert(5)

    res = obj.getRandom()

    obj.remove(4)
    obj.remove(4)
    obj.remove(5)

    res = obj.getRandom()

    obj.insert(6)
    obj.insert(5)
    


    # #############
    obj = RandomizedCollection()
    
    res = obj.insert(0)
    res = obj.remove(0)
    
    res = obj.insert(-1)
    res = obj.remove(0)

    res = obj.getRandom()
    
    res = obj.getRandom()

    res = obj.getRandom()

    res = obj.getRandom()

    res = obj.getRandom()

    res = obj.getRandom()

    res = obj.getRandom()

    pass