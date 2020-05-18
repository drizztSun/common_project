/*

The Iterator Trait and the next Method
All iterators implement a trait named Iterator that is defined in the standard library. The definition of the trait looks like this:



pub trait Iterator {
    type Item;

    fn next(&mut self) -> Option<Self::Item>;

    // methods with default implementations elided
}

Notice this definition uses some new syntax: type Item and Self::Item, which are defining an associated type with this trait.
We’ll talk about associated types in depth in Chapter 19.
For now, all you need to know is that this code says implementing the Iterator trait requires that you also define an Item type, and this Item type is used in the return type of the next method.
In other words, the Item type will be the type returned from the iterator.

The Iterator trait only requires implementors to define one method: the next method, which returns one item of the iterator at a time wrapped in Some and, when iteration is over, returns None.

We can call the next method on iterators directly; Listing 13-15 demonstrates what values are returned from repeated calls to next on the iterator created from the vector.
*/

fn test_iterator_basic() {
    let v = vec![1, 2, 3];

    for c in v.iter() {
        println!("Got v: {}", c);
    }

    /*
    Note that we needed to make v1_iter mutable: calling the next method on an iterator changes internal state that the iterator uses to keep track of where it is in the sequence.
    In other words, this code consumes, or uses up, the iterator. Each call to next eats up an item from the iterator.
    We didn’t need to make v1_iter mutable when we used a for loop because the loop took ownership of v1_iter and made it mutable behind the scenes.

    Also note that the values we get from the calls to next are immutable references to the values in the vector. The iter method produces an iterator over immutable references.
    If we want to create an iterator that takes ownership of v1 and returns owned values, we can call into_iter instead of iter.
    Similarly, if we want to iterate over mutable references, we can call iter_mut instead of iter.
    */

    let mut v_it = v.iter();
    assert_eq!(v_it.next(), Some(&1));
    assert_eq!(v_it.next(), Some(&2));
    assert_eq!(v_it.next(), Some(&3));
    assert_eq!(v_it.next(), None);
    assert_eq!(v_it.next(), None);
    assert_eq!(v_it.next(), None);

    let v1 = vec![1, 2, 3];
    // v1.map(|x| x + 1);
    // errors:  The code doesn’t do anything; the closure we’ve specified never gets called.
    // The warning reminds us why: iterator adaptors are lazy, and we need to consume the iterator here

    let v2: Vec<_> = v1.map(|x| x + 1).collect();
    // To fix this and consume the iterator, we’ll use the collect method,
    // This method consumes the iterator and collects the resulting values into a collection data type.
    assert_eq!(v2, vec![2, 3, 4]);
}

/*
*** Creating Our Own Iterators with the Iterator Trait ***

*/
struct Counter {
    count: u32,
}

impl Counter {
    fn new() -> Counter {
        Counter { count: 0 }
    }
}

impl Iterator for Counter {
    //  associated Item type for our iterator to u32, meaning the iterator will return u32 values.
    type Item = u32;

    // Next, we’ll implement the Iterator trait for our Counter type by defining the body of the next method to specify what we want to happen when this iterator is used,
    fn next(&mut self) -> Option<Self::Item> {
        if self.count < 5 {
            self.count += 1;
            Some(self.count)
        } else {
            None
        }
    }
}

fn test_basic_user_defined_iterator() {
    let mut cnt = Counter::new();

    assert_eq!(cnt.next(), Some(1));
    assert_eq!(cnt.next(), Some(2));
    assert_eq!(cnt.next(), Some(3));
    assert_eq!(cnt.next(), Some(4));
    assert_eq!(cnt.next(), Some(5));
    assert_eq!(cnt.next(), None);

    // *** Using Other Iterator Trait Methods ***
    // We implemented the Iterator trait by defining the next method, so we can now use any Iterator trait method’s default implementations as defined in the standard library,
    // because they all use the next method’s functionality.

    let sum: u32 = Counter::new()
        .zip(Counter::new().skip(1))
        .map(|a, b| a * b)
        .filter(|x| x % 3 == 0)
        .sum();
    assert_eq!(18, sum);
}

fn test_iterator() {
    test_iterator_basic();
}
