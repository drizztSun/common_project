use std::option;

/*

    *** Option ***
Sometimes it's desirable to catch the failure of some parts of a program instead of calling panic!; this can be accomplished using the Option enum.

The Option<T> enum has two variants:

1) None, to indicate failure or lack of value, and
2) Some(value), a tuple struct that wraps a value with type T.


Type Option represents an optional value: every Option is either Some and contains a value, or None, and does not.
Option types are very common in Rust code, as they have a number of uses:

Initial values
Return values for functions that are not defined over their entire input range (partial functions)
Return value for otherwise reporting simple errors, where None is returned on error
Optional struct fields
Struct fields that can be loaned or "taken"
Optional function arguments
Nullable pointers
Swapping things out of difficult situations
*/

// An integer division that doesn't `panic!`
fn checked_division(dividend: i32, divisor: i32) -> Option<i32> {
    if divisor == 0 {
        // Failure is represented as the `None` variant
        None
    } else {
        // Result is wrapped in a `Some` variant
        Some(dividend / divisor)
    }
}

// This function handles a division that may not succeed
fn try_division(dividend: i32, divisor: i32) {
    // `Option` values can be pattern matched, just like other enums
    match checked_division(dividend, divisor) {
        None => println!("{} / {} failed!", dividend, divisor),
        Some(quotient) => println!("{} / {} = {}", dividend, divisor, quotient),
    }
}

fn test_options_basic() {
    try_division(4, 2);
    try_division(1, 0);

    // Binding `None` to a variable needs to be type annotated
    let none: Option<i32> = None;
    let _equivalent_none = None::<i32>;

    let optional_float = Some(0f32);

    // Unwrapping a `Some` variant will extract the value wrapped.
    println!(
        "{:?} unwraps to {:?}",
        optional_float,
        optional_float.unwrap()
    );

    // Unwrapping a `None` variant will `panic!`
    println!("{:?} unwraps to {:?}", none, none.unwrap());


    {
        let x: Option<u32> = Some(2);
        assert_eq!(x.is_some(), true);

        let x: Option<u32> = None;
        assert_eq!(x.is_some(), false);
    }


    {
        let x: Option<u32> = Some(2);
        assert_eq!(x.is_none(), false);

        let x: Option<u32> = None;
        assert_eq!(x.is_none(), true);
    }

    {
        #![feature(option_result_contains)]
        let x: Option<u32> = Some(2);
        assert_eq!(x.contains(&2), true);
        
        let x: Option<u32> = Some(3);
        assert_eq!(x.contains(&2), false);
        
        let x: Option<u32> = None;
        assert_eq!(x.contains(&2), false);
    }

    {
        let text: Option<String> = Some("Hello, world!".to_string());
        // First, cast `Option<String>` to `Option<&String>` with `as_ref`,
        // then consume *that* with `map`, leaving `text` on the stack.
        let text_length: Option<usize> = text.as_ref().map(|s| s.len());
        println!("still can print text: {:?}", text);
    }

    {
        let mut x = Some(2);
        match x.as_mut() {
            Some(v) => *v = 42,
            None => {},
        }
        assert_eq!(x, Some(42));
    }

    {
        /*
        pub fn unwrap(self) -> T

        Returns the contained Some value, consuming the self value.
        Because this function may panic, its use is generally discouraged. Instead, prefer to use pattern matching and handle the None case explicitly, or call unwrap_or, unwrap_or_else, or unwrap_or_default.
        Panics if the self value equals None.
        */
        let x = Some("air");
        assert_eq!(x.unwrap(), "air");
    }

    {
        // pub fn unwrap_or(self, default: T) -> T
        assert_eq!(Some("car").unwrap_or("bike"), "car");
        assert_eq!(None.unwrap_or("bike"), "bike");
    }

    {
        // pub fn unwrap_or_else<F>(self, f: F) -> T
        let k = 10;
        assert_eq!(Some(4).unwrap_or_else(|| 2 * k), 4);
        assert_eq!(None.unwrap_or_else(|| 2 * k), 20);
    }

    {
        // pub fn map<U, F>(self, f: F) -> Option<U>
        let maybe_some_string = Some(String::from("Hello, World!"));
        // `Option::map` takes self *by value*, consuming `maybe_some_string`
        let maybe_some_len = maybe_some_string.map(|s| s.len());

        assert_eq!(maybe_some_len, Some(13));
    }

    {
        // pub fn map_or<U, F>(self, default: U, f: F) -> U

        // Applies a function to the contained value (if any), or returns the provided default (if not).
        // Arguments passed to map_or are eagerly evaluated; if you are passing the result of a function call, it is recommended to use map_or_else, which is lazily evaluated.
        let x = Some("foo");
        assert_eq!(x.map_or(42, |v| v.len()), 3);

        let x: Option<&str> = None;
        assert_eq!(x.map_or(42, |v| v.len()), 42);
    }

    {
        // pub fn map_or_else<U, D, F>(self, default: D, f: F) -> U
        let k = 21;
        let x = Some("foo");
        assert_eq!(x.map_or_else(|| 2 * k, |v| v.len()), 3);

        let x: Option<&str> = None;
        assert_eq!(x.map_or_else(|| 2 * k, |v| v.len()), 42);
    }

    {
        // pub fn take(&mut self) -> Option<T>
        let mut x = Some(2);
        let y = x.take();
        assert_eq!(x, None);
        assert_eq!(y, Some(2));

        let mut x: Option<u32> = None;
        let y = x.take();
        assert_eq!(x, None);
        assert_eq!(y, None);
    }

    {
        // pub fn replace(&mut self, value: T) -> Option<T>
        let mut x = Some(2);
        let old = x.replace(5);
        assert_eq!(x, Some(5));
        assert_eq!(old, Some(2));

        let mut x = None;
        let old = x.replace(3);
        assert_eq!(x, Some(3));
        assert_eq!(old, None);
    }

    {
        // pub fn get_or_insert(&mut self, v: T) -> &mut T
        // Inserts v into the option if it is None, then returns a mutable reference to the contained value.
        let mut x = None;

        {
            let y: &mut u32 = x.get_or_insert(5);
            assert_eq!(y, &5);

            *y = 7;
        }

        assert_eq!(x, Some(7));
    }

    {
        // pub fn get_or_insert_with<F>(&mut self, f: F) -> &mut T
        // Inserts a value computed from f into the option if it is None, then returns a mutable reference to the contained value.
        let mut x = None;

        {
            let y: &mut u32 = x.get_or_insert_with(|| 5);
            assert_eq!(y, &5);

            *y = 7;
        }

        assert_eq!(x, Some(7));
    }

    {
        // pub fn ok_or<E>(self, err: E) -> Result<T, E>
        // Transforms the Option<T> into a Result<T, E>, mapping Some(v) to Ok(v) and None to Err(err).
        let x = Some("foo");
        assert_eq!(x.ok_or(0), Ok("foo"));
        
        let x: Option<&str> = None;
        assert_eq!(x.ok_or(0), Err(0));
    }

    {
        #![feature(option_zip)]
        let x = Some(1);
        let y = Some("hi");
        let z = None::<u8>;

        assert_eq!(x.zip(y), Some((1, "hi")));
        assert_eq!(x.zip(z), None);
    }


}

