extern crate wasm_bindgen;
// The first line says "hey Rust, we're using a library called wasm_bindgen." 
// Libraries are called "crates" in Rust, and we're using an external one, so we use the extern keyword.

// we're importing everything in the wasm_bindgen::prelude module
// wasm-pack uses wasm-bindgen, another tool, to provide a bridge between the types of JavaScript and Rust. 
// It allows JavaScript to call a Rust API with a string, or a Rust function to catch a JavaScript exception.
use wasm_bindgen::prelude::*;


// The bit inside the #[ ] is called an "attribute", and it modifies the next statement somehow. 
// In this case, that statement is an extern, which tells Rust that we want to call some externally defined functions. 
// The attribute says "wasm-bindgen knows how to find these functions".
#[wasm_bindgen]
extern{
    pub fn alert(s: &str);
}

// Once again, we see the #[wasm_bindgen] attribute. In this case, it's not modifying an extern block, but a fn; 
// this means that we want this Rust function to be able to be called by JavaScript. 
// It's the opposite of extern: these aren't the functions we need, but rather the functions we're giving out to the world.
#[wasm_bindgen]
pub fn greet(name: &str) {
    alert(&format!("Hello {}", name));
}