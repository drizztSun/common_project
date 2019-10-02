
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
        pub(in crate::my_mod) fn public_func_in_my_mod() {
            println!("Calling 'my_mod::nest_mod::public_func()'");
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
        nest_mod::public_function_in_my_mod();
        print!("> ");
        nest_mod::public_func_in_super_mode();
        nest_mod::public_func_in_nested();
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

pub fn test_modules() {

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