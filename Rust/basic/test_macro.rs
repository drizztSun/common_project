// *** Macros
// We’ve used macros like println! throughout this book, but we haven’t fully explored what a macro is and how it works. 
// The term macro refers to a family of features in Rust: declarative macros with macro_rules! and three kinds of procedural macros:

// 1) Custom #[derive] macros that specify code added with the derive attribute used on structs and enums
// 2) Attribute-like macros that define custom attributes usable on any item
// 3) Function-like macros that look like function calls but operate on the tokens specified as their argument

// We’ll talk about each of these in turn, but first, let’s look at why we even need macros when we already have functions.

// *** The Difference Between Macros and Functions
// Fundamentally, macros are a way of writing code that writes other code, which is known as metaprogramming. 
// Metaprogramming is useful for reducing the amount of code you have to write and maintain, which is also one of the roles of functions. 
// However, macros have some additional powers that functions don’t.

// A function signature must declare the number and type of parameters the function has. 
// Macros, on the other hand, can take a variable number of parameters: we can call println!("hello") with one argument or println!("hello {}", name) with two arguments. 
// Also, macros are expanded before the compiler interprets the meaning of the code, so a macro can, for example, implement a trait on a given type. 
// A function can’t, because it gets called at runtime and a trait needs to be implemented at compile time.

// The downside to implementing a macro instead of a function is that macro definitions are more complex than function definitions because you’re writing Rust code that writes Rust code. 
// Due to this indirection, macro definitions are generally more difficult to read, understand, and maintain than function definitions.

// Another important difference between macros and functions is that you must define macros or bring them into scope before you call them in a file, as opposed to functions you can define anywhere and call anywhere.

// *** Declarative Macros with 'macro_rules!' for General Metaprogramming

// The #[macro_export] annotation indicates that this macro should be made available whenever the crate in which the macro is defined is brought into scope. 
// Without this annotation, the macro can’t be brought into scope.
// We then start the macro definition with macro_rules! and the name of the macro we’re defining without the exclamation mark.

#[macro_export]
macro_rules! VECMAKER {
    (  $( $x:expr ),* ) => {
        {
            let mut temp_vec = Vec::new();
            $(
                temp_vec.push($x);
            )*
            temp_vec
        }
    };
}

// Here we have one arm with the pattern ( $( $x:expr ),* ), followed by => and the block of code associated with this pattern. 
// If the pattern matches, the associated block of code will be emitted. 
// Given that this is the only pattern in this macro, there is only one valid way to match; any other pattern will result in an error. 
// More complex macros will have more than one arm.

// First, a set of parentheses encompasses the whole pattern. 
// A dollar sign ($) is next, followed by a set of parentheses that captures values that match the pattern within the parentheses for use in the replacement code. 
// Within $() is $x:expr, which matches any Rust expression and gives the expression the name $x.

// The comma following $() indicates that a literal comma separator character could optionally appear after the code that matches the code in $(). 
// The * specifies that the pattern matches zero or more of whatever precedes the *.


// *** Procedural Macros for Generating Code from Attributes

// The second form of macros is procedural macros, which act more like functions (and are a type of procedure). 
// Procedural macros accept some code as an input, operate on that code, and produce some code as an output rather than matching against patterns and replacing the code with other code as declarative macros do.
// The three kinds of procedural macros (custom derive, attribute-like, and function-like) all work in a similar fashion.

// When creating procedural macros, the definitions must reside in their own crate with a special crate type. 
// This is for complex technical reasons that we hope to eliminate in the future.


pub fn test_macro() {

    let tmp = VECMAKER![1, 2, 3];

    for i in tmp {
        println!("R: {}", i);
    }
}