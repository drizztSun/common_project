use futures::{
    join,
    future::TryFutureExt,
    try_join!,

    pin_mut,
    select.
};

/*
Executing Multiple Futures at a Time
Up until now, we've mostly executed futures by using .await, which blocks the current task until a particular Future completes.
However, real asynchronous applications often need to execute several different operations concurrently.

In this chapter, we'll cover some ways to execute multiple asynchronous operations at the same time:

join!: waits for futures to all complete
select!: waits for one of several futures to complete
Spawning: creates a top-level task which ambiently runs a future to completion
FuturesUnordered: a group of futures which yields the result of each subfuture

*/

/*
join!
The futures::join macro makes it possible to wait for multiple different futures to complete while executing them all concurrently.

join!
When performing multiple asynchronous operations, it's tempting to simply .await them in a series:

try_join!
For futures which return Result, consider using try_join! rather than join!.
Since join! only completes once all subfutures have completed, it'll continue processing other futures even after one of its subfutures has returned an Err.

Unlike join!, try_join! will complete immediately if one of the subfutures returns an error.


Note that the futures passed to try_join! must all have the same error type. Consider using the .map_err(|e| ...) and .err_into() functions
from futures::future::TryFutureExt to consolidate the error types:

*/

struct Book {
    name: String,
}

struct Music {
    name: String,
}

async fn get_book() -> Book {
    Book{}
}

async fn get_music() -> Music {
    Music{}
}

async fn get_book_and_music() -> (Book, Music) {

    // let book = get_book().await()
    // let music = get_music().await()
    // (book, music)
    // *** However, this will be slower than necessary, since it won't start trying to get_music until after get_book has completed

    // In some other languages, futures are ambiently run to completion, so two operations can be run concurrently by first calling each async fn to start the futures,
    // and then awaiting them both:
    //
    // WRONG don"t do this
    // let book_future = get_book();
    // let music_future = get_music();
    // (book_future.await, music_future.await)

    // However, Rust futures won't do any work until they're actively .awaited. This means that the two code snippets above will both run book_future and music_future
    // in series rather than running them concurrently. To correctly run the two futures concurrently, use futures::join!:
    let book_fut = get_book();
    let music_fut = get_music();
    join!(book_fut, music_fut)
}

async fn get_book_res() -> Result<Book, String> {
    Ok(Book)
}

async fn get_music_res() -> Result<Music, String> {
    Ok(Music)
}

async fn get_book_and_music_res() -> Result<(Book, Music), String> {
    let book_fut = get_book_res();
    let music_fut = get_music_res();

    try_join!(book_fut, music_fut)
}

async fn get_book_lic() -> Result<Book, ()> { /* ... */ Ok(Book) }

async fn get_book_and_music_res() -> Result<(Book, Music), String> {
    let book_fut = get_book_lic().map_err(|()| "Unable to get book".to_string());
    let music_fut = get_music_res();

    try_join!(book_fut, music_fut)
}

/*
select!
The futures::select macro runs multiple futures simultaneously, allowing the user to respond as soon as any future completes.

The basic syntax for select is <pattern> = <expression> => <code>,, repeated for as many futures as you would like to select over.

*/

async fn task_one() {}
async fn task_two() {}

async fn race_tasks() {
    let t1 = task_one().fuse();
    let t2 = task_two().fuse();

    pin_mut!(t1, t2);

    select! {
        () = t1 => println!("Task one completed first"),
        () = t2 => println!("Task twi completed frist"),
    }
}

/*

default => ... and complete => ...
select also supports default and complete branches.

A default branch will run if none of the futures being selected over are yet complete.
A select with a default branch will therefore always return immediately, since default will be run if none of the other futures are ready.

complete branches can be used to handle the case where all futures being selected over have completed and will no longer make progress.
This is often handy when looping over a select!.

*/

async fn count() {
    let mut a_fut = future::ready(4);
    let mut b_fut = future::ready(6);
    let mut total = 0;

    loop {
        select! {
            a = a_fut => total += a,
            b = b_fut => total += b,
            complete => break,
            default => unreachable!(), // never runs (futures are ready, then complete)
        };
    }
    assert_eq!(total, 10);
}


