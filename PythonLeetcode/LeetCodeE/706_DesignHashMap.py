"""
706. Design HashMap

Design a HashMap without using any built-in hash table libraries.

To be specific, your design should include these functions:

put(key, value) : Insert a (key, value) pair into the HashMap. If the value already exists in the HashMap, update the value.
get(key): Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
remove(key) : Remove the mapping for the value key if this map contains the mapping for the key.

Example:

MyHashMap hashMap = new MyHashMap();
hashMap.put(1, 1);
hashMap.put(2, 2);
hashMap.get(1);            // returns 1
hashMap.get(3);            // returns -1 (not found)
hashMap.put(2, 1);          // update the existing value
hashMap.get(2);            // returns 1
hashMap.remove(2);          // remove the mapping for 2
hashMap.get(2);            // returns -1 (not found)

Note:

All keys and values will be in the range of [0, 1000000].
The number of operations will be in the range of [1, 10000].
Please do not use the built-in HashMap library.

"""

"""

Intuition
Hashmap is a common data structure that is implemented in various forms in different programming languages, e.g. dict in 
Python and HashMap in Java. The most distinguish characteristic about hashmap is that it provides a fast access to a value that is associated with a given key.

There are two main issues that we should tackle, in order to design an efficient hashmap data structure: 1). hash function design and 2). collision handling.

1). hash function design: the purpose of hash function is to map a key value to an address in the storage space, similarly to the system that we assign a postcode to each mail address. As one can image, 
for a good hash function, it should map different keys evenly across the storage space, so that we don't end up with the case that the majority of the keys are concentrated in a few spaces.

2). collision handling: essentially the hash function reduces the vast key space into a limited address space. 
As a result, there could be the case where two different keys are mapped to the same address, which is what we call 'collision'. Since the collision is inevitable, it is important that we have a strategy to handle the collision.

Depending on how we deal with each of the above two issues, we could have various implementation of hashmap data structure.


Approach 1: Modulo + Array
Intuition

As one of the most intuitive implementations, we could adopt the modulo operator as the hash function, since the key value is of integer type. 
In addition, in order to minimize the potential collisions, it is advisable to use a prime number as the base of modulo, e.g. 2069.

We organize the storage space as an array where each element is indexed with the output value of the hash function.

In case of collision, where two different keys are mapped to the same address, we use a bucket to hold all the values. 
The bucket is a container that hold all the values that are assigned by the hash function. We could use either a LinkedList or an Array to implement the bucket data structure.

Algorithm

For each of the methods in hashmap data structure, namely get(), put() and remove(), it all boils down to the method to locate the value that is stored in hashmap, given the key.

This localization process can be done in two steps:

For a given key value, first we apply the hash function to generate a hash key, which corresponds to the address in our main storage. 
With this hash key, we would find the bucket where the value should be stored.
Now that we found the bucket, we simply iterate through the bucket to check if the desired <key, value> pair does exist.

"""

class Bucket:
    def __init__(self):
        self.bucket = []

    def get(self, key):
        for (k, v) in self.bucket:
            if k == key:
                return v
        return -1

    def update(self, key, value):
        found = False
        for i, kv in enumerate(self.bucket):
            if key == kv[0]:
                self.bucket[i] = (key, value)
                found = True
                break

        if not found:
            self.bucket.append((key, value))

    def remove(self, key):
        for i, kv in enumerate(self.bucket):
            if key == kv[0]:
                del self.bucket[i]


class MyHashMap(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        # better to be a prime number, less collision
        self.key_space = 2069
        self.hash_table = [Bucket() for i in range(self.key_space)]

    def put(self, key, value):
        """
        value will always be non-negative.
        :type key: int
        :type value: int
        :rtype: None
        """
        hash_key = key % self.key_space
        self.hash_table[hash_key].update(key, value)

    def get(self, key):
        """
        Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key
        :type key: int
        :rtype: int
        """
        hash_key = key % self.key_space
        return self.hash_table[hash_key].get(key)

    def remove(self, key):
        """
        Removes the mapping of the specified value key if this map contains a mapping for the key
        :type key: int
        :rtype: None
        """
        hash_key = key % self.key_space
        self.hash_table[hash_key].remove(key)


class MyHashMap:

    class node:

        def __init__(self, key, val):
            self.key = key
            self.val = val
            self.next = self.pre = None

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._size = 1024
        self._buket = [None] * self._size

    def _getitem(self, key):
        n = self._buket[key % self._size]
        while n:
            if n.key == key:
                break
            n = n.next

        return n

    def put(self, key: int, value: int) -> None:
        """
        value will always be non-negative.
        """

        if n := self._getitem(key):
            n.val = value
            return

        c = key % self._size
        n = MyHashMap.node(key, value)

        if not self._buket[c]:
            n.pre == c
            self._buket[c] = n
        else:
            n.next, n.pre, self._buket[c].pre = self._buket[c], c, n

    def get(self, key: int) -> int:
        """
        Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key
        """
        n = self._getitem(key)
        return -1 if not n else n.val

    def remove(self, key: int) -> None:
        """
        Removes the mapping of the specified value key if this map contains a mapping for the key
        """
        self._buket[key % self._size] = None


if __name__ == '__main__':

    hashMap = MyHashMap()
    hashMap.put(1, 1)
    hashMap.put(2, 2)
    hashMap.get(1)
    hashMap.get(3)
    hashMap.put(2, 1)
    hashMap.get(2)
    hashMap.remove(2)
    hashMap.get(2)