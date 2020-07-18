use std::mpsc;

/*

The Stream Trait
The Stream trait is similar to Future but can yield multiple values before completing, similar to the Iterator trait from the standard library:


trait Stream {
    /// The type of the value yielded by the stream.
    type Item;

    /// Attempt to resolve the next item in the stream.
    /// Returns `Poll::Pending` if not ready, `Poll::Ready(Some(x))` if a value
    /// is ready, and `Poll::Ready(None)` if the stream has completed.
    fn poll_next(self: Pin<&mut Self>, cx: &mut Context<'_>)
        -> Poll<Option<Self::Item>>;
}

One common example of a Stream is the Receiver for the channel type from the futures crate. It will yield Some(val) every time a value is sent from the Sender end,
and will yield None once the Sender has been dropped and all pending messages have been received:
*/

async fn send_recv() {
    const BUFFER_SIZE: usize = 10;
    let (mut tx, mut rx) = mpsc::channel::<i32>(BUFFER_SIZE);

    tx.send(1).await.unwrap();
    tx.send(2).await.unwrap();
    drop(tx);

    // `StreamExt::next` is similar to `Iterator::next`, but returns a
    // type that implements `Future<Output = Option<T>>`.
    assert_eq!(Some(1), rx.next().await);
    assert_eq!(Some(2), rx.next().await);
    assert_eq!(None, rx.next().await);
}

/*

Iteration and Concurrency
Similar to synchronous Iterators, there are many different ways to iterate over and process the values in a Stream.
There are combinator-style methods such as map, filter, and fold, and their early-exit-on-error cousins try_map, try_filter, and try_fold.

Unfortunately, for loops are not usable with Streams, but for imperative-style code, while let and the next/try_next functions can be used:

*/

async fn sum_with_next(mut stream: Pin<&mut dyn Stream<Item = i32>>) -> i32  {
    use futures::stream::streamExt; // for  'next'
    let mut sum = 0;
    while let Some(item) = stream.next().await {
        sum += item;
    }
    sum
}

async fn sum_with_try_next(
    mut stream: Pin<&mut dyn Stream<Item = Result<i32, io::Error>>>,
) -> Result<i32, io::Error> {
    use futures::stream::TryStreamExt; // for `try_next`
    let mut sum = 0;
    while let Some(item) = stream.try_next().await? {
        sum += item;
    }
    Ok(sum)
}

/*

However, if we're just processing one element at a time, we're potentially leaving behind opportunity for concurrency, which is, after all, why we're writing async code in the first place.
To process multiple items from a stream concurrently, use the for_each_concurrent and try_for_each_concurrent methods:

*/

async fn jump_around(
    mut stream: Pin<&mut dyn Stream<Item = Result<u8, io::Error>>>,
) -> Result<(), io::Error> {
    use futures::stream::TryStreamExt; // for `try_for_each_concurrent`
    const MAX_CONCURRENT_JUMPERS: usize = 100;

    stream.try_for_each_concurrent(MAX_CONCURRENT_JUMPERS, |num| async move {
        jump_n_times(num).await?;
        report_n_jumps(num).await?;
        Ok(())
    }).await?;

    Ok(())
}