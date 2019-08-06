
struct user {
    name: String,
    email: String,
    sign_in: u64,
    active: bool,
};

// tuple structs
/* 
Using Tuple Structs without Named Fields to Create Different Types
You can also define structs that look similar to tuples, called tuple structs. 
Tuple structs have the added meaning the struct name provides but don’t have names associated with their fields; 
rather, they just have the types of the fields. Tuple structs are useful 
when you want to give the whole tuple a name and make the tuple be a different type from other tuples, 
and naming each field as in a regular struct would be verbose or redundant.
*/
struct color(i32, i32, i32);
struct point(i32, i32, i32);

/* 
Unit-Like Structs Without Any Fields
You can also define structs that don’t have any fields! These are called unit-like structs because they behave similarly to (), 
the unit type. Unit-like structs can be useful in situations in which you need to implement a trait on some type 
but don’t have any data that you want to store in the type itself. 
*/

#[derive(Debug)]
struct Rectangle{
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height;
    }
}

// allow multiple impl blocks
impl Rectangle {
    fn can_hold(&self, another: &Rectangle) -> bool {
        self.width > another.width && self.height > another.height;
    }

    // Rectangle These are called associated functions because they’re associated with the struct.
    fn square(size: u32) -> Rectangle {
        Rectangle {width: size, height: size}
    }
}

fn test_structs() {

    let user1 = user {
        name: String::from("yuxin"),
        email: String::from("yuxin.sun@outlook.com"),
        sign_in: 1,
        active: true,
    };

    let user2 = user {
        name: String::from("Jeff"),
        email: String::from("jeff@outlook.com"),
        sign_in: user1.sign_in,
        active: user1.active,
    };

    let user3 = user {
        name: String::from("Michael"),
        email: String::from("Michael.Rache@outlook.com"),
        ..user1
    };

    let black = color(0, 0, 0);
    let origin = Point(0, 0, 0);


}