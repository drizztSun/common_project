extern crate wasm_bindgen;

use wasm_bindgen::prelude::*;


// The bit inside the #[ ] is called an "attribute", and it modifies the next statement somehow. 
// In this case, that statement is an extern, which tells Rust that we want to call some externally defined functions. 
// The attribute says "wasm-bindgen knows how to find these functions".
#[wasm_bindgen]
extern{
    pub fn alert(s: &str);
}

#[wasm_bindgen]
pub fn greet(name: &str) {
    alert(&format!("Hello, {} !", &name));
}