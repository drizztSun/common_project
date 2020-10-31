"""
460. LFU Cache

# Design and implement a data structure for Least Frequently Used (LFU) cache.
# It should support the following operations: get and put.

# get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.

# put(key, value) - Set or insert the value if the key is not already present.

# When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item.
# For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency),
# the least recently used key would be evicted.

# Follow up:
# Could you do both operations in O(1) time complexity?


# Example:

# LFUCache cache = new LFUCache( 2 /* capacity */ );

# cache.put(1, 1);
# cache.put(2, 2);
# cache.get(1);       // returns 1
# cache.put(3, 3);    // evicts key 2
# cache.get(2);       // returns -1 (not found)
# cache.get(3);       // returns 3.
# cache.put(4, 4);    // evicts key 1.
# cache.get(1);       // returns -1 (not found)
# cache.get(3);       // returns 3
# cache.get(4);       // returns 4
"""
from collections import defaultdict, OrderedDict


class LFUCache:

    # All have O(1) Time
    def __init__(self, capacity: int):
        self.Freq, self.capacity, self.level = {}, capacity, 0
        self.Ordering = defaultdict(OrderedDict)

    def get(self, key: int) -> int:
        if key not in self.Freq:
            return -1

        freq = self.Freq[key]
        Data = self.Ordering[freq]
        value = Data.pop(key)

        # Update Step
        if self.level == freq and len(Data) == 0:
            self.level += 1

        self.Freq[key] += 1
        self.Ordering[freq + 1][key] = value
        return value

    def put(self, key: int, value: int) -> None:
        if self.capacity == 0:
            return

        freq = 0
        if key in self.Freq:
            freq = self.Freq[key]
            Data = self.Ordering[freq]
            del Data[key]

            if self.level == freq and len(Data) == 0:
                self.level += 1

        elif len(self.Freq) == self.capacity:
            k, v = self.Ordering[self.level].popitem(last=False)
            del self.Freq[k]

        if freq == 0:
            self.level = 1

        self.Freq[key] = freq + 1
        self.Ordering[freq + 1][key] = value


class listNode:

    def __init__(self, key=None, value=None):
        self.key_ = key
        self.val_ = value
        self.prev_, self.next_ = key, value

    def connect(self, next):
        if not next:
            return
        self.next_ = next
        next.prev_ = self


class LFUCache:

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.cap_ = capacity
        self.head_, self.tail_ = listNode(), listNode()
        self.head_.connect(self.tail_)

        self.keyV_ = {None: [self.tail_, 0]}
        self.cnt_ = {0: self.tail_}

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        if key not in self.keyV_:
            return -1

        self.moveForward(key)
        return self.keyV_[key][0].val_

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """
        if self.cap_ == 0:
            return -1

        if key in self.keyV_:
            self.keyV_[key][0].val_ = value
            self.moveForward(key)
            return

        if len(self.keyV_) > self.cap_:
            self.remove(self.tail_.prev_.key_)

        self.add(key, value, 0)        

    def moveForward(self, key):
        """
        :type key: int
        """
        node, cnt = self.keyV_[key]
    
        self.add('tmp', node.val_, cnt+1)
        self.remove(key)
    
        self.keyV_[key] = self.keyV_['tmp'] 
        self.keyV_[key][0].key_ = key
        del self.keyV_['tmp']

    def add(self, key, value, cnt):
        """
        """
        if cnt in self.cnt_:
            loc = self.cnt_[cnt]
        else:
            loc = self.cnt_[cnt - 1]

        node = listNode(key, value)

        loc.prev_.connect(node)
        node.connect(loc)

        self.cnt_[cnt] = node
        self.keyV_[key] = [node, cnt]

    def remove(self, key):
        """
        """
        node, cnt = self.keyV_[key]
        if self.cnt_[cnt] != node:
            node.prev_.connect(node.next_)

        elif self.keyV_[node.next_.key_][1] == cnt:
            node.prev_.connect(node.next_)
            self.cnt_[cnt] = self.cnt_[cnt].next_

        else:
            node.prev_.connect(node.next_)
            del self.cnt_[cnt]

        del self.keyV_[key]


if __name__ == "__main__":

    cache = LFUCache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    res = cache.get(1);       # returns 1
    cache.put(3, 3);    # evicts key 2
    res = cache.get(2);       # returns -1 (not found)
    res = cache.get(3);       # returns 3.
    cache.put(4, 4);    # evicts key 1.
    res = cache.get(1);       # returns -1 (not found)
    res = cache.get(3);       # returns 3
    res = cache.get(4);       # returns 4


    obj = LFUCache(2)

    obj.put(3, 1)
    obj.put(2, 1)
    obj.put(2, 2)

    obj.put(4, 4)
    
    res = obj.get(2)


    obj = LFUCache(3)

    obj.put(2, 2)
    obj.put(1, 1)
    res = obj.get(2)
    res = obj.get(1)
    res = obj.get(2)

    obj.put(3, 3)
    obj.put(4, 4)
    
    res = obj.get(3)
    res = obj.get(2)
    res = obj.get(1)
    res = obj.get(4)

    pass                    

