
/*
        *** use declaration ***

The use declaration can be used to bind a full path to a new name, for easier access. It is often used like this:
extern crate deeply; // normally, this would exist and not be commented out!

use crate::deeply::nested::{
    my_first_function,
    my_second_function,
    AndATraitType
};

You can use the as keyword to bind imports to a different name:

// Bind the `deeply::nested::function` path to `other_function`.
use deeply::nested::function as other_function;

fn function() {
    println!("called `function()`");
}

mod deeply {
    pub mod nested {
        pub fn function() {
            println!("called `deeply::nested::function()`");
        }
    }
}

fn main() {
    // Easier access to `deeply::nested::function`
    other_function();

    println!("Entering block");
    {
        // This is equivalent to `use deeply::nested::function as function`.
        // This `function()` will shadow the outer one.
        use crate::deeply::nested::function;
        function();

        // `use` bindings have a local scope. In this case, the
        // shadowing of `function()` is only in this block.
        println!("Leaving block");
    }

    function();
}
*/

/*
        *** Visibility ***
By default, the items in a module have private visibility, but this can be overridden with the pub modifier.
Only the public items of a module can be accessed from outside the module scope.
*/
// A mod named "my_mod"
mod my_mod {

    // Item in mod by default is private and invisible outside
    fn private_func() {
        println!("Calling 'my_mod::private_function()'");
    }

    // Use the 'pub' modifier to overwrite the default visibility
    pub fn function() {
        println!("Calling 'my_mod::public_function()'");
    }

    // Item can access other items in the same modules
    // even they are private and invisible
    pub fn indirect_access() {
        println!("Calling 'my_mod::indirect_access()'");
        println!("indirect access to private function");
        private_func();
    }

    // mod can be nested, pub is visible outside parent
    pub mod nest_mod {

        pub fn function() {
            println!("Calling 'my_mod::nest_mod::function()'");
        }

        #[allow(dead_code)]
        fn private_function() {
            println!("Calling 'my_mod::nest_mod::private_function()'");
        }

        // Functions declared using `pub(in path)` syntax are only visible
        // within the given path. `path` must be a parent or ancestor module
        pub(in crate::test_module::my_mod) fn public_func_in_my_mod() {
            println!("Calling 'my_mod::nest_mod::public_func()'");
            public_func_in_nested();
        }

        // Functions declared using `pub(self)` syntax are only visible within
        // the current module, which is the same as leaving them private
        pub(self) fn public_func_in_nested() {
            println!("Calling 'my_mod::nest_mod::public_func_in_nested()'");
        }

        // Functions declared using `pub(super)` syntax are only visible within
        // the parent module
        pub(super) fn public_func_in_super_mode() {
            println!("Calling 'my_mod::nest_mod::public_func_in_super_mode()'");
        }
    }

    pub fn call_public_function_in_my_mod() {
        print!("Calling 'my_mod::call_public_function_in_my_mod()', that \n> ");
        nest_mod::public_func_in_my_mod();
        print!("> ");
        nest_mod::public_func_in_super_mode();
        // nest_mod::public_func_in_nested(); // error because it is private, or pub(self)
    }

    // pub(crate) makes functions visible only within the current crate
    pub(crate) fn public_function_in_crate() {
        println!("Calling 'my_mod::public_function_in_crate()'");
    }

    // Nested modules follow the same rules for visibility
    mod privated_nested {
        #[allow(dead_code)]
        pub fn function() {
            println!("Calling 'my_mod::privated_nested::function()'");
        }

        // Private parent items will still restrict the visibility of a child item,
        // even if it is declared as visible within a bigger scope.
        pub(crate) fn restricted_function() {
            println!("Calling 'my_mod::private_nested::restricted_function()'");
        }
    }
}

fn function() {
    println!("Calling 'function()");
}

/*
    *** Structv Visibility ***
Structs have an extra level of visibility with their fields.
The visibility defaults to private, and can be overridden with the pub modifier.
This visibility only matters when a struct is accessed from outside the module where it is defined,
and has the goal of hiding information (encapsulation).
*/
mod my {

    // A public struct with a public filed of generic type 'T'
    pub struct OpenBox<T> {
        pub content: T,
    }

    // A public struct with a private field of generic type 'T'
    #[allow(dead_code)]
    pub struct CloseBox<T> {
        content: T,
    }

    impl<T> CloseBox<T> {
        // A public constructor method
        pub fn new(contents: T) -> CloseBox<T> {
            CloseBox { content: contents }
        }
    }
}

fn test_visibility_struct() {
    // Public structs with public fields can be constructed as usual
    let open_box = my::OpenBox {
        content: "public information",
    };

    // and their fields can be normally accessed.
    println!("The open box contains: {}", open_box.content);

    // Public structs with private fields cannot be constructed using field names.
    // Error! `ClosedBox` has private fields
    //let closed_box = my::ClosedBox { contents: "classified information" };
    // TODO ^ Try uncommenting this line

    // However, structs with private fields can be created using
    // public constructors
    let _closed_box = my::CloseBox::new("classified information");

    // and the private fields of a public struct cannot be accessed.
    // Error! The `contents` field is private
    //println!("The closed box contains: {}", _closed_box.contents);
    // TODO ^ Try uncommenting this line
}

fn test_visibility() {
    // Modules allow disambiguation between items that have the same name.
    function();

    my_mod::function();

    // Public items, including those inside nested modules, can be
    // accessed from outside the parent module.
    my_mod::function();
    my_mod::nest_mod::function();
    my_mod::call_public_function_in_my_mod();

    my_mod::indirect_access();

    // pub(crate) items can be called from anywhere in the same crate
    my_mod::public_function_in_crate();

    // pub(in path) items can only be called from within the mode specified
    // Error! function `public_function_in_my_mod` is private
    //my_mod::nest_mod::public_function_in_my_mod();
    // TODO ^ Try uncommenting this line

    // Private items of a module cannot be directly accessed, even if
    // nested in a public module:

    // Error! `private_function` is private
    //my_mod::private_function();
    // TODO ^ Try uncommenting this line

    // Error! `private_function` is private
    //my_mod::nest_mod::private_function();
    // TODO ^ Try uncommenting this line

    // Error! `private_nested` is a private module
    //my_mod::private_nested::function();
    // TODO ^ Try uncommenting this line

    // Error! `private_nested` is a private module
    //my_mod::private_nested::restricted_function();
    // TODO ^ Try uncommenting this line
}

/*
    *** super and self ***
The super and self keywords can be used in the path to remove ambiguity when accessing items and to prevent unnecessary hardcoding of paths.
*/

mod cool {
    pub fn function() {
        println!("called `cool::function()`");
    }
}

mod my_cool {
    fn function() {
        println!("called `my::function()`");
    }

    mod cool {
        pub fn function() {
            println!("called `my::cool::function()`");
        }
    }

    pub fn indirect_call() {
        // Let's access all the functions named `function` from this scope!
        print!("called `my::indirect_call()`, that\n> ");

        // The `self` keyword refers to the current module scope - in this case `my`.
        // Calling `self::function()` and calling `function()` directly both give
        // the same result, because they refer to the same function.
        self::function();
        function();

        // We can also use `self` to access another module inside `my`:
        self::cool::function();

        // The `super` keyword refers to the parent scope (outside the `my` module).
        super::function();

        // This will bind to the `cool::function` in the *crate* scope.
        // In this case the crate scope is the outermost scope.
        {
            use crate::test_module::cool::function as root_function;
            root_function();
        }
    }
}

pub fn test_modules() {
    test_visibility();

    test_visibility_struct();

    my_cool::indirect_call();
}
