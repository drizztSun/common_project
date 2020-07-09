use std::pin::Pin;
use std::marker::PhantomPinned;
use std::ptr::NonNull;
use std::mem;


// *** Summary
// The concepts of ownership, borrowing, and slices ensure memory safety in Rust programs at compile time.
// The Rust language gives you control over your memory usage in the same way as other systems programming languages,
// but having the owner of data automatically clean up that data when the owner goes out of scope means you don’t have to write and debug extra code to get this control.

// What Is Ownership?
// Rust’s central feature is ownership. Although the feature is straightforward to explain, it has deep implications for the rest of the language.
// All programs have to manage the way they use a computer’s memory while running.
// Some languages have garbage collection that constantly looks for no longer used memory as the program runs;
// in other languages, the programmer must explicitly allocate and free the memory.
// Rust uses a third approach: memory is managed through a system of ownership with a set of rules that the compiler checks at compile time.
// None of the ownership features slow down your program while it’s running.

// Rust takes a different path: the memory is automatically returned once the variable that owns it goes out of scope.

// The Stack and the Heap
// Both the stack and the heap are parts of memory that are available to your code to use at runtime, but they are structured in different ways.
// The stack stores values in the order it gets them and removes the values in the opposite order. This is referred to as last in, first out.
// Think of a stack of plates: when you add more plates, you put them on top of the pile, and when you need a plate, you take one off the top.
// Adding or removing plates from the middle or bottom wouldn’t work as well! Adding data is called pushing onto the stack, and removing data is called popping off the stack.

// All data stored on the stack must have a known, fixed size. Data with an unknown size at compile time or a size that might change must be stored on the heap instead.
// The heap is less organized: when you put data on the heap, you request a certain amount of space.
// The operating system finds an empty spot in the heap that is big enough, marks it as being in use, and returns a pointer, which is the address of that location.
// This process is called allocating on the heap and is sometimes abbreviated as just allocating. Pushing values onto the stack is not considered allocating.
// Because the pointer is a known, fixed size, you can store the pointer on the stack, but when you want the actual data, you must follow the pointer.

// Ownership Rules
// First, let’s take a look at the ownership rules. Keep these rules in mind as we work through the examples that illustrate them:

// 1）Each value in Rust has a variable that’s called its owner.
// 2）There can only be one owner at a time.
// 3）When the owner goes out of scope, the value will be dropped.

// * Ownership and Functions
// The semantics for passing a value to a function are similar to those for assigning a value to a variable.
// Passing a variable to a function will move or copy, just as assignment does.

fn ownership_and_function() {
    let s = String::from("hello"); // s comes into scope

    takes_ownership(s); // s's value moves into the function...
                        // ... and so is no longer valid here

    let x = 5; // x comes into scope

    makes_copy(x); // x would move into the function,
                   // but i32 is Copy, so it’s okay to still
                   // use x afterward
}

// Here, x goes out of scope, then s. But because s's value was moved, nothing
// special happens.
fn takes_ownership(some_string: String) {
    // some_string comes into scope
    println!("{}", some_string);
} // Here, some_string goes out of scope and `drop` is called. The backing memory is freed.

fn makes_copy(some_integer: i32) {
    // some_integer comes into scope
    println!("{}", some_integer);
} // Here, some_integer goes out of scope. Nothing special happens.

// * Return Values and Scope
// Returning values can also transfer ownership

fn return_value_and_scope() {
    let s1 = gives_ownership(); // gives_ownership moves its return
                                // value into s1

    let s2 = String::from("hello"); // s2 comes into scope

    let s3 = takes_and_gives_back(s2); // s2 is moved into
                                       // takes_and_gives_back, which also
                                       // moves its return value into s3
} // Here, s3 goes out of scope and is dropped. s2 goes out of scope but was
  // moved, so nothing happens. s1 goes out of scope and is dropped.

fn gives_ownership() -> String {
    // gives_ownership will move its
    // return value into the function
    // that calls it

    let some_string = String::from("hello"); // some_string comes into scope

    some_string // some_string is returned and
                // moves out to the calling
                // function
}

// takes_and_gives_back will take a String and return one
fn takes_and_gives_back(a_string: String) -> String {
    // a_string comes into
    // scope

    a_string // a_string is returned and moves out to the calling function
}

fn return_value_and_scope1() {
    let s1 = String::from("hello");

    let (s2, len) = calculate_length(s1);

    println!("The length of '{}' is {}.", s2, len);
}