/*

Interaction with Unpin and FusedFuture
One thing you may have noticed in the first example above is that we had to call .fuse() on the futures returned by the two async fns, as well as pinning them with pin_mut.
Both of these calls are necessary because the futures used in select must implement both the Unpin trait and the FusedFuture trait.

Unpin is necessary because the futures used by select are not taken by value, but by mutable reference. By not taking ownership of the future, uncompleted futures can be used again after the call to select.

Similarly, the FusedFuture trait is required because select must not poll a future after it has completed. FusedFuture is implemented by futures which track whether or not they have completed.
This makes it possible to use select in a loop, only polling the futures which still have yet to complete. This can be seen in the example above, where a_fut or b_fut will have completed the second time through the loop.
Because the future returned by future::ready implements FusedFuture, it's able to tell select not to poll it again.

Note that streams have a corresponding FusedStream trait. Streams which implement this trait or have been wrapped using .fuse() will yield FusedFuture futures from their .next() / .try_next() combinators.


*/

async fn add_two_streams(
    mut s1: impl Stream<Item = u8> + FusedStream + Unpin,
    mut s2: impl Stream<Item = u8> + FusedStream + Unpin,
) -> u8 {
    let mut total = 0;

    loop {
        let item = select! {
            x = s1.next() => x,
            x = s2.next() => x,
            complete => break,
        };

        if let Some(next_num) = item {
            total += next_num;
        }
    }

    total
}

/*

Concurrent tasks in a select loop with Fuse and FuturesUnordered

One somewhat hard-to-discover but handy function is Fuse::terminated(), which allows constructing an empty future which is already terminated, and can later be filled in with a future that needs to be run.

This can be handy when there's a task that needs to be run during a select loop but which is created inside the select loop itself.

Note the use of the .select_next_some() function. This can be used with select to only run the branch for Some(_) values returned from the stream, ignoring Nones.

*/
use futures::{
    future::{Fuse, FusedFuture, FutureExt},
    stream::{FusedStream, FuturesUnordered, Stream, StreamExt},
    pin_mut,
    select,
};

async fn get_new_num() -> u8 { /* ... */ 5 }

async fn run_on_new_num(_: u8) { /* ... */ }

async fn run_loop(
    mut interval_timer: impl Stream<Item = ()> + FusedStream + Unpin,
    starting_num: u8,
) {
    let run_on_new_num_fut = run_on_new_num(starting_num).fuse();
    let get_new_num_fut = Fuse::terminated();
    pin_mut!(run_on_new_num_fut, get_new_num_fut);
    loop {
        select! {
            () = interval_timer.select_next_some() => {
                // The timer has elapsed. Start a new `get_new_num_fut`
                // if one was not already running.
                if get_new_num_fut.is_terminated() {
                    get_new_num_fut.set(get_new_num().fuse());
                }
            },
            new_num = get_new_num_fut => {
                // A new number has arrived-- start a new `run_on_new_num_fut`,
                // dropping the old one.
                run_on_new_num_fut.set(run_on_new_num(new_num).fuse());
            },
            // Run the `run_on_new_num_fut`
            () = run_on_new_num_fut => {},
            // panic if everything completed, since the `interval_timer` should
            // keep yielding values indefinitely.
            complete => panic!("`interval_timer` completed unexpectedly"),
        }
    }
}

/*

When many copies of the same future need to be run simultaneously, use the FuturesUnordered type.
The following example is similar to the one above, but will run each copy of run_on_new_num_fut to completion, rather than aborting them when a new one is created.
It will also print out a value returned by run_on_new_num_fut.

*/

// Runs `run_on_new_num` with the latest number
// retrieved from `get_new_num`.
//
// `get_new_num` is re-run every time a timer elapses,
// immediately cancelling the currently running
// `run_on_new_num` and replacing it with the newly
// returned value.
async fn run_loop_h(
    mut interval_timer: impl Stream<Item = ()> + FusedStream + Unpin,
    starting_num: u8,
) {
    let mut run_on_new_num_futs = FuturesUnordered::new();
    run_on_new_num_futs.push(run_on_new_num(starting_num));
    let get_new_num_fut = Fuse::terminated();
    pin_mut!(get_new_num_fut);
    loop {
        select! {
            () = interval_timer.select_next_some() => {
                // The timer has elapsed. Start a new `get_new_num_fut`
                // if one was not already running.
                if get_new_num_fut.is_terminated() {
                    get_new_num_fut.set(get_new_num().fuse());
                }
            },
            new_num = get_new_num_fut => {
                // A new number has arrived-- start a new `run_on_new_num_fut`.
                run_on_new_num_futs.push(run_on_new_num(new_num));
            },
            // Run the `run_on_new_num_futs` and check if any have completed
            res = run_on_new_num_futs.select_next_some() => {
                println!("run_on_new_num_fut returned {:?}", res);
            },
            // panic if everything completed, since the `interval_timer` should
            // keep yielding values indefinitely.
            complete => panic!("`interval_timer` completed unexpectedly"),
        }
    }
}

