//use mod::result;

use std::fmt;
use std::fs::File;
use std::io::prelude::*;
use std::io::{self, ErrorKind};
// use std::process::ExitCode;

/*
Result<T, E> is the type used for returning and propagating errors.
It is an enum with the variants, Ok(T), representing success and containing a value, and Err(E), representing error and containing an error value.

enum Result<T, E> {
   Ok(T),
   Err(E),
}
The T and E are generic type parameters:
ß
Functions return Result whenever errors are expected and recoverable. In the std crate, Result is most prominently used for I/O.
*/

#[derive(Debug)]
enum Version {
    Version1,
    Version2,
}

// A simple function returning Result might be defined and used like so:
fn parse_version(header: &[u8]) -> Result<Version, &'static str> {
    match header.get(0) {
        None => Err("invalid header length"),
        Some(&1) => Ok(Version::Version1),
        Some(&2) => Ok(Version::Version2),
        Some(_) => Err("invalid version"),
    }
}

fn handle_operation_result() -> Result<String, io::Error> {
    {
        let f = File::open("hello.txt");

        let f = match f {
            Ok(file) => file,
            Err(error) => match error.kind() {
                ErrorKind::NotFound => match File::create("hello.txt") {
                    Ok(fc) => fc,
                    Err(e) => panic!("Problem creating the file: {:?}", e),
                },
                other_error => panic!("Problem opening the file: {:?}", other_error),
            },
        };
    }

    {
        let f = File::open("hello.txt").unwrap_or_else(|error| {
            if error.kind() == ErrorKind::NotFound {
                File::create("hello.txt").unwrap_or_else(|error| {
                    panic!("Problem creating the file: {:?}", error);
                })
            } else {
                panic!("Problem opening the file: {:?}", error);
            }
        });
    }

    {
        // Shortcuts for Panic on Error: unwrap and expect

        // The Result<T, E> type has many helper methods defined on it to do various tasks.
        // One of those methods, called unwrap, is a shortcut method that is implemented just like the match
        // If the Result value is the Ok variant, unwrap will return the value inside the Ok. If the Result is the Err variant, unwrap will call the panic! macro for us.
        let f = File::open("hello.txt").unwrap();

        // Another method, expect, which is similar to unwrap, lets us also choose the panic! error message.
        // Using expect instead of unwrap and providing good error messages can convey your intent and make tracking down the source of a panic easier.
        let f = File::open("hello.txt").expect("Failed to open hello.txt");
        // We use expect in the same way as unwrap: to return the file handle or call the panic! macro.
        // The error message used by expect in its call to panic! will be the parameter that we pass to expect, rather than the default panic! message that unwrap uses.
    }

    {
        // This pattern of propagating errors is so common in Rust that Rust provides the question mark operator ? to make this easier.
        // The ? Operator Can Be Used in Functions That Return Result
        // The ? operator can be used in functions that have a return type of Result, because it is defined to work in the same way as the match expression we defined in Listing 9-6.
        // The part of the match that requires a return type of Result is return Err(e), so the return type of the function can be a Result to be compatible with this return.
        let mut f = File::open("hello.txt")?;
        let mut s = String::new();
        f.read_to_string(&mut s)?;
        Ok(s)
        // File::open("hello.txt")?.read_to_string(&mut s)?;

        // The ? placed after a Result value is defined to work in almost the same way as the match expressions we defined to handle the Result values in Listing 9-6.
        // If the value of the Result is an Ok, the value inside the Ok will get returned from this expression, and the program will continue.
        // If the value is an Err, the Err will be returned from the whole function as if we had used the return keyword so the error value gets propagated to the calling code.
    }
}

