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
mod test_crate_model;
mod test_errorhandling;
mod test_format_print;
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
mod test_pattern_matching;
mod test_rc;
mod test_refcell;
mod test_result;
mod test_smart_pointer;
mod test_smart_pointer_refer_cycle;
mod test_string;
mod test_thread;
mod test_trait;
mod test_unsafe;
mod test_vec;
mod test_vecdeque;
mod traits;
mod test_primitives;
mod test_type;
mod test_conversion;
mod test_flow_control;
mod test_function;
mod test_extern_crate;
mod test_rary;
mod test_generic;
mod test_scoping_rules;
mod test_pin;
mod test_ops;

// mod. will import each one into the main.rs and be compiled. if not doing this, it could not be compiled and use by others.


fn main() {
    println!("--- Starting RUST syntax ---");

    test_ops::test_ops();

    test_binaryheap::test_binaryheap();

    test_trait::test_traits_basic();

    test_option::test_option();

    test_result::test_result();

    test_hashset::test_hashset();

    test_linkedlist::test_linkedlist();

    test_crate_model::test_crate_model();

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

    test_smart_pointer_refer_cycle::test_reference_cycle();

    test_rc::test_rc();

    test_pattern_matching::test_pattern_match();

    test_unsafe::test_unsafe();

    test_format_print::test_format_print();

    test_primitives::test_primitive();

    test_type::test_type();

    test_conversion::test_conversions();

    test_flow_control::test_flow_control();

    test_function::test_functions();

    test_extern_crate::test_extern_crate();

    test_generic::test_generic();

    test_scoping_rules::test_scoping_rules();

    test_pin::test_pin();
}
