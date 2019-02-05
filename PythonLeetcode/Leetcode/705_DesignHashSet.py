# 705. Design HashSet

# Design a HashSet without using any built-in hash table libraries.

# To be specific, your design should include these functions:

# add(value): Insert a value into the HashSet. 
# contains(value) : Return whether the value exists in the HashSet or not.
# remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.

# Example:

# MyHashSet hashSet = new MyHashSet();
# hashSet.add(1);         
# hashSet.add(2);         
# hashSet.contains(1);    // returns true
# hashSet.contains(3);    // returns false (not found)
# hashSet.add(2);          
# hashSet.contains(2);    // returns true
# hashSet.remove(2);          
# hashSet.contains(2);    // returns false (already removed)

import bisect

class MyHashSet:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.__group = []

    def add(self, key: 'int') -> 'None':
        i = bisect.bisect_left(self.__group, key)
        if i == len(self.__group) or (0 <= i < len(self.__group) and self.__group[i] != key):
            bisect.insort_left(self.__group, key)

    def remove(self, key: 'int') -> 'None':
        i = bisect.bisect_left(self.__group, key)
        if 0 <= i < len(self.__group) and self.__group[i] == key:
            self.__group.pop(i)

    def contains(self, key: 'int') -> 'bool':
        """
        Returns true if this set contains the specified element
        """
        i = bisect.bisect_left(self.__group, key)
        return True if 0 <= i < len(self.__group) and self.__group[i] == key else False



class MyHashSet2:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.myHashSet = [None] *10000
        

    def add(self, key):
        """
        :type key: int
        :rtype: void
        """
        index = key%10000
        if not self.myHashSet[index]:
            self.myHashSet[index] = [key]
        elif key not in self.myHashSet[index]:
            self.myHashSet[index].append(key)
        

    def remove(self, key):
        """
        :type key: int
        :rtype: void
        """
        index = key%10000
        if self.myHashSet[index] and key in self.myHashSet[index]:
            self.myHashSet[index].remove(key)


    def contains(self, key):
        """
        Returns true if this set contains the specified element
        :type key: int
        :rtype: bool
        """
        index = key%10000
        if self.myHashSet[index] and key in self.myHashSet[index]:
            return True
        return False


# Your MyHashSet object will be instantiated and called as such:
# obj = MyHashSet()
# obj.add(key)
# obj.remove(key)
# param_3 = obj.contains(key)
if __name__ == "__main__":

    obj = MyHashSet()

    obj.add(1)
    obj.add(2)
    
    res = obj.contains(1)
    res = obj.contains(3)

    obj.add(2)
    res = obj.contains(2)

    obj.remove(2)
    res = obj.contains(2)            

    res = False

