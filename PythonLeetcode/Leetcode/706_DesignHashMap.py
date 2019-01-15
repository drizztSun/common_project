# 706. Design HashMap

# Design a HashMap without using any built-in hash table libraries.

# To be specific, your design should include these functions:

# put(key, value) : Insert a (key, value) pair into the HashMap. If the value already exists in the HashMap, update the value.
# get(key): Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
# remove(key) : Remove the mapping for the value key if this map contains the mapping for the key.

# Example:

# MyHashMap hashMap = new MyHashMap();
# hashMap.put(1, 1);          
# hashMap.put(2, 2);         
# hashMap.get(1);            // returns 1
# hashMap.get(3);            // returns -1 (not found)
# hashMap.put(2, 1);          // update the existing value
# hashMap.get(2);            // returns 1 
# hashMap.remove(2);          // remove the mapping for 2
# hashMap.get(2);            // returns -1 (not found) 



class MyHashMap:

    class __listNode:
        def __init__(self, key, val):
            self.pair = (key, val)
            self.next = None


    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.m = 1000
        self.h = [None] * self.m
        

    def put(self, key, value):
        """
        value will always be non-negative.
        :type key: int
        :type value: int
        :rtype: void
        """
        index = key % self.m
        if not self.h[index]:
            self.h[index] = MyHashMap.__listNode(key, value)
            return 

        cur = self.h[index]
        while cur:
            if cur.pair[0] == key:
                cur.pair = (key, value) #update
                break
            elif not cur.next:
                cur.next = MyHashMap.__listNode(key, value)
                break
            cur = cur.next
        

    def get(self, key):
        """
        Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key
        :type key: int
        :rtype: int
        """
        index = key % self.m
        cur = self.h[index]
        while cur:
            if cur.pair[0] == key:
                return cur.pair[1]
            cur = cur.next
        return -1
            
        

    def remove(self, key):
        """
        Removes the mapping of the specified value key if this map contains a mapping for the key
        :type key: int
        :rtype: void
        """
        index = key % self.m
        if not self.h[index]:
            return 

        cur = prev = self.h[index]
        if self.h[index].pair[0] == key:
            self.h[index]= cur.next
            return
        else:
            while cur:
                if cur.pair[0] == key:
                    prev.next = cur.next
                    break
                cur, prev = cur.next, cur
        

if __name__ == "__main__":

    obj1 = MyHashMap()
    obj1.put(1, 1)
    obj1.put(2, 2)
    res = obj1.get(1)     
    res = obj1.get(3)   
    obj1.put(2, 1)  
    res = obj1.get(2)   
    obj1.remove(2)  
    res = obj1.get(2)


    obj = MyHashMap()
    obj.remove(14)
    res = obj.get(4)
    obj.put(7, 3)
    obj.put(11, 1)
    obj.put(12, 1)
    res = obj.get(7)
    obj.put(1, 19)
    obj.put(0, 3)
    obj.put(1, 8)
    obj.put(2, 6) 

    res = 0