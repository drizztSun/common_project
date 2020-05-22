/*
*** Fearless Concurrency ***
Handling concurrent programming safely and efficiently is another of Rust’s major goals.
Concurrent programming, where different parts of a program execute independently, and parallel programming, where different parts of a program execute at the same time,
are becoming increasingly important as more computers take advantage of their multiple processors. Historically, programming in these contexts has been difficult and error prone: Rust hopes to change that.

Initially, the Rust team thought that ensuring memory safety and preventing concurrency problems were two separate challenges to be solved with different methods.
Over time, the team discovered that the ownership and type systems are a powerful set of tools to help manage memory safety and concurrency problems! By leveraging ownership and type checking,
many concurrency errors are compile-time errors in Rust rather than runtime errors.

Therefore, rather than making you spend lots of time trying to reproduce the exact circumstances under which a runtime concurrency bug occurs, incorrect code will refuse to compile and present an error explaining the problem.
As a result, you can fix your code while you’re working on it rather than potentially after it has been shipped to production.
We’ve nicknamed this aspect of Rust fearless concurrency. Fearless concurrency allows you to write code that is free of subtle bugs and is easy to refactor without introducing new bugs.


Note: For simplicity’s sake, we’ll refer to many of the problems as concurrent rather than being more precise by saying concurrent and/or parallel.
If this book were about concurrency and/or parallelism, we’d be more specific. For this chapter, please mentally substitute concurrent and/or parallel whenever we use concurrent.

Many languages are dogmatic about the solutions they offer for handling concurrent problems.
For example, Erlang has elegant functionality for message-passing concurrency but has only obscure ways to share state between threads.
Supporting only a subset of possible solutions is a reasonable strategy for higher-level languages, because a higher-level language promises benefits from giving up some control to gain abstractions.
However, lower-level languages are expected to provide the solution with the best performance in any given situation and have fewer abstractions over the hardware.
Therefore, Rust offers a variety of tools for modeling problems in whatever way is appropriate for your situation and requirements.

Here are the topics we’ll cover in this chapter:

How to create threads to run multiple pieces of code at the same time
Message-passing concurrency, where channels send messages between threads
Shared-state concurrency, where multiple threads have access to some piece of data
The Sync and Send traits, which extend Rust’s concurrency guarantees to user-defined types as well as types provided by the standard library
*/

/*
*** Using Threads to Run Code Simultaneously ***
In most current operating systems, an executed program’s code is run in a process, and the operating system manages multiple processes at once.
Within your program, you can also have independent parts that run simultaneously. The features that run these independent parts are called threads.

// Splitting the computation in your program into multiple threads can improve performance because the program does multiple tasks at the same time, but it also adds complexity.
// Because threads can run simultaneously, there’s no inherent guarantee about the order in which parts of your code on different threads will run. This can lead to problems, such as:

1) Race conditions, where threads are accessing data or resources in an inconsistent order
2)  Deadlocks, where two threads are waiting for each other to finish using a resource the other thread has, preventing both threads from continuing
3) Bugs that happen only in certain situations and are hard to reproduce and fix reliab

Rust attempts to mitigate the negative effects of using threads, but programming in a multithreaded context still takes careful thought and requires a code structure that is different from that in programs running in a single thread.

Programming languages implement threads in a few different ways. Many operating systems provide an API for creating new threads.
This model where a language calls the operating system APIs to create threads is sometimes called 1:1, meaning one operating system thread per one language thread.

Many programming languages provide their own special implementation of threads. Programming language-provided threads are known as green threads,
and languages that use these green threads will execute them in the context of a different number of operating system threads.
For this reason, the green-threaded model is called the M:N model: there are M green threads per N operating system threads, where M and N are not necessarily the same number.

Each model has its own advantages and trade-offs, and the trade-off most important to Rust is runtime support. Runtime is a confusing term and can have different meanings in different contexts.

In this context, by runtime we mean code that is included by the language in every binary. This code can be large or small depending on the language,
but every non-assembly language will have some amount of runtime code. For that reason, colloquially when people say a language has “no runtime,” they often mean “small runtime.”
Smaller runtimes have fewer features but have the advantage of resulting in smaller binaries, which make it easier to combine the language with other languages in more contexts.
Although many languages are okay with increasing the runtime size in exchange for more features, Rust needs to have nearly no runtime and cannot compromise on being able to call into C to maintain performance.

The green-threading M:N model requires a larger language runtime to manage threads. As such, the Rust standard library only provides an implementation of 1:1 threading.
Because Rust is such a low-level language, there are crates that implement M:N threading if you would rather trade overhead for aspects such as more control overwhich threads run when and lower costs of context switching, for example.

Now that we’ve defined threads in Rust, let’s explore how to use the thread-related API provided by the standard library.

*/

use std::thread;
use std::time::Duration;


// *** Creating a New Thread with spawn ***
// To create a new thread, we call the thread::spawn function and pass it a closure (we talked about closures in Chapter 13) containing the code we want to run in the new thread.

