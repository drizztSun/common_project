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

#[macro_export]
macro_rules! VECMAKER {
    () => {

    };
}




pub fn test_macro() {

}