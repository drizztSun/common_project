/*

    *** Cargo ***
cargo is the official Rust package management tool. It has lots of really useful features to improve code quality and developer velocity! These include

    1) Dependency management and integration with crates.io (the official Rust package registry)
    2) Awareness of unit tests
    3) Awareness of benchmarks
This chapter will go through some quick basics, but you can find the comprehensive docs in The Cargo Book.



    *** Dependencies ***
Most programs have dependencies on some libraries. If you have ever managed dependencies by hand, you know how much of a pain this can be. Luckily,
the Rust ecosystem comes standard with cargo! cargo can manage dependencies for a project.

To create a new Rust project,


# A binary
$  cargo new foo

# OR A library
$ cargo new --lib foo


For the rest of this chapter, let's assume we are making a binary, rather than a library, but all of the concepts are the same.

After the above commands, you should see a file hierarchy like this:


foo
├── Cargo.toml
└── src
    └── main.rs
The main.rs is the root source file for your new project -- nothing new there. The Cargo.toml is the config file for cargo for this project (foo). If you look inside it, you should see something like this:


[package]
name = "foo"
version = "0.1.0"
authors = ["mark"]

[dependencies]
The name field under [package] determines the name of the project. This is used by crates.io if you publish the crate (more later). It is also the name of the output binary when you compile.

The version field is a crate version number using Semantic Versioning.

The authors field is a list of authors used when publishing the crate.

The [dependencies] section lets you add dependencies for your project.

For example, suppose that we want our program to have a great CLI. You can find lots of great packages on crates.io (the official Rust package registry).
One popular choice is clap. As of this writing, the most recent published version of clap is 2.27.1.
To add a dependency to our program, we can simply add the following to our Cargo.toml under [dependencies]: clap = "2.27.1".
And of course, extern crate clap in main.rs, just like normal. And that's it! You can start using clap in your program.

cargo also supports other types of dependencies. Here is just a small sampling:


[package]
name = "foo"
version = "0.1.0"
authors = ["mark"]

[dependencies]
clap = "2.27.1" # from crates.io
rand = { git = "https://github.com/rust-lang-nursery/rand" } # from online repo
bar = { path = "../bar" } # from a path in the local filesystem
cargo is more than a dependency manager. All of the available configuration options are listed in the format specification of Cargo.toml.

To build our project we can execute cargo build anywhere in the project directory (including subdirectories!).
We can also do cargo run to build and run. Notice that these commands will resolve all dependencies, download crates if needed, and build everything, including your crate.
(Note that it only rebuilds what it has not already built, similar to make).


    *** Conventions ***
In the previous chapter, we saw the following directory hierarchy:


foo
├── Cargo.toml
└── src
    └── main.rs
Suppose that we wanted to have two binaries in the same project, though. What then?

It turns out that cargo supports this. The default binary name is main, as we saw before, but you can add additional binaries by placing them in a bin/ directory:


foo
├── Cargo.toml
└── src
    ├── main.rs
    └── bin
        └── my_other_bin.rs
To tell cargo to compile or run this binary as opposed to the default or other binaries, we just pass cargo the --bin my_other_bin flag, where my_other_bin is the name of the binary we want to work with.

In addition to extra binaries, cargo supports more features such as benchmarks, tests, and examples.

In the next chapter, we will look more closely at tests.



    *** Testing ***
As we know testing is integral to any piece of software! Rust has first-class support for unit and integration testing (see this chapter in TRPL).

From the testing chapters linked above, we see how to write unit tests and integration tests. Organizationally, we can place unit tests in the modules they test and integration tests in their own tests/ directory:


foo
├── Cargo.toml
├── src
│   └── main.rs
└── tests
    ├── my_test.rs
    └── my_other_test.rs
Each file in tests is a separate integration test.

cargo naturally provides an easy way to run all of your tests!


$ cargo test
You should see output like this:


$ cargo test
   Compiling blah v0.1.0 (file:///nobackup/blah)
    Finished dev [unoptimized + debuginfo] target(s) in 0.89 secs
     Running target/debug/deps/blah-d3b32b97275ec472

running 3 tests
test test_bar ... ok
test test_baz ... ok
test test_foo_bar ... ok
test test_foo ... ok

test result: ok. 3 passed; 0 failed; 0 ignored; 0 measured; 0 filtered out
You can also run tests whose name matches a pattern:


$ cargo test test_foo

$ cargo test test_foo
   Compiling blah v0.1.0 (file:///nobackup/blah)
    Finished dev [unoptimized + debuginfo] target(s) in 0.35 secs
     Running target/debug/deps/blah-d3b32b97275ec472

running 2 tests
test test_foo ... ok
test test_foo_bar ... ok

test result: ok. 2 passed; 0 failed; 0 ignored; 0 measured; 2 filtered out
One word of caution: Cargo may run multiple tests concurrently, so make sure that they don't race with each other.
For example, if they all output to a file, you should make them write to different files.



    *** Build Scripts ***
Sometimes a normal build from cargo is not enough. Perhaps your crate needs some pre-requisites before cargo will successfully compile, things like code generation,
or some native code that needs to be compiled. To solve this problem we have build scripts that Cargo can run.

To add a build script to your package it can either be specified in the Cargo.toml as follows:


[package]
...
build = "build.rs"
Otherwise Cargo will look for a build.rs file in the project directory by default.

    *** How to use a build script ***

The build script is simply another Rust file that will be compiled and invoked prior to compiling anything else in the package.
Hence it can be used to fulfill pre-requisites of your crate.

Cargo provides the script with inputs via environment variables specified here that can be used.

The script provides output via stdout. All lines printed are written to target/debug/build/<pkg>/output. Further, lines prefixed with cargo:
will be interpreted by Cargo directly and hence can be used to define parameters for the package's compilation.

For further specification and examples have a read of the Cargo specification.



*/