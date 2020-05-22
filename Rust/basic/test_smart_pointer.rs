use std::io;
use std::ops::Deref;
use std::ops::Drop;
use List::{Cons, Nil};

// This chapter covered how to use smart pointers to make different guarantees and trade-offs from those Rust makes by default with regular references.
// The Box<T> type has a known size and points to data allocated on the heap.
// The Rc<T> type keeps track of the number of references to data on the heap so that data can have multiple owners.
// The RefCell<T> type with its interior mutability gives us a type that we can use when we need an immutable type but need to change an inner value of that type;
// it also enforces the borrowing rules at runtime instead of at compile time.

// Also discussed were the Deref and Drop traits, which enable a lot of the functionality of smart pointers.
// We explored reference cycles that can cause memory leaks and how to prevent them using Weak<T>.

// *** Here is a recap of the reasons to choose Box<T>, Rc<T>, or RefCell<T> *** :

// 1) Rc<T> enables multiple owners of the same data; Box<T> and RefCell<T> have single owners.
// 2) Box<T> allows immutable or mutable borrows checked at compile time; Rc<T> allows only immutable borrows checked at compile time;
//    RefCell<T> allows immutable or mutable borrows checked at runtime.
// 3) Because RefCell<T> allows mutable borrows checked at runtime, you can mutate the value inside the RefCell<T> even when the RefCell<T> is immutable.

// Use recusive memory, no way to figure out the size
enum List {
    // Cons(i32, List),  Cons # error, because its size is not decidable. It is infinite size
    Cons(i32, Box<List>),
    Nil,
}

/*
Note: there’s one big difference between the MyBox<T> type we’re about to build and the real Box<T>: our version will not store its data on the heap.
We are focusing this example on Deref, so where the data is actually stored is less important than the pointer-like behavior.
*/

// user-defined smart-pointer
// The Box<T> type is ultimately defined as a tuple struct with one element, so Listing 15-8 defines a MyBox<T> type in the same way.
struct MyBox<T>(T);

impl<T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}
// *** Treating Smart Pointers Like Regular References with the Deref Trait ***
impl<T> Deref for MyBox<T> {
    // The type Target = T; syntax defines an associated type for the Deref trait to use.
    // Associated types are a slightly different way of declaring a generic parameter
    type Target = T;

    // We fill in the body of the deref method with &self.0 so deref returns a reference to the value we want to access with the * operator
    fn deref(&self) -> &T {
        &self.0
    }
}

fn hello(name: &str) {
    println!("hello, {}", name);
}

