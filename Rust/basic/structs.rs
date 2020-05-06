struct User {
    name: String,
    email: String,
    sign_in: u64,
    active: bool,
}

fn build_user(email: String, username: String) -> User {
    User {
        name: username,
        email: email,
        sign_in: 1,
        active: true,
    }
}

// or
// Using Field Init Shorthand
fn build_user_field_init_shorthand(email: String, name: String) -> User {
    User {
        name,
        email,
        sign_in: 1,
        active: true,
    }
}

// tuple structs
/*
Using Tuple Structs without Named Fields to Create Different Types
You can also define structs that look similar to tuples, called tuple structs.
Tuple structs have the added meaning the struct name provides but don’t have names associated with their fields;
rather, they just have the types of the fields. Tuple structs are useful
when you want to give the whole tuple a name and make the tuple be a different type from other tuples,
and naming each field as in a regular struct would be verbose or redundant.
*/
struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

/*
Unit-Like Structs Without Any Fields
You can also define structs that don’t have any fields! These are called unit-like structs because they behave similarly to (),
the unit type. Unit-like structs can be useful in situations in which you need to implement a trait on some type
but don’t have any data that you want to store in the type itself.
*/

/*
Rust does include functionality to print out debugging information,
but we have to explicitly opt in to make that functionality available for our struct.
To do that, we add the annotation #[derive(Debug)] just before the struct definition,
*/

// Rust does include functionality to print out debugging information, but we have to explicitly opt in to make that functionality available for our struct.
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        return self.width * self.height;
    }
}

// allow multiple impl blocks
impl Rectangle {
    fn can_hold(&self, another: &Rectangle) -> bool {
        return self.width > another.width && self.height > another.height;
    }

    // Rectangle These are called associated functions because they’re associated with the struct.
    fn square(size: u32) -> Rectangle {
        Rectangle {
            width: size,
            height: size,
        }
    }
}

pub fn test_structs() {
    println!(" --- start test structs ---");

    let user1 = User {
        name: String::from("yuxin"),
        email: String::from("yuxin.sun@outlook.com"),
        sign_in: 1,
        active: true,
    };

    println!(
        "user1 \n name:{}, email:{}, sign_in:{}, active:{}",
        user1.name, user1.email, user1.sign_in, user1.active
    );

    // Creating Instances From Other Instances With Struct Update Syntax
    let user2 = User {
        name: String::from("Jeff"),
        email: String::from("jeff@outlook.com"),
        sign_in: user1.sign_in,
        active: user1.active,
    };

    println!(
        "user2 \n name:{}, email:{}, sign_in:{}, active:{}",
        user2.name, user2.email, user2.sign_in, user2.active
    );

    let user3 = User {
        name: String::from("Michael"),
        email: String::from("Michael.Rache@outlook.com"),
        ..user1
    };

    println!(
        "user3 \n name:{}, email:{}, sign_in:{}, active:{}",
        user3.name, user3.email, user3.sign_in, user3.active
    );

    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);

    println!("black {}, {}, {} ", black.0, black.1, black.2);
    println!("origin {}, {}, {}", origin.0, origin.1, origin.2);

    let m = Rectangle {
        width: 100,
        height: 100,
    };
    println!("m's aera = {}", m.area());
    println!("m can_hold = {}", m.can_hold(&m));
    println!("m square width = {}", Rectangle::square(20).area());

    //  When we have larger structs, it’s useful to have output that’s a bit easier to read; in those cases, we can use {:#?} instead of {:?} in the println! string.
    println!("rect1 is {:?} ", m)
}
