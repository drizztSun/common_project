use std::io;
mod slice;
mod owenership;
mod enums;
mod structs;
mod syntax;

fn main() {

    println!("--- Starting RUST syntax ---");

    syntax::test_syntax();

    slice::test_slice();

    owenership::test_owenership();

    enums::test_enums();

    structs::test_structs();
}