package main

import (
	"fmt"
	"sync"
)

/*
Map is like a Go map[interface{}]interface{} but is safe for concurrent use by multiple goroutines without additional locking or coordination.
Loads, stores, and deletes run in amortized constant time.

The Map type is specialized. Most code should use a plain Go map instead, with separate locking or coordination,
for better type safety and to make it easier to maintain other invariants along with the map content.

The Map type is optimized for two common use cases: (1) when the entry for a given key is only ever written once but read many times,
as in caches that only grow, or (2) when multiple goroutines read, write, and overwrite entries for disjoint sets of keys.
In these two cases, use of a Map may significantly reduce lock contention compared to a Go map paired with a separate Mutex or RWMutex.

The zero Map is empty and ready for use. A Map must not be copied after first use.

*/

func test_map_sync_multi() {
	var m sync.Map

	var a = []struct {
		club  string
		score int
	}{
		{
			"Barca",
			65,
		}, {
			"RealMadrid",
			59,
		}, {
			"Madrid Althetic",
			59,
		},
	}

	var c = make(chan bool, len(a))

	for _, v := range a {
		go func(club string, score int) {
			m.Store(club, score)
			c <- true
		}(v.club, v.score)
	}

	for i := 0; i < len(a); i++ {
		<-c
	}

}

func test_map_sync() {

	var m sync.Map

	m.Store("Barca", 65)
	m.Store("Real Madrid", 59)
	m.Store("Madrid Althetic", 59)

	v, ok := m.Load("Barca")
	fmt.Printf("Barca %d ,%b \n", v, ok)
	v, ok = m.Load("Real Madrid")
	fmt.Printf("Real Madrid %d \n", v, ok)
	v, ok = m.Load("Madrid Althetic")
	fmt.Printf("Madrid Althetic %d \n", v, ok)

	v, ok = m.LoadOrStore("Barca", 100)
	if ok {
		fmt.Println("Barca is there, %V \n", v)
	}

	v, ok = m.LoadOrStore("Valencia", 50)
	if !ok {
		fmt.Println("Valencia is %V %b", v, ok)
	}

	m.Delete("Valencia")

	if v, ok = m.Load("Valencia"); !ok {
		fmt.Println("Valencia does not existed")
	}

}

func main() {
	test_map_sync()
}
