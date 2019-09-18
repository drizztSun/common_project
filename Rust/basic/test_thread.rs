// Initially, the Rust team thought that ensuring memory safety and preventing concurrency problems were two separate challenges to be solved with different methods. 
// Over time, the team discovered that the ownership and type systems are a powerful set of tools to help manage memory safety and concurrency problems! 
// By leveraging ownership and type checking, many concurrency errors are compile-time errors in Rust rather than runtime errors. 
// Therefore, rather than making you spend lots of time trying to reproduce the exact circumstances under which a runtime concurrency bug occurs, incorrect code will refuse to compile and present an error explaining the problem. 
// As a result, you can fix your code while you’re working on it rather than potentially after it has been shipped to production. We’ve nicknamed this aspect of Rust fearless concurrency. 
// Fearless concurrency allows you to write code that is free of subtle bugs and is easy to refactor without introducing new bugs.

// Here are the topics we’ll cover in this chapter:

// How to create threads to run multiple pieces of code at the same time
// Message-passing concurrency, where channels send messages between threads
// Shared-state concurrency, where multiple threads have access to some piece of data
// The Sync and Send traits, which extend Rust’s concurrency guarantees to user-defined types as well as types provided by the standard library

// Splitting the computation in your program into multiple threads can improve performance because the program does multiple tasks at the same time, but it also adds complexity. Because threads can run simultaneously, there’s no inherent guarantee about the order in which parts of your code on different threads will run. This can lead to problems, such as:

// Race conditions, where threads are accessing data or resources in an inconsistent order
// Deadlocks, where two threads are waiting for each other to finish using a resource the other thread has, preventing both threads from continuing
// Bugs that happen only in certain situations and are hard to reproduce and fix reliab

use std::thread;
use std::time::Duration;

fn test_thread_basic() {

    // The calls to thread::sleep force a thread to stop its execution for a short duration, allowing a different thread to run. 
    // The threads will probably take turns, but that isn’t guaranteed: it depends on how your operating system schedules the threads. 
    // In this run, the main thread printed first, even though the print statement from the spawned thread appears first in the code. 
    // And even though we told the spawned thread to print until i is 9, it only got to 5 before the main thread shut down.
    let slave = thread::spawn(|| {
        for i in 1..10 {
            println!("hi number {} from spawn thread", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..5 {
        println!("hi number {} from main thread", i);
        thread::sleep(Duration::from_millis(1));
    }

    slave.join().unwrap();
}

fn test_thread_basic2() {

    // Using move Closures with Threads
    // The move closure is often used alongside thread::spawn because it allows you to use data from one thread in another thread.
    let v = vec![1, 2, 3];

    let handle = thread::spawn(move || {
        println!("Here's a vector {:?}", v);
    });

    handle.join().unwrap();
}

// One increasingly popular approach to ensuring safe concurrency is message passing, where threads or actors communicate by sending each other messages containing data. 
// Here’s the idea in a slogan from the Go language documentation: “Do not communicate by sharing memory; instead, share memory by communicating.”

// One major tool Rust has for accomplishing message-sending concurrency is the channel, a programming concept that Rust’s standard library provides an implementation of. 
// You can imagine a channel in programming as being like a channel of water, such as a stream or a river. 
// If you put something like a rubber duck or boat into a stream, it will travel downstream to the end of the waterway.

// One increasingly popular approach to ensuring safe concurrency is message passing, where threads or actors communicate by sending each other messages containing data. 
// Here’s the idea in a slogan from the Go language documentation: “Do not communicate by sharing memory; instead, share memory by communicating.”

// One major tool Rust has for accomplishing message-sending concurrency is the channel, a programming concept that Rust’s standard library provides an implementation of. 
// You can imagine a channel in programming as being like a channel of water, such as a stream or a river. 
// If you put something like a rubber duck or boat into a stream, it will travel downstream to the end of the waterway.

// Channels and Ownership Transference
// The ownership rules play a vital role in message sending because they help you write safe, concurrent code. 
// Preventing errors in concurrent programming is the advantage of thinking about ownership throughout your Rust programs.
// 

use std::sync::mpsc;
fn test_thread_channel() {

    let (tx, rv) = mpsc::channel();

    let slave = thread::spawn(move || {
        let info = String::from("channel message");
        println!("slave thread send : {}", info);
        tx.send(info).unwrap(); // Here, info has been Move. Channels and Ownership Transference
        // println!("slave thread send : {}", info); // Compile Error: value borrowed here after move, Info is None now.
     });

    let info = rv.recv().unwrap(); 
    // return Result<T, E> block func, "try_recv" non-block func, "unwrap" in Result will panic if error, or return value
    println!("Main thread get : {}", info);
}

// Sending Multiple Values and Seeing the Receiver Waiting
fn test_thread_channel_multiple_info() {
    let (tx, rv) = mpsc::channel();

    let slave = thread::spawn(move || {
        let info = vec![
            String::from("Hello"),
            String::from("from"),
            String::from("Slave"),
            String::from("thread")
        ];

        for i in info {
            tx.send(i).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    for v in rv {
        println!("Rv : {}", v);
    }
}

// Creating Multiple Producers by Cloning the Transmitter
fn test_thread_multiple_producer() {
    let (tx, rv) = mpsc::channel();
    let tx1 = mpsc::Sender::clone(&tx);

    let slave1 = thread::spawn( move || {

        let vals = vec![
            String::from("Hello"),
            String::from("from"),
            String::from("Slave"),
            String::from("thread"),
        ];

        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    let slave2 = thread::spawn( move || {
        let vals = vec![
            String::from("hello1"),
            String::from("from1"),
            String::from("slave1"),
            String::from("thread1"),
        ];

        for val in vals {
            tx1.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    for v in rv {
        println!("Got : {}", v);
    }
}

pub fn test_thread() {

    test_thread_basic();

    test_thread_basic2();

    test_thread_channel();

    test_thread_channel_multiple_info();

    test_thread_multiple_producer();
}