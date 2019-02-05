package leetcodeE

type MyHashMap struct {
	keys   []int
	values []int
}

/** Initialize your data structure here. */
func MyHashMapConstructor() MyHashMap {
	a := MyHashMap{}
	a.keys = make([]int, 0)
	a.values = make([]int, 0)
	return a
}

/** value will always be non-negative. */
func (this *MyHashMap) Put(key int, value int) {
	i := 0
	for i < len(this.keys) {
		if this.keys[i] == key {
			break
		}
		i++
	}

	if i == len(this.keys) {
		this.keys = append(this.keys, key)
		this.values = append(this.values, value)
	} else {
		this.values[i] = value
	}
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
func (this *MyHashMap) Get(key int) int {
	i := 0
	for i < len(this.keys) {
		if this.keys[i] == key {
			break
		}
		i++
	}
	if i == len(this.keys) {
		return -1
	} else {
		return this.values[i]
	}
}

/** Removes the mapping of the specified value key if this map contains a mapping for the key */
func (this *MyHashMap) Remove(key int) {
	i := 0
	for i < len(this.keys) {
		if this.keys[i] == key {
			break
		}
		i++
	}

	if i == len(this.keys) {
		return
	}

	this.keys = append(this.keys[:i], this.keys[i+1:]...)
	this.values = append(this.values[:i], this.values[i+1:]...)
}

/**
 * Your MyHashMap object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Put(key,value);
 * param_2 := obj.Get(key);
 * obj.Remove(key);
 */