fn calculate_length(s: String) -> (String, usize) {
    let length = s.len(); // len() returns the length of a String
    (s, length)
}

/*
The Rules of References
Let’s recap what we’ve discussed about references:

    1) At any given time, you can have either one mutable reference or any number of immutable references.
    2) References must always be valid.
 */

// Reference and Borrowing
fn reference_borrow() {
    let s1 = String::from("hello");

    let len = calculate_length_ref(&s1);

    println!("The length of {} is {}.", s1, len);
}

fn calculate_length_ref(s: &String) -> usize {
    // s is a reference to a String
    s.len()
} // Here, s goes out of scope. But because it does not have ownership of what
  // it refers to, nothing happens.
  // The scope in which the variable s is valid is the same as any function parameter’s scope,
  // but we don’t drop what the reference points to when it goes out of scope because we don’t have ownership.

// Reference and Borrowing
fn reference_borrow_mut() {
    // *** Mutable References
    let mut s = String::from("hello ");

    // But mutable references have one big restriction: *** you can have only one mutable reference to
    // a particular piece of data in a particular scope. This code will fail:
    change(&mut s);

    // compile error, because there are two reference;
    let r1 = &mut s;
    // let r2 = &mut s;

    // This restriction allows for mutation but in a very controlled fashion. It’s something that new Rustaceans struggle with,
    // because most languages let you mutate whenever you’d like.

    // The benefit of having this restriction is that Rust can prevent data races at compile time. A data race is similar to a race condition and happens
    // when these three behaviors occur:

    // 1) Two or more pointers access the same data at the same time.
    // 2) At least one of the pointers is being used to write to the data.
    // 3) There’s no mechanism being used to synchronize access to the data.
    // Data races cause undefined behavior and can be difficult to diagnose and fix when you’re trying to track them down at runtime;
    // Rust prevents this problem from happening because it won’t even compile code with data races!

    let c1 = &s; // no problem
    let c2 = &s; // no problem, could be more than one const ref in a scope

    // * let c3 = &mut s; // big problem, limitd, ref and mut ref in a scope.

    {
        /*
                let mut s = String::from("hello");

                let r1 = &s; // no problem
                let r2 = &s; // no problem
                let r3 = &mut s; // BIG PROBLEM

                println!("{}, {}, and {}", r1, r2, r3);

                error[E0502]: cannot borrow `s` as mutable because it is also borrowed as immutable
         --> src/main.rs:6:14
          |
        4 |     let r1 = &s; // no problem
          |              -- immutable borrow occurs here
        5 |     let r2 = &s; // no problem
        6 |     let r3 = &mut s; // BIG PROBLEM
          |              ^^^^^^ mutable borrow occurs here
        7 |
        8 |     println!("{}, {}, and {}", r1, r2, r3);
          |                                -- immutable borrow later used here

                Whew! *** We also cannot have a mutable reference while we have an immutable one.
                Users of an immutable reference don’t expect the values to suddenly change out from under them! However,
                multiple immutable references are okay because no one who is just reading the data has the ability
                to affect anyone else’s reading of the data.

                Note that a reference’s scope starts from where it is introduced and continues
                through the last time that reference is used. For instance,
                this code will compile because the last usage of the immutable references occurs
                before the mutable reference is introduced:
                */

        // ***
        // 1) At any given time, you can have either one mutable reference or any number of immutable references.
        // 2) References must always be valid.

        let mut s = String::from("hello");

        let r1 = &s; // no problem
        let r2 = &s; // no problem
        println!("{} and {}", r1, r2);
        // r1 and r2 are no longer used after this point

        let r3 = &mut s; // no problem
        println!("{}", r3);

        // The scopes of the immutable references r1 and r2 end after the println! where they are last used,
        // which is before the mutable reference r3 is created. These scopes don’t overlap, so this code is allowed.
    }
}

fn change(something: &mut String) {
    something.push_str("world!");
}

