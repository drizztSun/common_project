// Refutability: Whether a Pattern Might Fail to Match
// Patterns come in two forms: refutable and irrefutable. Patterns that will match for any possible value passed are irrefutable. 
// Patterns come in two forms: refutable and irrefutable. Patterns that will match for any possible value passed are irrefutable. 
// An example would be x in the statement let x = 5; because x matches anything and therefore cannot fail to match. 
// Patterns that can fail to match for some possible value are refutable. An example would be Some(x) in the expression if let Some(x) = a_value because if the value in the a_value variable is None rather than Some, the Some(x) pattern will not match.

fn test_pattern_basic() {

    // Match arms
    let m = vec![1, 2, 3];
    match m.get(2) {
        Some(val) => println!("val = {}", val),
        None => println!("index error"),
    }

    let x = 1;
    match x {
        1 | 2 => println!("one or two"),
        3 => println!("three"),
        4...10 => println!("four ... ten"),
        _ => println!("others"),
    }

    let x1 = Some(5);
    let y1 = 10;

    let x = 'c';
    match x {
        'a'...'j' => println!("early ASCII letter"),
        'k'...'z' => println!("late ASCII letter"),
        _ => println!("something else"),
    }

    match x1 {
        Some(50) => println!("Got 50"),
        Some(y) => println!("Matched y = {}", y),
        _ => println!("Default case x = {:?}", x1),
    }
    println!("At the end, x1 = {:?}, y = {:?}", x1, y1);

    // Conditional if let Expressions
    let favorite_color: Option<&str> = None;
    let is_tuesday = false;
    let age: Result<u32, _> = "34".parse();

    if let Some(value) = favorite_color {
        println!("Using your favorite color {}, as the backgroud", value);
    } else if is_tuesday {
        println!("It is Tuesday, green day");
    } else if let Ok(v) = age {
        if v > 30 {
            println!("Using purple as background color");
        } else {
            println!("Using orange as background color");
        }
    } else {
        println!("Using blue as default background color");
    }

    // while let Conditional Loops
    let mut stack = Vec::new();
    stack.push(1);
    stack.push(2);
    stack.push(3);

    while let Some(top) = stack.pop() {
        println!("pop : {}", top);
    }

    // for Loops
    let v = vec!['a', 'b', 'c'];

    for (i, v) in v.iter().enumerate() {
        println!("{} is at index {}", v, i);
    }


    // let Statements
    let (x, y) = (1, 2);
    println!("x = {}, y = {}", x, y);

    //let (x, y) = (1, 2, 3)  Error because Pattern failed. 
    // expected a tuple with 3 elements, found one with 2 elements
    // note: expected type `({integer}, {integer}, {integer})`
    //         found type `(_, _)`

    // Function Parameters
    let point = (2, 3);
    print_coordinates(&point);
}

fn print_coordinates(&(x, y): &(u32, u32)) {
    println!("x = {}, y = {}", x, y);
}

struct Point{
    x: i32,
    y: i32,
}

enum Color {
   Rgb(i32, i32, i32),
   Hsv(i32, i32, i32),
}

enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
    ChangeColorO(Color),
}