// *** Waiting for All Threads to Finish Using join Handles ***
// The return type of thread::spawn is JoinHandle. A JoinHandle is an owned value that, when we call the join method on it, will wait for its thread to finish.

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

// *** Using move Closures with Threads ***
// The move closure is often used alongside thread::spawn because it allows you to use data from one thread in another thread.


fn test_thread_basic2() {

    let v = vec![1, 2, 3];

    // we can use the move keyword before the parameter list of a closure to force the closure to take ownership of the values it uses in the environment.
    // This technique is especially useful when creating new threads in order to transfer ownership of values from one thread to another.
    let handle = thread::spawn(move || {
        println!("Here's a vector {:?}", v);
    });

    // Rust infers how to capture v, and because println! only needs a reference to v, the closure tries to borrow v.
    // However, there’s a problem: Rust can’t tell how long the spawned thread will run, so it doesn’t know if the reference to v will always be valid.

    //  If we added move to the closure, we would move v into the closure’s environment, and we could no longer call drop on it in the main thread.
    //  drop(v); // oh no!

    handle.join().unwrap();
}

// *** Using Message Passing to Transfer Data Between Threads ***

// One increasingly popular approach to ensuring safe concurrency is message passing, where threads or actors communicate by sending each other messages containing data.
// Here’s the idea in a slogan from the Go language documentation: “Do not communicate by sharing memory; instead, share memory by communicating.”

// One major tool Rust has for accomplishing message-sending concurrency is the channel, a programming concept that Rust’s standard library provides an implementation of.
// You can imagine a channel in programming as being like a channel of water, such as a stream or a river.
// If you put something like a rubber duck or boat into a stream, it will travel downstream to the end of the waterway.

// A channel in programming has two halves: a transmitter and a receiver.
// The transmitter half is the upstream location where you put rubber ducks into the river, and the receiver half is where the rubber duck ends up downstream.
// One part of your code calls methods on the transmitter with the data you want to send, and another part checks the receiving end for arriving messages.
// A channel is said to be closed if either the transmitter or receiver half is dropped.

// *** Channels and Ownership Transference ***
// The ownership rules play a vital role in message sending because they help you write safe, concurrent code.
// Preventing errors in concurrent programming is the advantage of thinking about ownership throughout your Rust programs.

// We create a new channel using the mpsc::channel function; mpsc stands for multiple producer, single consumer.
// In short, the way Rust’s standard library implements channels means a channel can have multiple sending ends that produce values but only one receiving end that consumes those values.

// The mpsc::channel function returns a tuple, the first element of which is the sending end and the second element is the receiving end.
// The abbreviations tx and rx are traditionally used in many fields for transmitter and receiver respectively, so we name our variables as such to indicate each end.



use std::sync::mpsc;

fn test_thread_channel() {
    let (tx, rv) = mpsc::channel();

    let slave = thread::spawn(move || {
        let info = String::from("channel message");
        println!("slave thread send : {}", info);

        // The transmitting end has a send method that takes the value we want to send. The send method returns a Result<T, E> type,
        tx.send(info).unwrap(); // Here, info has been Move. Channels and Ownership Transference
        // println!("slave thread send : {}", info); // Compile Error: value borrowed here after move, Info is None now.
    });

    let info = rv.recv().unwrap();
    // The receiving end of a channel has two useful methods: recv and try_recv.
    // Once a value is sent, recv will return it in a Result<T, E>. When the sending end of the channel closes, recv will return an error to signal that no more values will be coming.

    // The try_recv method doesn’t block, but will instead return a Result<T, E> immediately: an Ok value holding a message if one is available and an Err value if there aren’t any messages this time.
    // Using try_recv is useful if this thread has other work to do while waiting for messages: we could write a loop that calls try_recv every so often, handles a message if one is available,
    // and otherwise does other work for a little while until checking again.
    // return Result<T, E> block func, "try_recv" non-block func, "unwrap" in Result will panic if error, or return value
    println!("Main thread get : {}", info);
}

// *** Sending Multiple Values and Seeing the Receiver Waiting ***
fn test_thread_channel_multiple_info() {
    let (tx, rv) = mpsc::channel();

    let slave = thread::spawn(move || {
        let info = vec![
            String::from("Hello"),
            String::from("from"),
            String::from("Slave"),
            String::from("thread"),
        ];

        for i in info {
            tx.send(i).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    for v in rv { // treating rx as an iterator
        println!("Rv : {}", v);
    }
}

// *** Creating Multiple Producers by Cloning the Transmitter ***
// Earlier we mentioned that mpsc was an acronym for multiple producer, single consumer.
fn test_thread_multiple_producer() {
    let (tx, rv) = mpsc::channel();
    let tx1 = mpsc::Sender::clone(&tx);

    let slave1 = thread::spawn(move || {
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

    let slave2 = thread::spawn(move || {
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
