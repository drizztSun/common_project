use std::thread;
use std::time::Duration;

/*
Closures don’t require you to annotate the types of the parameters or the return value like fn functions do.
Type annotations are required on functions because they’re part of an explicit interface exposed to your users.
Defining this interface rigidly is important for ensuring that everyone agrees on what types of values a function uses and returns.
But closures aren’t used in an exposed interface like this:
they’re stored in variables and used without naming them and exposing them to users of our library.

Closures are usually short and relevant only within a narrow context rather than in any arbitrary scenario.
Within these limited contexts, the compiler is reliably able to infer the types of the parameters and the return type,
similar to how it’s able to infer the types of most variables.

Making programmers annotate the types in these small, anonymous functions would be annoying and largely redundant
with the information the compiler already has available.
Closure definitions will have one concrete type inferred for each of their parameters and for their return value.
*/

fn generate_workout(intensity: u32, random_number: u32) {
    let expensive_closure = |num| {
        println!("calculating slowly ...!");
        thread::sleep(Duration::from_secs(2));
        num
    };

    if intensity > 25 {
        println!("Today do {} pushups !", expensive_closure(intensity));
        println!("Next, do {} situpds", expensive_closure(intensity));
    } else {
        if random_number == 3 {
            println!("Take a break today! remember to stay hydrated");
        } else {
            println!("Today, run for {} minutes", expensive_closure(intensity));
        }
    }
}

fn add_one_v1(x: u32) -> u32 {
    x + 1
}

fn test_closure_basic() {
    {
        // This illustrates how closure syntax is similar to function syntax except for the use of pipes and the amount of syntax that is optional:
        let add_one_v2 = |x: u32| -> u32 { x + 1 };
        let add_one_v3 = |x: u32| x + 1;
        let add_one_v4 = |x: u32| x + 1;
    }

    {
        // This closure isn’t very useful except for the purposes of this example.
        // Note that we haven’t added any type annotations to the definition: if we then try to call the closure twice,
        // using a String as an argument the first time and a u32 the second time, we’ll get an error.
        let example_closure = |x| x;

        let s = example_closure(String::from("hello"));
        // let n = example_closure(5); // error: example_closure has inferred to be String
    }
}

pub fn test_closure() {}
