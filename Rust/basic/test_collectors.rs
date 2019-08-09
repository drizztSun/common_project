// use std::collections::Vec;

fn test_vec() {
    let v: Vec<i32> = Vec::new();
    /* 
    As with any variable, if we want to be able to change its value, 
    we need to make it mutable using the mut keyword, as discussed in Chapter 3. 
    The numbers we place inside are all of type i32, and Rust infers this from the data, so we don’t need the Vec<i32> annotation
    */
    let mut s = Vec::new();

    s.push(1);
    s.push(2);
    s.push(3);

    /* 
    Note two details here. First, we use the index value of 2 to get the third element: 
    vectors are indexed by number, starting at zero. Second, the two ways to get the third element are by using & and [], 
    which gives us a reference, or by using the get method with the index passed as an argument, which gives us an Option<&T>.
    */
    let m = vec![1, 2, 3];
    let third: &i32 = &m[2];
    println!("The thrid element is {}", third);

    match m.get(2) {
        Some(third) => println!("The third element is {}", third),
        None => println!("There is no third element"),
    }

    /*
    let doesn't_exist: &i32 = &m[100];
    thread 'main' panicked at 'index out of bounds: the len is 5 but the index is 100'
    When the get method is passed an index that is outside the vector, 
    it returns None without panicking. You would use this method if accessing an element 
    beyond the range of the vector happens occasionally under normal circumstances. 
    Your code will then have logic to handle having either Some(&element) or None, 
    */
    match m.get(100) {
        Some(third) => println!("The 100th element is {}", third),
        None => println!("There is no 100th element"),
    }


    /*
    When the program has a valid reference, the borrow checker enforces the ownership and borrowing rules 
    (covered in Chapter 4) to ensure this reference and any other references to the contents of the vector 
    remain valid. Recall the rule that states you can’t have mutable and immutable references in the same scope. That rule applies in Listing 8-7, where we hold an immutable reference to the first element in a vector and try to add an element to the end, which won’t work.
    
    let mut v = vec![1, 2, 3, 4, 5];
    let first = &v[0];
    v.push(6);
    println!("The first element is: {}", first);
    
    error[E0502]: cannot borrow `v` as mutable because it is also borrowed as immutable
 --> src/main.rs:6:5
  |
4 |     let first = &v[0];
  |                  - immutable borrow occurs here
5 |
6 |     v.push(6);
  |     ^^^^^^^^^ mutable borrow occurs here
7 |
8 |     println!("The first element is: {}", first);
  |                                          ----- immutable borrow later used here
    */

    { // Iterate the array
        let v = vec![100, 32, 57];
        for i in &v {
            println!("{}", i);
        }
    }

    { 
        let mut v = vec![100, 32, 57];
        for i in &mut v {
            *i += 50;
        }
    }

    {
        // using an enum to store multiple values
        let row = vec![
            SpreadsheetCell::Int(3),
            SpreadsheetCell::Float(3.2),
            SpreadsheetCell::Text(String::from("blue")),
        ];

        for i in &row {
            match i {
                SpreadsheetCell::Int(state) => println!("Int: {}", state),
                SpreadsheetCell::Float(state) => println!("Float: {}", state),
                SpreadsheetCell::Text(state) => println!("String: {}", state),
                _ => println!("default"),
            }
        }
    }
}

enum SpreadsheetCell {
    Int(i32),
    Float(f64),
    Text(String),
}

pub fn test_collectors() {

    test_vec();
}