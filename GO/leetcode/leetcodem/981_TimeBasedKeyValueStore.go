package leetcodem

import (
	"fmt"
)

type item struct {
	TimeStamp int
	Value     string
}
type TimeMap struct {
	group map[string][]item
}

func TimeMap_Constructor() TimeMap {
	return TimeMap{group: make(map[string][]item)}
}

func (this *TimeMap) Set(key string, value string, timestamp int) {

	this.group[key] = append(this.group[key], item{TimeStamp: timestamp, Value: value})
}

func (this *TimeMap) Get(key string, timestamp int) string {

	if len(this.group[key]) == 0 || this.group[key][0].TimeStamp > timestamp {
		return ""
	}

	v := this.group[key]
	l, r := 0, len(v)-1

	for l <= r {

		mid := (l + r) / 2

		if v[mid].TimeStamp == timestamp {
			return v[mid].Value
		} else if v[mid].TimeStamp > timestamp {
			r = mid - 1
		} else {
			l = mid + 1
		}
	}

	return v[r].Value
}

func Test_981_time_based_key_value_store() {

	var kv = TimeMap_Constructor()
	var res string

	kv.Set("foo", "bar2", 0)
	kv.Set("foo", "bar", 1) // store the key "foo" and value "bar" along with timestamp = 1
	kv.Set("foo", "bar3", 3)
	kv.Set("foo", "bar4", 4)
	kv.Set("foo", "bar5", 5)

	res = kv.Get("foo", 1) // output "bar"
	res = kv.Get("foo", 2) // output "bar" since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 ie "bar"

	res = kv.Get("foo", 4) // output "bar2"
	res = kv.Get("foo", 5) //output "bar2"

	fmt.Println(res)
}
