// `block_on` blocks the current thread until the provided future has run to
// completion. Other executors provide more complex behavior, like scheduling
// multiple futures onto the same thread.
use futures::executor::block_on;
use std::thread;

// Why Async?
// We all love how Rust allows us to write fast, safe software. But why write asynchronous code?
// Asynchronous code allows us to run multiple tasks concurrently on the same OS thread.
// In a typical threaded application, if you wanted to download two different webpages at the same time, you would spread the work across two different threads, like this:
fn download(url: string) {}

fn get_two_sites() {

    // Spawn two threads to do work.
    let thread_one = thread::spawn(|| download("https://www.foo.com"));
    let thread_two = thread::spawn(|| download("https://www.bar.com"));

    // Wait for both threads to complete.
    thread_one.join().expect("thread one panicked");
    thread_two.join().expect("thread two panicked");
}

// This works fine for many applications-- after all, threads were designed to do just this: run multiple different tasks at once. However, they also come with some limitations.
// There's a lot of overhead involved in the process of switching between different threads and sharing data between threads. Even a thread which just sits and does nothing uses up valuable system resources.
// These are the costs that asynchronous code is designed to eliminate.
// We can rewrite the function above using Rust's async/.await notation, which will allow us to run multiple tasks at once without creating multiple threads:
async download_async(url: string) { }

async fn get_two_sites_async() {
    // Create two different "futures" which, when run to completion,
    // will asynchronously download the webpages.
    let future_one = download_async("https://www.foo.com");
    let future_two = download_async("https://www.bar.com");

    // Run both futures to completion at the same time.
    join!(future_one, future_two);
}

// Overall, asynchronous applications have the potential to be much faster and use fewer resources than a corresponding threaded implementation.
// However, there is a cost. Threads are natively supported by the operating system, and using them doesn't require any special programming model-- any function can create a thread,
// and calling a function that uses threads is usually just as easy as calling any normal function. However, asynchronous functions require special support from the language or libraries.

// In Rust, async fn creates an asynchronous function which returns a Future. To execute the body of the function, the returned Future must be run to completion.

// It's important to remember that traditional threaded applications can be quite effective, and that Rust's small memory footprint and predictability mean that you can get far without ever using async.
// The increased complexity of the asynchronous programming model isn't always worth it, and it's important to consider whether your application would be better served by using a simpler threaded model.

async fn do_something() {
    println!("do_something");
}

async fn hello_world() {
    println!("Hello world");
}

// Inside an async fn, you can use .await to wait for the completion of another type that implements the Future trait, such as the output of another async fn.
// Unlike block_on, .await doesn't block the current thread, but instead asynchronously waits for the future to complete, allowing other tasks to run if the future is currently unable to make progress.
struct Song {
    name: string,
}

async fn learn_song() -> Song { /* ... */

    Song{}
}

async fn sing_song(song: Song) { /* ... */

}

async fn dance() { /* ... */

}

async fn learn_and_sing() {
    // Wait until the song has been learned before singing it.
    // We use `.await` here rather than `block_on` to prevent blocking the
    // thread, which makes it possible to `dance` at the same time.
    let song = learn_song().await;
    sing_song(song).await;
}

async test_async_basic() {
    // However, we're not giving the best performance possible this way-- we're only ever doing one thing at once! Clearly we have to learn the song before we can sing it,
    // but it's possible to dance at the same time as learning and singing the song. To do this, we can create two separate async fn which can be run concurrently:
    {
        let f1 = learn_and_sing();
        let f2 = dance();

        // `join!` is like `.await` but can wait for multiple futures concurrently.
        // If we're temporarily blocked in the `learn_and_sing` future, the `dance`
        // future will take over the current thread. If `dance` becomes blocked,
        // `learn_and_sing` can take back over. If both futures are blocked, then
        // `async_main` is blocked and will yield to the executor.
        futures::join!(f1, f2);
    }
}

pub fn test_async() {

    let future = hello_world(); // Nothing is printed

    block_on(future);   // `future` is run and "hello, world!" is printed


    let song = block_on(learn_song());
    block_on(sing_song(song));
    block_on(dance());

    block_on(test_async_basic());

}
