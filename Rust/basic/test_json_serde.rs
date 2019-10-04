extern crate serde_json;
extern crate serde;

use serde_json::Value as jsonValue;
use serde_json::json;
use serde_json::Result;
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize)]
struct Address {
    street: String,
    city: String,
}

// Any type that implements Serde's Serialize trait can be serialized this way. 
// This includes built-in Rust standard library types like Vec<T> and HashMap<K, V>, as well as any structs or enums annotated with #[derive(Serialize)].
fn test_json_by_serielizing_data_struct() {
    // Some data structure.
    let address = Address {
        street: "10 Downing Street".to_owned(),
        city: "London".to_owned(),
    };

    // Serialize it to a JSON string.
    let j = serde_json::to_string(&address).unwrap();

    // Print, write to a file, or send to an HTTP server.
    println!("{}", j);
}

fn test_json_serde_from_str() {

    let content = r#"
        {
            "name": "John Doe",
            "age": 43,
            "phones": [
                "+11 1234567",
                "+11 6789101"
            ]
        }
    "#;

    let v: jsonValue = serde_json::from_str(content).unwrap();

    println!("name: {}, age: {}, phones: {}", v["name"], v["age"], v["phones"]);

    println!("{}", v.to_string());

    
    let john = json!({
        "name": "John Doe",
        "age": 43,
        "phones": [
            "+44 1234567",
            "+44 2345678"
        ]
    });

    println!("first phone number: {}", john["phones"][0]);

    // Convert to a string of JSON and print it out
    println!("{}", john.to_string());
}


// *** Parsing JSON as strongly typed data structures
#[derive(Serialize, Deserialize)]
struct Person {
    name: String,
    age: u8,
    phones: Vec<String>,
}

fn test_json_serde_from_strong_type() {

    let content = r#"
        {
            "name": "John Doe",
            "age": 43,
            "phones": [
                "+11 1234567",
                "+11 6789101"
            ]
        }
    "#;

    let v: Person = serde_json::from_str(content).unwrap();

    println!("Pleace call {} at the number {}", v.name, v.phones[1]);

    {

    }
}




pub fn test_json_serde() {
    // Serde JSON provides a json! macro to build serde_json::Value objects with very natural JSON syntax.

    test_json_serde_from_str();

    test_json_serde_from_strong_type();
}