fn test_pattern_syntax() {

    // Pattern syntax
    let m = vec![1, 2, 3];
    match m.get(2) {
        Some(val) => println!("val = {}", val),
        None => println!("index error"),
    }

    let x = 1;
    match x {
        // Multiple Patterns
        1 | 2 => println!("one or two"),
        3 => println!("three"),
        // Matching Ranges of Values with ...
        4...10 => println!("four ... ten"),
        _ => println!("others"),
    }

    let x1 = Some(5);
    let y1 = 10;

    let x = 'c';
    match x {
        'a'...'j' => println!("early ASCII letter"),
        'k'...'z' => println!("late ASCII letter"),
        _ => println!("something else"),
    }

    match x1 {
        Some(50) => println!("Got 50"),
        Some(y) => println!("Matched y = {}", y),
        _ => println!("Default case x = {:?}", x1),
    }
    println!("At the end, x1 = {:?}, y = {:?}", x1, y1);


    // *** Extra Conditionals with Match Guards
    {
        let num = Some(4);

        match num {
            Some(x) if x < 5 => println!("less than five: {}", x),
            Some(x) => println!("{}", x),
            None => (),
        }

        let x = Some(5);
        let y = 10;

        match x {
            Some(50) => println!("Got 50"),
            Some(n) if n == y => println!("Matched, n = {:?}", n),
            _ => println!("Default case, x = {:?}", x),
        }

        println!("at the end: x = {:?}, y = {:?}", x, y);
    }


    // *** Destructuring to Break Apart Values
    // We can also use patterns to destructure structs, enums, tuples, and references to use different parts of these values. 
    // Let’s walk through each value.
    {
        let p = Point{x: 0, y: 7};
        let Point{x: a, y: b} = p;

        println!("a = {}, b = {}", a, b);
        assert_eq!(a, 0);
        assert_eq!(b, 7);
    }

    {
        let p = Point{x: 0, y: 7};
        let Point{x, y} = p;
        
        println!("x = {}, y = {}", x, y);
        assert_eq!(x, 0);
        assert_eq!(y, 7);
    }

    {
        let p = Point{x: 0, y: 2};
        match p {
            Point{x: 0, y} => println!("Y axis at {}", y),
            Point{x, y: 0} => println!("X axis at {}", x),
            Point{x, y} => println!("On neither axis, ({}, {})", x, y),
        }
    }

    {
        // *** Destruct Enum
        let msg = Message::ChangeColor(0, 160, 255);

        match msg {
            Message::Quit => {
                println!("The Quit variant has no data to destructure.")
            },
            Message::Move { x, y } => {
                println!(
                    "Move in the x direction {} and in the y direction {}",
                    x,
                    y
                );
            },
            Message::Write(text) => println!("Text message: {}", text),
            Message::ChangeColor(r, g, b) => {
                println!(
                    "Change the color to red {}, green {}, and blue {}",
                    r,
                    g,
                    b
                )
            },
            Message::ChangeColorO(Color::Rgb(a, b, c)) => {
                println!(
                    "Change the color to red {}, green {} and blue {}",
                    a,
                    b,
                    c
                )
            },
            Message::ChangeColorO(Color::Hsv(a, b, c)) => {
                println!(
                    "Change the color to red {}, green {} and blue {}",
                    a,
                    b,
                    c
                )
            },
        }
    }

    {
        // *** Destructuring Nested Structs and Enums
        let msg = Message::ChangeColorO(Color::Hsv(0, 160, 255));

        match msg {
            Message::ChangeColorO(Color::Rgb(r, g, b)) => {
                println!(
                    "Change the color to red {}, green {}, and blue {}",
                    r,
                    g,
                    b
                )
            },
            Message::ChangeColorO(Color::Hsv(h, s, v)) => {
                println!(
                    "Change the color to hue {}, saturation {}, and value {}",
                    h,
                    s,
                    v
                )
            },
            _ => (),
        }
    }

    // *** Destructuring Structs and Tuples
    // We can mix, match, and nest destructuring patterns in even more complex ways. 
    // The following example shows a complicated destructure where we nest structs and tuples inside a tuple and destructure all the primitive values out:
    let ((feet, inches), Point {x, y}) = ((3, 10), Point { x: 3, y: -10 });

    // *** Ignoring an Entire Value with _
    foo(3, 4);

    // *** Ignoring Parts of a Value with a Nested _
    {
        let mut setting_value = Some(5);
        let new_setting_value = Some(10);

        match (setting_value, new_setting_value) {
            (Some(_), Some(_)) => {
                println!("Can't overwrite an existing customized value");
            }
            _ => {
                setting_value = new_setting_value;
            }
        }

        println!("setting is {:?}", setting_value);


        let numbers = (2, 4, 8, 16, 32);

        match numbers {
            (first, _, third, _, fifth) => {
                println!("Some numbers: {}, {}, {}", first, third, fifth)
            },
        }
    }

    // *** Ignoring an Unused Variable by Starting Its Name with _
    // If you create a variable but don’t use it anywhere, Rust will usually issue a warning because that could be a bug. 
    // But sometimes it’s useful to create a variable you won’t use yet, such as when you’re prototyping or just starting a project. 
    // In this situation, you can tell Rust not to warn you about the unused variable by starting the name of the variable with an underscore.
    {
        let _x = 5;
        let y = 10;
    }


    // *** Ignoring Remaining Parts of a Value with ..
    {
        // The syntax .. will expand to as many values as it needs to be.
        // However, using .. must be unambiguous. 
        // If it is unclear which values are intended for matching and which should be ignored, Rust will give us an error.
        struct Point {
            x: i32,
            y: i32,
            z: i32,
        }

        let origin = Point { x: 0, y: 0, z: 0 };

        match origin {
            Point { x, .. } => println!("x is {}", x),
        }
    }

    // *** @ Bindings
    // The at operator (@) lets us create a variable that holds a value at the same time we’re testing that value to see whether it matches a pattern.
    // a Message::Hello id field is within the range 3...7. 
    // But we also want to bind the value to the variable id_variable so we can use it in the code associated with the arm.
    // Using @ lets us test a value and save it in a variable within one pattern
    {
        enum Message {
            Hello { id: i32 },
        }

        let msg = Message::Hello { id: 5 };

        match msg {
            Message::Hello { id: id_variable @ 3...7 } => {
                println!("Found an id in range: {}", id_variable)
            },
            Message::Hello { id: 10...12 } => {
                println!("Found an id in another range")
            },
            Message::Hello { id } => {
                println!("Found some other id: {}", id)
            },
        }
    }
}

// *** Ignoring an Entire Value with _
// We’ve used the underscore (_) as a wildcard pattern that will match any value but not bind to the value. 
// Although the underscore _ pattern is especially useful as the last arm in a match expression, 
fn foo(_: i32, y: i32) {
    println!("This code only uses the y parameter: {}", y);
}





pub fn test_pattern() {

    test_pattern_basic();


}