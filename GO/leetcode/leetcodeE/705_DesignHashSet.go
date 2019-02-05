package leetcodeE

import "fmt"

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

func (this *MyHashSet) Search(key int) int {
	low, high := 0, len(this.Vars)
	for low < high {
		mid := (low + high) / 2
		if this.Vars[mid] == key {
			return mid
		} else if this.Vars[mid] > key {
			high = mid
		} else {
			low = mid + 1
		}
	}
	return low
}

func (this *MyHashSet) Add(key int) {

	i := this.Search(key)
	if i == len(this.Vars) {
		this.Vars = append(this.Vars, key)
	} else if this.Vars[i] != key {
		this.Vars = append(this.Vars[:i], append([]int{key}, this.Vars[i:]...)...)
	}
	return
}

func (this *MyHashSet) Remove(key int) {
	i := this.Search(key)
	if i != len(this.Vars) && this.Vars[i] == key {
		this.Vars = append(this.Vars[:i], this.Vars[i+1:]...)
	}
}

func (this *MyHashSet) Contains(key int) bool {
	i := this.Search(key)
	return i != len(this.Vars) && this.Vars[i] == key
}

func test705DegisnHashSet() {

	obj := MyHashSetConstructor()

	obj.Add(1)
	obj.Add(2)

	fmt.Println(obj.Contains(1))
	fmt.Println(obj.Contains(3))

	obj.Add(2)

	fmt.Println(obj.Contains(2))
	obj.Remove(2)
	fmt.Println(obj.Contains(2))

}
