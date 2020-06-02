
/*
    *** Types ***
Rust provides several mechanisms to change or define the type of primitive and user defined types. The following sections cover:

1) Casting between primitive types
2) Specifying the desired type of literals
3) Using type inference
4) Aliasing types



*/

// Suppress all warnings from casts which overflow.
#![allow(overflowing_literals)]


use std::mem;




fn test_type_cast() {
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

/*
    *** Literals ***
Numeric literals can be type annotated by adding the type as a suffix.
As an example, to specify that the literal 42 should have the type i32, write 42i32.

The type of unsuffixed numeric literals will depend on how they are used.
If no constraint exists, the compiler will use i32 for integers, and f64 for floating-point numbers.

There are some concepts used in the previous code that haven't been explained yet, here's a brief explanation for the impatient readers:

    1) fun(&foo) is used to pass an argument to a function by reference, rather than by value (fun(foo)). For more details see borrowing.
    2) std::mem::size_of_val is a function, but called with its full path. Code can be split in logical units called modules.
       In this case, the size_of_val function is defined in the mem module, and the mem module is defined in the std crate. For more details, see modules and crates.
*/

fn test_literal() {
    // Suffixed literals, their types are known at initialization
    let x = 1u8;
    let y = 2u32;
    let z = 3f32;

    // Unsuffixed literal, their types depend on how they are used
    let i = 1;
    let f = 1.0;

    // `size_of_val` returns the size of a variable in bytes
    println!("size of `x` in bytes: {}", std::mem::size_of_val(&x));
    println!("size of `y` in bytes: {}", std::mem::size_of_val(&y));
    println!("size of `z` in bytes: {}", std::mem::size_of_val(&z));
    println!("size of `i` in bytes: {}", std::mem::size_of_val(&i));
    println!("size of `f` in bytes: {}", std::mem::size_of_val(&f));
}

/*
    *** Inference ***
The type inference engine is pretty smart. It does more than looking at the type of the value expression during an initialization.
It also looks at how the variable is used afterwards to infer its type. Here's an advanced example of type inference:
*/

fn test_inference() {
    // Because of the annotation, the compiler knows that `elem` has type u8.
    let elem = 5u8;

    // Create an empty vector (a growable array).
    let mut vec = Vec::new();
    // At this point the compiler doesn't know the exact type of `vec`, it
    // just knows that it's a vector of something (`Vec<_>`).

    // Insert `elem` in the vector.
    vec.push(elem);
    // Aha! Now the compiler knows that `vec` is a vector of `u8`s (`Vec<u8>`)
    // TODO ^ Try commenting out the `vec.push(elem)` line

    println!("{:?}", vec);
}

/*
    *** Aliasing ***
The type statement can be used to give a new name to an existing type. Types must have UpperCamelCase names, or the compiler will raise a warning.
The exception to this rule are the primitive types: usize, f32, etc.
The main use of aliases is to reduce boilerplate; for example the IoResult<T> type is an alias for the Result<T, IoError> type.
*/

// `NanoSecond` is a new name for `u64`.
type NanoSecond = u64;
type Inch = u64;

// Use an attribute to silence warning.
#[allow(non_camel_case_types)]
type u64_t = u64;
// TODO ^ Try removing the attribute

fn test_aliasing() {
    // `NanoSecond` = `Inch` = `u64_t` = `u64`.
    let nanoseconds: NanoSecond = 5 as u64_t;
    let inches: Inch = 2 as u64_t;

    // Note that type aliases *don't* provide any extra type safety, because
    // aliases are *not* new types
    println!("{} nanoseconds + {} inches = {} unit?",
             nanoseconds,
             inches,
             nanoseconds + inches);
}



pub fn test_type() {

    test_type_cast();

    test_literal();

    test_inference();

    test_aliasing();
}