/*


    *** Attributes ***
An attribute is metadata applied to some module, crate or item. This metadata can be used to/for:

    1) conditional compilation of code
    2) set crate name, version and type (binary or library)
    3) disable lints (warnings)
    4) enable compiler features (macros, glob imports, etc.)
    5) link to a foreign library
    6) mark functions as unit tests
    7) mark functions that will be part of a benchmark

    When attributes apply to a whole crate, their syntax is #![crate_attribute], and when they apply to a module or item,
the syntax is #[item_attribute] (notice the missing bang !).

Attributes can take arguments with different syntaxes:

    1) #[attribute = "value"]
    2) #[attribute(key = "value")]
    3) #[attribute(value)]


Attributes can have multiple values and can be separated over multiple lines, too:

#[attribute(value, value2)]

#[attribute(value, value2, value3,
            value4, value5)]



    *** dead_code ***

The compiler provides a dead_code lint that will warn about unused functions. An attribute can be used to disable the lint.

fn used_function() {}

// `#[allow(dead_code)]` is an attribute that disables the `dead_code` lint
#[allow(dead_code)]
fn unused_function() {}

fn noisy_unused_function() {}
// FIXME ^ Add an attribute to suppress the warning

fn main() {
    used_function();
}

Note that in real programs, you should eliminate dead code. In these examples we'll allow dead code in some places because of the interactive nature of the examples.


    *** Crates ***
The crate_type attribute can be used to tell the compiler whether a crate is a binary or a library (and even which type of library),
and the crate_name attribute can be used to set the name of the crate.

However, it is important to note that both the "crate_type" and "crate_name" attributes have no effect whatsoever when using Cargo, the Rust package manager.
Since Cargo is used for the majority of Rust projects, this means real-world uses of "crate_type" and "crate_name" are relatively limited.

// This crate is a library
#![crate_type = "lib"]
// The library is named "rary"
#![crate_name = "rary"]

pub fn public_function() {
    println!("called rary's `public_function()`");
}

fn private_function() {
    println!("called rary's `private_function()`");
}

pub fn indirect_access() {
    print!("called rary's `indirect_access()`, that\n> ");

    private_function();
}

When the crate_type attribute is used, we no longer need to pass the --crate-type flag to rustc.


$ rustc lib.rs
$ ls lib*
library.rlib



    *** cfg ***

Conditional compilation is possible through two different operators:

    1) the cfg attribute: #[cfg(...)] in attribute position
    2) the cfg! macro: cfg!(...) in boolean expressions

Both utilize identical argument syntax.



// This function only gets compiled if the target OS is linux
#[cfg(target_os = "linux")]
fn are_you_on_linux() {
    println!("You are running linux!");
}

// And this function only gets compiled if the target OS is *not* linux
#[cfg(not(target_os = "linux"))]
fn are_you_on_linux() {
    println!("You are *not* running linux!");
}

fn main() {
    are_you_on_linux();
    
    println!("Are you sure?");
    if cfg!(target_os = "linux") {
        println!("Yes. It's definitely linux!");
    } else {
        println!("Yes. It's definitely *not* linux!");
    }
}


    *** Custom ***
Some conditionals like target_os are implicitly provided by rustc, but custom conditionals must be passed to rustc using the --cfg flag.

#[cfg(some_condition)]
fn conditional_function() {
    println!("condition met!");
}

fn main() {
    conditional_function();
}



Try to run this to see what happens without the custom cfg flag.

With the custom cfg flag:


$ rustc --cfg some_condition custom.rs && ./custom
condition met!


*/