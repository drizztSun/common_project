package leetcodem

/*

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
Follow up:
Could you do get and put in O(1) time complexity?



Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4


Constraints:

1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 104
At most 3 * 104 calls will be made to get and put.

*/

type node struct {
	Key, Val int

	Pre, Next *node
}

type LRUCache struct {
	KeyMap map[int]*node

	Head, Tail *node

	Capacity int
}

func LRU_Constructor(capacity int) LRUCache {

	return LRUCache{
		KeyMap:   make(map[int]*node, 0),
		Head:     nil,
		Tail:     nil,
		Capacity: capacity,
	}
}

func (this *LRUCache) remove(c *node) {

	if this.Head == this.Tail {
		if this.Head == c {
			this.Head = nil
			this.Tail = nil
		}
		return
	} else if this.Head == c {
		this.Head = c.Next
		c.Next.Pre, c.Next = nil, nil
		return
	} else if this.Tail == c {
		this.Tail = c.Pre
		c.Pre, c.Pre.Next = nil, nil
		return
	}

	c.Pre.Next, c.Next.Pre = c.Next, c.Pre
}

func (this *LRUCache) moveToHead(c *node) {

	if this.Head == nil && this.Tail == nil {
		this.Head = c
		this.Tail = c
	} else {
		c.Next, c.Pre = this.Head, nil
		this.Head.Pre = c
		this.Head = c
	}
}

func (this *LRUCache) Get(key int) int {

	c, ok := this.KeyMap[key]
	if !ok {
		return -1
	}

	this.remove(c)
	this.moveToHead(c)
	return c.Val
}

func (this *LRUCache) Put(key int, value int) {

	if c, ok := this.KeyMap[key]; ok {
		c.Val = value
		this.remove(c)
		this.moveToHead(c)
		return
	}
	c := &node{
		Key:  key,
		Val:  value,
		Pre:  nil,
		Next: nil,
	}

	this.KeyMap[key] = c
	this.moveToHead(c)

	if len(this.KeyMap) > this.Capacity {
		key = this.Tail.Key
		delete(this.KeyMap, key)
		this.remove(this.Tail)
	}
}

func Test_146_LRUCache() {

	{
		obj := LRU_Constructor(2)

		obj.Put(1, 1)
		obj.Put(2, 2)
		obj.Get(1)
		obj.Put(3, 3)
		obj.Put(4, 4)
		obj.Get(1)
		obj.Get(3)
		obj.Get(4)
	}

	{
		obj1 := LRU_Constructor(2)

		obj1.Put(2, 1)
		obj1.Put(1, 1)
		obj1.Put(2, 3)
		obj1.Put(4, 1)
		obj1.Get(1)
		obj1.Get(2)

	}

}
