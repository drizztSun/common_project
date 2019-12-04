// *** RefCell<T> and the Interior Mutability Pattern
// Interior mutability is a design pattern in Rust that allows you to mutate data even when there are immutable references to that data; normally, this action is disallowed by the borrowing rules.
// To mutate data, the pattern uses unsafe code inside a data structure to bend Rust’s usual rules that govern mutation and borrowing. We haven’t yet covered unsafe code; we will in Chapter 19.
// We can use types that use the interior mutability pattern when we can ensure that the borrowing rules will be followed at runtime, even though the compiler can’t guarantee that.
// The unsafe code involved is then wrapped in a safe API, and the outer type is still immutable.

// Let’s explore this concept by looking at the RefCell<T> type that follows the interior mutability pattern.

// *** Enforcing Borrowing Rules at Runtime with RefCell<T>
// *** Unlike Rc<T>, the RefCell<T> type represents SINGLE OWNERSHIP over the data it holds. So, what makes RefCell<T> different from a type like Box<T>?

// *** Recall the borrowing rules you learned in Chapter 4:
// 1) At any given time, you can have either (but not both of) one mutable reference or any number of immutable references.
// 2) References must always be valid.
// With references and Box<T>, the borrowing rules’ invariants are enforced at COMPILE time. With RefCell<T>, these invariants are enforced at RUNTIME.
// With references, if you break these rules, you’ll get a compiler error. With RefCell<T>, if you break these rules, your program will panic and exit.

// The advantages of checking the borrowing rules at compile time are that errors will be caught sooner in the development process,
// and there is no impact on runtime performance because all the analysis is completed beforehand.
// For those reasons, checking the borrowing rules at compile time is the best choice in the majority of cases, which is why this is Rust’s defaul t.

// The advantage of checking the borrowing rules at runtime instead is that certain memory-safe scenarios are then allowed, whereas they are disallowed by the compile-time checks.
// Static analysis, like the Rust compiler, is inherently conservative. Some properties of code are impossible to detect by analyzing the code: the most famous example is the Halting Problem, which is beyond the scope of this book but is an interesting topic to research.

// Because some analysis is impossible, if the Rust compiler can’t be sure the code complies with the ownership rules, it might reject a correct program;
// in this way, it’s conservative. If Rust accepted an incorrect program, users wouldn’t be able to trust in the guarantees Rust makes.
// However, if Rust rejects a correct program, the programmer will be inconvenienced, but nothing catastrophic can occur.

// *** The RefCell<T> type is useful when you’re sure your code follows the borrowing rules but the compiler is unable to understand and guarantee that.

// *** Similar to Rc<T>, RefCell<T> is only for use in single-threaded scenarios and will give you a compile-time error if you try using it in a multithreaded context.
// We’ll talk about how to get the functionality of

// *** Here is a recap of the reasons to choose Box<T>, Rc<T>, or RefCell<T>:

// 1) Rc<T> enables multiple owners of the same data; Box<T> and RefCell<T> have single owners.
// 2) Box<T> allows immutable or mutable borrows checked at compile time; Rc<T> allows only immutable borrows checked at compile time; RefCell<T> allows immutable or mutable borrows checked at runtime.
// 3) Because RefCell<T> allows mutable borrows checked at runtime, you can mutate the value inside the RefCell<T> even when the RefCell<T> is immutable.

// Mutating the value inside an immutable value is the interior mutability pattern. Let’s look at a situation in which interior mutability is useful and examine how it’s possible.

use std::cell::RefCell;

trait Messager {
    fn send(&self, msg: &str);
}

struct LimitTrack<'a, T: Messager> {
    messager: &'a T,
    value: usize,
    max: usize,
}

impl<'a, T> LimitTrack<'a, T>
where
    T: Messager,
{
    pub fn new(messager: &T, max: usize) -> LimitTrack<T> {
        LimitTrack {
            messager,
            value: 0,
            max,
        }
    }

    pub fn set_value(&mut self, val: usize) {
        self.value = val;
        let percentage_of_max = self.value as f64 / self.max as f64;

        if percentage_of_max >= 1.0 {
            self.messager.send("Error: you are over your quota!");
        } else if percentage_of_max >= 0.9 {
            self.messager
                .send("Urgent warning: you are over 90% of your quote!");
        } else if percentage_of_max >= 0.75 {
            self.messager
                .send("Waning: You've used up over 75% of your quota!");
        }
    }
}

