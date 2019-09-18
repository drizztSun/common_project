// Function Pointers
// We’ve talked about how to pass closures to functions; you can also pass regular functions to functions! 
// This technique is useful when you want to pass a function you’ve already defined rather than defining a new closure. 
// Doing this with function pointers will allow you to use functions as arguments to other functions. 
// Functions coerce to the type fn (with a lowercase f), not to be confused with the Fn closure trait. 
// The fn type is called a function pointer. 
// The syntax for specifying that a parameter is a function pointer is similar to that of closures,

// Unlike closures, fn is a type rather than a trait, so we specify fn as the parameter type directly 
// rather than declaring a generic type parameter with one of the Fn traits as a trait bound.

fn add_one(a: i32) -> i32 {
    a + 1
}

fn do_twice(func: fn(i32)->i32, num: i32) -> i32 {
    add_one(num) + add_one(num)
}

fn test_function_pointer_basic() {

    let anwser = do_twice(add_one, 5);
    println!("anwser = {}", anwser);
}

// Function pointers implement all three of the closure traits (Fn, FnMut, and FnOnce), 
// so you can always pass a function pointer as an argument for a function that expects a closure. 
// It’s best to write functions using a generic type and one of the closure traits so your functions can accept either functions or closures.

// An example of where you would want to only accept fn and not closures is when interfacing with external code that doesn’t have closures:
// C functions can accept functions as arguments, but C doesn’t have closures.

// As an example of where you could use either a closure defined inline or a named function, 
// let’s look at a use of map. To use the map function to turn a vector of numbers into a vector of strings, we could use a closure, 
// like this:
fn test_function_call() {
    
    {
        let list_of_nums = vec![1, 2, 3, 4, 5];
        let list_of_strings: Vec<String> = list_of_nums.iter().map(|i| i.to_string()).collect();

        println!("nums : {:?}", list_of_nums);
        println!("nums str: {:?}", list_of_strings);
    }

    {
        let list_of_nums = vec![1, 2, 3];
        let list_of_strings: Vec<String> = list_of_nums.iter().map(ToString::to_string).collect();

        println!("nums : {:?}", list_of_nums);
        println!("nums str: {:?}", list_of_strings);
    }
}

fn test_return_closure() {

}

pub fn test_function_pointer() {

    test_function_pointer_basic();

    test_return_closure();
}