fn test_basic_result() {
    let version = parse_version(&[1, 2, 3, 4]);

    match version {
        Ok(v) => println!("working with version: {:?}", v),
        Err(e) => println!("error parsing header: {:?}", e),
    }

    // Pattern matching on Results is clear and straightforward for simple cases, but Result comes with some convenience methods that make working with it more succinct.

    let good_result: Result<i32, i32> = Ok(10);
    let bad_result: Result<i32, i32> = Err(10);

    // The `is_ok` and `is_err` methods do what they say.
    assert!(good_result.is_ok() && !good_result.is_err());
    assert!(bad_result.is_err() && !bad_result.is_ok());

    // `map` consumes the `Result` and produces another.
    let good_result: Result<i32, i32> = good_result.map(|i| i + 1);
    let bad_result: Result<i32, i32> = bad_result.map(|i| i - 1);

    // Use `and_then` to continue the computation.
    let good_result: Result<bool, i32> = good_result.and_then(|i| Ok(i == 11));

    // Use `or_else` to handle the error.
    let bad_result: Result<i32, i32> = bad_result.or_else(|i| Ok(i + 20));

    // Consume the result and return the contents with `unwrap`.
    let final_awesome_result = good_result.unwrap();

    // and
    // Returns res if the result is Ok, otherwise returns the Err value of self.
    {
        let x: Result<u32, &str> = Ok(2);
        let y: Result<&str, &str> = Err("late error");
        assert_eq!(x.and(y), Err("late error"));
        let x: Result<u32, &str> = Err("early error");
        let y: Result<&str, &str> = Ok("foo");
        assert_eq!(x.and(y), Err("early error"));
        let x: Result<u32, &str> = Err("not a 2");
        let y: Result<&str, &str> = Err("late error");
        assert_eq!(x.and(y), Err("not a 2"));
        let x: Result<u32, &str> = Ok(2);
        let y: Result<&str, &str> = Ok("different result type");
        assert_eq!(x.and(y), Ok("different result type"));
    }

    // and_then
    // Calls op if the result is Ok, otherwise returns the Err value of self.
    // This function can be used for control flow based on result values.

    {
        fn sq(x: u32) -> Result<u32, u32> {
            Ok(x * x)
        }
        fn err(x: u32) -> Result<u32, u32> {
            Err(x)
        }
        assert_eq!(Ok(2).and_then(sq).and_then(sq), Ok(16));
        assert_eq!(Ok(2).and_then(sq).and_then(err), Err(4));
        assert_eq!(Ok(2).and_then(err).and_then(sq), Err(2));
        assert_eq!(Err(3).and_then(sq).and_then(sq), Err(3));
    }

    // or
    // Returns res if the result is Err, otherwise returns the Ok value of self.
    {
        let x: Result<u32, &str> = Ok(2);
        let y: Result<u32, &str> = Err("late error");
        assert_eq!(x.or(y), Ok(2));

        let x: Result<u32, &str> = Err("early error");
        let y: Result<u32, &str> = Ok(2);
        assert_eq!(x.or(y), Ok(2));

        let x: Result<u32, &str> = Err("not a 2");
        let y: Result<u32, &str> = Err("late error");
        assert_eq!(x.or(y), Err("late error"));

        let x: Result<u32, &str> = Ok(2);
        let y: Result<u32, &str> = Ok(100);
        assert_eq!(x.or(y), Ok(2));
    }

    // or_else
    // Calls op if the result is Err, otherwise returns the Ok value of self.
    // This function can be used for control flow based on result values.
    {
        fn sq(x: u32) -> Result<u32, u32> {
            Ok(x * x)
        }
        fn err(x: u32) -> Result<u32, u32> {
            Err(x)
        }

        assert_eq!(Ok(2).or_else(sq).or_else(sq), Ok(2));
        assert_eq!(Ok(2).or_else(err).or_else(sq), Ok(2));
        assert_eq!(Err(3).or_else(sq).or_else(err), Ok(9));
        assert_eq!(Err(3).or_else(err).or_else(err), Err(3));
    }
}

// The question mark operator, ?

// When writing code that calls many functions that return the Result type, the error handling can be tedious.
// The question mark operator, ?, hides some of the boilerplate of propagating errors up the call stack.
struct Info {
    name: String,
    age: i32,
    rating: i32,
}

fn write_info(info: &Info) -> io::Result<()> {
    let mut file = match File::create("test_result.txt") {
        Ok(f) => f,
        Err(e) => return Err(e),
    };

    if let Err(e) = file.write_all(format!("name: {}\n", info.name).as_bytes()) {
        return Err(e);
    }

    if let Err(e) = file.write_all(format!("age: {}\n", info.age).as_bytes()) {
        return Err(e);
    }

    if let Err(e) = file.write_all(format!("rating: {}\n", info.rating).as_bytes()) {
        return Err(e);
    }

    Ok(())
}

// It's much nicer!
// Ending the expression with ? will result in the unwrapped success (Ok) value, unless the result is Err, in which case Err is returned early from the enclosing function.
// ? can only be used in functions that return Result because of the early return of Err that it provides.
fn write_info_with_question(info: &Info) -> io::Result<()> {
    let mut file = File::create("test_result.txt")?;

    file.write_all(format!("name: {}\n", info.name).as_bytes())?;
    file.write_all(format!("ageL {}\n", info.age).as_bytes())?;
    file.write_all(format!("rating: {}\n", info.rating).as_bytes())?;

    Ok(())
}

