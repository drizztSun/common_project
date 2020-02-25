//use mod::result;

use std::fs::File;
use std::io;
use std::io::prelude::*;

/*
Result<T, E> is the type used for returning and propagating errors.
It is an enum with the variants, Ok(T), representing success and containing a value, and Err(E), representing error and containing an error value.

enum Result<T, E> {
   Ok(T),
   Err(E),
}
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