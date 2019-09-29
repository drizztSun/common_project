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

pub fn test_unsafe() {
    
    // 1) Dereferencing a Raw Pointer
    // we mentioned that the compiler ensures references are always valid. 
    // Unsafe Rust has two new types called raw pointers that are similar to references. 
    // As with references, raw pointers can be immutable or mutable and are written as *const T and *mut T, respectively. 
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

unsafe dangerous() {
    println!("This is dangerous !");
}