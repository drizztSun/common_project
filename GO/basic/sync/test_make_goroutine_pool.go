package main

// A very simple Thread Pool mode
type Task func()

type Pool struct {
	work chan Task
	sem  chan struct{} // semaphore
	quit chan struct{}
}

func NewThreadPool(size int) *Pool {
	return &Pool{
		work: make(chan Task),
		sem:  make(chan struct{}, size),
		quit: make(chan struct{}, size),
	}
}

func (p *Pool) Send(task Task) {

	select {
	case p.work <- task:
	case p.sem <- struct{}{}: // sem, use it to manage work routine
		go p.WorkTask(task)
	}
}

func (p *Pool) WorkTask(task Task) {
	for {
		task()

		select {
		case <-p.quit:
			break
		case task = <-p.work:
		}
	}
	<-p.sem // func out, than remove semaphore
}
