use std::fmt::{self, Display, Formatter};

/*

    *** Formatted print ***
Printing is handled by a series of macros defined in std::fmt some of which include:

1) format!: write formatted text to String
2) print!: same as format! but the text is printed to the console (io::stdout).
3) println!: same as print! but a newline is appended.
4) eprint!: same as format! but the text is printed to the standard error (io::stderr).
5) eprintln!: same as eprint!but a newline is appended.

All parse text in the same fashion. As a plus, Rust checks formatting correctness at compile time.

std::fmt contains many traits which govern the display of text. The base form of two important ones are listed below:

1) fmt::Debug: Uses the {:?} marker. Format text for debugging purposes.
2) fmt::Display: Uses the {} marker. Format text in a more elegant, user friendly fashion.
Here, we used fmt::Display because the std library provides implementations for these types. To print text for custom types, more steps are required.

Implementing the fmt::Display trait automatically implements the ToString trait which allows us to convert the type to String.

Activities
Fix the two issues in the above code (see FIXME) so that it runs without error.
Add a println! macro that prints: Pi is roughly 3.142 by controlling the number of decimal places shown.
For the purposes of this exercise, use let pi = 3.141592 as an estimate for pi.
(Hint: you may need to check the std::fmt documentation for setting the number of decimals to display)

*/

fn test_format_print_basic() {
    // In general, the `{}` will be automatically replaced with any
    // arguments. These will be stringified.
    println!("{} days", 31);

    // Without a suffix, 31 becomes an i32. You can change what type 31 is
    // by providing a suffix.

    // There are various optional patterns this works with. Positional
    // arguments can be used.
    println!("{0}, this is {1}. {1}, this is {0}", "Alice", "Bob");

    // As can named arguments.
    println!(
        "{subject} {verb} {object}",
        object = "the lazy dog",
        subject = "the quick brown fox",
        verb = "jumps over"
    );

    // Special formatting can be specified after a `:`.
    println!(
        "{} of {:b} people know binary, the other half doesn't",
        1, 2
    );

    // You can right-align text with a specified width. This will output
    // "     1". 5 white spaces and a "1".
    println!("{number:>width$}", number = 1, width = 6);

    // You can pad numbers with extra zeroes. This will output "000001".
    println!("{number:>0width$}", number = 1, width = 6);

    // Rust even checks to make sure the correct number of arguments are
    // used.
    println!("My name is {0}, {1} {0}", "Bond", "James");
    // FIXME ^ Add the missing argument: "James"

    // Create a structure named `Structure` which contains an `i32`.
    // #[allow(dead_code)]
    // struct Structure(i32);

    // However, custom types such as this structure require more complicated
    // handling. This will not work.
    // println!("This struct `{}` won't print...", Structure(3));
    // FIXME ^ Comment out this line.
}

/*
    *** Debug ***
All types which want to use std::fmt formatting traits require an implementation to be printable.
Automatic implementations are only provided for types such as in the std library.
All others must be manually implemented somehow.

The fmt::Debug trait makes this very straightforward. All types can derive (automatically create) the fmt::Debug implementation.
This is not true for fmt::Display which must be manually implemented.
*/

// This structure cannot be printed either with `fmt::Display` or
// with `fmt::Debug`.
struct UnPrintable(i32);

// The `derive` attribute automatically creates the implementation
// required to make this `struct` printable with `fmt::Debug`.
#[derive(Debug)]
struct DebugPrintable(i32);

// All std library types automatically are printable with {:?} too:

// Derive the `fmt::Debug` implementation for `Structure`. `Structure`
// is a structure which contains a single `i32`.
#[derive(Debug)]
struct Structure(i32);

// Put a `Structure` inside of the structure `Deep`. Make it printable
// also.
#[derive(Debug)]
struct Deep(Structure);

#[derive(Debug)]
struct Person<'a> {
    name: &'a str,
    age: u8,
}

fn test_debug_format() {
    // Printing with `{:?}` is similar to with `{}`.
    println!("{:?} months in a year.", 12);
    println!(
        "{1:?} {0:?} is the {actor:?} name.",
        "Slater",
        "Christian",
        actor = "actor's"
    );

    // `Structure` is printable!
    println!("Now {:?} will print!", Structure(3));

    // The problem with `derive` is there is no control over how
    // the results look. What if I want this to just show a `7`?
    println!("Now {:?} will print!", Deep(Structure(7)));

    // So fmt::Debug definitely makes this printable but sacrifices some elegance. Rust also provides "pretty printing" with {:#?}.
    let name = "Peter";
    let age = 27;
    let peter = Person { name, age };

    // Pretty print
    println!("{:#?}", peter);
}

/*
    *** Display ***
fmt::Debug hardly looks compact and clean, so it is often advantageous to customize the output appearance.
This is done by manually implementing fmt::Display, which uses the {} print marker. Implementing it looks like this:

fmt::Display may be cleaner than fmt::Debug but this presents a problem for the std library.
How should ambiguous types be displayed? For example, if the std library implemented a single style for all Vec<T>, what style should it be? Would it be either of these two?

Vec<path>: /:/etc:/home/username:/bin (split on :)
Vec<number>: 1,2,3 (split on ,)
No, because there is no ideal style for all types and the std library doesn't presume to dictate one.
fmt::Display is not implemented for Vec<T> or for any other generic containers. fmt::Debug must then be used for these generic cases.

This is not a problem though because for any new container type which is not generic,fmt::Display can be implemented.

*/
// Import (via `use`) the `fmt` module to make it available.
// use std::fmt;

