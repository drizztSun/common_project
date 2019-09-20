mod slice;
mod owenership;
mod enums;
mod structs;
mod syntax;
mod generic;
mod test_collectors;
mod test_string;
mod test_hashmap;
mod traits;
mod closure;
mod test_errorhandling;
mod test_smart_pointer;
mod test_list;
mod test_thread;
mod pattern;
mod function_pointer;
mod test_macro;

fn main() {

    println!("--- Starting RUST syntax ---");

    syntax::test_syntax();

    slice::test_slice();

    owenership::test_owenership();

    enums::test_enums();

    structs::test_structs();

    generic::test_generic();

    traits::test_traits();

    closure::test_closure();

    pattern::test_pattern();

    test_macro::test_macro();

    function_pointer::test_function_pointer();

    test_collectors::test_collectors();

    test_string::test_string();

    test_hashmap::test_hashmap();

    test_errorhandling::test_errorhandling();

    test_smart_pointer::test_smart_pointer();

    test_list::test_list();

    test_thread::test_thread();
}