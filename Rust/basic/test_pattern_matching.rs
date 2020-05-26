/*

*** Patterns and Matching ***
Patterns are a special syntax in Rust for matching against the structure of types, both complex and simple.
Using patterns in conjunction with match expressions and other constructs gives you more control over a program’s control flow.
A pattern consists of some combination of the following:

1) Literals
2) Destructured arrays, enums, structs, or tuples
3) Variables
4) Wildcards
5) Placeholders
These components describe the shape of the data we’re working with, which we then match against values to determine whether our program has the correct data to continue running a particular piece of code.


*/

/*

*** All the Places Patterns Can Be Used ***
Patterns pop up in a number of places in Rust, and you’ve been using them a lot without realizing it! This section discusses all the places where patterns are valid.

*** match Arms ***
Formally, match expressions are defined as the keyword match, a value to match on, and one or more match arms that consist of a pattern and an expression to run if the value matches that arm’s pattern, like this:


match VALUE {
    PATTERN => EXPRESSION,
    PATTERN => EXPRESSION,
    PATTERN => EXPRESSION,
}
One requirement for match expressions is that they need to be exhaustive in the sense that all possibilities for the value in the match expression must be accounted for.
One way to ensure you’ve covered every possibility is to have a catchall pattern for the last arm: for example, a variable name matching any value can never fail and thus covers every remaining case.

A particular pattern _ will match anything, but it never binds to a variable, so it’s often used in the last match arm. The _ pattern can be useful when you want to ignore any value not specified, for example.
We’ll cover the _ pattern in more detail in the “Ignoring Values in a Pattern” section later in this chapter.

*** Conditional if let Expressions ***

use if let expressions mainly as a shorter way to write the equivalent of a match that only matches one case.
Optionally, if let can have a corresponding else containing code to run if the pattern in the if let doesn’t match.

 mix and match if let, else if, and else if let expressions. Doing so gives us more flexibility than a match expression in which we can express only one value to compare with the patterns.
 Also, the conditions in a series of if let, else if, else if let arms aren’t required to relate to each other.

 *** while let Conditional Loops ***
Similar in construction to if let, the while let conditional loop allows a while loop to run for as long as a pattern continues to match.

*** for Loops ***
for loop is the most common loop construction in Rust code, but we haven’t yet discussed the pattern that for takes.
In a for loop, the pattern is the value that directly follows the keyword for, so in for x in y the x is the pattern.


*** let Statements ***

let PATTERN = EXPRESSION;

let (x, y, z) = (1, 2, 3);

*/

struct Point {
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
    ChangeColor(Color),
    ChangeColor1(i32, i32, i32),
}

enum Message1 {
    Hello { id: i32 },
}

pub fn test_pattern_match() {
    let favorite_color: Option<&str> = None;
    let is_tuesday = false;
    let age: Result<u8, _> = "34".parse();

    match favorite_color {
        Some(color) => println!("Using your favorite color, {}, as the background", color),
        _ => println!("None"),
    }

    if let Some(color) = favorite_color {
        println!("Using your favorite color, {}, as the background", color);
    } else if is_tuesday {
        println!("Tuesday is green day!");
    } else if let Ok(age) = age {
        if age > 30 {
            println!("Using purple as the background color");
        } else {
            println!("Using orange as the background color");
        }
    } else {
        println!("Using blue as the background color");
    }

    // while let loop that uses a vector as a stack and prints the values in the vector in the opposite order in which they were pushed.
    let mut stack = vec![];
    stack.push(1);
    stack.push(2);
    stack.push(3);

    while let Some(top) = stack.pop() {
        println!("{}", top);
    }

    let v = vec!['a', 'b', 'c'];

    for (index, value) in v.iter().enumerate() {
        println!("{} is at index {}", value, index);
    }

    let (x, y, z) = (1, 2, 3);
}

