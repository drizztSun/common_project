/*

*** Lifetime

One detail we didn’t discuss in the “References and Borrowing” section in Chapter 4 is that every reference in Rust has a lifetime,
which is the scope for which that reference is valid. Most of the time, lifetimes are implicit and inferred, just like most of the time, types are inferred.
We must annotate types when multiple types are possible.

In a similar way, we must annotate lifetimes when the lifetimes of references could be related in a few different ways.
Rust requires us to annotate the relationships using generic lifetime parameters to ensure the actual references used at runtime will definitely be valid.

Lifetime annotations don’t change how long any of the references live.
Just as functions can accept any type when the signature specifies a generic type parameter, functions can accept references with any lifetime by specifying a generic lifetime parameter.
Lifetime annotations describe the relationships of the lifetimes of multiple references to each other without affecting the lifetimes.

Lifetime annotations have a slightly unusual syntax: the names of lifetime parameters must start with an apostrophe (')
and are usually all lowercase and very short, like generic types.
Most people use the name 'a. We place lifetime parameter annotations after the & of a reference,
using a space to separate the annotation from the reference’s type.

Here are some examples: a reference to an i32 without a lifetime parameter,
a reference to an i32 that has a lifetime parameter named 'a, and a mutable reference to an i32 that also has the lifetime 'a.

    &i32        // a reference
    &'a i32     // a reference with an explicit lifetime
    &'a mut i32 // a mutable reference with an explicit lifetime

One lifetime annotation by itself doesn’t have much meaning, because the annotations are meant to tell Rust
how generic lifetime parameters of multiple references relate to each other.
For example, let’s say we have a function with the parameter first that is a reference to an i32 with lifetime 'a.
The function also has another parameter named second that is another reference to an i32 that also has the lifetime 'a.
The lifetime annotations indicate that the references first and second must both live as long as that generic lifetime.


    *** Functions ***
Ignoring elision, function signatures with lifetimes have a few constraints:

1) any reference must have an annotated lifetime.
2) any reference being returned must have the same lifetime as an input or be static.
Additionally, note that returning references without input is banned if it would result in returning references to invalid data.
The following example shows off some valid forms of functions with lifetimes:

fn largestStr(x: &str, y: &str) -> &str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

error[E0106]: missing lifetime specifier
 --> src/main.rs:1:33
  |
1 | fn longest(x: &str, y: &str) -> &str {
  |                                 ^ expected lifetime parameter
  |
  = help: this function's return type contains a borrowed value, but the
signature does not say whether it is borrowed from `x` or `y`

 */

 /*

 ****

 Ultimately, lifetime syntax is about connecting the lifetimes of various parameters and return values of functions.
 Once they’re connected, Rust has enough information to allow memory-safe operations and disallow operations that would create dangling pointers or otherwise violate memory safety.

 ****
 */

fn largestStr<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

fn test_lifetime_basic() {
    let strings1 = String::from("String1 working");

    {
        let string2 = String::from("String2 ");

        let result = largestStr(strings1.as_str(), string2.as_str());

        println!("longest str is {}", result);
    }
}

/*
*** Thinking in Terms of Lifetimes ***
The way in which you need to specify lifetime parameters depends on what your function is doing.
For example, if we changed the implementation of the longest function to always return the first parameter rather than the longest string slice,
we wouldn’t need to specify a lifetime on the y parameter. The following code will compile:

Filename: src/main.rs
*/

fn longest<'a>(x: &'a str, y: &str) -> &'a str {
    x
}

/*
In this example, we’ve specified a lifetime parameter 'a for the parameter x and the return type, but not for the parameter y,
because the lifetime of y does not have any relationship with the lifetime of x or the return value.

When returning a reference from a function, the lifetime parameter for the return type needs to match the lifetime parameter for one of the parameters.
If the reference returned does not refer to one of the parameters, it must refer to a value created within this function,
which would be a dangling reference because the value will go out of scope at the end of the function.


fn longest<'a>(x: &str, y: &str) -> &'a str {
    let result = String::from("really long string");
    result.as_str()
}
Here, even though we’ve specified a lifetime parameter 'a for the return type, this implementation will fail to compile
because the return value lifetime is not related to the lifetime of the parameters at all. Here is the error message we get:


$ cargo run
   Compiling chapter10 v0.1.0 (file:///projects/chapter10)
error[E0515]: cannot return value referencing local variable `result`
  --> src/main.rs:11:5
   |
11 |     result.as_str()
   |     ------^^^^^^^^^
   |     |
   |     returns a value referencing data owned by the current function
   |     `result` is borrowed here

error: aborting due to previous error

For more information about this error, try `rustc --explain E0515`.
error: could not compile `chapter10`.

To learn more, run the command again with --verbose.

The problem is that result goes out of scope and gets cleaned up at the end of the longest function. We’re also trying to return a reference to result from the function.
There is no way we can specify lifetime parameters that would change the dangling reference, and Rust won’t let us create a dangling reference.
In this case, the best fix would be to return an owned data type rather than a reference so the calling function is then responsible for cleaning up the value.
*/

