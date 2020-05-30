use std::ops::{Add, Mul, Sub};
// *** macro_rules! ***
// Rust provides a powerful macro system that allows metaprogramming. As you've seen in previous chapters, macros look like functions, except that their name ends with a bang !,
// but instead of generating a function call, macros are expanded into source code that gets compiled with the rest of the program. However, unlike macros in C and other languages,
// Rust macros are expanded into abstract syntax trees, rather than string preprocessing, so you don't get unexpected precedence bugs.

// Macros are created using the macro_rules! macro.

// This is a simple macro named `say_hello`.
macro_rules! say_hello {
    // `()` indicates that the macro takes no argument.
    () => {
        // The macro will expand into the contents of this block.
        println!("Hello from defined macro!");
    };
}

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

macro_rules! assert_equal_len {
    ($a:expr, $b:expr, $func:ident, $op:tt) => {
        assert!(
            $a.len() == $b.len(),
            "{:?}: dimension mismatch: {:?} {:?} {:?}",
            stringify!($func),
            ($a.len()),
            stringify!($op),
            ($b.len(),)
        );
    };
}

macro_rules! op {
    ($func:ident, $bound:ident, $op:tt, $method:ident) => {
        fn $func<T: $bound<T, Output = T> + Copy>(xs: &mut Vec<T>, ys: &mut Vec<T>) {
            assert_equal_len!(xs, ys, $func, $op);

            for (x, y) in xs.iter_mut().zip(ys.iter()) {
                *x = $bound::$method(*x, *y);
                // *x = x.$method(*y)
            }
        }
    };
}

// *** Domain Specific Languages (DSLs) ***
// A DSL is a mini "language" embedded in a Rust macro. It is completely valid Rust because the macro system expands into normal Rust constructs,
// but it looks like a small language. This allows you to define concise or intuitive syntax for some special functionality (within bounds).

// Suppose that I want to define a little calculator API. I would like to supply an expression and have the output printed to console.

macro_rules! calculate{
    (eval $e:expr) => {{
        {
            let val: usize = $e; // Force types to be integers
            println!("{} == {}", stringify!{$e}, val);
        }
    }};
}

// Implement `add_assign`, `mul_assign`, and `sub_assign` functions.
op!(add_assign, Add, +=, add);
op!(mul_assign, Mul, *=, mul);
op!(sub_assign, Sub, -=, sub);

mod test {
    use std::iter;
    macro_rules! test {
        ($func:ident, $x:expr, $y:expr, $z:expr) => {
            #[test]
            fn $func() {
                for size in 0usize..10 {
                    let mut x: Vec<_> = iter::repeat($x).take(size).collect();
                    let y: Vec<_> = iter::repeat($y).take(size).collect();
                    let z: Vec<_> = iter::repeat($z).take(size).collect();

                    super::$func(&mut x, &mut y);

                    assert_eq!(x, z);
                }
            }
        };
    }

    // Test `add_assign`, `mul_assign`, and `sub_assign`.
    test!(add_assign, 1u32, 2u32, 3u32);
    test!(mul_assign, 2u32, 3u32, 6u32);
    test!(sub_assign, 3u32, 2u32, 1u32);
}

// The structure in the VECMAKER! body is similar to the structure of a match expression.
// Here we have one arm with the pattern ( $( $x:expr ),* ), followed by => and the block of code associated with this pattern.
// If the pattern matches, the associated block of code will be emitted.
// Given that this is the only pattern in this macro, there is only one valid way to match; any other pattern will result in an error.
// More complex macros will have more than one arm.

// First, a set of parentheses encompasses the whole pattern.
// A dollar sign ($) is next, followed by a set of parentheses that captures values that match the pattern within the parentheses for use in the replacement code.
// Within $() is $x:expr, which matches any Rust expression and gives the expression the name $x.

// The comma following $() indicates that a literal comma separator character could optionally appear after the code that matches the code in $().
// The * specifies that the pattern matches zero or more of whatever precedes the *.

// When we call this macro with vec![1, 2, 3];, the $x pattern matches three times with the three expressions 1, 2, and 3.

// Now let’s look at the pattern in the body of the code associated with this arm: temp_vec.push() within $()* is generated for each part
// that matches $() in the pattern zero or more times depending on how many times the pattern matches. The $x is replaced with each expression matched.

// *** Procedural Macros for Generating Code from Attributes

// The second form of macros is procedural macros, which act more like functions (and are a type of procedure).
// Procedural macros accept some code as an input, operate on that code, and produce some code as an output rather than matching against patterns and replacing the code with other code as declarative macros do.

// *** The three kinds of procedural macros ***
// (custom derive, attribute-like, and function-like) all work in a similar fashion.

// When creating procedural macros, the definitions must reside in their own crate with a special crate type.
// This is for complex technical reasons that we hope to eliminate in the future.

fn test_macro_basic() {
    let tmp = VECMAKER![1, 2, 3];

    for i in tmp {
        println!("R: {}", i);
    }

    say_hello!();
}

// *** How to Write a Custom derive Macro ***
//
trait HelloMacro {
    fn hello_macro();
}

//#[derive(Hellomacro)]
struct NextHelllomacro;

impl HelloMacro for NextHelllomacro {
    fn hello_macro() {
        println!("Hello macro");
    }
}

fn test_calculate_DSLS() {
    calculate! {
        eval 1 + 2 // 'eval' is not Rust keyword
    }

    calculate! {
        eval (1+2) * (3/4)
    }
}

pub fn test_macro() {
    test_macro_basic();

    test_calculate_DSLS();
}