fn ownership() {
    {
        // Move
        let s1 = String::from("hello world");
        println!("s1 : {}", s1);

        // Move: s1 has been moved into s2
        // after it, s1 is none
        // it avoid the double call to drop func of memory
        let s2 = s1;
        println!("s2 : {}", s2);
    }

    {
        // Clone
        let s1 = String::from("hello world");
        let s2 = s1.clone();

        println!("s1: {} s2: {}", s1, s2);
    }

    {
        // *** Stack-Only Data: Copy ***
        // But this code seems to contradict what we just learned: we don’t have a call to clone,
        // but x is still valid and wasn’t moved into y.
        let x = 5;
        let y = x;
        println!("x: {}, y: {}", x, y);

        // The reason is that types such as integers that have a known size at compile time are stored entirely on the stack,
        // so copies of the actual values are quick to make.
        // That means there’s no reason we would want to prevent x from being valid after we create the variable y.
        // In other words, there’s no difference between deep and shallow copying here,
        // so calling clone wouldn’t do anything different from the usual shallow copying and we can leave it out.

        /*
        Rust has a special annotation called the Copy trait that we can place on types like integers that are stored on the stack (we’ll talk more about traits in Chapter 10).
        If a type has the Copy trait, an older variable is still usable after assignment.
        Rust won’t let us annotate a type with the Copy trait if the type, or any of its parts, has implemented the Drop trait.
        If the type needs something special to happen when the value goes out of scope and we add the Copy annotation to that type,
        we’ll get a compile-time error. To learn about how to add the Copy annotation to your type, see “Derivable Traits” in Appendix C.

        So what types are Copy? You can check the documentation for the given type to be sure,
        but as a general rule, any group of simple scalar values can be Copy,
        and nothing that requires allocation or is some form of resource is Copy.
        Here are some of the types that are Copy:

        1) All the integer types, such as u32.
        2) The Boolean type, bool, with values true and false.
        3) All the floating point types, such as f64.
        4) The character type, char.
        5) Tuples, if they only contain types that are also Copy. For example, (i32, i32) is Copy, but (i32, String) is not.

        */
    }
}

// Defining a function to take a string slice instead of a reference to a String makes our API more general and useful without losing any functionality:
fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    &s[..]
}

fn test_slice() {
    // *** Slice   s[n..m] starts from n and ends up to m-1
    // Another data type that does not have ownership is the slice.
    // Slices let you reference a contiguous sequence of elements in a collection rather than the whole collection.

    // Here’s a small programming problem: write a function that takes a string and returns the first word it finds in that string.
    // If the function doesn’t find a space in the string, the whole string must be one word, so the entire string should be returned

    // A string slice is a reference to part of a String
    let mut s = String::from("hello world");

    let hello = &s[0..5];
    let world = &s[6..11];
    // This is similar to taking a reference to the whole String but with the extra [0..5] bit. Rather than a reference to the entire String, it’s a reference to a portion of the String.

    // We can create slices using a range within brackets by specifying [starting_index..ending_index],
    // where starting_index is the first position in the slice and ending_index is one more than the last position in the slice.
    let my_string = String::from("hello world");

    // first_word works on slices of `String`s
    let word = first_word(&my_string[..]);
    // let word = first_word(my_string);  // error expected &str, found struct `std::string::String`

    let my_string_literal = "hello world";

    // first_word works on slices of string literals
    let word = first_word(&my_string_literal[..]);

    // Because string literals *are* string slices already,
    // this works too, without the slice syntax!
    let word = first_word(my_string_literal);

    {
        let s = String::from("hello");

        // take start of string, to 2
        let slice1 = &s[0..2];
        let slice2 = &s[..2];

        println!("1:{}, 2:{}", slice1, slice2);

        let len = s.len();

        // take n to end of string
        let slice1 = &s[3..len];
        let slice2 = &s[3..];
        println!("1:{}, 2:{}", slice1, slice2);

        // take the entire string
        let slice1 = &s[0..len];
        let slice2 = &s[..];
        println!("1:{}, 2:{}", slice1, slice2);
    }
}

// Module std::pin
// Types that pin data to its location in memory.

// It is sometimes useful to have objects that are guaranteed not to move, in the sense that their placement in memory does not change, and can thus be relied upon.
// A prime example of such a scenario would be building self-referential structs, as moving an object with pointers to itself will invalidate them, which could cause undefined behavior.

// A Pin<P> ensures that the pointee of any pointer type P has a stable location in memory, meaning it cannot be moved elsewhere and its memory cannot be deallocated until it gets dropped.
// We say that the pointee is "pinned".

