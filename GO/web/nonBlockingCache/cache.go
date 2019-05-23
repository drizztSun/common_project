package main

import (
	"sync"
)

type Result struct {
	Value []byte
	Err	error
}

type Cache struct {
	cache map[string] *Result
	sync.Mutex
}

type Func func() ([]byte, error)

func NewCache() *Cache {
	return &Cache{cache: make(map[string] *Result)} 
}

// solution 1
func (c *Cache) Get_1 (key string, f Func) ([]byte, error) {
	// It is becoming a blocking cache, because of sync.Mutex
	// only one go routine to get-in in the same time
	c.Lock()
	defer c.Unlock()

	res, ok := c.cache[key]
	if !ok {
		res = &Result{}
		res.Value, res.Err = f()
		c.cache[key] = res 
	}

	return res.Value, res.Err
}

func (c *Cache) Get_2 (key string, f Func) ([]byte, error) {
	// read action and write action, we need use lock to control it.
	// this allows more goroutine to enter in the same time, only one can write. 
	// if it write, all other gorountine will be blocked
	// read action
	c.Lock()
	res, ok := c.cache[key]
	c.Unlock()

	if !ok {
		res = &Result{}
		res.Value, res.Err = f()
		
		// write action
		c.Lock()
		c.cache[key] = res
		c.Unlock()
	}

	return res.Value, res.Err
}
