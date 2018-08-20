
# 432. All O`one Data Structure

# Implement a data structure supporting the following operations:

# Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.

# Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1.
#    If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.

# GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".

# GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".

# Challenge: Perform all these in O(1) time complexity.



import collections
class AllOne(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.buff_ = collections.defaultdict(int)

        self.max_, self.min_ = float('-inf'), float('inf')

        self.nums_ = collections.defaultdict(set)

    def inc(self, key):
        """
        Inserts a new key <Key> with value 1. Or increments an existing key by 1.
        :type key: str
        :rtype: void
        """
        old = self.buff_[key]
        self.buff_[key] += 1

        if old != 0:
            self.nums_[old].remove(key)
            if not self.nums_[old]:
                del self.nums_[old]

        self.nums_[self.buff_[key]].add(key)

        
            

    def dec(self, key):
        """
        Decrements an existing key by 1. If Key's value is 1, remove it from the data structure.
        :type key: str
        :rtype: void
        """
        if key in self.buff_:
            old = self.buff_[key]
            if old != 1:
                self.buff_[key] -= 1
                self.nums_[self.buff_[key]].add(key) 
            else:
                del self.buff_[key]

            self.nums_[old].remove(key)
            if not self.nums_[old]:
                del self.nums_[old]
            

    def getMaxKey(self):
        """
        Returns one of the keys with maximal value.
        :rtype: str
        """
        return list(self.nums_[max(self.nums_.keys())])[0]

    def getMinKey(self):
        """
        Returns one of the keys with Minimal value.
        :rtype: str
        """
        return list(self.nums_[min(self.nums_.keys())])[0]





class AllOne1(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.my_ds = {}

    def inc(self, key):
        """
        Inserts a new key <Key> with value 1. Or increments an existing key by 1.
        :type key: str
        :rtype: void
        """
        if key in self.my_ds:
            self.my_ds[key] += 1
        else:
            self.my_ds[key] = 1

    def dec(self, key):
        """
        Decrements an existing key by 1. If Key's value is 1, remove it from the data structure.
        :type key: str
        :rtype: void
        """
        if key in self.my_ds:
            if self.my_ds[key] > 1:
                self.my_ds[key] -= 1
            elif self.my_ds[key] == 1:
                del self.my_ds[key]

    def getMaxKey(self):
        """
        Returns one of the keys with maximal value.
        :rtype: str
        """
        if not self.my_ds:
            return ""
        else:
            max_val = 0
            max_key = ""
            for key in self.my_ds:
                if self.my_ds[key] > max_val:
                    max_val = self.my_ds[key]
                    max_key = key
                
            if max_key == "":
                return ""
            else:
                return max_key

    def getMinKey(self):
        """
        Returns one of the keys with Minimal value.
        :rtype: str
        """
        if not self.my_ds:
            return ""
        else:
            min_val = sys.maxint
            min_key = ""
            for key in self.my_ds:
                if self.my_ds[key] < min_val:
                    min_val = self.my_ds[key]
                    min_key = key
                
            if min_key == "":
                return ""
            else:
                return min_key

# Your AllOne object will be instantiated and called as such:
# obj = AllOne()
# obj.inc(key)
# obj.dec(key)
# param_3 = obj.getMaxKey()
# param_4 = obj.getMinKey()

if __name__=="__main__":

    obj = AllOne()

    obj.inc("a")
    obj.inc('b')
    obj.inc('b')

    obj.inc('c')
    obj.inc('c')
    obj.inc('c')

    obj.dec('b')
    obj.dec('b')


    res = obj.getMaxKey()
    res = obj.getMinKey()

    #obj.dec('df')
    obj.dec('a')

    res = obj.getMaxKey()
    res = obj.getMinKey()


    pass        