// use std::fmt::{self, Display}; // self means fmt itself
/*
In the body of largest we wanted to compare two values of type T using the greater than (>) operator.
Because that operator is defined as a default method on the standard library trait std::cmp::PartialOrd,
we need to specify PartialOrd in the trait bounds for T so the largest function can work on slices of any type that we can compare.
We don’t need to bring PartialOrd into scope because it’s in the prelude.

Rust has a special annotation called the Copy trait that we can place on types like integers that are stored on the stack
(we’ll talk more about traits in Chapter 10).

If a type has the Copy trait, an older variable is still usable after assignment.
Rust won’t let us annotate a type with the Copy trait if the type, or any of its parts, has implemented the Drop trait.
If the type needs something special to happen when the value goes out of scope and we add the Copy annotation to that type,
we’ll get a compile-time error. To learn about how to add the Copy annotation to your type, see “Derivable Traits” in Appendix C.

So what types are Copy? You can check the documentation for the given type to be sure, but as a general rule,
any group of simple scalar values can be Copy, and nothing that requires allocation or is some form of resource is Copy.
Here are some of the types that are Copy:

All the integer types, such as u32.
The Boolean type, bool, with values true and false.
All the floating point types, such as f64.
The character type, char.
Tuples, if they only contain types that are also Copy. For example, (i32, i32) is Copy, but (i32, String) is not.

The key line in this error is cannot move out of type [T], a non-copy slice. With our non-generic versions of the largest function, we were only trying to find the largest i32 or char.
As discussed in the “Stack-Only Data: Copy” section in Chapter 4, types like i32 and char that have a known size can be stored on the stack, so they implement the Copy trait.
But when we made the largest function generic, it became possible for the list parameter to have types in it that don’t implement the Copy trait.
Consequently, we wouldn’t be able to move the value out of list[0] and into the largest variable, resulting in this error.

To call this code with only those types that implement the Copy trait, we can add Copy to the trait bounds of T!
Listing 10-15 shows the complete code of a generic largest function that will compile as long as the types of the values in the slice that we pass into the function implement the PartialOrd and Copy traits, like i32 and char do.

Performance of Code Using Generics
You might be wondering whether there is a runtime cost when you’re using generic type parameters.
The good news is that Rust implements generics in such a way that your code doesn’t run any slower using generic types than it would with concrete types.

Rust accomplishes this by performing monomorphization of the code that is using generics at compile time.
Monomorphization is the process of turning generic code into specific code by filling in the concrete types that are used when compiled.
*/
use std::fmt::Display;

fn largest<T: PartialOrd + Copy>(list: &[T]) -> T {
    let mut largest = list[0];

    for &item in list.iter() {
        if item > largest {
            largest = item;
        }
    }

    return largest;
}

struct Point<T> {
    x: T,
    y: T,
}

fn largest_i32(list: &[i32]) -> i32 {
    let mut largest = list[0];

    for &item in list {
        if item > largest {
            largest = item;
        }
    }

    largest
}

fn largest_char(list: &[char]) -> char {
    let mut largest = list[0];

    for &item in list {
        if item > largest {
            largest = item;
        }
    }

    largest
}

/*
Note that we have to declare T just after impl so we can use it to specify that we’re implementing methods on the type Point<T>.
By declaring T as a generic type after impl, Rust can identify that the type in the angle brackets in Point is a generic type rather than a concrete type.
*/
impl<T> Point<T> {
    fn x(&self) -> &T {
        return &self.x;
    }
}

/*
We could, for example, implement methods only on Point<f32> instances rather than on Point<T> instances with any generic type.
In Listing 10-10 we use the concrete type f32, meaning we don’t declare any types after impl.

This code means the type Point<f32> will have a method named distance_from_origin and other instances of Point<T>
where T is not of type f32 will not have this method defined.
*/
impl Point<f32> {
    fn distance_from_origin(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}

/*
impl<T> fmt::Display for Point<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Point<T> Displays as ({}, {})", self.x, self.y)
    }
}*/

struct Point2<T, U> {
    x: T,
    y: U,
}

impl<T, U> Point2<T, U> {
    fn muxup<V, W>(self, other: Point2<V, W>) -> Point2<T, W> {
        Point2 {
            x: self.x,
            y: other.y,
        }
    }
}

/*

*** Using Trait Bounds to Conditionally Implement Methods ***

By using a trait bound with an impl block that uses generic type parameters, we can implement methods conditionally for types that implement the specified traits.

or example, the type Pair<T> in Listing 10-16 always implements the new function. But Pair<T> only implements the cmp_display method if its inner type T
implements the PartialOrd trait that enables comparison and the Display trait that enables printing.
*/

struct Pair<T> {
    x: T,
    y: T,
}

impl<T> Pair<T> {
    fn new(x: T, y: T) -> Self {
        Self { x, y }
    }
}

impl<T: Display + PartialOrd> Pair<T> {
    fn cmp_display(&self) {
        if self.x >= self.y {
            println!("The largest member is x = {}", self.x);
        } else {
            println!("Thes largest member is y = {}", self.y);
        }
    }
}

pub fn test_generic() {
    println!(" --- generic ---");

    let number_list = vec![10, 20, 30, 40];
    println!("The largest number is: {}", largest(&number_list));

    let char_list = vec!['y', 'a', 'b', 'g'];
    println!("The largest letter is: {}", largest(&char_list));

    let intPoint = Point { x: 1, y: 2 };
    println!("X is {}", intPoint.x());

    let float = Point { x: 1.0, y: 3.0 };
    println!("float is {}, {}", float.x, float.y);

    // special for Point<f32>
    println!("distance: {}", float.distance_from_origin());

    let both_int = Point2 { x: 1, y: 2 };
    let both_float = Point2 { x: 1.0, y: 3.0 };
    let int_float = Point2 { x: 1.0, y: 2 };

    let p1 = Point2 { x: 5, y: 10.4 };
    let p2 = Point2 { x: "Hello", y: 'c' };
    let p3 = p1.muxup(p2);

    println!("p3,x = {}, p3.y = {}", p3.x, p3.y);
}
