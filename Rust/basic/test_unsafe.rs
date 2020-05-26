/*
            *** Unsafe Rust ***
All the code we’ve discussed so far has had Rust’s memory safety guarantees enforced at compile time.
However, Rust has a second language hidden inside it that doesn’t enforce these memory safety guarantees:
        it’s called unsafe Rust and works just like regular Rust, but gives us extra superpowers.

Unsafe Rust exists because, by nature, static analysis is conservative.
When the compiler tries to determine whether or not code upholds the guarantees, it’s better for it to reject some valid programs rather than accept some invalid programs.
\Although the code might be okay, as far as Rust is able to tell, it’s not! In these cases, you can use unsafe code to tell the compiler, “Trust me, I know what I’m doing.”
The downside is that you use it at your own risk: if you use unsafe code incorrectly, problems due to memory unsafety, such as null pointer dereferencing, can occur.

Another reason Rust has an unsafe alter ego is that the underlying computer hardware is inherently unsafe.
If Rust didn’t let you do unsafe operations, you couldn’t do certain tasks.
Rust needs to allow you to do low-level systems programming, such as directly interacting with the operating system or even writing your own operating system.
Working with low-level systems programming is one of the goals of the language.
Let’s explore what we can do with unsafe Rust and how to do it.


    *** Unsafe Superpowers ***
To switch to unsafe Rust, use the 'unsafe' keyword and then start a new block that holds the unsafe code.
You can take four actions in unsafe Rust, called unsafe superpowers, that you can’t in safe Rust.
Those superpowers include the ability to:

1) Dereference a raw pointer
2) Call an unsafe function or method
3) Access or modify a mutable static variable
4) Implement an unsafe trait
5) Access fields of unions

It’s important to understand that unsafe doesn’t turn off the borrow checker or disable any other of Rust’s safety checks:
*** if you use a reference in unsafe code, it will still be checked.
The unsafe keyword only gives you access to these four features that are then not checked by the compiler for memory safety.
You’ll still get some degree of safety inside of an unsafe block.

In addition, unsafe does not mean the code inside the block is necessarily dangerous or that it will definitely have memory safety problems:
the intent is that as the programmer, you’ll ensure the code inside an unsafe block will access memory in a valid way.

People are fallible, and mistakes will happen, but by requiring these four unsafe operations to be inside blocks annotated
with unsafe you’ll know that any errors related to memory safety must be within an unsafe block.
Keep unsafe blocks small; you’ll be thankful later when you investigate memory bugs.

To isolate unsafe code as much as possible, it’s best to enclose unsafe code within a safe abstraction and provide a safe API,
which we’ll discuss later in the chapter when we examine unsafe functions and methods.
Parts of the standard library are implemented as safe abstractions over unsafe code that has been audited.

Wrapping unsafe code in a safe abstraction prevents uses of unsafe from leaking out into all the places that you or your users might want to use the functionality implemented with unsafe code, because using a safe abstraction is safe.

Let’s look at each of the four unsafe superpowers in turn. We’ll also look at some abstractions that provide a safe interface to unsafe code.

 */

use std::slice;

pub fn test_unsafe_basic() {
    // 1) Dereferencing a Raw Pointer
    // we mentioned that the compiler ensures references are always valid.
    // Unsafe Rust has two new types called raw pointers that are similar to references.
    // As with references, raw pointers can be immutable or mutable and are written as ( *const T ) and ( *mut T ), respectively.
    // The asterisk isn’t the dereference operator; it’s part of the type name. In the context of raw pointers, immutable means that the pointer can’t be directly assigned to after being dereferenced.

    // Different from references and smart pointers, raw pointers:

    // 1) Are allowed to ignore the borrowing rules by having both immutable and mutable pointers or multiple mutable pointers to the same location
    // 2) Aren’t guaranteed to point to valid memory
    // 3) Are allowed to be null
    // 4) Don’t implement any automatic cleanup
    let mut num = 5;

    let r1 = &num as *const i32;
    let r2 = &mut num as *mut i32;
    // Notice that we don’t include the unsafe keyword in this code. We can create raw pointers in safe code;
    // we just can’t dereference raw pointers outside an unsafe block, as you’ll see in a bit

    // Next, we’ll create a raw pointer whose validity we can’t be so certain
    let address = 0x123456usize;
    let r = address as *const i32;

    unsafe {
        println!("r1 is {}", *r1);
        println!("r2 is {}", *r2);

        // We must call the dangerous function within a separate unsafe block. If we try to call dangerous without the unsafe block, we’ll get an error:
        dangerous();
    }
}

// *** Calling an Unsafe Function or Method ***
// Unsafe functions and methods look exactly like regular functions and methods, but they have an extra unsafe before the rest of the definition.
// The unsafe keyword in this context indicates the function has requirements we need to uphold when we call this function, because Rust can’t guarantee we’ve met these requirements.
// By calling an unsafe function within an unsafe block, we’re saying that we’ve read this function’s documentation and take responsibility for upholding the function’s contracts.

unsafe fn dangerous() {
    println!("This is dangerous !");
}

// *** Creating a Safe Abstraction over Unsafe Code ***
// Just because a function contains unsafe code doesn’t mean we need to mark the entire function as unsafe. In fact, wrapping unsafe code in a safe function is a common abstraction.

