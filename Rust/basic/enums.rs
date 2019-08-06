use std::net::Ipv4Addr;

enum IpAddrKind {
    V4,
    V6,
}

struct IpAddrStruct {
    kind: IpAddrKind,
    address: String,
}

/* 
We can represent the same concept in a more concise way using just an enum, rather than an enum inside a struct, by putting data directly into each enum variant. 
This new definition of the IpAddr enum says that both V4 and V6 variants will have associated String values:
*/

enum IpAddrStr {
    V4(String),
    V6(String),
}

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
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn call(&self) {
        println!("msg: {}", self.Move);
    }
}

enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => {
            println!("Lucky penny!");
            1
        },
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}

fn test_enums() {

    let home = IpAddrStruct {
        kind: IpAddrKind.V4,
        address: String.from("127.0.0.1"),
    };

    let loopback = IpAddrStruct {
        kind: IpAddrKind.V6,
        address: String.from("::1"),
    };

    println!("home = {} , loopback = {} ", home, loopback);

    let homes = IpAddrStr::V4(String::from("127.0.0.1"));
    let loopbacks = IpAddrStr::V6(String::from("::1"));

    let homei = IpAddrInt::V4(127,0,0,1);
    let loopbacki = IpAddrInt::V6(String::from("::1"));

    // using std::net::Ipv4Addr
    let localhost = Ipv4Addr::new(127, 0, 0, 1);
    assert_eq!("127.0.0.1".parse(), Ok(localhost));
    assert_eq!(localhost.is_loopback(), true);

    // Message
    let m = Message::Write(String::from("hello"));
    m.call();

    // coin
    let c = Coin::Quarter;
    println!("Quarter = {}", value_in_cents(c));
}