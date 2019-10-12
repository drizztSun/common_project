use std::vec::*;
use std::mem;
use std::ptr;


/*
*** Capacity and reallocation
The capacity of a vector is the amount of space allocated for any future elements that will be added onto the vector. 
This is not to be confused with the length of a vector, which specifies the number of actual elements within the vector. 
If a vector's length exceeds its capacity, its capacity will automatically be increased, but its elements will have to be reallocated.

For example, a vector with capacity 10 and length 0 would be an empty vector with space for 10 more elements. 
Pushing 10 or fewer elements onto the vector will not change its capacity or cause reallocation to occur. 
However, if the vector's length is increased to 11, it will have to reallocate, which can be slow. 
For this reason, it is recommended to use Vec::with_capacity whenever possible to specify how big the vector is expected to get.
*/
fn test_vec_basic() {

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

    assert_eq!(vec, [7, 1, 2, 3]);

    {
        // Use a Vec<T> as an efficient stack:
        let mut stack = Vec::new();
        stack.push(1);
        stack.push(2);
        stack.push(3);

        while let Some(top) = stack.pop() {
            println!("{}", top);
        }
    }

    // indexing
    {
        let v = vec![1, 2, 3, 4];
        println!("{}", v[0]);

        // println!("{}", v[6]); //panic
    }

    // slicing
    {
        // A Vec can be mutable. Slices, on the other hand, are read-only objects. To get a slice, use &. Exampl
        let v = vec![0, 1, 2];

        read_slice(&v);

        let x : &[usize] = &v;

        // In Rust, it's more common to pass slices as arguments rather than vectors when you just want to provide a read access. 
        // The same goes for String and &str.
    }

}

fn read_slice(r: &[usize]) {

}

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
    assert_eq!(v, [0, 0, 0, 0, 0]);

    v.resize(5, 0);
    v.reserve(10);
    assert!(v.capacity() >= 11);
}

fn test_vec_add_remove_iter() {

}


pub fn test_vec() {

    test_vec_basic();

    test_vec_macro();

    test_vec_funcs_capacity();

    test_vec_funcs_from_raw_ptrs();

    test_vec_add_remove_iter();
}