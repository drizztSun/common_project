// Suppress all warnings from casts which overflow. must be put in the very begining
#![allow(overflowing_literals)]

pub mod test_mod{

    pub fn test_func() {

    }
}

fn test_casting() {
    // Casting
    // Rust provides no implicit type conversion (coercion) between primitive types. But, explicit type conversion (casting) can be performed using the as keyword.

    // Rules for converting between integral types follow C conventions generally, except in cases where C has undefined behavior.
    // The behavior of all casts between integral types is well defined in Rust.
    let decimal = 65.4321_f32;

    // Error! No implicit conversion
    // let integer: u8 = decimal;
    // FIXME ^ Comment out this line

    // Explicit conversion
    let integer = decimal as u8;
    let character = integer as char;

    println!("Casting: {} -> {} -> {}", decimal, integer, character);

    // when casting any value to an unsigned type, T,
    // std::T::MAX + 1 is added or subtracted until the value
    // fits into the new type

    // 1000 already fits in a u16
    println!("1000 as a u16 is: {}", 1000 as u16);

    // 1000 - 256 - 256 - 256 = 232
    // Under the hood, the first 8 least significant bits (LSB) are kept,
    // while the rest towards the most significant bit (MSB) get truncated.
    println!("1000 as a u8 is : {}", 1000 as u8);
    // -1 + 256 = 255
    println!("  -1 as a u8 is : {}", (-1i8) as u8);

    // For positive numbers, this is the same as the modulus
    println!("1000 mod 256 is : {}", 1000 % 256);

    // When casting to a signed type, the (bitwise) result is the same as
    // first casting to the corresponding unsigned type. If the most significant
    // bit of that value is 1, then the value is negative.

    // Unless it already fits, of course.
    println!(" 128 as a i16 is: {}", 128 as i16);
    // 128 as u8 -> 128, whose two's complement in eight bits is:
    println!(" 128 as a i8 is : {}", 128 as i8);

    // repeating the example above
    // 1000 as u8 -> 232
    println!("1000 as a u8 is : {}", 1000 as u8);
    // and the two's complement of 232 is -24
    println!(" 232 as a i8 is : {}", 232 as i8);
}

fn test_if(number: i32) {
    if number % 4 == 0 {
        println!("number is divided by 4");
    } else if number % 3 == 0 {
        println!("number is divided by 3");
    } else if number % 2 == 0 {
        println!("number is divided by 2");
    } else {
        println!("number is divided by 4, 3, 2")
    }

    // use if in let Statement
    let condition = true;
    let num = if condition { 5 } else { 6 };

    println!("num is {}", num);
}

fn test_loop() {
    let mut i = 0;
    // loop
    loop {
        println!(" i == {}", i);
        if i == 5 {
            break;
        }
        i += 1;
    }

    // return value from loops
    let mut count = 1;
    let res = loop {
        count += 1;
        if count == 5 {
            break count * 2;
        }
    };
    println!("res = {}", res);

    // condition loop with while
    let mut number = 3;
    while number != 0 {
        number -= 1;
        println!("number = {}", number);
    }

    // looping throught a collection with for
    let a = [10, 20, 30, 40, 50];
    for element in a.iter() {
        println!("the value is : {}", element);
    }

    // reverse
    for number in (1..4).rev() {
        println!("the value is : {}", number);
    }
}

// define a function
fn add(a: i32, b: i32) -> i32 {
    println!("a + b = {} ", a + b);
    return a + b;
}

