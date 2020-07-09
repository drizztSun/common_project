use std::fs::File;
use std::io;
use std::io::ErrorKind;
use std::io::Read;


#[allow(unused_variables)]
//#![allow(dead_code)]
/*

Unwinding the Stack or Aborting in Response to a Panic
By default, when a panic occurs, the program starts unwinding, which means Rust walks back up the stack and cleans up the data from each function it encounters.
But this walking back and cleanup is a lot of work. The alternative is to immediately abort, which ends the program without cleaning up.
Memory that the program was using will then need to be cleaned up by the operating system. If in your project you need to make the resulting binary as small as possible,
you can switch from unwinding to aborting upon a panic by adding panic = 'abort' to the appropriate [profile] sections in your Cargo.toml file. For example,
if you want to abort on panic in release mode, add this:


[profile.release]
panic = 'abort'

*/

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
        },
    };

    let mut s = String::new();

    match f.read_to_string(&mut s) {
        Ok(_) => Ok(s),
        Err(e) => Err(e),
    }
}

fn test_result_enum_without_match() {
    let f = File::open("hello.txt").unwrap_or_else(|error| {
        if error.kind() == ErrorKind::NotFound {
            File::create("hello.txt").unwrap_or_else(|error| {
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

    // panic!("cash and burn");

    // Unwinding the Stack or Aborting in Response to a Panic
    // By default, when a panic occurs, the program starts unwinding, which means Rust walks back up the stack and cleans up the data
    // from each function it encounters. But this walking back and cleanup is a lot of work. The alternative is to immediately abort,
    // which ends the program without cleaning up.
    // Memory that the program was using will then need to be cleaned up by the operating system.
    // If in your project you need to make the resulting binary as small as possible, you can switch from unwinding to aborting upon a panic by adding panic = 'abort' to the appropriate [profile] sections in your Cargo.toml file. For example, if you want to abort on panic in release mode, add this:

    // [profile.release]
    // panic = 'abort'

    test_result_enum();

    test_and_then();

    test_option_unwrap();
}

/*

    *** Option & unwrap ***
In the last example, we showed that we can induce program failure at will. We told our program to panic if the princess received an inappropriate gift - a snake.
But what if the princess expected a gift and didn't receive one? That case would be just as bad, so it needs to be handled!

We could test this against the null string ("") as we do with a snake. Since we're using Rust, let's instead have the compiler point out cases where there's no gift.

An enum called Option<T> in the std library is used when absence is a possibility. It manifests itself as one of two "options":

    1) Some(T): An element of type T was found
    2) None: No element was found
These cases can either be explicitly handled via match or implicitly with unwrap. Implicit handling will either return the inner element or panic.

Note that it's possible to manually customize panic with expect, but unwrap otherwise leaves us with a less meaningful output than explicit handling.
In the following example, explicit handling yields a more controlled result while retaining the option to panic if desired.

    *** Unpacking options with ? ***
You can unpack Options by using match statements, but it's often easier to use the ? operator.
If x is an Option, then evaluating x? will return the underlying value if x is Some, otherwise it will terminate whatever function is being executed and return None.

    *** Combinators: map ***
match is a valid method for handling Options. However, you may eventually find heavy usage tedious, especially with operations only valid with an input.
In these cases, combinators can be used to manage control flow in a modular fashion.

Option has a built in method called map(), a combinator for the simple mapping of Some -> Some and None -> None. Multiple map() calls can be chained together for even more flexibility.

In the following example, process() replaces all functions previous to it while staying compact.

    *** Combinators: and_then ***
map() was described as a chainable way to simplify match statements. However, using map() on a function that returns an Option<T> results in the nested Option<Option<T>>.
Chaining multiple calls together can then become confusing. That's where another combinator called and_then(), known in some languages as flatmap, comes in.

and_then() calls its function input with the wrapped value and returns the result. If the Option is None, then it returns None instead.

In the following example, cookable_v2() results in an Option<Food>. Using map() instead of and_then() would have given an Option<Option<Food>>, which is an invalid type for eat().

*/
// The commoner has seen it all, and can handle any gift well.
// All gifts are handled explicitly using `match`.
fn give_commoner(gift: Option<&str>) {
    // Specify a course of action for each case.
    match gift {
        Some("snake") => println!("Yuck! I'm putting this snake back in the forest."),
        Some(inner) => println!("{}? How nice.", inner),
        None => println!("No gift? Oh well."),
    }
}

// Our sheltered princess will `panic` at the sight of snakes.
// All gifts are handled implicitly using `unwrap`.
fn give_princess(gift: Option<&str>) {
    // `unwrap` returns a `panic` when it receives a `None`.
    let inside = gift.unwrap();
    if inside == "snake" {
        panic!("AAAaaaaa!!!!");
    }

    println!("I love {}s!!!!!", inside);
}

fn next_birthday(current_age: Option<u8>) -> Option<String> {
    // If `current_age` is `None`, this returns `None`.
    // If `current_age` is `Some`, the inner `u8` gets assigned to `next_age`
    let next_age: u8 = current_age?;
    Some(format!("Next year I will be {}", next_age))
}

// *** Unpacking options with ? ***

struct Person {
    job: Option<Job>,
}

#[derive(Clone, Copy)]
struct Job {
    phone_number: Option<PhoneNumber>,
}

#[derive(Clone, Copy)]
struct PhoneNumber {
    area_code: Option<u8>,
    number: u32,
}

impl Person {
    // Gets the area code of the phone number of the person's job, if it exists.
    fn work_phone_area_code(&self) -> Option<u8> {
        // This would need many nested `match` statements without the `?` operator.
        // It would take a lot more code - try writing it yourself and see which
        // is easier.
        self.job?.phone_number?.area_code
    }
}

fn test_option_unwrap() {
    let food = Some("cabbage");
    let snake = Some("snake");
    let void = None;

    give_commoner(food);
    give_commoner(snake);
    give_commoner(void);

    let bird = Some("robin");
    let nothing = None;

    give_princess(bird);
    give_princess(nothing);

    // Unpacking options with ?
    let p = Person {
        job: Some(Job {
            phone_number: Some(PhoneNumber {
                area_code: Some(61),
                number: 439222222,
            }),
        }),
    };

    assert_eq!(p.work_phone_area_code(), Some(61));

    // Combinators: map
    let apple = Some(Food::Apple);
    let carrot = Some(Food::Carrot);
    let potato = None;

    let cooked_apple = cook(chop(peel(apple)));
    let cooked_carrot = cook(chop(peel(carrot)));
    // Let's try the simpler looking `process()` now.
    let cooked_potato = process(potato);

    eat(cooked_apple);
    eat(cooked_carrot);
    eat(cooked_potato);
}

// *** Combinators: map ***

#[derive(Debug)]
enum Food {
    Apple,
    Carrot,
    Potato,
}

#[derive(Debug)]
struct Peeled(Food);
#[derive(Debug)]
struct Chopped(Food);
#[derive(Debug)]
struct Cooked(Food);

// Peeling food. If there isn't any, then return `None`.
// Otherwise, return the peeled food.
fn peel(food: Option<Food>) -> Option<Peeled> {
    match food {
        Some(food) => Some(Peeled(food)),
        None => None,
    }
}

// Chopping food. If there isn't any, then return `None`.
// Otherwise, return the chopped food.
fn chop(peeled: Option<Peeled>) -> Option<Chopped> {
    match peeled {
        Some(Peeled(food)) => Some(Chopped(food)),
        None => None,
    }
}

// Cooking food. Here, we showcase `map()` instead of `match` for case handling.
fn cook(chopped: Option<Chopped>) -> Option<Cooked> {
    chopped.map(|Chopped(food)| Cooked(food))
}

// A function to peel, chop, and cook food all in sequence.
// We chain multiple uses of `map()` to simplify the code.
fn process(food: Option<Food>) -> Option<Cooked> {
    food.map(|f| Peeled(f))
        .map(|Peeled(f)| Chopped(f))
        .map(|Chopped(f)| Cooked(f))
}

// Check whether there's food or not before trying to eat it!
fn eat(food: Option<Cooked>) {
    match food {
        Some(food) => println!("Mmm. I love {:?}", food),
        None => println!("Oh no! It wasn't edible."),
    }
}

// *** Combinators: and_then ***
#[derive(Debug)]
enum Food1 {
    CordonBleu,
    Steak,
    Sushi,
}
#[derive(Debug)]
enum Day {
    Monday,
    Tuesday,
    Wednesday,
}

// We don't have the ingredients to make Sushi.
fn have_ingredients(food: Food1) -> Option<Food1> {
    match food {
        Food1::Sushi => None,
        _ => Some(food),
    }
}

// We have the recipe for everything except Cordon Bleu.
fn have_recipe(food: Food1) -> Option<Food1> {
    match food {
        Food1::CordonBleu => None,
        _ => Some(food),
    }
}

// To make a dish, we need both the recipe and the ingredients.
// We can represent the logic with a chain of `match`es:
fn cookable_v1(food: Food1) -> Option<Food1> {
    match have_recipe(food) {
        None => None,
        Some(food) => match have_ingredients(food) {
            None => None,
            Some(food) => Some(food),
        },
    }
}

// This can conveniently be rewritten more compactly with `and_then()`:
fn cookable_v2(food: Food1) -> Option<Food1> {
    have_recipe(food).and_then(have_ingredients)
}

fn eat1(food: Food1, day: Day) {
    match cookable_v2(food) {
        Some(food) => println!("Yay! On {:?} we get to eat {:?}.", day, food),
        None => println!("Oh no. We don't get to eat on {:?}?", day),
    }
}

fn test_and_then() {
    let (cordon_bleu, steak, sushi) = (Food1::CordonBleu, Food1::Steak, Food1::Sushi);

    eat1(cordon_bleu, Day::Monday);
    eat1(steak, Day::Tuesday);
    eat1(sushi, Day::Wednesday);
}

/*
    *** Result ***
    *** map for Result ***
Panicking in the previous example's multiply does not make for robust code.
Generally, we want to return the error to the caller so it can decide what is the right way to respond to errors.

We first need to know what kind of error type we are dealing with. To determine the Err type, we look to parse(),
which is implemented with the FromStr trait for i32. As a result, the Err type is specified as ParseIntError.

In the example below, the straightforward match statement leads to code that is overall more cumbersome.


    *** aliases for Result ***
How about when we want to reuse a specific Result type many times? Recall that Rust allows us to create aliases.
Conveniently, we can define one for the specific Result in question.

At a module level, creating aliases can be particularly helpful. Errors found in a specific module often have the same Err type,
so a single alias can succinctly define all associated Results. This is so useful that the std library even supplies one: io::Result!

    *** Early returns ***
In the previous example, we explicitly handled the errors using combinators.
Another way to deal with this case analysis is to use a combination of match statements and early returns.

That is, we can simply stop executing the function and return the error if one occurs.
For some, this form of code can be easier to both read and write. Consider this version of the previous example, rewritten using early returns:

    *** Introducing ? ***
Sometimes we just want the simplicity of unwrap without the possibility of a panic.
Until now, unwrap has forced us to nest deeper and deeper when what we really wanted was to get the variable out. This is exactly the purpose of ?.

Upon finding an Err, there are two valid actions to take:

    1) panic! which we already decided to try to avoid if possible
    2) return because an Err means it cannot be handled
? is almost1 exactly equivalent to an unwrap which returns instead of panicking on Errs. Let's see how we can simplify the earlier example that used combinators:

    *** The try! macro ***
Before there was ?, the same functionality was achieved with the try! macro. The ? operator is now recommended, but you may still find try! when looking at older code.
The same multiply function from the previous example would look like this using try!:
*/
use std::num::ParseIntError;

// With the return type rewritten, we use pattern matching without `unwrap()`.
fn multiply(first_number_str: &str, second_number_str: &str) -> Result<i32, ParseIntError> {
    match first_number_str.parse::<i32>() {
        Ok(first_number) => match second_number_str.parse::<i32>() {
            Ok(second_number) => Ok(first_number * second_number),
            Err(e) => return Err(e),
        },
        Err(e) => Err(e),
    }
}

// Luckily, Option's map, and_then, and many other combinators are also implemented for Result.
// As with `Option`, we can use combinators such as `map()`.
// This function is otherwise identical to the one above and reads:
// Modify n if the value is valid, otherwise pass on the error.
fn multiply1(first_number_str: &str, second_number_str: &str) -> Result<i32, ParseIntError> {
    first_number_str.parse::<i32>().and_then(|first_number| {
        second_number_str
            .parse::<i32>()
            .map(|second_number| first_number * second_number)
    })
}

fn print(result: Result<i32, ParseIntError>) {
    match result {
        Ok(n) => println!("n is {}", n),
        Err(e) => println!("Error: {}", e),
    }
}

fn test_result_basic() {
    // *** map for Result ***
    // This still presents a reasonable answer.
    let twenty = multiply("10", "2");
    print(twenty);

    // The following now provides a much more helpful error message.
    let tt = multiply("t", "2");
    print(tt);

    // *** aliases for Result ***
    print_aliasedResult(multiply("10", "2"));
    print_aliasedResult(multiply("t", "2"));
}

// *** aliases for Result ***
// Define a generic alias for a `Result` with the error type `ParseIntError`.
type AliasedResult<T> = Result<T, ParseIntError>;

// Use the above alias to refer to our specific `Result` type.
fn multiply2(first_number_str: &str, second_number_str: &str) -> AliasedResult<i32> {
    first_number_str.parse::<i32>().and_then(|first_number| {
        second_number_str
            .parse::<i32>()
            .map(|second_number| first_number * second_number)
    })
}

// Here, the alias again allows us to save some space.
fn print_aliasedResult(result: AliasedResult<i32>) {
    match result {
        Ok(n) => println!("n is {}", n),
        Err(e) => println!("Error: {}", e),
    }
}

// *** Introducing ? ***
fn multiply3(first_number_str: &str, second_number_str: &str) -> Result<i32, ParseIntError> {
    let first_number = first_number_str.parse::<i32>()?;
    let second_number = second_number_str.parse::<i32>()?;

    Ok(first_number * second_number)
}

// To compile and run this example without errors, while using Cargo, change the value
// of the `edition` field, in the `[package]` section of the `Cargo.toml` file, to "2015"
fn multiply4(first_number_str: &str, second_number_str: &str) -> Result<i32, ParseIntError> {
    // let first_number = try!(first_number_str.parse::<i32>());
    // let second_number = try!(second_number_str.parse::<i32>());

    let first_number = r#try!(first_number_str.parse::<i32>());
    let second_number = r#try!(second_number_str.parse::<i32>());

    Ok(first_number * second_number)
}

/*
    *** Multiple error types ***
The previous examples have always been very convenient; Results interact with other Results and Options interact with other Options.

Sometimes an Option needs to interact with a Result, or a Result<T, Error1> needs to interact with a Result<T, Error2>.
n those cases, we want to manage our different error types in a way that makes them composable and easy to interact with.

In the following code, two instances of unwrap generate different error types. Vec::first returns an Option, while parse::<i32> returns a Result<i32, ParseIntError>:


    *** Pulling Results out of Options ***
The most basic way of handling mixed error types is to just embed them in each other.

    *** Defining an error type ***
Sometimes it simplifies the code to mask all of the different errors with a single type of error. We'll show this with a custom error.

Rust allows us to define our own error types. In general, a "good" error type:

    1) Represents different errors with the same type
    2) Presents nice error messages to the user
    3) Is easy to compare with other types
        Good: Err(EmptyVec)
        Bad: Err("Please use a vector with at least one element".to_owned())
    4) Can hold information about the error
        Good: Err(BadChar(c, position))
        Bad: Err("+ cannot be used here".to_owned())
    5)  Composes well with other errors

*/

// The most basic way of handling mixed error types is to just embed them in each other.
fn double_first1(vec: Vec<&str>) -> Option<Result<i32, ParseIntError>> {
    vec.first().map(|first| first.parse::<i32>().map(|n| 2 * n))
}

// There are times when we'll want to stop processing on errors (like with ?) but keep going when the Option is None.
// A couple of combinators come in handy to swap the Result and Option.
fn double_first2(vec: Vec<&str>) -> Result<Option<i32>, ParseIntError> {
    let opt = vec.first().map(|first| first.parse::<i32>().map(|n| 2 * n));

    opt.map_or(Ok(None), |r| r.map(Some))
}

fn test_multiple_error_types() {
    //     *** Multiple error types ***
    let numbers = vec!["42", "93", "18"];
    let empty = vec![];
    let strings = vec!["tofu", "93", "18"];

    println!("The first doubled is {:?}", double_first1(numbers));

    println!("The first doubled is {:?}", double_first1(empty));
    // Error 1: the input vector is empty

    println!("The first doubled is {:?}", double_first1(strings));
    // Error 2: the element doesn't parse to a number

    let numbers = vec!["42", "93", "18"];
    let empty = vec![];
    let strings = vec!["tofu", "93", "18"];
    println!("The first doubled is {:?}", double_first2(numbers));
    println!("The first doubled is {:?}", double_first2(empty));
    println!("The first doubled is {:?}", double_first2(strings));
}
