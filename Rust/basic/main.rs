use std::io;
mod slice;
mod owenership;
mod enums;
mod structs;
mod syntax;
mod test_collectors;
mod test_string;
mod test_hashmap;

fn main() {

    println!("--- Starting RUST syntax ---");

    syntax::test_syntax();

    slice::test_slice();

    owenership::test_owenership();

    enums::test_enums();

    structs::test_structs();

    test_collectors::test_collectors();

    test_string::test_string();

    test_hashmap::test_hashmap();
}