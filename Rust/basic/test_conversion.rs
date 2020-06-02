/*
    *** Conversion ***
Rust addresses conversion between types by the use of traits. The generic conversions will use the From and Into traits.
However there are more specific ones for the more common cases, in particular when converting to and from Strings.
*/



/*
    *** From and Into ***
The From and Into traits are inherently linked, and this is actually part of its implementation.
If you are able to convert type A from type B, then it should be easy to believe that we should be able to convert type B to type A.

    *** From ***
The From trait allows for a type to define how to create itself from another type, hence providing a very simple mechanism for converting between several types.
There are numerous implementations of this trait within the standard library for conversion of primitive and common types.

    *** Into ***
The Into trait is simply the reciprocal of the From trait. That is, if you have implemented the From trait for your type, Into will call it when necessary.

Using the Into trait will typically require specification of the type to convert into as the compiler is unable to determine this most of the time.
However this is a small trade-off considering we get the functionality for free.

*/

// For example we can easily convert a str into a String
use std::convert::{From, TryFrom, TryInto};
use std::fmt;

#[derive(Debug)]
struct Number {
    value: i32,
}

impl From<i32> for Number {
    fn from(item: i32) -> Self {
        Number { value : item}
    }
}

fn test_from_into() {
    let num = Number::from(30);
    println!("My number is {:?}", num);

    let int = 5;
    // Try removing the type declaration
    let num: Number = int.into();
    println!("My number is {:?}", num);
}

/*
    *** TryFrom and TryInto ***
Similar to From and Into, TryFrom and TryInto are generic traits for converting between types.
Unlike From/Into, the TryFrom/TryInto traits are used for fallible conversions, and as such, return Results.
*/

#[derive(Debug, PartialEq)]
struct EvenNumber(i32);

impl TryFrom<i32> for EvenNumber {
    type Error = ();

    fn try_from(value: i32) -> Result<Self, Self::Error> {
        if value % 2  == 0 {
            Ok(EvenNumber(value))
        } else {
            Err(())
        }
    }
}

fn test_try_from_into() {
    // TryFrom

    assert_eq!(EvenNumber::try_from(8), Ok(EvenNumber(8)));
    assert_eq!(EvenNumber::try_from(5), Err(()));

    // TryInto

    let result: Result<EvenNumber, ()> = 8i32.try_into();
    assert_eq!(result, Ok(EvenNumber(8)));
    let result: Result<EvenNumber, ()> = 5i32.try_into();
    assert_eq!(result, Err(()));
}

/*
    *** To and from Strings ***

    *** Converting to String ***
To convert any type to a String is as simple as implementing the ToString trait for the type.
Rather than doing so directly, you should implement the fmt::Display trait which automagically provides
ToString and also allows printing the type as discussed in the section on print!.

    *** Parsing a String ***
One of the more common types to convert a string into is a number.
The idiomatic approach to this is to use the parse function and either to arrange for type inference or to specify the type to parse using the 'turbofish' syntax.
Both alternatives are shown in the following example.

This will convert the string into the type specified so long as the FromStr trait is implemented for that type.
This is implemented for numerous types within the standard library. To obtain this functionality on a user defined type simply implement the FromStr trait for that type.
*/

struct Circle {
    radius: i32,
}

impl fmt::Display for Circle {

    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Circle of radius {}", self.radius)
    }
}

fn test_from_to_strings() {
    let circle = Circle{ radius: 6};

    println!("{}", circle.to_string());

    let parsed: i32 = "5".parse().unwrap();
    let turbo_parsed = "10".parse::<i32>().unwrap();

    let sum = parsed + turbo_parsed;
    println!("Sum: {:?}", sum);
}

pub fn test_conversions() {

    test_conversions();

    test_from_into();

    test_from_to_strings();

    test_try_from_into();

}