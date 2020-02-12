use std::option;

/*
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
    test_basic_option();

    test_advaned_option();
}