fn read_username_from_file() -> Result<String, io::Error> {
    let f = File::open("username.txt");

    let mut f = match f {
        Ok(file) => file,
        Err(e) => return Err(e),
    };

    let mut s = String::new();

    match f.read_to_string(&mut s) {
        Ok(_) => Ok(s),
        Err(e) => Err(e),
    }
}
//
// The ? operator for easier error handling
// Rust has gained a new operator, ?, that makes error handling more pleasant by reducing the visual noise involved.

// This code has two paths that can fail, opening the file and reading the data from it.
// If either of these fail to work, we'd like to return an error from read_username_from_file.
// Doing so involves matching on the result of the I/O operations. In simple cases like this though, where we are only propagating errors up the call stack,
// the matching is just boilerplate - seeing it written out, in the same pattern every time, doesn't provide the reader with a great deal of useful information.

// With ?, the above code looks like this:
fn test_question_operator() -> Result<String, io::Error> {
    let mut f = File::open("username.txt")?;
    let mut s = String::new();

    f.read_to_string(&mut s)?;

    Ok(s)
}

// The ? is shorthand for the entire match statements we wrote earlier.
// In other words, ? applies to a Result value, and if it was an Ok, it unwraps it and gives the inner value.
// If it was an Err, it returns from the function you're currently in. Visually, it is much more straightforward.
// Instead of an entire match statement, now we are just using the single "?" character to indicate that here we are handling errors in the standard way, by passing them up the call stack.

// Seasoned Rustaceans may recognize that this is the same as the try! macro that's been available since Rust 1.0.
// And indeed, they are the same. Previously, read_username_from_file could have been implemented like this:

// The ? operator was added to replace try! and should be used instead.
// Furthermore, try is a reserved word in Rust 2018, so if you must use it, you will need to use the raw-identifier syntax: r#try.
fn read_username_from_file_try() -> Result<String, io::Error> {
    let mut f = r#try!(File::open("username.txt"));

    let mut s = String::new();
    r#try!(f.read_to_string(&mut s));

    Ok(s)
}

// Results must be used

/*
A common problem with using return values to indicate errors is that it is easy to ignore the return value,
thus failing to handle the error. Result is annotated with the #[must_use] attribute,
which will cause the compiler to issue a warning when a Result value is ignored.
This makes Result especially useful with functions that may encounter errors but don't otherwise return a useful value.

Consider the write_all method defined for I/O types by the Write trait:

trait Write {
    fn write_all(&mut self, bytes: &[u8]) -> Result<(), io::Error>;
}
Note: The actual definition of Write uses io::Result, which is just a synonym for Result<T, io::Error>.
*/

// In Rust 2018 you can instead let your #[test]s and main functions return a Result:
/*

// Rust 2018

use std::fs::File;

fn main() -> Result<(), std::io::Error> {
    let f = File::open("bar.txt")?;

    Ok(())
}
*/

// More details
// Getting -> Result<..> to work in the context of main and #[test]s is not magic.
// It is all backed up by a Termination trait which all valid return types of main and testing functions must implement. The trait is defined as:

pub trait Termination {
    fn report(self) -> i32;
}

impl Termination for () {
    fn report(self) -> i32 {
        //ExitCode::success.report();
        return 1;
    }
}

impl<E: fmt::Debug> Termination for Result<(), E> {
    fn report(self) -> i32 {
        match self {
            Ok(()) => ().report(),
            Err(err) => {
                eprintln!("Error: {:?}", err);
                // ExitCode::FAILURE.report()
                2
            }
        }
    }
}

fn test_basic_result_question() {
    let mut file = File::create("valuable_data.txt").unwrap();
    // If `write_all` errors, then we'll never know, because the return
    // value is ignored.
    file.write_all(b"important message");

    //' If you do write that in Rust, the compiler will give you a warning (by default, controlled by the unused_must_use lint).
    //You might instead, if you don't want to handle the error, simply assert success with expect.
    // This will panic if the write fails, providing a marginally useful message indicating why:
    file.write_all(b"important message")
        .expect("failed to write message");

    // You might also simply assert success:
    assert!(file.write_all(b"important message").is_ok());

    // file.write_all(b"important message")?;
}

pub fn test_result() {
    test_basic_result();

    test_basic_result_question();
}
