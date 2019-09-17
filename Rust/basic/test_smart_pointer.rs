use std::io;
use List::{Cons, Nil};
use std::ops::Deref;
use std::ops::Drop;

// This chapter covered how to use smart pointers to make different guarantees and trade-offs from those Rust makes by default with regular references. 
// The Box<T> type has a known size and points to data allocated on the heap. 
// The Rc<T> type keeps track of the number of references to data on the heap so that data can have multiple owners. 
// The RefCell<T> type with its interior mutability gives us a type that we can use when we need an immutable type but need to change an inner value of that type; 
// it also enforces the borrowing rules at runtime instead of at compile time.

// Also discussed were the Deref and Drop traits, which enable a lot of the functionality of smart pointers. 
// We explored reference cycles that can cause memory leaks and how to prevent them using Weak<T>.

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

struct exam {
    i: i32,
}

impl Drop for exam {

    fn drop(&mut self) {
        println!("Dropping the instance of example {}", self.i);
    } 
}

use std::mem::drop; 

fn test_drop() {
    {
        let a = exam{i : 21};
        let b = exam{i : 32};
        println!("Instances of Example type are created");
        // Dropping a Value Early with std::mem::drop
        drop(a);
        // a.drop() // error, can't call drop explicit
    }
}

use std::rc::Rc;

enum list {
    Cons(i32, Rc<list>),
    Nil,
}

fn test_rc_t() {
    // To enable multiple ownership, Rust has a type called Rc<T>, which is an abbreviation for reference counting. 
    // The Rc<T> type keeps track of the number of references to a value which determines whether or not a value is still in use.
    // If there are zero references to a value, the value can be cleaned up without any references becoming invalid.
    {
        let a = Cons(5,
                Box::new(Cons(10, 
                    Box::new(Nil))));

        //let b = Cons(3, Box::new(a)); // - value moved here
        //let c = Cons(4, Box::new(a)); //  ^ value used here after move
    }

    {
        let a = Rc::new(list::Cons(5, Rc::new(list::Cons(5, Rc::new(list::Nil)))));
        println!("counting after creating a = {}", Rc::strong_count(&a));

        let b = list::Cons(3, Rc::clone(&a));
        println!("counting after creating b = {}", Rc::strong_count(&a));
        {
            let c = list::Cons(4, Rc::clone(&a));
            println!("counting after creating c = {}", Rc::strong_count(&a));
        }

        // We could have called a.clone() rather than Rc::clone(&a), but Rust’s convention is to use Rc::clone in this case. 
        // The implementation of Rc::clone doesn’t make a deep copy of all the data like most types’ implementations of clone do. 
        // The call to Rc::clone only increments the reference count, which doesn’t take much time. 
        // Deep copies of data can take a lot of time. By using Rc::clone for reference counting, 
        // we can visually distinguish between the deep-copy kinds of clones and the kinds of clones that increase the reference count. 
        // When looking for performance problems in the code, we only need to consider the deep-copy clones and can disregard calls to Rc::clone.
    
        println!("couting after destroying c = {}", Rc::strong_count(&a));
        // We can see that the Rc<List> in a has an initial reference count of 1; then each time we call clone, the count goes up by 1. 
        // When c goes out of scope, the count goes down by 1. 
        // We don’t have to call a function to decrease the reference count like we have to call Rc::clone to increase the reference count: 
        // the implementation of the Drop trait decreases the reference count automatically when an Rc<T> value goes out of scope.

        // What we can’t see in this example is that when b and then a go out of scope at the end of main, the count is then 0, and the Rc<List> is cleaned up completely at that point. 
        // Using Rc<T> allows a single value to have multiple owners, and the count ensures that the value remains valid as long as any of the owners still exist.

        // Via immutable references, Rc<T> allows you to share data between multiple parts of your program for reading only. 
        // If Rc<T> allowed you to have multiple mutable references too, you might violate one of the borrowing rules discussed in Chapter 4: 
        // multiple mutable borrows to the same place can cause data races and inconsistencies. 
        // But being able to mutate data is very useful! In the next section, we’ll discuss the interior mutability pattern and the RefCell<T> type that you can use in conjunction with an Rc<T> to work with this immutability restriction.
    }
}

use std::cell::RefCell;
use std::rc::Weak;

#[derive(Debug)]
enum List1{
    Cons(i32, RefCell<Rc<List1>>),
    Nil,
}

impl List1 {
    fn tail(&self) -> Option<&RefCell<Rc<List1>>> {
        match self {
            List1::Cons(_, item) => Some(item),
            List1::Nil => None,
        }
    }
}