// By default, all types in Rust are movable. Rust allows passing all types by-value, and common smart-pointer types such as Box<T> and &mut T allow replacing and moving the values they contain: you can move out of a Box<T>, or you can use mem::swap.
/// Pin<P> wraps a pointer type P, so Pin<Box<T>> functions much like a regular Box<T>: when a Pin<Box<T>> gets dropped, so do its contents, and the memory gets deallocated.
// Similarly, Pin<&mut T> is a lot like &mut T. However, Pin<P> does not let clients actually obtain a Box<T> or &mut T to pinned data, which implies that you cannot use operations such as mem::swap:
fn swap_pins<T>(x: Pin<&mut T>, y: Pin<&mut T>) {
    // `mem::swap` needs `&mut T`, but we cannot get it.
    // We are stuck, we cannot swap the contents of these references.
    // We could use `Pin::get_unchecked_mut`, but that is unsafe for a reason:
    // we are not allowed to use it for moving things out of the `Pin`.


}

// It is worth reiterating that Pin<P> does not change the fact that a Rust compiler considers all types movable. mem::swap remains callable for any T.
// Instead, Pin<P> prevents certain values (pointed to by pointers wrapped in Pin<P>) from being moved by making it impossible to call methods that require &mut T on them (like mem::swap).

// Pin<P> can be used to wrap any pointer type P, and as such it interacts with Deref and DerefMut.
// A Pin<P> where P: Deref should be considered as a "P-style pointer" to a pinned P::Target -- so, a Pin<Box<T>> is an owned pointer to a pinned T, and a Pin<Rc<T>> is a reference-counted pointer to a pinned T.
// For correctness, Pin<P> relies on the implementations of Deref and DerefMut not to move out of their self parameter, and only ever to return a pointer to pinned data when they are called on a pinned pointer.

fn test_pin() {

    let unmoved = Unmovable::new("hello".to_string());
    // The pointer should point to the correct location,
    // so long as the struct hasn't moved.
    // Meanwhile, we are free to move the pointer around.
    let mut still_unmoved = unmoved;
    assert_eq!(still_unmoved.slice, NonNull::from(&still_unmoved.data));

    // Since our type doesn't implement Unpin, this will fail to compile:
    // let mut new_unmoved = Unmovable::new("world".to_string());
    // std::mem::swap(&mut *still_unmoved, &mut *new_unmoved);
}

// This is a self-referential struct because the slice field points to the data field.
// We cannot inform the compiler about that with a normal reference,
// as this pattern cannot be described with the usual borrowing rules.
// Instead we use a raw pointer, though one which is known not to be null,
// as we know it's pointing at the string.
struct Unmovable {
    data: String,
    slice: NonNull<String>,
    _pin: PhantomPinned,
}

impl Unmovable {
    // To ensure the data doesn't move when the function returns,
    // we place it in the heap where it will stay for the lifetime of the object,
    // and the only way to access it would be through a pointer to it.
    fn new(data: String) -> Pin<Box<Self>> {
        let res = Unmovable {
            data,
            // we only create the pointer once the data is in place
            // otherwise it will have already moved before we even started
            slice: NonNull::dangling(),
            _pin: PhantomPinned,
        };
        let mut boxed = Box::pin(res);

        let slice = NonNull::from(&boxed.data);
        // we know this is safe because modifying a field doesn't move the whole struct
        unsafe {
            let mut_ref: Pin<&mut Self> = Pin::as_mut(&mut boxed);
            Pin::get_unchecked_mut(mut_ref).slice = slice;
        }
        boxed
    }
}


// *** Unpin ***
// Many types are always freely movable, even when pinned, because they do not rely on having a stable address.
// This includes all the basic types (like bool, i32, and references) as well as types consisting solely of these types.
// Types that do not care about pinning implement the Unpin auto-trait, which cancels the effect of Pin<P>.
// For T: Unpin, Pin<Box<T>> and Box<T> function identically, as do Pin<&mut T> and &mut T.

// Note that pinning and Unpin only affect the pointed-to type P::Target, not the pointer type P itself that got wrapped in Pin<P>.
// For example, whether or not Box<T> is Unpin has no effect on the behavior of Pin<Box<T>> (here, T is the pointed-to type).
fn test_unpin() {

    // string is unpin object,
    let mut string = "this".to_string();
    let mut pinned_string = Pin::new(&mut string);

    // We need a mutable reference to call `mem::replace`.
    // We can obtain such a reference by (implicitly) invoking `Pin::deref_mut`,
    // but that is only possible because `String` implements `Unpin`.
    mem::replace(&mut *pinned_string, "other".to_string());

    println!("{}", *pinned_string); // "other"
}

pub fn test_owenership() {
    ownership();

    ownership_and_function();

    test_slice()
}
