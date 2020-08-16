package algorithm

/*
【题目】

　　哈希表常见的三个操作是 put、get 和 containsKey ，而且这三个操作的时间复杂度为 O(1)。现在想加一个 putAll 功能，就是把所有的 key 的 value 值都设成统一的值。请使用 Golang 设计并实现这种有 putAll 功能的哈希表，并且 put、 get、和 putAll 操作的时间复杂度都为 O(1) 。

【基本思路】

　　加入版本号字段 Version

　　1、把每一个记录的版本号都 + 1，标记每条记录建立的顺序；

　　2、设置一个 putAll 记录在之前 put 的操作之上版本号再 +1，以标记 putAll 记录何时建立；

　　3、查询记录时，如果某条记录的版本号小于 putAll 记录的版本，说明 putAll 是最新数据，返回 putAll 记录的值。如果某条记录的版本号大于 putAll 记录的版本，说明该记录的值是最新数据，返回该条记录的值。

* golang 代码实现 *

*/

import "fmt"

type PutAllValue struct {
	Value   string
	Version int
}

func (p *PutAllValue) GetValue() string {
	return p.Value
}

func (p *PutAllValue) GetVersion() int {
	return p.Version
}

type MyMap struct {
	Version int

	Mp map[string]*PutAllValue
}

func (m *MyMap) Put(key, value string) {
	p := &PutAllValue{}
	p.Value = value
	m.Version += 1
	m.Mp[key] = p
}

var pForPutAll = &PutAllValue{}

func (m *MyMap) PutAll(value string) {

	pForPutAll.Value = value
	m.Version += 1

	// 关键操作，要共享版本号的值
	pForPutAll.Version = m.Version
}

func (m *MyMap) Get(key string) string {

	if v, ok := m.Mp[key]; ok {
		if v.GetVersion() < pForPutAll.GetVersion() {
			return pForPutAll.GetValue()
		} else {
			return v.GetValue()
		}
	} else {
		return ""
	}
}

func test_map() {
	tmpM := make(map[string]*PutAllValue)
	mm := &MyMap{0, tmpM}

	mm.Put("1", "a")
	mm.Put("2", "b")
	mm.Put("3", "c")

	res := mm.Get("2")
	fmt.Println(res)

	// Put all the key as 'd'
	mm.PutAll("d")

	afterRes := mm.Get("1")
	fmt.Println(afterRes)
	res2 := mm.Get("2")
	fmt.Println(res2)
	fmt.Println("All the key's value set as 'd' ")
}
