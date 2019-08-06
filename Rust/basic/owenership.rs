fn owenership_and_function() {
    
    let s = String::from("hello");  // s comes into scope

    takes_ownership(s);             // s's value moves into the function...
                                    // ... and so is no longer valid here

    let x = 5;                      // x comes into scope

    makes_copy(x);                  // x would move into the function,
                                    // but i32 is Copy, so it’s okay to still
                                    // use x afterward

}

// Here, x goes out of scope, then s. But because s's value was moved, nothing
// special happens.
fn takes_ownership(some_string: String) { // some_string comes into scope
    println!("{}", some_string);
} // Here, some_string goes out of scope and `drop` is called. The backing
  // memory is freed.

fn makes_copy(some_integer: i32) { // some_integer comes into scope
    println!("{}", some_integer);
} // Here, some_integer goes out of scope. Nothing special happens.

fn return_value_and_scope() {
    let s1 = gives_ownership();         // gives_ownership moves its return
                                        // value into s1

    let s2 = String::from("hello");     // s2 comes into scope

    let s3 = takes_and_gives_back(s2);  // s2 is moved into
                                        // takes_and_gives_back, which also
                                        // moves its return value into s3
} // Here, s3 goes out of scope and is dropped. s2 goes out of scope but was
  // moved, so nothing happens. s1 goes out of scope and is dropped.

fn gives_ownership() -> String {             // gives_ownership will move its
                                             // return value into the function
                                             // that calls it

    let some_string = String::from("hello"); // some_string comes into scope

    some_string                              // some_string is returned and
                                             // moves out to the calling
                                             // function
}

// takes_and_gives_back will take a String and return one
fn takes_and_gives_back(a_string: String) -> String { // a_string comes into
                                                      // scope

    a_string  // a_string is returned and moves out to the calling function
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
    s.len()
}

// Reference and Borrowing 
fn reference_borrow_mut() {
    let mut s = String::from("hello ");

    // But mutable references have one big restriction: you can have only one mutable reference to 
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
}

fn change(something: &mut String) {
    something.push_str("world!");
}

fn test_owenership() {
    
    owenership_and_function();
}