fn split_at_mut(slice: &mut [i32], mid: usize) -> (&mut [i32], &mut [i32]) {
    let len = slice.len();
    let ptr = slice.as_mut_ptr();

    let address = 0x01234usize;
    let r = address as *mut i32;

    let slice: &[i32] = unsafe { slice::from_raw_parts_mut(r, 10000) };

    assert!(mid <= len);
    // without unsafe, below is wrong
    // (&mut slice[..mid], &mut slice[mid..])  // error[E0499]: cannot borrow `*slice` as mutable more than once at a time

    // Recall from “The Slice Type” section in Chapter 4 that slices are a pointer to some data and the length of the slice.
    // We use the len method to get the length of a slice and the as_mut_ptr method to access the raw pointer of a slice.
    // In this case, because we have a mutable slice to i32 values, as_mut_ptr returns a raw pointer with the type *mut i32, which we’ve stored in the variable ptr.

    // The function slice::from_raw_parts_mut is unsafe because it takes a raw pointer and must trust that this pointer is valid.
    // The add method on raw pointers is also unsafe, because it must trust that the offset location is also a valid pointer.

    unsafe {
        (
            slice::from_raw_parts_mut(ptr, mid),
            slice::from_raw_parts_mut(ptr.add(mid), len - mid),
        )
    }
}

// *** Using extern Functions to call external code ***
// Sometimes, your Rust code might need to interact with code written in another language.
// For this, Rust has a keyword, extern, that facilitates the creation and use of a Foreign Function Interface (FFI).
// An FFI is a way for a programming language to define functions and enable a different (foreign) programming language to call those functions.

// Within the extern "C" block, we list the names and signatures of external functions from another language we want to call.
// The "C" part defines which application binary interface (ABI) the external function uses: the ABI defines how to call the function at the assembly level.
// The "C" ABI is the most common and follows the C programming language’s ABI.
extern "C" {
    fn abs(input: i32) -> i32;
}

fn test_extern_language() {
    unsafe {
        println!("Absolute value of -3 according to C: {}", abs(-3));
    }
}

// *** Calling Rust Functions from Other Languages ***
// We can also use extern to create an interface that allows other languages to call Rust functions.
// Instead of an extern block, we add the extern keyword and specify the ABI to use just before the fn keyword.
// We also need to add a #[no_mangle] annotation to tell the Rust compiler not to mangle the name of this function.
// Mangling is when a compiler changes the name we’ve given a function to a different name that contains more information
// for other parts of the compilation process to consume but is less human readable.
// Every programming language compiler mangles names slightly differently, so for a Rust function to be nameable by other languages,
// we must disable the Rust compiler’s name mangling.
#[no_mangle]
pub extern "C" fn call_from_c() {
    println!("Just called a Rust function from C!");
}

// *** Accessing or Modifying a Mutable Static Variable ***
// Until now, we’ve not talked about global variables, which Rust does support but can be problematic with Rust’s ownership rules.
// If two threads are accessing the same mutable global variable, it can cause a data race.

// In Rust, global variables are called static variables.
static HELLO_WORLD: &str = "Hello world";

static mut COUNTER: u32 = 0;
fn add_to_count(inc: u32) {
    unsafe {
        COUNTER += inc;
    }
}

fn test_static_variable() {
    println!("Name is {}", HELLO_WORLD);

    add_to_count(3);

    unsafe {
        println!("COUNTER: {}", COUNTER); // without unsafe, it
    }
}

// *** Implement an Unsafe Trait ***
// The final action that works only with unsafe is implementing an unsafe trait.
// A trait is unsafe when at least one of its methods has some invariant that the compiler can’t verify.
// We can declare that a trait is unsafe by adding the unsafe keyword before trait and marking the implementation of the trait as unsafe too

// As an example, recall the Sync and Send marker traits we discussed in the “Extensible Concurrency with the Sync and Send Traits” section in Chapter 16:
// the compiler implements these traits automatically if our types are composed entirely of Send and Sync types.
// If we implement a type that contains a type that is not Send or Sync, such as raw pointers, and we want to mark that type as Send or Sync, we must use unsafe.
// Rust can’t verify that our type upholds the guarantees that it can be safely sent across threads or accessed from multiple threads;
// therefore, we need to do those checks manually and indicate as such with unsafe.
unsafe trait Foo {
    // methods go here
}

unsafe impl Foo for i32 {
    // method implementations go here
}

fn test_implement_unsafe_trait() {}

pub fn test_unsafe() {
    test_unsafe_basic();

    test_extern_language();

    test_static_variable();
}

// *** Accessing Fields of a Union ***
// A union is similar to a struct, but only one declared field is used in a particular instance at one time.
// Unions are primarily used to interface with unions in C code.
// Accessing union fields is unsafe because Rust can’t guarantee the type of the data currently being stored in the union instance.
// You can learn more about unions in the reference.

// *** When to Use Unsafe Code ***
// Using unsafe to take one of the five actions (superpowers) just discussed isn’t wrong or even frowned upon.
// But it is trickier to get unsafe code correct because the compiler can’t help uphold memory safety.
// When you have a reason to use unsafe code, you can do so, and having the explicit unsafe annotation makes it easier to track down the source of problems when they occur.