struct MockMessager {
    // send_messages: Vec<String>,
    send_messages: RefCell<Vec<String>>,
}

impl MockMessager {
    fn new() -> MockMessager {
        MockMessager {
            send_messages: RefCell::new(vec![]),
        }
    }
}

impl Messager for MockMessager {
    fn send(&self, msg: &str) {
        // error ----- help: consider changing this to be a mutable reference: `&mut self`
        self.send_messages.borrow_mut().push(String::from(msg)); // error `self` is a `&` reference, so the data it refers to cannot be borrowed as mutable
    }
    // We can’t modify the MockMessenger to keep track of the messages, because the send method takes an immutable reference to self.
    // We also can’t take the suggestion from the error text to use &mut self instead,
    // because then the signature of send wouldn’t match the signature in the Messenger trait definition (feel free to try and see what error message you get).

    // This is a situation in which interior mutability can help! We’ll store the sent_messages within a RefCell<T>,
    // and then the send message will be able to modify sent_messages to store the messages we’ve seen.

    //The sent_messages field is now of type RefCell<Vec<String>> instead of Vec<String>. In the new function, we create a new RefCell<Vec<String>> instance around the empty vector.

    // For the implementation of the send method, the first parameter is still an immutable borrow of self, which matches the trait definition.
    // We call borrow_mut on the RefCell<Vec<String>> in self.sent_messages to get a mutable reference to the value inside the RefCell<Vec<String>>, which is the vector.
    // Then we can call push on the mutable reference to the vector to keep track of the messages sent during the test.

    // The last change we have to make is in the assertion: to see how many items are in the inner vector, we call borrow on the RefCell<Vec<String>> to get an immutable reference to the vector.
}

fn test_ref_cell_basic() {
    // let x = 5;
    // - help: consider changing this to be mutable: `mut x`
    // let y = &mut x;
    // ^^^^^^ cannot borrow as mutable

    // However, there are situations in which it would be useful for a value to mutate itself in its methods but appear immutable to other code.
    // Code outside the value’s methods would not be able to mutate the value.

    // Using RefCell<T> is one way to get the ability to have interior mutability.
    // But RefCell<T> doesn’t get around the borrowing rules completely: the borrow checker in the compiler allows this interior mutability,
    // and the borrowing rules are checked at runtime instead. If you violate the rules, you’ll get a panic! instead of a compiler error.

    let mockmessage = MockMessager::new();
    let mut track = LimitTrack::new(&mockmessage, 100);
    track.set_value(80);

    assert_eq!(mockmessage.send_messages.borrow().len(), 1);
}

// *** Keeping Track of Borrows at Runtime with RefCell<T>
// When creating immutable and mutable references, we use the & and &mut syntax, respectively. With RefCell<T>,
// we use the borrow and borrow_mut methods, which are part of the safe API that belongs to RefCell<T>.
// The borrow method returns the smart pointer type Ref<T>, and borrow_mut returns the smart pointer type RefMut<T>.
// Both types implement Deref, so we can treat them like regular references.

// he RefCell<T> keeps track of how many Ref<T> and RefMut<T> smart pointers are currently active.
// Every time we call borrow, the RefCell<T> increases its count of how many immutable borrows are active.
// When a Ref<T> value goes out of scope, the count of immutable borrows goes down by one.
// Just like the compile-time borrowing rules, RefCell<T> lets us have many immutable borrows or one mutable borrow at any point in time.

/*
impl Messenger for MockMessenger {
    fn send(&self, message: &str) {
        let mut one_borrow = self.sent_messages.borrow_mut();
        let mut two_borrow = self.sent_messages.borrow_mut();

        // runtime error, multiple mut
        // We create a variable one_borrow for the RefMut<T> smart pointer returned from borrow_mut.
        // Then we create another mutable borrow in the same way in the variable two_borrow.
        // This makes two mutable references in the same scope, which isn’t allowed.
        // When we run the tests for our library, the code in Listing 15-23 will compile without any errors, but the test will fail:

        one_borrow.push(String::from(message));
        two_borrow.push(String::from(message));
    }
}
*/

// Catching borrowing errors at runtime rather than compile time means that you would find a mistake in your code later in the development process and possibly not until your code was deployed to production.
// Also, your code would incur a small runtime performance penalty as a result of keeping track of the borrows at runtime rather than compile time.

// However, using RefCell<T> makes it possible to write a mock object that can modify itself to keep track of the messages it has seen while you’re using it in a context where only immutable values are allowed.
// You can use RefCell<T> despite its trade-offs to get more functionality than regular references provide.