// Define a structure for which `fmt::Display` will be implemented. This is
// a tuple struct named `Structure` that contains an `i32`.
// struct Structure(i32);

// To use the `{}` marker, the trait `fmt::Display` must be implemented
// manually for the type.
impl fmt::Display for Structure {
    // This trait requires `fmt` with this exact signature.
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Write strictly the first element into the supplied output
        // stream: `f`. Returns `fmt::Result` which indicates whether the
        // operation succeeded or failed. Note that `write!` uses syntax which
        // is very similar to `println!`.
        write!(f, "{}", self.0)
    }
}

// A structure holding two numbers. `Debug` will be derived so the results can
// be contrasted with `Display`.
#[derive(Debug)]
struct MinMax(i64, i64);

// Implement `Display` for `MinMax`.
impl fmt::Display for MinMax {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Use `self.number` to refer to each positional data point.
        write!(f, "({}, {})", self.0, self.1)
    }
}

// Define a structure where the fields are nameable for comparison.
#[derive(Debug)]
struct Point2D {
    x: f64,
    y: f64,
}

// Similarly, implement `Display` for `Point2D`
impl fmt::Display for Point2D {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Customize so only `x` and `y` are denoted.
        write!(f, "x: {}, y: {}", self.x, self.y)
    }
}

fn test_display_basic() {
    let minmax = MinMax(0, 14);

    println!("Compare structures:");
    println!("Display: {}", minmax);
    println!("Debug: {:?}", minmax);

    let big_range = MinMax(-300, 300);
    let small_range = MinMax(-3, 3);

    println!(
        "The big range is {big} and the small is {small}",
        small = small_range,
        big = big_range
    );

    let point = Point2D { x: 3.3, y: 7.2 };

    println!("Compare points:");
    println!("Display: {}", point);
    println!("Debug: {:?}", point);

    // Error. Both `Debug` and `Display` were implemented, but `{:b}`
    // requires `fmt::Binary` to be implemented. This will not work.
    // println!("What does Point2D look like in binary: {:b}?", point);

    //  *** fmt.binary ***
    // So, fmt::Display has been implemented but fmt::Binary has not, and therefore cannot be used. std::fmt has many such traits and each requires its own implementation.
    // This is detailed further in std::fmt.
}

/*
    *** Formatting ***
We've seen that formatting is specified via a format string:

format!("{}", foo) -> "3735928559"
format!("0x{:X}", foo) -> "0xDEADBEEF"
format!("0o{:o}", foo) -> "0o33653337357"
The same variable (foo) can be formatted differently depending on which argument type is used: X vs o vs unspecified.

This formatting functionality is implemented via traits, and there is one trait for each argument type.
The most common formatting trait is Display, which handles cases where the argument type is left unspecified: {} for instance.
*/

struct City {
    name: &'static str,
    // Latitude
    lat: f32,
    // Longitude
    lon: f32,
}

impl Display for City {
    // `f` is a buffer, and this method must write the formatted string into it
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        let lat_c = if self.lat >= 0.0 { 'N' } else { 'S' };
        let lon_c = if self.lon >= 0.0 { 'E' } else { 'W' };

        // `write!` is like `format!`, but it will write the formatted string
        // into a buffer (the first argument)
        write!(
            f,
            "{}: {:.3}°{} {:.3}°{}",
            self.name,
            self.lat.abs(),
            lat_c,
            self.lon.abs(),
            lon_c
        )
    }
}

#[derive(Debug)]
struct Color {
    red: u8,
    green: u8,
    blue: u8,
}

fn test_formatting_basic() {
    for city in [
        City { name: "Dublin", lat: 53.347778, lon: -6.259722 },
        City { name: "Oslo", lat: 59.95, lon: 10.75 },
        City { name: "Vancouver", lat: 49.25, lon: -123.1 },
    ].iter() {
        println!("{}", *city);
    }
    for color in [
        Color { red: 128, green: 255, blue: 90 },
        Color { red: 0, green: 3, blue: 254 },
        Color { red: 0, green: 0, blue: 0 },
    ].iter() {
        // Switch this to use {} once you've added an implementation
        // for fmt::Display.
        println!("{:?}", *color);
    }
}

/*
Formatting traits
When requesting that an argument be formatted with a particular type, you are actually requesting that an argument ascribes to a particular trait.
This allows multiple actual types to be formatted via {:x} (like i8 as well as isize). The current mapping of types to traits is:

nothing ⇒ Display
? ⇒ Debug
x? ⇒ Debug with lower-case hexadecimal integers
X? ⇒ Debug with upper-case hexadecimal integers
o ⇒ Octal
x ⇒ LowerHex
X ⇒ UpperHex
p ⇒ Pointer
b ⇒ Binary
e ⇒ LowerExp
E ⇒ UpperExp
*/


pub fn test_format_print() {
    test_format_print_basic();

    test_debug_format();

    test_display_basic();

    test_formatting_basic();
}
