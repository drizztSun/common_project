use std::io;
use std::io::Read;
use std::io::ErrorKind;
use std::fs::File;


fn test_result_enum() -> Result<String, io::Error> {

    let f = File::open("hello.txt"); // Result<std::fs::File, std::io::Error>

    let mut f = match f {
        Ok(file) => file,
        Err(e) => match e.kind() {
            ErrorKind::NotFound => match File::create("hello.txt") {
                Ok(fc) => fc,
                Err(e) => panic!("Problem creating the file {:?}", e),
            },
            other_error => panic!("Problem opening the file {:?}", other_error),
        }
    };

    let mut s = String::new();

    match f.read_to_string(&mut s) {
        Ok(_) => Ok(s),
        Err(e) => Err(e),
    }
}

fn test_result_enum_without_match() {

    let f = File::open("hello.txt").unwrap_or_else( |error| {
        if error.kind() == ErrorKind::NotFound {
            File::create("hello.txt").unwrap_or_else( |error| {
                panic!("Problem creating the file {:?}", error);
            })
        } else {
            panic!("Problem opening file {:?} ", error);
        }
    });

    // Shortcuts for Panic on Error: unwrap and expect
    // Using match works well enough, but it can be a bit verbose and doesn’t always communicate intent well. 
    // The Result<T, E> type has many helper methods defined on it to do various tasks. One of those methods, 
    // called unwrap, is a shortcut method that is implemented just like the match expression
    // f the Result value is the Ok variant, unwrap will return the value inside the Ok.
    // If the Result is the Err variant, unwrap will call the panic! macro for us
    let f = File::open("hello.txt").unwrap();

    // We use expect in the same way as unwrap: to return the file handle or call the panic! macro. 
    // The error message used by expect in its call to panic! will be the parameter that we pass to expect,
    // rather than the default panic! message that unwrap uses.
    let f = File::open("hello.txt").expect("Failed to open file!");

}

fn read_username_from_file() -> Result<String, io::Error> {
    // Propagating Errors
    // When you’re writing a function whose implementation calls something that might fail, 
    // instead of handling the error within this function, you can return the error to the calling code so that it can decide what to do.
    // This is known as propagating the error and gives more control to the calling code, 
    // where there might be more information or logic that dictates how the error should be handled than what you have available in the context of your code.

    let f = File::open("hello.txt");

    let mut f = match f {
        Ok(file) => file,
        Err(e) => return Err(e),
    };

    let mut s = String::new();

    match f.read_to_string(&mut s) {
        Ok(_) => Ok(s),
        Err(e) => Err(e),
    };

    {
        // A Shortcut for Propagating Errors: the ? Operator
        // The ? Operator Can Only Be Used in Functions That Return Result
        // The ? placed after a Result value is defined to work in almost the same way as the match expressions we defined 
        // to handle the Result values in Listing 9-6. 
        // If the value of the Result is an Ok, the value inside the Ok will get returned from this expression, 
        // and the program will continue. If the value is an Err, the Err will be returned from the whole function as if we had used the return keyword so the error value gets propagated to the calling code.
        let mut f = File::open("hello.txt")?;
        let mut s = String::new();
        f.read_to_string(&mut s)?;
        Ok(s)
        // There is a difference between what the match expression from Listing 9-6 and the ? operator do: error values that have the ? operator called on them go through the from function, defined in the From trait in the standard library, which is used to convert errors from one type into another. When the ? operator calls the from function, the error type received is converted into the error type defined in the return type of the current function. This is useful when a function returns one error type to represent all the ways a function might fail, even if parts might fail for many different reasons. As long as each error type implements the from function to define how to convert itself to the returned error type, the ? operator takes care of the conversion automatically.
    }
    
}

pub fn test_errorhandling() {

    // In these cases, Rust has the panic! macro. When the panic! macro executes, your program will print a failure message, 
    // unwind and clean up the stack, and then quit. 
    panic!("cash and burn");

    // Unwinding the Stack or Aborting in Response to a Panic
    // By default, when a panic occurs, the program starts unwinding, which means Rust walks back up the stack and cleans up the data 
    // from each function it encounters. But this walking back and cleanup is a lot of work. The alternative is to immediately abort,
    // which ends the program without cleaning up. 
    // Memory that the program was using will then need to be cleaned up by the operating system. 
    // If in your project you need to make the resulting binary as small as possible, you can switch from unwinding to aborting upon a panic by adding panic = 'abort' to the appropriate [profile] sections in your Cargo.toml file. For example, if you want to abort on panic in release mode, add this:

    // [profile.release]
    // panic = 'abort'

    test_result_enum();
}   