/*




    *** Crates ***
A crate is a compilation unit in Rust. Whenever rustc some_file.rs is called, some_file.rs is treated as the crate file.
If some_file.rs has mod declarations in it, then the contents of the module files would be inserted in places where mod declarations in the crate file are found, before running the compiler over it.
In other words, modules do not get compiled individually, only crates get compiled.

A crate can be compiled into a binary or into a library.
By default, rustc will produce a binary from a crate. This behavior can be overridden by passing the --crate-type flag to lib.

    *** extern crate ***
To link a crate to this new library, the extern crate declaration must be used.
This will not only link the library, but also import all its items under a module named the same as the library.
The visibility rules that apply to modules also apply to libraries.



# Where library.rlib is the path to the compiled library, assumed that it's
# in the same directory here:

$ rustc executable.rs --extern rary=library.rlib && ./executable

called rary's `public_function()`
called rary's `indirect_access()`, that
> called rary's `private_function()`


*/

// Link to `library`, import items under the `rary` module
// extern crate test_rary;
use crate::test_rary;
// use crate::test_string;
// use test_rary;
// use crate::test_json;

pub fn test_extern_crate() {

    // test_json::test_json();

    // test_string::test_string();


    test_rary::public_function();

    // Error! `private_function` is private
    //rary::private_function();

    test_rary::indirect_access();
}