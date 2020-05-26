
// *** Shared-State Concurrency ***
// Message passing is a fine way of handling concurrency, but it’s not the only one. 
// Consider this part of the slogan from the Go language documentation again: “communicate by sharing memory.”

// What would communicating by sharing memory look like? In addition, why would message-passing enthusiasts not use it and do the opposite instead?

// 1） In a way, channels in any programming language are similar to single ownership, because once you transfer a value down a channel, you should no longer use that value.
// 2） Shared memory concurrency is like multiple ownership: multiple threads can access the same memory location at the same time.
// As you saw in Chapter 15, where smart pointers made multiple ownership possible, multiple ownership can add complexity because these different owners need managing. 
// Rust’s type system and ownership rules greatly assist in getting this management correct. For an example, let’s look at mutexes, one of the more common concurrency primitives for shared memory.


use std::thread;
use std::sync::{Mutex, Arc};

// *** Using Mutexes to Allow Access to Data from One Thread at a Time ***

// Mutex is an abbreviation for mutual exclusion, as in, a mutex allows only one thread to access some data at any given time.
// To access the data in a mutex, a thread must first signal that it wants access by asking to acquire the mutex’s lock.
// The lock is a data structure that is part of the mutex that keeps track of who currently has exclusive access to the data.
// Therefore, the mutex is described as guarding the data it holds via the locking system.

// Mutexes have a reputation for being difficult to use because you have to remember two rules:

// 1） You must attempt to acquire the lock before using the data.
// 2） When you’re done with the data that the mutex guards, you must unlock the data so other threads can acquire the lock.

// For a real-world metaphor for a mutex, imagine a panel discussion at a conference with only one microphone. 
// Before a panelist can speak, they have to ask or signal that they want to use the microphone. 
// When they get the microphone, they can talk for as long as they want to and then hand the microphone to the next panelist who requests to speak. If a panelist forgets to hand the microphone off when they’re finished with it, no one else is able to speak. If management of the shared microphone goes wrong, the panel won’t work as planned!


// Management of mutexes can be incredibly tricky to get right, which is why so many people are enthusiastic about channels.
// However, thanks to Rust’s type system and ownership rules, you can’t get locking and unlocking wrong.

fn test_mutex_basic() {
    let m = Mutex::new(5);

    {
        // The call to lock would fail if another thread holding the lock panicked. In that case, no one would ever be able to get the lock,
        // so we’ve chosen to unwrap and have this thread panic if we’re in that situation.
        let mut num = m.lock().unwrap();

        // As you might suspect, Mutex<T> is a smart pointer. More accurately, the call to lock returns a smart pointer called MutexGuard, wrapped in a LockResult that we handled with the call to unwrap.
        // The MutexGuard smart pointer implements Deref to point at our inner data; the smart pointer also has a Drop implementation that releases the lock automatically when a MutexGuard goes out of scope,
        // which happens at the end of the inner scope
        // As a result, we don’t risk forgetting to release the lock and blocking the mutex from being used by other threads because the lock release happens automatically.
        *num = 6;
    }

    println!("m = {:?}", m);
}


/*
// *** Sharing a Mutex<T> Between Multiple Threads ***
fn test_mutex_between_threads() {

    let counter = Mutex::new(0);
    let mut handles = vec![];

    for _ in 0..10 {
        let handle = thread::spawn( move || {
            let mut num = counter.lock().unwrap();
            *num += 1;
        });

        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter)
}


*** Multiple Ownership with Multiple Threads ***

fn main() {
    let counter = Rc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Rc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();

            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());
}

The compiler is also telling us the reason why: the trait `Send` is not implemented for `Rc<Mutex<i32>>` .
We’ll talk about Send in the next section: it’s one of the traits that ensures the types we use with threads are meant for use in concurrent situations.

Unfortunately, Rc<T> is not safe to share across threads. When Rc<T> manages the reference count, it adds to the count for each call to clone and subtracts from the count when each clone is dropped.

But it doesn’t use any concurrency primitives to make sure that changes to the count can’t be interrupted by another thread.
This could lead to wrong counts—subtle bugs that could in turn lead to memory leaks or a value being dropped before we’re done with it.
What we need is a type exactly like Rc<T> but one that makes changes to the reference count in a thread-safe way.
*/

// *** Atomic Reference Counting with Arc<T> ***
// Fortunately, Arc<T> is a type like Rc<T> that is safe to use in concurrent situations.
// The a stands for atomic, meaning it’s an atomically reference counted type.

// Atomics are an additional kind of concurrency primitive that we won’t cover in detail here: see the standard library documentation for std::sync::atomic for more details.
// At this point, you just need to know that atomics work like primitive types but are safe to share across threads.

// You might then wonder why all primitive types aren’t atomic and why standard library types aren’t implemented to use Arc<T> by default.
// The reason is that thread safety comes with a performance penalty that you only want to pay when you really need to.
// If you’re just performing operations on values within a single thread, your code can run faster if it doesn’t have to enforce the guarantees atomics provide.

