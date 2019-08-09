#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);

        let m = crate::tests::hosting::add_to_waitlist();
        println!("absolute path = {}", m);

        let n = tests::hosting::add_to_waitlist();
        println!("relative path = {}", n);
    }

    /*
    Modules let us organize code within a crate into groups for readability and easy reuse. 
    Modules also control the privacy of items, which is whether an item can be used by outside code (public) or 
    whether it’s an internal implementation detail and not available for outside use (private).

    A path can take two forms:

    An absolute path starts from a crate root by using a crate name or a literal crate.
    A relative path starts from the current module and uses self, super, or an identifier in the current module.
    Both absolute and relative paths are followed by one or more identifiers separated by double colons (::).
    */
    mod hosting {
        pub fn add_to_waitlist() -> String {
            return String::from("add_to_waitlist");
        }

        fn seat_at_table() -> String {
            return String::from("seat_at_table");
        }
    }

    mod serving {
        pub fn take_order() -> String {
            return String::from("Take_order");
        }

        fn serve_order() -> String {
            return String::from("serve_order");
        }

        fn take_payment() -> String {
            return String::from("take_payment");
        }
    }
}

// absolute short way to show package import
use crate::tests::hosting::add_to_waitlist;

// relative short way
use self::tests::hosting;

pub fn test_modref() {
    let m = hosting::add_to_waitlist();
    println!("result = {}", m);

    let n = add_to_waitlist();
    println!("result = {}", n);    
}