fn test_box() {
    // *** Using Box<T> to Point to Data on the Heap ***

    // The most straightforward smart pointer is a box, whose type is written Box<T>. Boxes allow you to store data on the heap rather than the stack.
    // What remains on the stack is the pointer to the heap data.

    // Boxes don’t have performance overhead, other than storing their data on the heap instead of on the stack.
    // But they don’t have many extra capabilities either. You’ll use them most often in these situations:

    // Boxes provide only the indirection and heap allocation; they don’t have any other special capabilities, like those we’ll see with the other smart pointer types.
    // The Box<T> type is a smart pointer because it implements the Deref trait, which allows Box<T> values to be treated like references.
    // When a Box<T> value goes out of scope, the heap data that the box is pointing to is cleaned up as well because of the Drop trait implementation.

    // When you have a type whose size can’t be known at compile time and you want to use a value of that type in a context that requires an exact size
    // When you have a large amount of data and you want to transfer ownership but ensure the data won’t be copied when you do so
    // When you want to own a value and you care only that it’s a type that implements a particular trait rather than being of a specific type
    let b = Box::new(5);
    println!("b = {}", b);
    // We define the variable b to have the value of a Box that points to the value 5, which is allocated on the heap.
    // it will be deallocated. The deallocation happens for the box (stored on the stack) and the data it points to (stored on the heap)

    // *** Enabling Recursive Types with Boxes ***

    // At compile time, Rust needs to know how much space a type takes up.
    // One type whose size can’t be known at compile time is a recursive type, where a value can have as part of itself another value of the same type.
    // Because this nesting of values could theoretically continue infinitely, Rust doesn’t know how much space a value of a recursive type needs.
    // However, boxes have a known size, so by inserting a box in a recursive type definition, you can have recursive types.

    // let list = Cons(1, Cons(2, Cons(3, Nil))); // error
    //  Cons(i32, List), List is a structure, no way to find out the size
    // ----- recursive without indirection
    // = help: insert indirection (e.g., a `Box`, `Rc`, or `&`) at some point to
    // The compiler starts by looking at the Cons variant, which holds a value of type i32 and a value of type List.
    // Therefore, Cons needs an amount of space equal to the size of an i32 plus the size of a List.
    // To figure out how much memory the List type needs, the compiler looks at the variants, starting with the Cons variant.
    // The Cons variant holds a value of type i32 and a value of type List, and this process continues infinitely

    // *** Using Box<T> to Get a Recursive Type with a Known Size ***

    // Rust can’t figure out how much space to allocate for recursively defined types, so the compiler gives the error
    // In this suggestion, “indirection” means that instead of storing a value directly, we’ll change the data structure to store the value indirectly by storing a pointer to the value instead.

    // Because a Box<T> is a pointer, Rust always knows how much space a Box<T> needs: a pointer’s size doesn’t change based on the amount of data it’s pointing to.
    // This means we can put a Box<T> inside the Cons variant instead of another List value directly.
    // The Box<T> will point to the next List value that will be on the heap rather than inside the Cons variant.
    // Conceptually, we still have a list, created with lists “holding” other lists, but this implementation is now more like placing the items next to one another rather than inside one another.
    let mut list = Box::new(Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil)))))));

    while let Cons(node, next) = *list {
        println!("Element : {}", node);
        list = next;
    }

    {
        // *** Using Box<T> Like a Reference ***
        // A regular reference is a type of pointer, and one way to think of a pointer is as an arrow to a value stored somewhere else.
        let x = 5;
        let z = &x;
        let y = Box::new(x);

        assert_eq!(5, x);
        assert_eq!(5, *y);
        assert_eq!(5, *z);
    }

    // The Box<T> type is a smart pointer because it implements the Deref trait, which allows Box<T> values to be treated like references.
    // When a Box<T> value goes out of scope, the heap data that the box is pointing to is cleaned up as well because of the Drop trait implementation.
    // Let’s explore these two traits in more detail. These two traits will be even more important to the functionality provided by the other smart pointer types we’ll discuss in the rest of this chapter.

    {
        let x = 5;
        let y = MyBox::new(x);

        assert_eq!(5, x);
        assert_eq!(5, *y); // == *(y.deref())
                           // Deref trait called
                           // Rust substitutes the * operator with a call to the deref method and then a plain dereference so we don’t have to think about whether or
                           // not we need to call the deref method. This Rust feature lets us write code that functions identically whether we have a regular reference or a type that implements Deref.

        // The reason the deref method returns a reference to a value, and that the plain dereference outside the parentheses in *(y.deref()) is still necessary,
        // is the ownership system. If the deref method returned the value directly instead of a reference to the value, the value would be moved out of self. We don’t want to take ownership of the inner value inside MyBox<T> in this case or in most cases where we use the dereference operator.

        // Note that the * operator is replaced with a call to the deref method and then a call to the * operator just once, each time we use a * in our code. Because the substitution of the * operator does not recurse infinitely, we end up with data of type i32, which matches the 5 in assert_eq!
    }

    {
        // *** Implicit Deref Coercions with Functions and Methods ***
        // Deref coercion is a convenience that Rust performs on arguments to functions and methods.
        // Deref coercion converts a reference to a type that implements Deref into a reference to a type that Deref can convert the original type into.
        // Deref coercion happens automatically when we pass a reference to a particular type’s value as an argument to a function or method that doesn’t match the parameter type in the function or method definition. A sequence of calls to the deref method converts the type we provided into the type the parameter needs.
        let x = Box::new(String::from("Testing box"));
        hello(&x);

        // Deref coercion was added to Rust so that programmers writing function and method calls don’t need to add as many explicit references and dereferences with & and *. The deref coercion feature also lets us write more code that can work for either references or smart pointers.

        // Deref coercion was added to Rust so that programmers writing function and method calls don’t need to add as many explicit references and dereferences with & and *.
        // The deref coercion feature also lets us write more code that can work for either references or smart pointers.
        hello(&(*x)[..]);
        // The (*m) dereferences the MyBox<String> into a String. Then the & and [..] take a string slice of the String that is equal to the whole string to match the signature of hello.
    }

    // *** Similar to how you use the Deref trait to override the * operator on immutable references, you can use the DerefMut trait to override the * operator on mutable references.

    // Rust does deref coercion when it finds types and trait implementations in three cases:

    // From &T to &U when T: Deref<Target=U>
    // From &mut T to &mut U when T: DerefMut<Target=U>
    // From &mut T to &U when T: Deref<Target=U>
    // The first two cases are the same except for mutability.
    // The first case states that if you have a &T, and T implements Deref to some type U, you can get a &U transparently.
    // The second case states that the same deref coercion happens for mutable references.

    // The third case is trickier: Rust will also coerce a mutable reference to an immutable one.
    // But the reverse is not possible: immutable references will never coerce to mutable references.
    // Because of the borrowing rules, if you have a mutable reference, that mutable reference must be the only reference to that data (otherwise, the program wouldn’t compile).
    // Converting one mutable reference to one immutable reference will never break the borrowing rules.
    // Converting an immutable reference to a mutable reference would require that there is only one immutable reference to that data, and the borrowing rules don’t guarantee that. Therefore, Rust can’t make the assumption that converting an immutable reference to a mutable reference is possible.
}

