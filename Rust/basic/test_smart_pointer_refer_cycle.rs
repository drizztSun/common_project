// *** Reference Cycles Can Leak Memory ***
// Rust’s memory safety guarantees make it difficult, but not impossible, to accidentally create memory that is never cleaned up (known as a memory leak).
// Preventing memory leaks entirely is not one of Rust’s guarantees in the same way that disallowing data races at compile time is, meaning memory leaks are memory safe in Rust.
// We can see that Rust allows memory leaks by using Rc<T> and RefCell<T>:
//         it’s possible to create references where items refer to each other in a cycle.
//         This creates memory leaks because the reference count of each item in the cycle will never reach 0, and the values will never be dropped.

mod refer_cycle {

    //use crate::List::{Cons, Nil};
    use std::cell::RefCell;
    use std::rc::{Rc, Weak};
    use std::vec;


    #[derive(Debug)]
    enum List2 {
        Cons2(i32, RefCell<Rc<List2>>),
        Nil,
    }

    use List2::{Cons2, Nil};

    impl List2 {
        fn tail(&self) -> Option<&RefCell<Rc<List2>>> {
            match self {
                Cons2(_, item) => Some(item),
                Nil => None,
            }
        }
    }

    pub fn test_reference_cycle() {
        let a = Rc::new(Cons2(5, RefCell::new(Rc::new(Nil))));

        println!("a initial rc count = {}", Rc::strong_count(&a));
        println!("a next item = {:?}", a.tail());

        let b = Rc::new(Cons2(6, RefCell::new(Rc::clone(&a))));

        println!("a rc count after b creation = {}", Rc::strong_count(&a));
        println!("b initial rc count = {}", Rc::strong_count(&b));
        println!("b next item ={:?}", b.tail());

        if let Some(link) = a.tail() {
            *link.borrow_mut() = Rc::clone(&b);
        }

        println!("b rc counter after changing a = {}", Rc::strong_count(&b));
        println!("a rc counter after changing b = {}", Rc::strong_count(&a));

        // Uncomment the next line to see that we have a cycle;
        // it will overflow the stack
        // println!("a next item = {:?}", a.tail());


        // Creating reference cycles is not easily done, but it’s not impossible either.
        // If you have RefCell<T> values that contain Rc<T> values or similar nested combinations of types with interior mutability and reference counting,
        // you must ensure that you don’t create cycles; you can’t rely on Rust to catch them.
        // Creating a reference cycle would be a logic bug in your program that you should use automated tests, code reviews, and other software development practices to minimize.
    }

    /*
    *** Preventing Reference Cycles: Turning an Rc<T> into a Weak<T> ***
    So far, we’ve demonstrated that calling Rc::clone increases the strong_count of an Rc<T> instance, and an Rc<T> instance is only cleaned up if its strong_count is 0.
    You can also create a weak reference to the value within an Rc<T> instance by calling Rc::downgrade and passing a reference to the Rc<T>.
    When you call Rc::downgrade, you get a smart pointer of type Weak<T>. Instead of increasing the strong_count in the Rc<T> instance by 1, calling Rc::downgrade increases the weak_count by 1.
    The Rc<T> type uses weak_count to keep track of how many Weak<T> references exist, similar to strong_count. The difference is the weak_count doesn’t need to be 0 for the Rc<T> instance to be cleaned up.

    Strong references are how you can share ownership of an Rc<T> instance. Weak references don’t express an ownership relationship.
    They won’t cause a reference cycle because any cycle involving some weak references will be broken once the strong reference count of values involved is 0.

    Because the value that Weak<T> references might have been dropped, to do anything with the value that a Weak<T> is pointing to,
    you must make sure the value still exists. Do this by calling the upgrade method on a Weak<T> instance, which will return an Option<Rc<T>>.
    You’ll get a result of Some if the Rc<T> value has not been dropped yet and a result of None if the Rc<T> value has been dropped.
    Because upgrade returns an Option<Rc<T>>, Rust will ensure that the Some case and the None case are handled, and there won’t be an invalid pointer.
    */

    #[derive(Debug)]
    struct Node {
        value: i32,
        parent: RefCell<Weak<Node>>, // points to parent
        children: RefCell<Vec<Rc<Node>>>, // points to children
    }

    pub fn test_weak_reference() {

        let leaf = Rc::new(Node{
            value: 3,
            parent: RefCell::new(Weak::new()),
            children: RefCell::new(vec![]),
        });

        println!("leaf strong ={}, weak={}", Rc::strong_count(&leaf), Rc::weak_count(&leaf));
        println!("leaf parent : {:?}", leaf.parent.borrow().upgrade());

        {
            let branch = Rc::new(Node{
                value: 5,
                parent: RefCell::new(Weak::new()),
                children: RefCell::new(vec![Rc::clone(&leaf)]),
            });

            *leaf.parent.borrow_mut() = Rc::downgrade(&branch);

            println!("branch strong = {}, weak = {}", Rc::strong_count(&branch), Rc::weak_count(&branch));
            println!("branch strong = {}, weak = {}", Rc::strong_count(&leaf), Rc::weak_count(&leaf));
        }

        println!("leaf parent : {:?}", leaf.parent.borrow().upgrade());
        println!("branch strong = {}, weak = {}", Rc::strong_count(&leaf), Rc::weak_count(&leaf));
    }

}

pub fn test_reference_cycle() {
    refer_cycle::test_reference_cycle();
}