fn test_mutex_between_threads() {

    let counter = Arc::new(Mutex.new(0)); // if we use Rc<T>, it will get problem because of Multithread.
    let mut handles = vec![];


    // We create a counter variable to hold an i32 inside a Mutex<T>, as we did in Listing 16-12. 
    // Next, we create 10 threads by iterating over a range of numbers.
    // We use thread::spawn and give all the threads the same closure, one that moves the counter into the thread, 
    // acquires a lock on the Mutex<T> by calling the lock method, and then adds 1 to the value in the mutex. 
    // When a thread finishes running its closure, num will go out of scope and release the lock so another thread can acquire it.
    for i in 0..10 {
        let cnt = Arc::clone(&counter);
        let handle = thread::spawn( move || {
            let mut num = cnt.lock().unwrap();
            *num += 1;
        });

        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());
}

use std::marker::{Send, Sync};
use std::sync::{atomic};


// *** Similarities Between RefCell<T>/Rc<T> and Mutex<T>/Arc<T> ***
// You might have noticed that counter is immutable but we could get a mutable reference to the value inside it; 
// this means Mutex<T> provides interior mutability, as the Cell family does.
// In the same way we used RefCell<T> in Chapter 15 to allow us to mutate contents inside an Rc<T>, we use Mutex<T> to mutate contents inside an Arc<T>.

// Another detail to note is that Rust can’t protect you from all kinds of logic errors when you use Mutex<T>. 
// Recall in Chapter 15 that using Rc<T> came with the risk of creating reference cycles, where two Rc<T> values refer to each other,
// causing memory leaks. Similarly, Mutex<T> comes with the risk of creating deadlocks.
// These occur when an operation needs to lock two resources and two threads have each acquired one of the locks,
// causing them to wait for each other forever. If you’re interested in deadlocks, try creating a Rust program that has a deadlock;
// then research deadlock mitigation strategies for mutexes in any language and have a go at implementing them in Rust. 
// The standard library API documentation for Mutex<T> and MutexGuard offers useful information.



// *** Extensible Concurrency with the Sync and Send Traits
// Interestingly, the Rust language has very few concurrency features.
// Almost every concurrency feature we’ve talked about so far in this chapter has been part of the standard library, not the language. 
// Your options for handling concurrency are not limited to the language or the standard library; you can write your own concurrency features or use those written by others.

// *** However, two concurrency concepts are embedded in the language: the std::marker traits Sync and Send ***.

// *** Allowing Transference of Ownership Between Threads with Send
// The Send marker trait indicates that ownership of the type implementing Send can be transferred between threads.
// Almost every Rust type is Send, but there are some exceptions, including Rc<T>: this cannot be Send because if you cloned an Rc<T> value and tried to transfer ownership of the clone to another thread, both threads might update the reference count at the same time.
// For this reason, Rc<T> is implemented for use in single-threaded situations where you don’t want to pay the thread-safe performance penalty.

// Therefore, Rust’s type system and trait bounds ensure that you can never accidentally send an Rc<T> value across threads unsafely. When we tried to do this in Listing 16-14, we got the error the trait Send is not implemented for Rc<Mutex<i32>>. When we switched to Arc<T>, which is Send, the code compiled.
// Any type composed entirely of Send types is automatically marked as Send as well. Almost all primitive types are Send, aside from raw pointers, which we’ll discuss in Chapter 19.

// *** Allowing Access from Multiple Threads with Sync
// The Sync marker trait indicates that it is safe for the type implementing Sync to be referenced from multiple threads. 
//  In other words, any type T is Sync if &T (a reference to T) is Send, meaning the reference can be sent safely to another thread. Similar to Send, primitive types are Sync, and types composed entirely of types that are Sync are also Sync.

// The smart pointer Rc<T> is also not Sync for the same reasons that it’s not Send. The RefCell<T> type (which we talked about in Chapter 15) and the family of related Cell<T> types are not Sync. The implementation of borrow checking that RefCell<T> does at runtime is not thread-safe. The smart pointer Mutex<T> is Sync and can be used to share access with multiple threads as you saw in the “Sharing a Mutex<T> Between Multiple Threads” section.

// *** Implementing Send and Sync Manually Is Unsafe
// Because types that are made up of Send and Sync traits are automatically also Send and Sync, 
// we don’t have to implement those traits manually. As marker traits, they don’t even have any methods to implement.
// They’re just useful for enforcing invariants related to concurrency.

// Manually implementing these traits involves implementing unsafe Rust code. We’ll talk about using unsafe Rust code in Chapter 19;
// for now, the important information is that building new concurrent types not made up of Send and Sync parts requires careful thought to uphold the safety guarantees. The Rustonomicon has more information about these guarantees and how to uphold them.

pub fn test_concurrency() {

    test_mutex_basic();

    test_mutex_between_threads();

}

