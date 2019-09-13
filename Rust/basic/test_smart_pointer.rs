use std::io;
use List::{Cons, Nil};
use std::ops::Deref;

// Use recusive memory, no way to figure out the size
enum List{
    // Cons(i32, List),  Cons
    Cons(i32, Box<List>),
    Nil,
}

// user-defined smart-pointer
struct myBox<T>(T);

impl<T> myBox<T> {

    fn new(x: T) -> myBox<T> {
        myBox(x)
    }
}

impl<T> Deref for myBox<T> {
    type Target = T;

    fn deref(&self) -> &T{
        &self.0
    }
}

fn test_box() {

    // Boxes don’t have performance overhead, other than storing their data on the heap instead of on the stack. 
    // But they don’t have many extra capabilities either. You’ll use them most often in these situations:

    // When you have a type whose size can’t be known at compile time and you want to use a value of that type in a context that requires an exact size
    // When you have a large amount of data and you want to transfer ownership but ensure the data won’t be copied when you do so
    // When you want to own a value and you care only that it’s a type that implements a particular trait rather than being of a specific type
    let b = Box::new(5);
    println!("b = {}", b);

    // let list = Cons(1, Cons(2, Cons(3, Nil))); // error
    //  Cons(i32, List), List is a structure, no way to find out the size
                // ----- recursive without indirection
    // = help: insert indirection (e.g., a `Box`, `Rc`, or `&`) at some point to
    let list = Cons(1, 
        Box::new(Cons(2, 
            Box::new(Cons(3,
                Box::new(Nil))))));

    let x = 5;
    let y = Box::new(x);

    assert_eq!(5, x);
    assert_eq!(5, *y);

    // The Box<T> type is a smart pointer because it implements the Deref trait, which allows Box<T> values to be treated like references. 
    // When a Box<T> value goes out of scope, the heap data that the box is pointing to is cleaned up as well because of the Drop trait implementation. 
    // Let’s explore these two traits in more detail. These two traits will be even more important to the functionality provided by the other smart pointer types we’ll discuss in the rest of this chapter.
    
    {
        let x = 5;
        let y = myBox::new(x);

        assert_eq!(5, x);
        assert_eq!(5, *y); // Deref trait called 
        // 
    }

}

pub fn test_smart_pointer() {

    test_box();


}