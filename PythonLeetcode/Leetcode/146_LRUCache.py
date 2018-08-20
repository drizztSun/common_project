

import os
import collections

# Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.
# get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
# put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
# Follow up:
# Could you do both operations in O(1) time complexity?
# Example:
# LRUCache cache = new LRUCache( 2 /* capacity */ );

# cache.put(1, 1);
# cache.put(2, 2);
# cache.get(1);       // returns 1
# cache.put(3, 3);    // evicts key 2
# cache.get(2);       // returns -1 (not found)
# cache.put(4, 4);    // evicts key 1
# cache.get(1);       // returns -1 (not found)
# cache.get(3);       // returns 3
# cache.get(4);       // returns 4






class LRUCache(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self._capacity = capacity
        self._buff = {}
        


    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        res = self._buff.get(key, -1)

        return res

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """
        self._buff[key] = value
        
        if self._capacity >= len(self._buff):
            del self._buff[keyMin]

        

class LRUCache1(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self._capacity = capacity
        self._orderedDict = collections.OrderedDict()        


    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        res = -1
        if key in self._orderedDict:
            res = self._orderedDict[key]
            del self._orderedDict[key]
            self._orderedDict[key] = res # set it as new value
        return res

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """
        if key in self._orderedDict:
            self._orderedDict.pop(key)
        else:
            if self._capacity > 0:
                self._capacity -= 1
            else:
                self._orderedDict.popitem(False)

        self._orderedDict[key] = value


if __name__=="__main__":


    cache = LRUCache1(2)

    cache.put(1, 1);
    cache.put(2, 2);
    res = cache.get(1);       # returns 1
    cache.put(3, 3);    # evicts key 2
    res = cache.get(2);       # returns -1 (not found)
    cache.put(4, 4);    # evicts key 1
    res = cache.get(1);       # returns -1 (not found)
    res = cache.get(3);       # returns 3
    res = cache.get(4);       # returns 4

    pass