// *** Having Multiple Owners of Mutable Data by Combining Rc<T> and RefCell<T>
// A common way to use RefCell<T> is in combination with Rc<T>.
// Recall that Rc<T> lets you have multiple owners of some data, but it only gives immutable access to that data.
// If you have an Rc<T> that holds a RefCell<T>, you can get a value that can have multiple owners and that you can mutate!

use std::rc::Rc;
use List::{Cons, Nil};
/*
#[derive(Debug)]
enum List {
    Cons(Rc<RefCell<i32>>, Rc<List>),
    Nil,
}

fn test_rc_refcell() {
    let value = Rc::new(RefCell::new(5));

    let a = Rc::new(Cons(Rc::clone(&value), Rc::new(Nil)));

    let b = Cons(Rc::new(RefCell::new(6)), Rc::clone(&a));
    let c = Cons(Rc::new(RefCell::new(10)), Rc::clone(&a));

    *value.borrow_mut() += 10;

    println!("a after = {:?}", a);
    println!("b after = {:?}", b);
    println!("c after = {:?}", c);
}
*/

// *** Reference Cycles Can Leak Memory
// Rust’s memory safety guarantees make it difficult, but not impossible, to accidentally create memory that is never cleaned up (known as a memory leak).
// Preventing memory leaks entirely is not one of Rust’s guarantees in the same way that disallowing data races at compile time is, meaning memory leaks are memory safe in Rust.
// We can see that Rust allows memory leaks by using Rc<T> and RefCell<T>: it’s possible to create references where items refer to each other in a cycle.
// This creates memory leaks because the reference count of each item in the cycle will never reach 0, and the values will never be dropped.

#[derive(Debug)]
enum List {
    Cons(i32, RefCell<Rc<List>>),
    Nil,
}

impl List {
    fn tail(&self) -> Option<&RefCell<Rc<List>>> {
        match self {
            Cons(_, item) => Some(item),
            Nil => None,
        }
    }
}

// We’re using another variation of the List definition from Listing 15-5.
// The second element in the Cons variant is now RefCell<Rc<List>>, meaning that instead of having the ability to modify the i32 value as we did in Listing 15-24,
// we want to modify which List value a Cons variant is pointing to.
// We’re also adding a tail method to make it convenient for us to access the second item if we have a Cons variant.

fn test_refcell_leak() {
    let a = Rc::new(Cons(5, RefCell::new(Rc::new(Nil))));

    println!("a initial rc count = {}", Rc::strong_count(&a));
    println!("a next item = {:?}", a.tail());

    let b = Rc::new(Cons(10, RefCell::new(Rc::clone(&a))));

    println!("a rc count after b creation = {}", Rc::strong_count(&a));
    println!("b initial rc count = {}", Rc::strong_count(&b));
    println!("b next item = {:?}", b.tail());

    if let Some(link) = a.tail() {
        *link.borrow_mut() = Rc::clone(&b);
    }

    println!("b rc count after changing a = {}", Rc::strong_count(&b));
    println!("a rc count after changing a = {}", Rc::strong_count(&a));

    // Uncomment the next line to see that we have a cycle;
    // it will overflow the stack
    // println!("a next item = {:?}", a.tail());
}

// *** Preventing Reference Cycles: Turning an Rc<T> into a Weak<T>

// So far, we’ve demonstrated that calling Rc::clone increases the strong_count of an Rc<T> instance, and an Rc<T> instance is only cleaned up if its strong_count is 0.
// You can also create a weak reference to the value within an Rc<T> instance by calling Rc::downgrade and passing a reference to the Rc<T>.
// When you call Rc::downgrade, you get a smart pointer of type Weak<T>.
// Instead of increasing the strong_count in the Rc<T> instance by 1, calling Rc::downgrade increases the weak_count by 1.
// The Rc<T> type uses weak_count to keep track of how many Weak<T> references exist, similar to strong_count.
// The difference is the weak_count doesn’t need to be 0 for the Rc<T> instance to be cleaned up.

// Strong references are how you can share ownership of an Rc<T> instance. Weak references don’t express an ownership relationship.
// They won’t cause a reference cycle because any cycle involving some weak references will be broken once the strong reference count of values involved is 0.

pub fn test_ref_cell() {
    test_ref_cell_basic();

    // test_rc_refcell();

    test_refcell_leak();
}
