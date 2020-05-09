use std::net::{IpAddr, Ipv4Addr, Ipv6Addr};

/*
old-style way has to use enum and struct to represent IP
 */
#[derive(Debug)]
enum IpAddrKind {
    V4,
    V6,
}

#[derive(Debug)]
struct IpAddrStruct {
    kind: IpAddrKind,
    address: String,
}

/*
We can represent the same concept in a more concise way using just an enum, rather than an enum inside a struct, by putting data directly into each enum variant.
This new definition of the IpAddr enum says that both V4 and V6 variants will have associated String values:
*/
#[derive(Debug)]
enum IpAddrStr {
    V4(String),
    V6(String),
}

#[derive(Debug)]
enum IpAddrInt {
    V4(u8, u8, u8, u8),
    V6(String),
}

fn test_ipaddr_enum() {
    let localhost_v4 = IpAddr::V4(Ipv4Addr::new(127, 0, 0, 1));

    let localhost_v6 = IpAddr::V6(Ipv6Addr::new(0, 0, 0, 0, 0, 0, 0, 1));

    assert_eq!("127.0.0.1".parse(), Ok(localhost_v4));
    assert_eq!("::1".parse(), Ok(localhost_v6));

    assert_eq!(localhost_v4.is_ipv6(), false);
    assert_eq!(localhost_v6.is_ipv4(), false);
}

/*
This enum has four variants with different types:

1) Quit has no data associated with it at all.
2) Move includes an anonymous struct inside it.
3) Write includes a single String.
4) ChangeColor includes three i32 values.
*/
#[derive(Debug)]
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn call(&self) {
        // println!("msg: {:?}", self::Message::Move);
    }
}

#[derive(Debug)]
enum UsState {
    Alaska,
    Massachusetts,
    Maine,
}
/*
Patterns that Bind to Values
Another useful feature of match arms is that they can bind to the parts of the values that match the pattern.
This is how we can extract values out of enum variants.
*/
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),
}

// *** C-like enum
// enum can also be used as C-like enums.
// An attribute to hide warnings for unused code.
#[allow(dead_code)]

// enum with implicit discriminator (starts at 0)
enum Number {
    Zero,
    One,
    Two,
}

// enum with explicit discriminator
enum Color {
    Red = 0xff0000,
    Green = 0x00ff00,
    Blue = 0x0000ff,
}

fn C_like_enum() {
    // `enums` can be cast as integers.
    println!("zero is {}", Number::Zero as i32);
    println!("one is {}", Number::One as i32);

    println!("roses are #{:06x}", Color::Red as i32);
    println!("violets are #{:06x}", Color::Blue as i32);
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => {
            println!("Lucky penny!");
            1
        }
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter(state) => {
            println!("State quarter from {:?}", state);
            25
        }
    }
}

fn test_enums_baisc() {
    // old style code
    let home = IpAddrStruct {
        kind: IpAddrKind::V4,
        address: String::from("127.0.0.1"),
    };

    let loopback = IpAddrStruct {
        kind: IpAddrKind::V6,
        address: String::from("::1"),
    };

    println!("home = {:?} , loopback = {:?} ", home, loopback);

    // use new style enum
    let homes = IpAddrStr::V4(String::from("127.0.0.1"));
    let loopbacks = IpAddrStr::V6(String::from("::1"));

    let homei = IpAddrInt::V4(127, 0, 0, 1);
    let loopbacki = IpAddrInt::V6(String::from("::1"));

    println!("homes = {:?}, loopbacks = {:?}", homes, loopbacks);
    println!("homei = {:?}, loopbacki = {:?}", homei, loopbacki);

    // using std::net::Ipv4Addr
    let localhost = Ipv4Addr::new(127, 0, 0, 1);
    assert_eq!("127.0.0.1".parse(), Ok(localhost));
    assert_eq!(localhost.is_loopback(), true);

    // Message
    let m = Message::Write(String::from("hello"));
    m.call();

    // coin
    let c = Coin::Quarter(UsState::Alaska);
    println!("Quarter = {}", value_in_cents(c));

    // match functon, '_' == default
    let some_u8_value = 0u8;
    match some_u8_value {
        1 => println!("one"),
        3 => println!("three"),
        5 => println!("five"),
        7 => println!("seven"),
        _ => (), // default
    }
}

