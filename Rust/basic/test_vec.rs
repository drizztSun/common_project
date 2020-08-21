use std::cmp;
use std::mem;
use std::ptr;
use std::vec::*;

/*

    *** Vectors ***
Vectors are re-sizable arrays. Like slices, their size is not known at compile time, but they can grow or shrink at any time.
A vector is represented using 3 parameters:

    1) pointer to the data
    2) length
    3) capacity
The capacity indicates how much memory is reserved for the vector. The vector can grow as long as the length is smaller than the capacity.
When this threshold needs to be surpassed, the vector is reallocated with a larger capacity.

    *** Capacity and reallocation ***
The capacity of a vector is the amount of space allocated for any future elements that will be added onto the vector.
This is not to be confused with the length of a vector, which specifies the number of actual elements within the vector.
If a vector's length exceeds its capacity, its capacity will automatically be increased, but its elements will have to be reallocated.

For example, a vector with capacity 10 and length 0 would be an empty vector with space for 10 more elements.
Pushing 10 or fewer elements onto the vector will not change its capacity or cause reallocation to occur.
However, if the vector's length is increased to 11, it will have to reallocate, which can be slow.
For this reason, it is recommended to use Vec::with_capacity whenever possible to specify how big the vector is expected to get.
*/

fn test_vec_basic1() {
    // Iterators can be collected into vectors
    let collected_iterator: Vec<i32> = (0..10).collect();
    println!("Collected (0..10) into: {:?}", collected_iterator);

    // The `vec!` macro can be used to initialize a vector
    let mut xs = vec![1i32, 2, 3];
    println!("Initial vector: {:?}", xs);

    // Insert new element at the end of the vector
    println!("Push 4 into the vector");
    xs.push(4);
    println!("Vector: {:?}", xs);

    // Error! Immutable vectors can't grow
    // collected_iterator.push(0);
    // FIXME ^ Comment out this line

    // The `len` method yields the number of elements currently stored in a vector
    println!("Vector length: {}", xs.len());

    // Indexing is done using the square brackets (indexing starts at 0)
    println!("Second element: {}", xs[1]);

    // `pop` removes the last element from the vector and returns it
    println!("Pop last element: {:?}", xs.pop());

    // Out of bounds indexing yields a panic
    println!("Fourth element: {}", xs[3]);
    // FIXME ^ Comment out this line

    // `Vector`s can be easily iterated over
    println!("Contents of xs:");
    for x in xs.iter() {
        println!("> {}", x);
    }

    // A `Vector` can also be iterated over while the iteration
    // count is enumerated in a separate variable (`i`)
    for (i, x) in xs.iter().enumerate() {
        println!("In position {} we have value {}", i, x);
    }

    // Thanks to `iter_mut`, mutable `Vector`s can also be iterated
    // over in a way that allows modifying each value
    for x in xs.iter_mut() {
        *x *= 3;
    }
    println!("Updated vector: {:?}", xs);
}