/*

*** Lifetime Elision ***
You’ve learned that every reference has a lifetime and that you need to specify lifetime parameters for functions or structs that use references

The patterns programmed into Rust’s analysis of references are called the ***lifetime elision*** rules.
These aren’t rules for programmers to follow; they’re a set of particular cases that the compiler will consider,
and if your code fits these cases, you don’t need to write the lifetimes explicitly.

The elision rules don’t provide full inference. If Rust deterministically applies the rules but there is still ambiguity as to what lifetimes the references have,
the compiler won’t guess what the lifetime of the remaining references should be. In this case, instead of guessing,
the compiler will give you an error that you can resolve by adding the lifetime annotations that specify how the references relate to each other.

*** Lifetimes on function or method parameters are called input lifetimes, and lifetimes on return values are called output lifetimes ***.

The compiler uses three rules to figure out what lifetimes references have when there aren’t explicit annotations.

*** The first rule applies to input lifetimes, and the second and third rules apply to output lifetimes. ***

If the compiler gets to the end of the three rules and there are still references for which it can’t figure out lifetimes,
the compiler will stop with an error. These rules apply to fn definitions as well as impl blocks.

1) *** The first rule is that each parameter that is a reference gets its own lifetime parameter In other words,
a function with one parameter gets one lifetime parameter:
fn foo<'a>(x: &'a i32);

a function with two parameters gets two separate lifetime parameters:
fn foo<'a, 'b>(x: &'a i32, y: &'b i32); and so on.

2) *** The second rule is if there is exactly one input lifetime parameter, that lifetime is assigned to all output lifetime parameters:
fn foo<'a>(x: &'a i32) -> &'a i32.

3) *** The third rule is if there are multiple input lifetime parameters, but one of them is &self or &mut self because this is a method, the lifetime of self is assigned
to all output lifetime parameters.
This third rule makes methods much nicer to read and write because fewer symbols are necessary.


Let’s pretend we’re the compiler. We’ll apply these rules to figure out what the lifetimes of the references in the signature of the first_word function in Listing 10-26 are.
The signature starts without any lifetimes associated with the references:


fn first_word(s: &str) -> &str {
Then the compiler applies the first rule, which specifies that each parameter gets its own lifetime. We’ll call it 'a as usual, so now the signature is this:


fn first_word<'a>(s: &'a str) -> &str {
The second rule applies because there is exactly one input lifetime. The second rule specifies that the lifetime of the one input parameter gets assigned to the output lifetime,
so the signature is now this:


fn first_word<'a>(s: &'a str) -> &'a str {
Now all the references in this function signature have lifetimes, and the compiler can continue its analysis without needing the programmer to annotate the lifetimes in this function signature.

Let’s look at another example, this time using the longest function that had no lifetime parameters when we started working with it in Listing 10-21:


fn longest(x: &str, y: &str) -> &str {
Let’s apply the first rule: each parameter gets its own lifetime. This time we have two parameters instead of one, so we have two lifetimes:


fn longest<'a, 'b>(x: &'a str, y: &'b str) -> &str {
You can see that the second rule doesn’t apply because there is more than one input lifetime.
The third rule doesn’t apply either, because longest is a function rather than a method, so none of the parameters are self. After working through all three rules,
we still haven’t figured out what the return type’s lifetime is. This is why we got an error trying to compile the code in Listing 10-21:
the compiler worked through the lifetime elision rules but still couldn’t figure out all the lifetimes of the references in the signature.

Because the third rule really only applies in method signatures, we’ll look at lifetimes in that context next to see why the third rule means
we don’t have to annotate lifetimes in method signatures very often.
*/

fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}

/*

The reason this function compiles without lifetime annotations is historical: in early versions (pre-1.0) of Rust,
this code wouldn’t have compiled because every reference needed an explicit lifetime. At that time, the function signature would have been written like this:


fn first_word<'a>(s: &'a str) -> &'a str {
After writing a lot of Rust code, the Rust team found that Rust programmers were entering the same lifetime annotations over and over in particular situations.
These situations were predictable and followed a few deterministic patterns. The developers programmed these patterns into the compiler’s code so the borrow checker could infer the lifetimes in these situations and wouldn’t need explicit annotations.

This piece of Rust history is relevant because it’s possible that more deterministic patterns will emerge and be added to the compiler.
In the future, even fewer lifetime annotations might be required.

*/

/*
*** Lifetime Annotations in Struct Definitions ***
So far, we’ve only defined structs to hold owned types.
It’s possible for structs to hold references, but in that case we would need to add a lifetime annotation on every reference in the struct’s definition.

This struct has one field, part, that holds a string slice, which is a reference.
As with generic data types, we declare the name of the generic lifetime parameter inside angle brackets after the name of the struct so we can use the lifetime parameter in the body of the struct definition.
*** This annotation means an instance of ImportantExcerpt can’t outlive the reference it holds in its part field. ***
*/

struct ImportantExcerpt<'a> {
    part: &'a str,
}

impl<'a> ImportantExcerpt<'a> {
    fn level(&self) -> i32 {
        3
    }
}

fn test_ImportanceExcerpt() {
    let novel = String::from("Call me Ishmael. Some years ago...");
    let first_sentence = novel.split('.').next().expect("Could not find a '.'");
    let i = ImportantExcerpt {
        part: first_sentence,
    };
}

// The lifetime parameter declaration after impl and its use after the type name are required,
// but we’re not required to annotate the lifetime of the reference to self because of the first elision rule.
impl<'a> ImportantExcerpt<'a> {
    fn announce_and_return_part(&self, announcement: &str) -> &str {
        println!("Attention please: {}", announcement);
        self.part
    }
}

fn test_lifetme_basic2() {
    /*
    The main function here creates an instance of the ImportantExcerpt struct that holds a reference to the first sentence of the String owned by the variable novel.
    The data in novel exists before the ImportantExcerpt instance is created. In addition, novel doesn’t go out of scope until after the ImportantExcerpt goes out of scope,
    so the reference in the ImportantExcerpt instance is valid.
    */

    let novel = String::from("Call me Ishmael. Some years ago...");
    let first_sentence = novel.split('.').next().expect("Could not find a '.'");
    let i = ImportantExcerpt {
        part: first_sentence,
    };
}


fn test_lifetime_basic() {

    /*
    *** The Static Lifetime ***
    One special lifetime we need to discuss is 'static, which means that this reference can live for the entire duration of the program.
    All string literals have the 'static lifetime, which we can annotate as follows:

    */

    let s: &'static str = "I have a static lifetime.";

    /*

    The text of this string is stored directly in the program’s binary, which is always available. Therefore, the lifetime of all string literals is 'static.

    You might see suggestions to use the 'static lifetime in error messages. But before specifying 'static as the lifetime for a reference,
    think about whether the reference you have actually lives the entire lifetime of your program or not.

    You might consider whether you want it to live that long, even if it could.
    Most of the time, the problem results from attempting to create a dangling reference or a mismatch of the available lifetimes.
    In such cases, the solution is fixing those problems, not specifying the 'static lifetime.
    */
}


/*

*** Generic Type Parameters, Trait Bounds, and Lifetimes Together ***

But now it has an extra parameter named ann of the generic type T, which can be filled in by any type that implements the Display trait as specified by the where clause.
This extra parameter will be printed before the function compares the lengths of the string slices, which is why the Display trait bound is necessary.
Because lifetimes are a type of generic, the declarations of the lifetime parameter 'a and the generic type parameter T go in the same list inside the angle brackets after the function name.

*/
fn longest_with_an_announcement<'a, T>(x: &'a str, y: &'a str, ann: T,) -> &'a str
            where
                T: Display,
{
    println!("Announcement! {}", ann);
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

fn test_lifetime() {

    test_lifetime_basic()

    test_lifetime_basic2()
}