fn iflet_vs_match() {
    let some_8 = Some(0u8);
    match some_8 {
        Some(3) => println!("three"),
        _ => (),
    }
    /*
    The syntax if let takes a pattern and an expression separated by an equal sign.
    It works the same way as a match, where the expression is given to the match and the pattern is its first arm.

    Using if let means less typing, less indentation, and less boilerplate code.
    However, you lose the exhaustive checking that match enforces.
    Choosing between match and if let depends on what you’re doing in your particular situation and whether gaining conciseness is an appropriate trade-off for losing exhaustive checking.

    In other words, you can think of if let as syntax sugar for a match that runs code when the value matches one pattern and then ignores all other values.
     */

    if let Some(3) = Some(0u8) {
        println!("three");
    }

    /*
    We can include an else with an if let. The block of code that goes with the else is the same as the block of code
    that would go with the _ case in the match expression that is equivalent to the if let and else.
    Recall the Coin enum definition in Listing 6-4, where the Quarter variant also held a UsState value.
    If we wanted to count all non-quarter coins we see while also announcing the state of the quarters,
    we could do that with a match expression like this:
    */

    let mut count = 0;
    let coin = Coin::Penny;
    match coin {
        Coin::Quarter(state) => println!("State quator from {:?}", state),
        _ => count += 1,
    }

    /*
    We can include an else with an if let. The block of code that goes with the else is the same as the block of code
    that would go with the _ case in the match expression that is equivalent to the if let and else.
    */
    let coin1 = Coin::Penny;
    if let Coin::Quarter(state1) = coin1 {
        println!("State quator from {:?}", state1);
    } else {
        count += 1;
    }
}

/*
Option<T>

The Option Enum and Its Advantages Over Null Values

enum Option<T> {
    Some(T),
    None,
}

The Option<T> enum is so useful that it’s even included in the prelude; you don’t need to bring it into scope explicitly.
In addition, so are its variants: you can use Some and None directly without the Option:: prefix.
The Option<T> enum is still just a regular enum, and Some(T) and None are still variants of type Option<T>.
 */
fn plus_one(a: Option<i32>) -> Option<i32> {
    match a {
        // None matched
        None => None,
        // some(i) matched
        Some(i) => Some(i + 1),
        // There, we need both 'None' and 'Some', because it covers all two situations.
    }
}

fn test_options() {
    let some_number = Some(5);
    let some_string = Some("a String");
    let absent_numer: Option<u32> = None;

    let five = Some(5);
    let Six = plus_one(five);
    let none = plus_one(None);
}

/*
enum Result<T, E> {
   Ok(T),
   Err(E),
}

Error handling with the Result type.

Result<T, E> is the type used for returning and propagating errors. It is an enum with the variants, Ok(T), representing success and containing a value,
and Err(E), representing error and containing an error value.

*/
#[derive(Debug)]
enum Version {
    Version1,
    Version2,
}

fn parse_version(header: &[u8]) -> Result<Version, &'static str> {
    match header.get(0) {
        None => Err("invalid header length"),
        Some(&1) => Ok(Version::Version1),
        Some(&2) => Ok(Version::Version2),
        Some(_) => Err("invalid version"),
    }
}

fn test_result() {
    let version = parse_version(&[1, 2, 3, 4]);
    match version {
        Ok(v) => println!("working with version: {:?}", v),
        Err(e) => println!("error parsing header: {:?}", e),
    }

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
}

pub fn test_enums() {
    test_enums_baisc();

    test_options();

    C_like_enum();
}
