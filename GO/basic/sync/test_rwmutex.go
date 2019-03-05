package main

import (
	"fmt"
	"sync"
)

// A RWMutex is a reader/writer mutual exclusion lock. The lock can be held by an arbitrary number of readers or a single writer.
// The zero value for a RWMutex is an unlocked mutex.

// A RWMutex must not be copied after first use.

// If a goroutine holds a RWMutex for reading and another goroutine might call Lock,
// no goroutine should expect to be able to acquire a read lock until the initial read lock is released.
// In particular, this prohibits recursive read locking. This is to ensure that the lock eventually becomes available; a blocked Lock call excludes new readers from acquiring the lock.

type counter struct {
	s int
}

func (obj *counter) read() int {
	return obj.s
}

func (obj *counter) write(b int) {
	obj.s += b
}

func read(id int, s *counter, m sync.RWMutex, w sync.WaitGroup) {

	for i := 0; i < 5; i++ {
		m.RLock()
		fmt.Println("Reader ", id, " val : ", s.read())
		m.RUnlock()
	}

	w.Done()
}

func write(id int, s *counter, m sync.RWMutex, w sync.WaitGroup) {

	for i := 0; i < 5; i++ {
		m.Lock()
		s.write(2)
		fmt.Println("Writer ", id, " val: ", s.read())
		m.Unlock()
	}

	w.Done()
}

func test_rwmutex() {

	var m sync.RWMutex
	s := counter{0}
	var w sync.WaitGroup

	w.Add(5)

	for i := 0; i < 3; i++ {
		go read(i, &s, m, w)
	}

	for i := 0; i < 2; i++ {
		go write(i, &s, m, w)
	}

	w.Wait()
}