/*

*** Running Code on Cleanup with the Drop Trait ***

The second trait important to the smart pointer pattern is Drop, which lets you customize what happens when a value is about to go out of scope.
You can provide an implementation for the Drop trait on any type, and the code you specify can be used to release resources like files or network connections.
We’re introducing Drop in the context of smart pointers because the functionality of the Drop trait is almost always used when implementing a smart pointer.
For example, Box<T> customizes Drop to deallocate the space on the heap that the box points to.

In some languages, the programmer must call code to free memory or resources every time they finish using an instance of a smart pointer.
If they forget, the system might become overloaded and crash.
In Rust, you can specify that a particular bit of code be run whenever a value goes out of scope, and the compiler will insert this code automatically.
As a result, you don’t need to be careful about placing cleanup code everywhere in a program that an instance of a particular type is finished with—you still won’t leak resources!

*/

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
        let a = exam { i: 21 };
        let b = exam { i: 32 };
        println!("Instances of Example type are created");
        // Dropping a Value Early with std::mem::drop
        // We can’t disable the automatic insertion of drop when a value goes out of scope, and we can’t call the drop method explicitly.
        // So, if we need to force a value to be cleaned up early, we can use the std::mem::drop function.
        // The std::mem::drop function is different from the drop method in the Drop trait. We call it by passing the value we want to force to be dropped early as an argument.
        drop(a);
        // a.drop() // error, can't call drop explicit
    }
}

use std::rc::Rc;

enum list {
    Cons(i32, Rc<list>),
    Nil,
}

/*

*** Rc<T>, the Reference Counted Smart Pointer ***
In the majority of cases, ownership is clear: you know exactly which variable owns a given value.
However, there are cases when a single value might have multiple owners. For example, in graph data structures, multiple edges might point to the same node,
and that node is conceptually owned by all of the edges that point to it. A node shouldn’t be cleaned up unless it doesn’t have any edges pointing to it.

To enable multiple ownership, Rust has a type called Rc<T>, which is an abbreviation for reference counting.
The Rc<T> type keeps track of the number of references to a value which determines whether or not a value is still in use.
If there are zero references to a value, the value can be cleaned up without any references becoming invalid.
*/