fn test_pattern_syntax() {
    {
        let x = 1;

        match x {
            1 => println!("one"),
            2 => println!("two"),
            3 => println!("three"),
            _ => println!("anything"),
        }
    }

    {
        // Matching Named Variables
        // Named variables are irrefutable patterns that match any value
        // However, there is a complication when you use named variables in match expressions.
        // Because match starts a new scope, variables declared as part of a pattern inside the match expression will shadow those with the same name outside the match construct, as is the case with all variables.
        let x = Some(5);
        let y = 10;

        match x {
            Some(50) => println!("Got 50"),
            Some(y) => println!("Matched, y = {:?}", y),
            _ => println!("Default case, x = {:?}", x),
        }
        println!("at the end: x = {:?}, y = {:?}", x, y);
    }

    {
        // Multiple Patterns
        // In match expressions, you can match multiple patterns using the | syntax, which means or
        let x = 1;

        match x {
            1 | 2 => println!("one or two"),
            3 => println!("three"),
            _ => println!("anything"),
        }
    }

    {
        // Matching Ranges of Values with ..=
        // The ..= syntax allows us to match to an inclusive range of values. In the following code, when a pattern matches any of the values within the range,
        let x = 5;

        match x {
            1..=5 => println!("one through five"),
            _ => println!("something else"),
        }

        let x = 'c';

        match x {
            'a'..='j' => println!("early ASCII letter"),
            'k'..='z' => println!("late ASCII letter"),
            _ => println!("something else"),
        }
    }

    // Destructuring to Break Apart Values
    // We can also use patterns to destructure structs, enums, tuples, and references to use different parts of these values. Let’s walk through each value.
    {
        let p = Point { x: 0, y: 7 };

        // This code creates the variables a and b that match the values of the x and y fields of the p struct.
        let Point { x: a, y: b } = p;
        assert_eq!(0, a);
        assert_eq!(7, b);

        let p = Point { x: 0, y: 7 };

        match p {
            Point { x, y: 0 } => println!("On the x axis at {}", x),
            Point { x: 0, y } => println!("On the y axis at {}", y),
            Point { x, y } => println!("On neither axis: ({}, {})", x, y),
        }
    }

    // Destructuring Enums
    {
        let msg = Message::ChangeColor1(0, 160, 255);

        match msg {
            Message::Quit => println!("The Quit variant has no data to destructure."),
            Message::Move { x, y } => {
                println!("Move in the x direction {} and in the y direction {}", x, y);
            }
            Message::Write(text) => println!("Text message: {}", text),
            Message::ChangeColor1(r, g, b) => {
                println!("Change the color to red {}, green {}, and blue {}", r, g, b)
            }
            _ => println!("None"),
        }
    }

    // Destructuring Nested Structs and Enums
    {
        let msg = Message::ChangeColor(Color::Hsv(0, 160, 255));

        match msg {
            Message::ChangeColor(Color::Rgb(r, g, b)) => {
                println!("Change the color to red {}, green {}, and blue {}", r, g, b)
            }
            Message::ChangeColor(Color::Hsv(h, s, v)) => println!(
                "Change the color to hue {}, saturation {}, and value {}",
                h, s, v
            ),
            _ => (),
        }
    }

    // Destructuring Structs and Tuples
    // We can mix, match, and nest destructuring patterns in even more complex ways.
    // The following example shows a complicated destructure where we nest structs and tuples inside a tuple and destructure all the primitive values out:
    {
        let ((feet, inches), Point { x, y }) = ((3, 10), Point { x: 3, y: -10 });
    }

    // Ignoring Values in a Pattern
    //  There are a few ways to ignore entire values or parts of values in a pattern:
    //  using the _ pattern (which you’ve seen), using the _ pattern within another pattern, using a name that starts with an underscore, or using .. to ignore remaining parts of a value

    // Ignoring Parts of a Value with a Nested _
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
            }
        }
    }

    // Ignoring an Unused Variable by Starting Its Name with _
    {
        let _x = 5;
        let y = 10;

        let s = Some(String::from("Hello!"));

        if let Some(_) = s {
            println!("found a string");
        }
        // However, using the underscore by itself doesn’t ever bind to the value. Listing 18-22 will compile without any errors because s doesn’t get moved into _.
        println!("{:?}", s);
    }

    // Ignoring Remaining Parts of a Value with ..
    {
        // With values that have many parts, we can use the .. syntax to use only a few parts and ignore the rest, avoiding the need to list underscores for each ignored value.
        // The .. pattern ignores any parts of a value that we haven’t explicitly matched in the rest of the pattern.

        let origin = Point { x: 0, y: 0 };

        match origin {
            Point { x, .. } => println!("x is {}", x),
        }

        let numbers = (2, 4, 8, 16, 32);

        match numbers {
            (first, .., last) => {
                println!("Some numbers: {}, {}", first, last);
            }
        }
    }

    {
        // Extra Conditionals with Match Guards
        // A match guard is an additional if condition specified after the pattern in a match arm that must also match, along with the pattern matching,
        // for that arm to be chosen. Match guards are useful for expressing more complex ideas than a pattern alone allows.
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
            Some(n) if n == y => println!("Matched, n = {}", n),
            _ => println!("Default case, x = {:?}", x),
        }

        println!("at the end: x = {:?}, y = {}", x, y);

        let x = 4;
        let y = false;
        match x {
            4 | 5 | 6 if y => println!("yes"),
            _ => println!("no"),
        }

        // The match condition states that the arm only matches if the value of x is equal to 4, 5, or 6 and if y is true.
        // When this code runs, the pattern of the first arm matches because x is 4, but the match guard if y is false, so the first arm is not chosen.
        // The code moves on to the second arm, which does match, and this program prints no. The reason is that the if condition applies to the whole pattern 4 | 5 | 6, not only to the last value 6.
        // In other words, the precedence of a match guard in relation to a pattern behaves like this:
    }

    {
        // @ Bindings
        // The at operator (@) lets us create a variable that holds a value at the same time we’re testing that value to see whether it matches a pattern.
        //  Message::Hello id field is within the range 3..=7. But we also want to bind the value to the variable id_variable so we can use it in the code associated with the arm.
        // We could name this variable id, the same as the field, but for this example we’ll use a different name.
        let msg = Message1::Hello { id: 5 };
        match msg {
            Message1::Hello {
                id: id_variable @ 3..=7,
            } => println!("Found an id in range: {}", id_variable),
            Message1::Hello { id: 10..=12 } => println!("Found an id in another range"),
            Message1::Hello { id } => println!("Found some other id: {}", id),
        }

        // In the second arm, where we only have a range specified in the pattern, the code associated with the arm doesn’t have a variable that contains the actual value of the id field.
        // The id field’s value could have been 10, 11, or 12, but the code that goes with that pattern doesn’t know which it is.
        // The pattern code isn’t able to use the value from the id field, because we haven’t saved the id value in a variable.

        // In the last arm, where we’ve specified a variable without a range, we do have the value available to use in the arm’s code in a variable named id.
        // The reason is that we’ve used the struct field shorthand syntax. But we haven’t applied any test to the value in the id field in this arm,
        // as we did with the first two arms: any value would match this pattern.
    }
}

/*

*** Refutability: Whether a Pattern Might Fail to Match ***
Patterns come in two forms: refutable and irrefutable. Patterns that will match for any possible value passed are irrefutable.
An example would be x in the statement let x = 5; because x matches anything and therefore cannot fail to match.

Patterns that can fail to match for some possible value are refutable.
An example would be Some(x) in the expression if let Some(x) = a_value because if the value in the a_value variable is None rather than Some, the Some(x) pattern will not match.

Function parameters, let statements, and for loops can only accept irrefutable patterns, because the program cannot do anything meaningful when values don’t match
The if let and while let expressions accept refutable and irrefutable patterns, but the compiler warns against irrefutable patterns because by definition they’re intended to handle possible failure: the functionality of a conditional is in its ability to perform differently depending on success or failure.



*/