#[derive(Debug)]
struct Node{
    val: i32,
    children: RefCell<Vec<Rc<Node>>>,
    parent: RefCell<Weak<Node>>,
}

fn test_ref_cell() {
    // Interior mutability is a design pattern in Rust that allows you to mutate data even when there are immutable references to that data; normally, this action is disallowed by the borrowing rules. 
    // To mutate data, the pattern uses unsafe code inside a data structure to bend Rust’s usual rules that govern mutation and borrowing.
    
    // Unlike Rc<T>, the RefCell<T> type represents single ownership over the data it holds. So, what makes RefCell<T> different from a type like Box<T>? 
    // Recall the borrowing rules you learned in Chapter 4:

    // At any given time, you can have either (but not both of) one mutable reference or any number of immutable references.
    // References must always be valid.
    // With references and Box<T>, the borrowing rules’ invariants are enforced at compile time. 
    // With RefCell<T>, these invariants are enforced at runtime. 
    // With references, if you break these rules, you’ll get a compiler error. 
    // With RefCell<T>, if you break these rules, your program will panic and exit.

    // The advantages of checking the borrowing rules at compile time are that errors will be caught sooner in the development process, 
    // and there is no impact on runtime performance because all the analysis is completed beforehand. 
    // For those reasons, checking the borrowing rules at compile time is the best choice in the majority of cases, which is why this is Rust’s default.

    // Because some analysis is impossible, if the Rust compiler can’t be sure the code complies with the ownership rules, it might reject a correct program; 
    // in this way, it’s conservative. If Rust accepted an incorrect program, users wouldn’t be able to trust in the guarantees Rust makes. 
    // However, if Rust rejects a correct program, the programmer will be inconvenienced, but nothing catastrophic can occur. 
    //  The RefCell<T> type is useful when you’re sure your code follows the borrowing rules but the compiler is unable to understand and guarantee that.

    // Similar to Rc<T>, RefCell<T> is only for use in single-threaded scenarios and will give you a compile-time error if you try using it in a multithreaded context. 
    // We’ll talk about how to get the functionality of RefCell<T> in a multithreaded program in Chapter 16.

    // Here is a recap of the reasons to choose Box<T>, Rc<T>, or RefCell<T>:

    // Rc<T> enables multiple owners of the same data; Box<T> and RefCell<T> have single owners.
    // Box<T> allows immutable or mutable borrows checked at compile time; Rc<T> allows only immutable borrows checked at compile time; RefCell<T> allows immutable or mutable borrows checked at runtime.
    // Because RefCell<T> allows mutable borrows checked at runtime, you can mutate the value inside the RefCell<T> even when the RefCell<T> is immutable.
    // Mutating the value inside an immutable value is the interior mutability pattern. Let’s look at a situation in which interior mutability is useful and examine how it’s possible.
    
    // Interior Mutability: A Mutable Borrow to an Immutable Value

    // However, there are situations in which it would be useful for a value to mutate itself in its methods but appear immutable to other code. 
    // Code outside the value’s methods would not be able to mutate the value. Using RefCell<T> is one way to get the ability to have interior mutability. 
    // But RefCell<T> doesn’t get around the borrowing rules completely: the borrow checker in the compiler allows this interior mutability, and the borrowing rules are checked at runtime instead.
    // If you violate the rules, you’ll get a panic! instead of a compiler error.

    // Keeping Track of Borrows at Runtime with RefCell<T>

    // When creating immutable and mutable references, we use the & and &mut syntax, respectively. 
    // With RefCell<T>, we use the borrow and borrow_mut methods, which are part of the safe API that belongs to RefCell<T>. 
    // The borrow method returns the smart pointer type Ref<T>, and borrow_mut returns the smart pointer type RefMut<T>. 
    // Both types implement Deref, so we can treat them like regular references.

    // The RefCell<T> keeps track of how many Ref<T> and RefMut<T> smart pointers are currently active. 
    // Every time we call borrow, the RefCell<T> increases its count of how many immutable borrows are active. 
    // When a Ref<T> value goes out of scope, the count of immutable borrows goes down by one. Just like the compile-time borrowing rules, RefCell<T> lets us have many immutable borrows or one mutable borrow at any point in time.

    // If we try to violate these rules, rather than getting a compiler error as we would with references, the implementation of RefCell<T> will panic at runtime.


    // Catching borrowing errors at runtime rather than compile time means that you would find a mistake in your code later in the development process and possibly not until your code was deployed to production. 
    // Also, your code would incur a small runtime performance penalty as a result of keeping track of the borrows at runtime rather than compile time. 
    // However, using RefCell<T> makes it possible to write a mock object that can modify itself to keep track of the messages it has seen while you’re using it in a context where only immutable values are allowed. You can use RefCell<T> despite its trade-offs to get more functionality than regular references provide.
    
    
    {
        let x = 5;
        // let y = &mut x; // error cannot borrow immutable local variable `x` as mutable
    }


    {
        // creating a reference cycle
        let a = Rc::new(List1::Cons(5, RefCell::new(Rc::new(List1::Nil))));
        println!("a initial rc count = {}", Rc::strong_count(&a));
        println!("a next item ={:?}", a.tail());

        let b = Rc::new(List1::Cons(10, RefCell::new(Rc::clone(&a))));
        println!("a rc count after b creation = {}", Rc::strong_count(&a));
        println!("b initial rc count = {}", Rc::strong_count(&b));
        println!("b next item = {:?}", b.tail());

        if let Some(link) = a.tail() {
            *link.borrow_mut() = Rc::clone(&b);
        }

        println!("b rc count after changing = {}", Rc::strong_count(&b));
        println!("a rc count after changing = {}", Rc::strong_count(&a));

        // Uncomment the next line to see that we have a cycle;
        // it will overflow the stack
        // println!("a next item = {:?}", a.tail());
    }

    {
        // Preventing Reference Cycles: Turning an Rc<T> into a Weak<T>
        // Adding a Reference from a Child to Its Parent
        let leaf = Rc::new(Node{
            val: 10,
            parent: RefCell::new(Weak::new()),
            children: RefCell::new(vec![]),
            });

        let branch = Rc::new(Node{
            val: 5,
            parent: RefCell::new(Weak::new()),
            children: RefCell::new(vec![Rc::clone(&leaf))],
        });

        *leaf.parent.borrow_mut() = Rc::downgrade(&branch);
        println!("leaf parent = {:?}", leaf.parent.borrow().upgrade());

        println!("branch strong = {}, weak = {}", Rc::strong_count(&branch), Rc::weak_count(&branch));
        println!("leaf strong = {}, weak = {}", Rc::strong_count(&leaf), Rc::weak_count(&leaf));
    }

}