fn test_rc_t() {
    {
        let a = Cons(5, Box::new(Cons(10, Box::new(Nil))));

        //let b = Cons(3, Box::new(a)); // - value moved here
        //let c = Cons(4, Box::new(a)); //  ^ value used here after move

        // We could change the definition of Cons to hold references instead, but then we would have to specify lifetime parameters.
        // By specifying lifetime parameters, we would be specifying that every element in the list will live at least as long as the entire list.
        // The borrow checker wouldn’t let us compile let a = Cons(10, &Nil);
        // for example, because the temporary Nil value would be dropped before a could take a reference to it.
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

// *** RefCell<T> and the Interior Mutability Pattern ***
// Interior mutability is a design pattern in Rust that allows you to mutate data even when there are immutable references to that data; normally, this action is disallowed by the borrowing rules.
// To mutate data, the pattern uses unsafe code inside a data structure to bend Rust’s usual rules that govern mutation and borrowing.

#[derive(Debug)]
enum List1 {
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
struct Node {
    val: i32,
    children: RefCell<Vec<Rc<Node>>>,
    parent: RefCell<Weak<Node>>,
}

fn test_ref_cell() {
    // *** Enforcing Borrowing Rules at Runtime with RefCell<T> ***
    // Unlike Rc<T>, the RefCell<T> type represents single ownership over the data it holds. So, what makes RefCell<T> different from a type like Box<T>?
    // Recall the borrowing rules you learned in Chapter 4:

    // 1) At any given time, you can have either (but not both of) one mutable reference or any number of immutable references.
    // 2) References must always be valid.

    // 1) With references and Box<T>, the borrowing rules’ invariants are enforced at compile time.
    // 2) With RefCell<T>, these invariants are enforced at runtime.

    // 1) With references, if you break these rules, you’ll get a compiler error.
    // 2) With RefCell<T>, if you break these rules, your program will panic and exit.

    // The advantages of checking the borrowing rules at compile time are that errors will be caught sooner in the development process,
    // and there is no impact on runtime performance because all the analysis is completed beforehand.
    // For those reasons, checking the borrowing rules at compile time is the best choice in the majority of cases, which is why this is Rust’s default.

    // Because some analysis is impossible, if the Rust compiler can’t be sure the code complies with the ownership rules, it might reject a correct program;
    // in this way, it’s conservative. If Rust accepted an incorrect program, users wouldn’t be able to trust in the guarantees Rust makes.
    // However, if Rust rejects a correct program, the programmer will be inconvenienced, but nothing catastrophic can occur.

    //  The RefCell<T> type is useful when you’re sure your code follows the borrowing rules but the compiler is unable to understand and guarantee that.

    // Similar to Rc<T>, RefCell<T> is only for use in single-threaded scenarios and will give you a compile-time error if you try using it in a multithreaded context.
    // We’ll talk about how to get the functionality of RefCell<T> in a multithreaded program in Chapter 16.

    // *** Here is a recap of the reasons to choose Box<T>, Rc<T>, or RefCell<T> *** :

    // 1) Rc<T> enables multiple owners of the same data; Box<T> and RefCell<T> have single owners.
    // 2) Box<T> allows immutable or mutable borrows checked at compile time; Rc<T> allows only immutable borrows checked at compile time;
    //    RefCell<T> allows immutable or mutable borrows checked at runtime.
    // 3) Because RefCell<T> allows mutable borrows checked at runtime, you can mutate the value inside the RefCell<T> even when the RefCell<T> is immutable.

    // Mutating the value inside an immutable value is the interior mutability pattern. Let’s look at a situation in which interior mutability is useful and examine how it’s possible.

    // *** Interior Mutability: A Mutable Borrow to an Immutable Value ***

    // However, there are situations in which it would be useful for a value to mutate itself in its methods but appear immutable to other code.
    // Code outside the value’s methods would not be able to mutate the value. Using RefCell<T> is one way to get the ability to have interior mutability.
    // But RefCell<T> doesn’t get around the borrowing rules completely: the borrow checker in the compiler allows this interior mutability, and the borrowing rules are checked at runtime instead.
    // If you violate the rules, you’ll get a panic! instead of a compiler error.

    // *** Keeping Track of Borrows at Runtime with RefCell<T> ***

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
        let leaf = Rc::new(Node {
            val: 10,
            parent: RefCell::new(Weak::new()),
            children: RefCell::new(vec![]),
        });

        let branch = Rc::new(Node {
            val: 5,
            parent: RefCell::new(Weak::new()),
            children: RefCell::new(vec![Rc::clone(&leaf)]),
        });

        *leaf.parent.borrow_mut() = Rc::downgrade(&branch);
        println!("leaf parent = {:?}", leaf.parent.borrow().upgrade());

        println!(
            "branch strong = {}, weak = {}",
            Rc::strong_count(&branch),
            Rc::weak_count(&branch)
        );
        println!(
            "leaf strong = {}, weak = {}",
            Rc::strong_count(&leaf),
            Rc::weak_count(&leaf)
        );
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
where
    T: Messenger,
{
    pub fn new(messenger: &T, max: usize) -> LimitTracker<T> {
        LimitTracker {
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
            self.messenger
                .send("Urgent warning: you've used up over 90% of your quota!");
        } else if percentage >= 0.75 {
            self.messenger
                .send("Warning: you've used up over 75% of your quota!");
        }
    }
}

#[derive(Debug)]
enum list_2r {
    Cons(Rc<RefCell<i32>>, Rc<list_2r>),
    Nil,
}

// *** Having Multiple Owners of Mutable Data by Combining Rc<T> and RefCell<T> ***
// A common way to use RefCell<T> is in combination with Rc<T>.
// Recall that Rc<T> lets you have multiple owners of some data, but it only gives immutable access to that data.
// If you have an Rc<T> that holds a RefCell<T>, you can get a value that can have multiple owners and that you can mutate!
fn test_combile_refcell_and_refcount() {
    let val = Rc::new(RefCell::new(5));

    let a = Rc::new(list_2r::Cons(Rc::clone(&val), Rc::new(list_2r::Nil)));
    let b = list_2r::Cons(Rc::new(RefCell::new(10)), Rc::clone(&a));
    let c = list_2r::Cons(Rc::new(RefCell::new(15)), Rc::clone(&a));

    *val.borrow_mut() += 15;

    println!("a = {:?}", a);
    println!("b = {:?}", b);
    println!("c = {:?}", c);
}

pub fn test_smart_pointer() {
    test_box();

    test_ref_cell();

    test_combile_refcell_and_refcount();
}
