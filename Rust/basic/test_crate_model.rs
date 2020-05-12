use std::fmt;
// use std::io;

use std::fmt::Result;
use std::io::Result as IoResult; // Result has conflicted with fmt::Result, so use as rename it.

// *** Using Nested Paths to Clean Up Large use Lists
// use std::cmp::Ordering;
// use std::io;
use std::{cmp::Ordering, vec};

use std::io::{self, Write}; // his line brings std::io and std::io::Write into scope.

// *** The Glob Operator
// If we want to bring all public items defined in a path into scope, we can specify that path followed by *, the glob operator:
use std::collections::*;

use crate::test_string;
use crate::test_string::test_string; // import a file <name>.rs which is equal to use mod <name> { } wrap all content in '<name>.rs'

// mod test_string     error, rust file not found for module
// Don't think of `mod` as a keyword for importing.
// `mod` is for creating modules, not importing them. Furthermore, modules are not synonymous with files.

// Bringing Paths into Scope with the use Keyword
// Adding use and a path in a scope is similar to creating a symbolic link in the filesystem.
// By adding use crate::front_of_house::hosting in the crate root, hosting is now a valid name in that scope,
// just as though the hosting module had been defined in the crate root. Paths brought into scope with use also check privacy, like any other paths.

// Providing New Names with the as Keyword
// use crate::test_result as result_test;

// *** Re-exporting Names with pub use

pub use crate::syntax::test_mod;

// *** Using External Packages
// In Cargo.toml
// [dependencies]
// rand = "0.5.5"

fn server_order() {
    println!("server_ordedr called");
}

mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {
            super::super::server_order();
        }
    }
}

use self::front_of_house::hosting; // You can also bring an item into scope with use and a relative path.

// The exception to this idiom is if we’re bringing two items with the same name into scope with use statements, because Rust doesn’t allow that.
fn function1() -> fmt::Result {
    return fmt::Result::Ok(());
}

fn function2() -> io::Result<()> {
    return io::Result::Ok(());
}

// Providing New Names with the as Keyword
fn function11() -> Result {
    return fmt::Result::Ok(());
}

fn function21() -> IoResult<()> {
    return IoResult::Ok(());
}

pub fn test_crate_model() {
    test_string(); // call test_string imported

    test_string::test_string(); // call function by its mod

    /*


    src
    ├── a
    │   ├── b
    │   │   ├── c
    │   │   │   ├── d.rs
    │   │   │   └── mod.rs
    │   │   └── mod.rs
    │   └── mod.rs
    └── main.rs

    mod.rs uses to publish mod files *.rs in that folders and its sub-folders mod.
    mod name could be files, folders, mod names.


    use self::a::b::c::d;

    d::print_dd();

    mod front_of_house {

        mod hosting {
            fn add_to_waitlist() {}

            fn seat_at_table() {}
        }

        mod serving {
            fn take_order() {}

            fn serve_order() {}

            fn take_payment() {}
        }
    }


    Paths for Referring to an Item in the Module Tree
    To show Rust where to find an item in a module tree, we use a path in the same way we use a path when navigating a filesystem. If we want to call a function, we need to know its path.

    A path can take two forms:

        1) An absolute path starts from a crate root by using a crate name or a literal crate.
        2) A relative path starts from the current module and uses
                self,
                super, or
                an identifier in the current module.
    Both absolute and relative paths are followed by one or more identifiers separated by double colons (::).

    */
    // Absolute path
    crate::test_crate_model::front_of_house::hosting::add_to_waitlist();

    // Relative path
    front_of_house::hosting::add_to_waitlist();

    hosting::add_to_waitlist();
}