pub trait Messenger {
    fn send(&self, msg: &str);
}

pub struct LimitTracker<'a, T: Messenger> {
    messenger: &'a T,
    value: usize,
    max: usize,
}

impl<'a, T> LimitTracker<'a, T> 
    where T: Messenger{

    pub fn new(messenger: &T, max:usize) -> LimitTracker<T> {
        LimitTracker{
            messenger,
            value: 0,
            max,
        }
    }

    pub fn set_value(&mut self, val: usize) {
        self.value = val;
        let percentage = self.value as f64 / self.max as f64;

        if percentage >= 1.0 {
            self.messenger.send("Error: you are over your quota!");
        } else if percentage >= 0.9 {
            self.messenger.send("Urgent warning: you've used up over 90% of your quota!");
        } else if percentage >= 0.75 {
            self.messenger.send("Warning: you've used up over 75% of your quota!");
        }
    }
}

#[derive(Debug)]
enum list_2r {
    Cons(Rc<RefCell<i32>>, Rc<list_2r>),
    Nil,
}

fn test_combile_refcell_and_refcount() {
    // Having Multiple Owners of Mutable Data by Combining Rc<T> and RefCell<T>
    // A common way to use RefCell<T> is in combination with Rc<T>. Recall that Rc<T> lets you have multiple owners of some data, but it only gives immutable access to that data. 
    // If you have an Rc<T> that holds a RefCell<T>, you can get a value that can have multiple owners and that you can mutate!

    let val = Rc::new(RefCell::new(5));

    let a = Rc::new(list_2r::Cons(Rc::clone(&val), Rc::new(list_2r::Nil)));
    let b = list_2r::Cons(Rc::new(RefCell::new(10)), Rc::clone(&a));
    let c = list_2r::Cons(Rc::new(RefCell::new(15)), Rc::clone(&a));

    *val.borrow_mut() += 15;

    println!("a = {:?}", a);
    println!("b = {:?}", b);
    println!("c = {:?}", c);
}

// Reference Cycles Can Leak Memory
// Rust’s memory safety guarantees make it difficult, but not impossible, to accidentally create memory that is never cleaned up (known as a memory leak). 
// Preventing memory leaks entirely is not one of Rust’s guarantees in the same way that disallowing data races at compile time is, meaning memory leaks are memory safe in Rust. 
// We can see that Rust allows memory leaks by using Rc<T> and RefCell<T>: it’s possible to create references where items refer to each other in a cycle. This creates memory leaks because the reference count of each item in the cycle will never reach 0, and the values will never be dropped.




pub fn test_smart_pointer() {

    test_box();


}