fn test_data_type() {
    println!("---- variable and const, Type---");
    // const numbers
    const NUMI8: i8 = 127;
    const NUMU8: u8 = 128;
    const NUMI16: i16 = 100;
    const NUMU16: u16 = 200;
    const NUMI32: i32 = 300;
    const NUMU32: u32 = 400;
    const NUMI64: i64 = 500;
    const NUMU64: u64 = 600;
    const NUMI128: i128 = 700;
    const NUMU128: u128 = 800;

    println!("i8 min:{}, max:{}", std::i8::MIN, std::i8::MAX);
    println!("u8 min:{}, max:{}", std::u8::MIN, std::u8::MAX);

    println!("i16 min:{}, max:{}", std::i16::MIN, std::i16::MAX);
    println!("u16 min:{}, max:{}", std::u16::MIN, std::u16::MAX);

    println!("i32 min:{}, max:{}", std::i32::MIN, std::i32::MAX);
    println!("u32 min:{}, max:{}", std::u32::MIN, std::u32::MAX);

    println!("i64 min:{}, max:{}", std::i64::MIN, std::i64::MAX);
    println!("u64 min:{}, max:{}", std::u64::MIN, std::u64::MAX);

    println!("i128 min:{}, max:{}", std::i128::MIN, std::i128::MAX);
    println!("u128 min:{}, max:{}", std::u128::MIN, std::u128::MAX);

    println!("f32 min:{}, max:{}", std::f32::MIN, std::f32::MAX);
    println!("f64 min:{}, max:{}", std::f64::MIN, std::f64::MAX);

    //
    // Decimal	        98_222
    // Hex	            0xff
    // Octal	        0o77
    // Binary	        0b1111_0000
    // Byte (u8 only)	b'A'

    println!(
        "NUMI8 = {} \n, NUMU8 = {}, \n, NUMI16 = {} \n, NUMU16 = {} \n, NUMI32 = {} \n,
        NUMU32 = {} \n, NUMI64 = {},\n NUMU64 = {},\n NUMI128 = {}, \n NUMU128 = {}\n",
        NUMI8, NUMU8, NUMI16, NUMU16, NUMI32, NUMU32, NUMI64, NUMU64, NUMI128, NUMU128
    );

    {
        // addition
        let sum = 5 + 10;

        // subtraction
        let difference = 95.5 - 4.3;

        // multiplication
        let product = 4 * 30;

        // division
        let quotient = 56.7 / 32.2;

        // remainder
        let remainder = 43 % 5;

        println!(
            "sum : {}, difference: {}, product: {}, quotient: {}, remainder: {}",
            sum, difference, product, quotient, remainder
        )
    }

    // const bool
    const TBOOL: bool = true;
    let t = false;

    println!("TBOOL {}, t {}", TBOOL, t);

    // const Character
    // Rust’s char type is four bytes in size and represents a Unicode Scalar Value, which means it can represent a lot more than just ASCII.
    // Accented letters; Chinese, Japanese, and Korean characters; emoji; and zero-width spaces are all valid char values in Rust.
    // Unicode Scalar Values range from U+0000 to U+D7FF and U+E000 to U+10FFFF inclusive.
    // However, a “character” isn’t really a concept in Unicode, so your human intuition for what a “character” is may not match up with what a char is in Rust.
    let c = 'z';
    let z = 'ℤ';
    let heart_eyed_cat = '😻';

    println!("c: {}, z: {}. heart_eyed_cat: {}", c, z, heart_eyed_cat);

    let x = String::new();

    let mut y = 10;
    let x = y;
    y = 100;

    println!("y was {}, now is {}", x, y);

    println!(" --- shadowing --- ");
    // shadowing means creating a new varialbe and covering old one, by each 'let'
    let z = 10;
    let z = z + 1;
    let z = z * 2;
    println!("z is {}", z);

    // Compound Types
    // Compound types can group multiple values into one type. Rust has two primitive compound types: tuples and arrays.

    // The Tuple Type
    // A tuple is a general way of grouping together some number of other values with a variety of types into one compound type.
    // Tuples have a fixed length: once declared, they cannot grow or shrink in size.

    // tuple
    let tup: (i32, f64, u8) = (500, 0.64, 1);
    println!("tup, 0 {} 1 {} 2 {}", tup.0, tup.1, tup.2);

    let (i1, i2, i3) = tup;
    println!("tup, i1 {}, i2 {}, i3 {}", i1, i2, i3);

    // array
    // Another way to have a collection of multiple values is with an array.
    // Unlike a tuple, every element of an array must have the same type.
    // Arrays in Rust are different from arrays in some other languages because arrays in Rust have a fixed length, like tuples.
    println!(" --- Array --- ");
    let months = [
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December",
    ];

    let a: [i32; 5] = [1, 2, 3, 4, 5];

    for b in months.iter() {
        print!("{}", b)
    }
    println!("");

    for c in a.iter() {
        println!("a : {}", c)
    }

    let d = [3; 5];
    for c in d.iter() {
        println!("c : {}", c)
    }

    println!("")
}

fn test_ownership() {
    let s1 = String::from("Hello");
    let s2 = s1;

    println!("--- heap object copy behavior ---");
    println!(
        " normally move value from one to another, aka shallow copy, but clone will deep copy"
    );

    // right now, s1 will be empty and s2 will take what was in s1
    // s1 had been moved into s2
    println!("s2 is {}", s2);

    // Ways Variables and Data Interact: Clone
    // deeply copy should use clone
    let c1 = String::from("Hello");
    let c2 = c1.clone();

    println!("c1 = {}, c2 = {}", c1, c2);

    //
    println!(" --- stack only behavior --- ");
    println!("stack objecrs only copy value ");

    /*
    So what types are Copy? You can check the documentation for the given type to be sure, but as a general rule,
    any group of simple scalar values can be Copy, and nothing that requires allocation or is some form of resource is Copy.
    Here are some of the types that are Copy:

    All the integer types, such as u32.
    The Boolean type, bool, with values true and false.
    All the floating point types, such as f64.
    The character type, char.
    Tuples, if they only contain types that are also Copy. For example, (i32, i32) is Copy, but (i32, String) is not.
     */

    let x = 5;
    let y = x;
    println!("x = {}, y = {}", x, y);
}

pub fn test_syntax() {
    test_data_type();

    test_if(100);

    test_loop();

    test_ownership();

    test_casting()
}
