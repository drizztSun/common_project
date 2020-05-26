// *** Advanced Types ***

// *** Using the Newtype Pattern for Type Safety and Abstraction ***

// The newtype pattern is useful for tasks beyond those we’ve discussed so far, including statically enforcing that values are never confused and indicating the units of a value.
// You saw an example of using newtypes to indicate units in Listing 19-15: recall that the Millimeters and Meters structs wrapped u32 values in a newtype.
// If we wrote a function with a parameter of type Millimeters, we couldn’t compile a program that accidentally tried to call that function with a value of type Meters or a plain u32.

//  Another use of the newtype pattern is in abstracting away some implementation details of a type:
// the new type can expose a public API that is different from the API of the private inner type if we used the new type directly to restrict the available functionality, for example.

// Newtypes can also hide internal implementation. For example, we could provide a People type to wrap a HashMap<i32, String> that stores a person’s ID associated with their name.
// Code using People would only interact with the public API we provide, such as a method to add a name string to the People collection; that code wouldn’t need to know that we assign an i32 ID to names internally.
// The newtype pattern is a lightweight way to achieve encapsulation to hide implementation details, which we discussed in the “Encapsulation that Hides Implementation Details” section of Chapter 17.

// *** Creating Type Synonyms with Type Aliases ***
// Along with the newtype pattern, Rust provides the ability to declare a type alias to give an existing type another name. For this we use the type keyword.

use std::fmt;
use std::io::Error;

fn test_advanced_types_basic() {
    // the alias Kilometers is a synonym for i32; unlike the Millimeters and Meters types we created in Listing 19-15, Kilometers is not a separate, new type.
    // Values that have the type Kilometers will be treated the same as values of type i32
    type Kilometers = i32;

    let x: i32 = 5;
    let y: Kilometers = 5;

    println!("x + y = {}", x + y);

    // The main use case for type synonyms is to reduce repetition. For example, we might have a lengthy type like this:
    type Thunk = Box<dyn Fn() + Send + 'static>;

    let f: Thunk = Box::new(|| println!("hi"));

    fn takes_long_type(f: Thunk) {
        // --snip--
    }

    fn returns_long_type() -> Thunk {
        // --snip--
    }
}
// Type aliases are also commonly used with the Result<T, E> type for reducing repetition.
// Consider the std::io module in the standard library. I/O operations often return a Result<T, E> to handle situations when operations fail to work.
// This library has a std::io::Error struct that represents all possible I/O errors.
// Many of the functions in std::io will be returning Result<T, E> where the E is std::io::Error, such as these functions in the Write trait:
type Result<T> = std::result::Result<T, std::io::Error>;

/*

pub trait Write {
    fn write(&mut self, buf: &[u8]) -> Result<usize, Error>;
    fn flush(&mut self) -> Result<(), Error>;

    fn write_all(&mut self, buf: &[u8]) -> Result<(), Error>;
    fn write_fmt(&mut self, fmt: fmt::Arguments) -> Result<(), Error>;
}
*/

pub trait Write {
    fn write(&mut self, buf: &[u8]) -> Result<usize>;
    fn flush(&mut self) -> Result<()>;

    fn write_all(&mut self, buf: &[u8]) -> Result<()>;
    fn write_fmt(&mut self, fmt: fmt::Arguments) -> Result<()>;
}

// *** The Never Type that Never Returns ***
// Rust has a special type named ! that’s known in type theory lingo as the empty type because it has no values. We prefer to call
// it the never type because it stands in the place of the return type when a function will never return.
fn bar() -> ! {
    // --snip--

    // This code is read as “the function bar returns never.” Functions that return never are called diverging functions. We can’t create values of the type ! so bar can never possibly return.
}

// *** Dynamically Sized Types and the Sized Trait ***
// Due to Rust’s need to know certain details, such as how much space to allocate for a value of a particular type, there is a corner of its type system that can be confusing:
// the concept of dynamically sized types. Sometimes referred to as DSTs or unsized types, these types let us write code using values whose size we can know only at runtime.

fn test_dynamically_size() {
    // Let’s dig into the details of a dynamically sized type called str, which we’ve been using throughout the book. That’s right, not &str, but str on its own, is a DST.
    // We can’t know how long the string is until runtime, meaning we can’t create a variable of type str, nor can we take an argument of type str.
    // Consider the following code, which does not work:

    // This code does not compile!
    // let s1: str = "Hello there!";
    // let s2: str = "How's it going?";
    // Rust needs to know how much memory to allocate for any value of a particular type, and all values of a type must use the same amount of memory.
    // If Rust allowed us to write this code, these two str values would need to take up the same amount of space. But they have different lengths: s1 needs 12 bytes of storage and s2 needs 15.
    // This is why it’s not possible to create a variable holding a dynamically sized type.

    // So what do we do? In this case, you already know the answer: we make the types of s1 and s2 a &str rather than a str. Recall that in the “String Slices” section of Chapter 4,
    // we said the slice data structure stores the starting position and the length of the slice.

    // So although a &T is a single value that stores the memory address of where the T is located, a &str is two values: the address of the str and its length.
    // As such, we can know the size of a &str value at compile time: it’s twice the length of a usize.
    // That is, we always know the size of a &str, no matter how long the string it refers to is. In general, this is the way in which dynamically sized types are used in Rust:
    // they have an extra bit of metadata that stores the size of the dynamic information. The golden rule of dynamically sized types is that we must always put values of dynamically sized types behind a pointer of some kind.

    // We can combine str with all kinds of pointers: for example, Box<str> or Rc<str>. In fact, you’ve seen this before but with a different dynamically sized type:
    // traits. Every trait is a dynamically sized type we can refer to by using the name of the trait. In Chapter 17 in the “Using Trait Objects That Allow for Values of Different Types” section,
    // we mentioned that to use traits as trait objects, we must put them behind a pointer, such as &dyn Trait or Box<dyn Trait> (Rc<dyn Trait> would work too).

    // To work with DSTs, Rust has a particular trait called the Sized trait to determine whether or not a type’s size is known at compile time.
    // This trait is automatically implemented for everything whose size is known at compile time. In addition, Rust implicitly adds a bound on Sized to every generic function.
    // That is, a generic function definition like this:

    fn generic<T>(t: T) {
        // --snip--
    }
    // is actually treated as though we had written this:
    fn generic<T: Sized>(t: T) {
        // --snip--
    }
    // By default, generic functions will work only on types that have a known size at compile time. However, you can use the following special syntax to relax this restriction:
    fn generic<T: ?Sized>(t: &T) {
        // --snip--
    }
    // A trait bound on ?Sized is the opposite of a trait bound on Sized: we would read this as “T may or may not be Sized.” This syntax is only available for Sized, not any other traits.

    // Also note that we switched the type of the t parameter from T to &T. Because the type might not be Sized, we need to use it behind some kind of pointer.
    // In this case, we’ve chosen a reference.

    //Next, we’ll talk about functions and closures!
}

pub fn test_advanced_types() {
    test_advanced_types_basic();
}
