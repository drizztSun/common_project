use std::thread;
use std::time::Duration;

/*
*** Closure Type Inference and Annotation ***
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


The closure definition comes after the = to assign it to the variable expensive_closure. To define a closure, we start with a pair of vertical pipes (|),
inside which we specify the parameters to the closure; this syntax was chosen because of its similarity to closure definitions in Smalltalk and Ruby.
This closure has one parameter named num: if we had more than one parameter, we would separate them with commas, like |param1, param2|.

After the parameters, we place curly brackets that hold the body of the closure—these are optional if the closure body is a single expression.
The end of the closure, after the curly brackets, needs a semicolon to complete the let statement.
The value returned from the last line in the closure body (num) will be the value returned from the closure when it’s called,
because that line doesn’t end in a semicolon; just as in function bodies.
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
        // fn  add_one_v1   (x: u32) -> u32 { x + 1 }
        // let add_one_v2 = |x: u32| -> u32 { x + 1 };
        // let add_one_v3 = |x: u32|    {x + 1};
        // let add_one_v4 = |x: u32|    x + 1;
    }

    {
        /*
        Closure definitions will have one concrete type inferred for each of their parameters and for their return value. For instance,
        Belows shows the definition of a short closure that just returns the value it receives as a parameter. This closure isn’t very useful except for the purposes of this example.
        Note that we haven’t added any type annotations to the definition: if we then try to call the closure twice, using a String as an argument the first time and a u32 the second time, we’ll get an error.
        */

        // This closure isn’t very useful except for the purposes of this example.
        // Note that we haven’t added any type annotations to the definition: if we then try to call the closure twice,
        // using a String as an argument the first time and a u32 the second time, we’ll get an error.
        let example_closure = |x| x;

        let s = example_closure(String::from("hello"));
        // let n = example_closure(5); // error: example_closure has inferred to be String
    }
}

/*

*** Storing Closures Using Generic Parameters and the Fn Traits ***


To make a struct that holds a closure, we need to specify the type of the closure, because a struct definition needs to know the types of each of its fields.
Each closure instance has its own unique anonymous type: that is, even if two closures have the same signature, their types are still considered different.
To define structs, enums, or function parameters that use closures, we use generics and trait bounds

The Fn traits are provided by the standard library. All closures implement at least one of the traits: Fn, FnMut, or FnOnce.
We’ll discuss the difference between these traits in the “Capturing the Environment with Closures” section; in this example, we can use the Fn trait.

We add types to the Fn trait bound to represent the types of the parameters and return values the closures must have to match this trait bound. In this case,
our closure has a parameter of type u32 and returns a u32, so the trait bound we specify is Fn(u32) -> u32.

*/

struct Cache<T>
where
    T: Fn(u32) -> u32, // T specify that it’s a closure by using the Fn trait
{
    calculation: T,
    value: Option<u32>,
}

impl<T> Cache<T>
where
    T: Fn(u32) -> u32,
{
    fn new(calculation: T) -> Cache<T> {
        Cache {
            calculation,
            value: None,
        }
    }

    fn value(&mut self, arg: u32) -> u32 {
        match self.value {
            Some(v) => v,
            None => {
                let v = (self.calculation)(arg);
                self.value = Some(v);
                v
            }
        }
    }
}

fn test_close_struct(intensity: u32, random_number: u32) {
    let mut expensive_result = Cache::new(|num| {
        println!("calculating slowly...");
        thread::sleep(Duration::from_secs(2));
        num
    });

    if intensity < 25 {
        println!("Today, do {} pushups!", expensive_result.value(intensity));
        println!("Next, do {} situps!", expensive_result.value(intensity));
    } else {
        if random_number == 3 {
            println!("Take a break today! Remember to stay hydrated!");
        } else {
            println!(
                "Today, run for {} minutes!",
                expensive_result.value(intensity)
            );
        }
    }
}

fn test_cloe_basic2() {
    /*
    *** Capturing the Environment with Closures ***
    In the workout generator example, we only used closures as inline anonymous functions. However, closures have an additional capability that functions don’t have:
    they can capture their environment and access variables from the scope in which they’re defined.


    When a closure captures a value from its environment, it uses memory to store the values for use in the closure body.
    This use of memory is overhead that we don’t want to pay in more common cases where we want to execute code that doesn’t capture its environment.
    Because functions are never allowed to capture their environment, defining and using functions will never incur this overhead.

    Closures can capture values from their environment in three ways, which directly map to the three ways a function can take a parameter:
    taking ownership, borrowing mutably, and borrowing immutably. These are encoded in the three Fn traits as follows:

    1) FnOnce consumes the variables it captures from its enclosing scope, known as the closure’s environment.
        To consume the captured variables, the closure must take ownership of these variables and move them into the closure when it is defined.
        The Once part of the name represents the fact that the closure can’t take ownership of the same variables more than once, so it can be called only once.
    2) FnMut can change the environment because it mutably borrows values.
    3) Fn borrows values from the environment immutably.


    When you create a closure, Rust infers which trait to use based on how the closure uses the values from the environment.
    All closures implement ‘FnOnce’ because they can all be called at least once.
    Closures that don’t move the captured variables also implement ‘FnMut’,
    and closures that don’t need mutable access to the captured variables also implement ‘Fn’.

    In Listing 13-12, the equal_to_x closure borrows x immutably (so equal_to_x has the Fn trait) because the body of the closure only needs to read the value in x.

    If you want to force the closure to take ownership of the values it uses in the environment, you can use the move keyword before the parameter list.
    This technique is mostly useful when passing a closure to a new thread to move the data so it’s owned by the new thread.

    */
    let x = 4;

    let equal_to_x = |z| z == x;

    // fn equal_to_x(z: i32) -> bool {
    //     z == x  // error[E0434]: can't capture dynamic environment in a fn item
    // }

    let y = 4;

    assert!(equal_to_x(y));

    {
        let x = vec![1, 2, 3];

        let equal_to_x = move |z| z == x;
        // println!("can't use x here: {:?}", x);  // error[E0382]: borrow of moved value: `x`
        /*

        The x value is moved into the closure when the closure is defined, because we added the move keyword.
        The closure then has ownership of x, and main isn’t allowed to use x anymore in the println! statement. Removing println! will fix this example.

        Most of the time when specifying one of the Fn trait bounds, you can start with Fn and the compiler will tell you if you need FnMut or FnOnce based on what happens in the closure body.
        */

        let y = vec![1, 2, 3];
        assert!(equal_to_x(y));
    }
}

pub fn test_closure() {
    test_closure_basic();

    test_close_struct(20, 10);

    generate_workout(20, 10);
}
