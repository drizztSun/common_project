use std::net::Ipv4Addr;

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

pub fn test_enums() {
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

    C_like_enum();
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
    if let Coin::Quarter(state1) = coin {
        println!("State quator from {:?}", state1);
    } else {
        count += 1;
    }*/
}

/*
Option<T>
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
