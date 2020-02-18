// #![deny(warning, missing_docs)]
mod closure;
mod enums;
mod function_pointer;
mod generic;
mod owenership;
mod pattern;
mod slice;
mod structs;
mod syntax;
mod test_advance_trait;
mod test_binaryheap;
mod test_box;
mod test_btree;
mod test_collectors;
mod test_errorhandling;
mod test_hashmap;
mod test_hashset;
mod test_json;
mod test_json_serde;
mod test_linkedlist;
mod test_list;
mod test_macro;
mod test_module;
mod test_network;
mod test_option;
mod test_result;
mod test_refcell;
mod test_smart_pointer;
mod test_string;
mod test_thread;
mod test_vec;
mod test_vecdeque;
mod traits;

fn main() {
    println!("--- Starting RUST syntax ---");

    test_binaryheap::test_binaryheap();

    test_option::test_option();

    test_result::test_result();

    test_hashset::test_hashset();

    test_linkedlist::test_linkedlist();

    test_vecdeque::test_vecdeque();

    test_btree::test_btree();

    test_box::test_box();

    test_vec::test_vec();

    test_refcell::test_ref_cell();

    test_json_serde::test_json_serde();

    test_json::test_json();

    test_module::test_modules();

    test_advance_trait::test_advance_trait();

    test_network::test_network();

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
