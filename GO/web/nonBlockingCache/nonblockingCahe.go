package main

import (
	"sync"
)

type entry struct {
	Res result
	ready chan struct{}  // chan struct{} is zero memory, only sync the action
}

type result struct {
	res []byte
	err error
}

type NBCache struct {
	sync.Mutex
	cache map[string] *entry
}

func (nbc *NBCache) GetNB(key string, f Func) ([]byte, error) {

	nbc.Lock()
	e, ok := nbc.cache[key]

	if !ok {
		// create a new one in cache mapping
		e = &entry{ready : make(chan struct{})}
		nbc.cache[key] = e
		nbc.Unlock()

		e.Res.res, e.Res.err = f()
		close(e.ready)
	} else {
		// we get this one, and wait if it is ready to use
		// by this code, maybe one routines creating and initializing it, another one doing read and wait it is ready to use.
		nbc.Unlock()
		<-e.ready // 
	}

	return e.Res.res, e.Res.err
}