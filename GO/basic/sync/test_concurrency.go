package main

import (
	"fmt"
	"sync"
)

// * if you have to wait for the result of an operation, it is easier to do it yourself
// * Release locks and semaphores in the reverse order you acquired them
// * Channels aren't resources like file and sockets, you don't need to close them to free them
// * Acquire semaphores when you're ready to use them
// * Avoid mixing annoymous functions with goroutines
// * Before start a goroutine, always know when, and how, it will stop

/*
func restore(repos []string) error {

	errChan := make(chan error, 1)
	sem := make(chan int, 4) // semphore allow four object once run

	var wg sync.WaitGroup
	wg.Add(len(repos))

	for _, repo := range repos {

		/* old codes problems
		go func () {

			defer func () {
				wg.Done()
				// There are four wg.Done executes. When last one done has been executed, wg.wait() in main thread will call and then close the "sem"
				// "close(sem)", and then last "<-sem" will fail, because it has been closed.
				<-sem
			}()

			// use repo caused problem. because four thread share the same repo, so it will be changed between for_loop
			// so we need change it to repos[i]
			if err := fetch(repo); err != nil {
				errChan <- err
			}
		}()

		sem <- 1
		go func(repo string) {
			defer wg.Done()
			if err := fetch(repo); err != nil {
				//
				errChan <- err
			}
			<-sem
		}(repos[i])
	}

	wg.Wait()
	close(sem) // chan is not like file and socket, you need to close it to free. so it is not necessary
	close(errChan)
	return <-errChan
} */

func fetch(repo string) error {

	return nil
}

func work(repo string, wg *sync.WaitGroup, sem chan int, errChan chan error) {
	defer wg.Done()
	sem <- 1
	if err := fetch(repo); err != nil {

		select {
		case <-errChan:
			fmt.Println("Put errchan result back")
		default:
			fmt.Println("some failure has already happened")
		}
	}

	<-sem
}

func restore(repos []string) error {
	errChan := make(chan error, 1)
	sem := make(chan int, 4)

	var wg sync.WaitGroup

	for i := range repos {
		go work(repos[i], &wg, sem, errChan)
	}

	wg.Wait()
	close(errChan)
	return <-errChan
}