fn test_vec_basic() {
    // constructor
    let mut vec: Vec<i32> = Vec::new();
    let mut vec: Vec<i32> = Vec::with_capacity(10);
    let mut vec: Vec<i32> = vec![0; 100]; // init vec 100 elements, all are 0, internal func  Vec::from_elem(0, 100);
    let mut vec: Vec<i32> = vec![1, 2, 3];

    // A contiguous growable array type, written Vec<T> but pronounced 'vector'.
    let mut vec = Vec::new();

    vec.push(1);
    vec.push(2);

    assert_eq!(vec.len(), 2);
    assert_eq!(vec[1], 2);

    vec[0] = 7;
    assert_eq!(vec[0], 7);

    vec.extend([1, 2, 3].iter().cloned());

    for x in &vec {
        println!("{}", x);
    }

    assert_eq!(vec, [7, 2, 1, 2, 3]);

    {
        // insert
        let mut vec = vec![1, 2, 3];

        vec.insert(1, 4);
        assert_eq!(vec, [1, 4, 2, 3]);

        vec.insert(4, 5);
        assert_eq!(vec, [1, 4, 2, 3, 5]);
    }

    {
        // push
        let mut vec = vec![1, 2];
        vec.push(3);
        assert_eq!(vec, [1, 2, 3]);

        // pop
        let mut vec = vec![1, 2, 3];
        assert_eq!(vec.pop(), Some(3));
        assert_eq!(vec, [1, 2]);
    }

    {
        // remove
        // Removes and returns the element at position index within the vector, shifting all elements after it to the left.
        let mut v = vec![1, 2, 3];
        assert_eq!(v.remove(1), 2);
        assert_eq!(v, [1, 3]);

        // remove_item
        // Removes the first instance of item from the vector if the item exists.
        let mut vec = vec![1, 2, 3, 1];
        // vec.remove_item(&1);  # remove_item is a function from unstable version
        assert_eq!(vec, vec![1, 2, 3, 1]);
    }

    {
        // Use a Vec<T> as an efficient stack:
        let mut stack = Vec::new();
        stack.push(1);
        stack.push(2);
        stack.push(3);

        while let Some(top) = stack.pop() {
            println!("{}", top);
        }

        assert_eq!(stack.is_empty(), true)
    }

    {
        // indexing
        let v = vec![1, 2, 3, 4];
        println!("{}", v[0]);

        // println!("{}", v[6]); //panic
    }

    {
        // slicing
        // A Vec can be mutable. Slices, on the other hand, are read-only objects. To get a slice, use &. Exampl
        let v = vec![0, 1, 2];

        read_slice(&v);

        let x: &[usize] = &v;

        // In Rust, it's more common to pass slices as arguments rather than vectors when you just want to provide a read access.
        // The same goes for String and &str.
    }

    {
        // append
        let mut vec = vec![1, 2, 3];
        let mut vec2 = vec![4, 5, 6];
        vec.append(&mut vec2);
        assert_eq!(vec, [1, 2, 3, 4, 5, 6]);
        assert_eq!(vec2.is_empty(), true);

        vec.clear();
    }

    {
        // iterating
        let v = vec![100, 32, 57];
        for i in &v {
            println!("{}", i);
        }

        let mut v1 = vec![100, 32, 57];
        for i in &mut v1 {
            *i += 50;
        }
    }
}

fn read_slice(r: &[usize]) {}

fn test_vec_macro() {
    {
        // The vec! macro is provided to make initialization more convenient:
        let mut vec = vec![1, 2, 3];
        vec.push(4);
        assert_eq!(vec, [1, 2, 3, 4]);
    }

    {
        // It can also initialize each element of a Vec<T> with a given value.
        // This may be more efficient than performing allocation and initialization in separate steps, especially when initializing a vector of zeros:
        let mut vec1 = vec![0; 5];
        assert_eq!(vec1, [0, 0, 0, 0, 0]);

        // The following is equivalent, but potentially slower:
        let mut vec2 = Vec::with_capacity(5);
        vec2.resize(5, 0);
        assert_eq!(vec2, [0, 0, 0, 0, 0]);
    }
}

fn test_vec_funcs_from_raw_ptrs() {
    let mut v = vec![1, 2, 3];

    // Pull out the various important pieces of information about `v
    let p = v.as_mut_ptr();
    let len = v.len();
    let cap = v.capacity();

    unsafe {
        // Cast `v` into the void: no destructor run, so we are in
        // complete control of the allocation to which `p` points.
        mem::forget(v);

        // Overwrite memory the 4, 5, 6
        for i in 0..len as isize {
            ptr::write(p.offset(i), 4 + i);
        }

        //
        let rebuilt = Vec::from_raw_parts(p, len, cap);
        assert_eq!(rebuilt, [4, 5, 6]);
    }
}

