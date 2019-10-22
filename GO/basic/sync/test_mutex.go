package main

import (
	"fmt"
	"sync"
	"time"
)

func test_synctest() {

	fmt.Println("--- Test_synctest begin ---")
	var m sync.Mutex
	// var c = make(chan int, 10)
	var wg sync.WaitGroup
	wg.Add(10)

	for i := 0; i < 10; i++ {
		fmt.Printf("create thread %d\n", i)
		go func(i int) {
			m.Lock()

			for N := 0; N < 10; N++ {
				fmt.Printf("It is coming from thread %d \n", i)
			}
			m.Unlock()
			wg.Done()
		}(i)
	}

	wg.Wait()
	fmt.Println("--- Test_synctest end ---")
}

type safeCount struct {
	v   map[string]int
	mux sync.Mutex
}

func (c *safeCount) Inc(key string) {
	c.mux.Lock()
	// Lock so only one goroutine at a time can access the map c.v.
	c.v[key]++
	c.mux.Unlock()
}

func (c *safeCount) Value(key string) int {
	c.mux.Lock()
	defer c.mux.Unlock()
	return c.v[key]
}

func test_safeCount() {
	c := safeCount{v: make(map[string]int)}

	for i := 0; i < 1000; i++ {
		go c.Inc("somekey")
	}

	time.Sleep(time.Second)
	fmt.Println(c.Value("somekey"))
}

/*
A RWMutex is a reader/writer mutual exclusion lock. The lock can be held by an arbitrary number of readers or a single writer. The zero value for a RWMutex is an unlocked mutex.

A RWMutex must not be copied after first use.

If a goroutine holds a RWMutex for reading and another goroutine might call Lock, no goroutine should expect to be able to acquire a read lock until the initial read lock is released. In particular, this prohibits recursive read locking. This is to ensure that the lock eventually becomes available; a blocked Lock call excludes new readers from acquiring the lock.

*/

func test_mutex_rw() {

}

func test_mutex_basic() {

	// *** Zero-value Mutexes are Valid
	// The zero-value of sync.Mutex and sync.RWMutex is valid, so you almost never need a pointer to a mutex.
	{
		// good
		var mu sync.Mutex
		mu.Lock()
		defer mu.Unlock()
	}

	{
		//bad
		mu := new(sync.Mutex)
		mu.Lock()
		defer mu.Unlock()
	}

}

// If you use a struct by pointer, then the mutex can be a non-pointer field.
// Unexported structs that use a mutex to protect fields of the struct may embed the mutex.
type smap struct {
	sync.Mutex // only for unexported types
	// Embed for private types or types that need to implement the Mutex interface.
	data map[string]string
}

func newSMap() *smap {
	return &smap{
		data: make(map[string]string),
	}
}

func (m *smap) Get(k string) string {
	m.Lock()
	defer m.Unlock()

	return m.data[k]
}

type SMap struct {
	mu sync.Mutex // 	For exported types, use a private field.

	data map[string]string
}

func NewSMap() *SMap {
	return &SMap{
		data: make(map[string]string),
	}
}

func (m *SMap) Get(k string) string {
	m.mu.Lock()
	defer m.mu.Unlock()

	return m.data[k]
}

func test_mutex() {

	test_synctest()
}