fn devide(numerator: f64, denominator: f64) -> Option<f64> {
    if denominator == 0.0 {
        None
    } else {
        Some(numerator / denominator)
    }
}

fn test_basic_option() {
    // the return value of device is Option
    let res = devide(1.0, 0.0);

    match res {
        Some(x) => println!("Result: {} ", x),
        None => println!("Cannot devide by 0"),
    }

    //The following example uses Option to create an optional box of i32.
    // Notice that in order to use the inner i32 value first, the check_optional function needs to use pattern
    // matching to determine whether the box has a value (i.e., it is Some(...)) or not (None).

    // Rust's pointer types must always point to a valid location; there are no "null" references.
    // Instead, Rust has optional pointers, like the optional owned box, Option<Box<T>>.
    let optional = None;
    check_option(optional);

    let optional = Some(Box::new(3000));
    check_option(optional);

    // Basic pattern matching on Option
    let msg = Some("howdy");

    // Take a reference to the contained string
    if let Some(x) = &msg {
        println!("{}", *x);
    }

    // remove the contained string, destorying the option
    let unwrapped_msg = msg.unwrap_or("default message");
    println!("unwapped_msg {}", unwrapped_msg);
}

fn check_option(opt: Option<Box<i32>>) {
    match opt {
        Some(x) => println!("Has value {}", x),
        None => println!("has no value"),
    }
}

enum Kingdom {
    Plant(u32, &'static str),
    Animal(u32, &'static str),
}

fn test_advaned_option() {
    // A list of data to search through.
    let all_the_big_things = [
        Kingdom::Plant(250, "redwood"),
        Kingdom::Plant(230, "noble fir"),
        Kingdom::Plant(229, "sugar pine"),
        Kingdom::Animal(25, "blue whale"),
        Kingdom::Animal(19, "fin whale"),
        Kingdom::Animal(15, "north pacific right whale"),
    ];

    // We're going to search for the name of the biggest animal,
    // but to start with we've just got `None`.
    let mut name_of_biggest_animal = None;
    let mut size_of_biggest_animal = 0;
    for big_thing in &all_the_big_things {
        match *big_thing {
            Kingdom::Animal(size, name) if size > size_of_biggest_animal => {
                // Now we've found the name of some big animal
                size_of_biggest_animal = size;
                name_of_biggest_animal = Some(name);
                println!("get special Animal {}, {}", size, name);
            }
            Kingdom::Animal(..) | Kingdom::Plant(..) => (),
        }
    }

    match name_of_biggest_animal {
        Some(name) => println!("the biggest animal is {}", name),
        None => println!("there are no animals :("),
    }
}

pub fn test_option() {
    test_options_basic();

    test_basic_option();

    test_advaned_option();
}