fn test_vec_funcs_capacity() {
    let mut v = Vec::with_capacity(5);

    assert_eq!(v.capacity(), 5);

    v.resize(5, 0);
    assert_eq!(v, [0, 0, 0, 0, 0]);

    v.reserve(10);
    assert!(v.capacity() >= 11);
}

fn test_vec_add_remove_iter() {}

fn test_vec_advanced_usage() {
    {
        // dedup
        // Removes consecutive repeated elements in the vector according to the PartialEq trait implementation.
        // If the vector is sorted, this removes all duplicates.
        let mut vec = vec![1, 2, 2, 3, 3, 4, 5, 6];

        vec.dedup();

        assert_eq!(vec, [1, 2, 3, 4, 5, 6]);
    }

    {
        // dedup_by
        // Removes all but the first of consecutive elements in the vector satisfying a given equality relation.
        // The same_bucket function is passed references to two elements from the vector and must determine if the elements compare equal.
        // The elements are passed in opposite order from their order in the slice, so if same_bucket(a, b) returns true, a is removed.
        // If the vector is sorted, this removes all duplicates.
        let mut vec = vec!["foo", "bar", "Bar", "baz", "bar"];

        vec.dedup_by(|a, b| a.eq_ignore_ascii_case(b));

        assert_eq!(vec, ["foo", "bar", "baz", "bar"]);
    }

    {
        // dedup_by_key
        // Removes all but the first of consecutive elements in the vector that resolve to the same key.
        // If the vector is sorted, this removes all duplicates.
        let mut vec = vec![10, 20, 21, 30, 20];

        vec.dedup_by_key(|x| *x / 10);

        assert_eq!(vec, [10, 20, 30, 20]);
    }

    {
        // drain
        // Creates a draining iterator that removes the specified range in the vector and yields the removed items.
        // Note 1: The element range is removed even if the iterator is only partially consumed or not consumed at all.
        // Note 2: It is unspecified how many elements are removed from the vector if the Drain value is leaked.

        let mut v = vec![1, 2, 3];
        let u: Vec<_> = v.drain(1..).collect();
        assert_eq!(u, &[2, 3]);
        assert_eq!(v, &[1]);

        // A full range clears the vector
        v.drain(..);
        assert_eq!(v.is_empty(), true);
    }

    {
        // drain_filter
        // Creates an iterator which uses a closure to determine if an element should be removed.
        // If the closure returns true, then the element is removed and yielded.
        // If the closure returns false, the element will remain in the vector and will not be yielded by the iterator.
        // Using this method is equivalent to the following code:

        let mut numbers = vec![1, 2, 3, 4, 5, 6, 8, 9, 11, 13, 14, 15];
        // #![allow(unused)]
        // #![feature(drain_filter)]
        // let evens = numbers.drain_filter(|x| *x % 2 == 0).collect::<Vec<_>>();
        let evens = vec![2, 4, 6, 8, 14];
        let odds = numbers;

        assert_eq!(evens, vec![2, 4, 6, 8, 14]);
        assert_eq!(odds, vec![1, 3, 5, 9, 11, 13, 15]);
    }

    {
        // extend_from_slice

        let mut vec = vec![1];
        vec.extend_from_slice(&[2, 3, 4]);
        assert_eq!(vec, [1, 2, 3, 4]);
    }

    {
        // splice
        let mut v = vec![1, 2, 3];
        let new = [7, 8];
        let u: Vec<_> = v.splice(..2, new.iter().cloned()).collect();
        assert_eq!(v, &[7, 8, 3]);
        assert_eq!(u, &[1, 2]);

        // Creates a splicing iterator that replaces the specified range in the vector with the given replace_with iterator and yields the removed items.
        // replace_with does not need to be the same length as range.
        // The element range is removed even if the iterator is not consumed until the end.
        // It is unspecified how many elements are removed from the vector if the Splice value is leaked.
        // The input iterator replace_with is only consumed when the Splice value is dropped.
        // This is optimal if:
        //  The tail (elements in the vector after range) is empty,
        // or replace_with yields fewer elements than range’s length
        // or the lower bound of its size_hint() is exact.
        // Otherwise, a temporary vector is allocated and the tail is moved twice.
    }

    {
        // shrink_to_fit
        // Shrinks the capacity of the vector as much as possible.
        // It will drop down as close as possible to the length but the allocator may still inform the vector that there is space for a few more elements.
        let mut vec = Vec::with_capacity(10);
        vec.extend([1, 2, 3].iter().cloned());
        assert_eq!(vec.capacity(), 10);
        vec.shrink_to_fit();
        assert!(vec.capacity() >= 3);
    }

    {
        // retain
        // Retains only the elements specified by the predicate.

        // In other words, remove all elements e such that f(&e) returns false.
        // This method operates in place, visiting each element exactly once in the original order, and preserves the order of the retained elements.

        let mut vec = vec![1, 2, 3, 4, 5, 6];

        vec.retain(|&x| x % 2 == 0);
        assert_eq!(vec, [2, 4, 6]);
    }

    {
        // split_off
        // Splits the collection into two at the given index.
        // Returns a newly allocated Self. self contains elements [0, at), and the returned Self contains elements [at, len).
        // Note that the capacity of self does not change.

        let mut vec = vec![1, 2, 3];
        let vec2 = vec.split_off(1);

        assert_eq!(vec, [1]);
        assert_eq!(vec2, [2, 3]);
    }

    {
        // swap_remove
        // Removes an element from the vector and returns it.
        // The removed element is replaced by the last element of the vector.
        // This does not preserve ordering, but is O(1).

        let mut v = vec!["foo", "bar", "baz", "qux"];

        assert_eq!(v.swap_remove(1), "bar");
        assert_eq!(v, ["foo", "qux", "baz"]);

        assert_eq!(v.swap_remove(0), "foo");
        assert_eq!(v, ["baz", "qux"]);
    }

    {
        // truncate
        // Shortens the vector, keeping the first len elements and dropping the rest.
        // If len is greater than the vector's current length, this has no effect.
        // The drain method can emulate truncate, but causes the excess elements to be returned instead of dropped.
        // Note that this method has no effect on the allocated capacity of the vector.
        let mut v = vec![1, 2, 3, 4, 5, 6];
        v.truncate(2);
        assert_eq!(v, [1, 2]);

        v.truncate(8);
        assert_eq!(v, [1, 2]);

        v.truncate(0);
        assert_eq!(v.is_empty(), true);
    }
}

fn test_max_range(a: Vec<i32>) -> i32 {
    let mut B: Vec<usize> = (0..a.len()).collect();

    B.sort_by(|i, j| {
        return a[*i].cmp(&a[*j]);
    });

    let mut min_index: i32 = a.len() as i32;
    let mut ans: i32 = 0;
    for c in B.iter() {
        ans = cmp::max(ans, *c as i32 - min_index);
        min_index = cmp::min(*c as i32, min_index);
    }

    return ans;
}

fn test_2d_array() {
    let n = 10;
    let m = 20;
    let mut array = vec![vec![0.0f64; n]; m];
    for i in 0..n {
        for j in 0..m {
            array[i][j] = (i * n + j) as f64;
        }
    }

    const CN: usize = 10;
    const CM: usize = 100;
    let mut x = [[0.0; CN]; CM]; // This works only when M and N are constant. Elements have type f64

    for i in 0..CM {
        for j in 0..CN {
            x[i][j] = (i * CN + j) as f64;
        }
    }
}

pub fn test_vec() {
    test_vec_basic();

    test_vec_macro();

    test_vec_funcs_capacity();

    test_vec_funcs_from_raw_ptrs();

    test_vec_add_remove_iter();

    test_2d_array();
}
