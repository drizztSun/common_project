"""
146 LRU Cache

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

"""


class node:
    
    def __init__(self, key, val, next=None, pre=None):
        self._key = key
        self._val = val
        self._next = next
        self._pre = pre


class LRUCache:

    def __init__(self, capacity: 'int'):
        self._capacity = capacity
        self._buff = {}
        self._chain = node(-1, -1)
        self._chain._next = self._chain
        self._chain._pre = self._chain
        
    def __move_to_head(self, c):
        # self._chain._next, c._next, c._pre, self._chain._next._pre = c, self._chain._next, self._chain, c
        c._next, self._chain._next._pre = self._chain._next, c
        c._pre, self._chain._next = self._chain, c

    def __remove_from_chain(self, res):        
        res._pre._next, res._next._pre = res._next, res._pre
        return res
    
    def get(self, key: 'int') -> 'int':
        if key not in self._buff:
            return -1

        res = self._buff[key]
        
        self.__move_to_head(self.__remove_from_chain(res))

        return res._val           

    def put(self, key: 'int', value: 'int') -> 'None':
        if key in self._buff:
            self.get(key)
            self._buff[key]._val = value
        else:
            c = node(key, value)
            self.__move_to_head(c)
            self._buff[key] = c

            if self._capacity < len(self._buff):
                c = self.__remove_from_chain(self._chain._pre)
                del self._buff[c._key]
            
            

        
import collections

class LRUCache2(object):

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




class Node1:
    
    def __init__(self, key, val, next = None, prev = None):
        self.key_ = key
        self.val_ = val
        self.next_ = next
        self.prev_ = prev


class LRUCache1:
    
    def __init__ (self, capcaity):
        self.cap_ = capcaity
        self.k2v_ = {}

        self.head_ = Node(0, 0)
        self.tail_ = Node(0, 0)

        self.head_.next_ = self.tail_
        self.tail_.prev_ = self.head_

        self.len_ = 0

    def get(self, key):
        
        if key in self.k2v_:
            node =self.k2v_[key]
            self.move_to_front(node)
            return node.val_
        else:
            return -1
    
    def put(self, key, val):
        
        if key in self.k2v_:
            node = self.k2v_[key]
            node.val_ = val
            self.move_to_front(node)

        elif self.len_ < self.cap_:
            
            node = Node(key, val)
            self.k2v_[key] = node
            self.len_ += 1
            self.add_to_front(node)

        else:
            lnode = self.tail_.prev_
            del self.k2v_[lnode.key_]
            self.remove_node(lnode)

            node = Node(key, val)
            self.k2v_[key] = node
            self.add_to_front(node)

    def add_to_front(self, node):
        
        node.next_ = self.head_.next_
        node.prev_ = self.head_
        self.head_.next_.prev_ = node
        self.head_.next_ = node
        
        

    def remove_node(self, node):
        node.prev_.next_ = node.next_
        node.next_.prev_ = node.prev_

        node.next_, node.prev_ = None, None

    def move_to_front(self, node):
        self.remove_node(node)
        self.add_to_front(node)

if __name__=="__main__":


    cache = LRUCache(2)

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