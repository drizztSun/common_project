package leetcodeE

/*
705. Design HashSet

Design a HashSet without using any built-in hash table libraries.

To be specific, your design should include these functions:

add(value): Insert a value into the HashSet.
contains(value) : Return whether the value exists in the HashSet or not.
remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.

Example:

MyHashSet hashSet = new MyHashSet();
hashSet.add(1);
hashSet.add(2);
hashSet.contains(1);    // returns true
hashSet.contains(3);    // returns false (not found)
hashSet.add(2);
hashSet.contains(2);    // returns true
hashSet.remove(2);
hashSet.contains(2);    // returns false (already removed)


*/

type MyHashSet struct {
	Vars []int
}

/** Initialize your data structure here. */
func MyHashSetConstructor() MyHashSet {
	obj := &MyHashSet{}
	return *obj
}

func (this *MyHashSet) Add(key int) {

}

func (this *MyHashSet) Remove(key int) {

}

/** Returns true if this set contains the specified element */
func (this *MyHashSet) Contains(key int) bool {

}
