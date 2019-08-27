use std::fmt;
/*
In the body of largest we wanted to compare two values of type T using the greater than (>) operator. 
Because that operator is defined as a default method on the standard library trait std::cmp::PartialOrd, 
we need to specify PartialOrd in the trait bounds for T so the largest function can work on slices of any type that we can compare. 
We don’t need to bring PartialOrd into scope because it’s in the prelude. 

Rust has a special annotation called the Copy trait that we can place on types like integers that are stored on the stack 
(we’ll talk more about traits in Chapter 10). If a type has the Copy trait, an older variable is still usable after assignment. 
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
*/
fn largest<T: PartialOrd + Copy>(list: &[T]) -> T {
    let mut largest = list[0];

    for &item in list.iter() {
        if item > largest{
            largest = item;
        }
    }

    return largest
}

struct Point<T> {
    x: T,
    y: T,
}

impl<T> Point<T> {
    fn x(&self) -> &T {
        return &self.x;
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

pub fn test_generic() {

    println!(" --- generic ---");

    let number_list = vec![10, 20, 30, 40];
    println!("The largest number is: {}", largest(&number_list));

    let char_list = vec!['y', 'a', 'b', 'g'];
    println!("The largest letter is: {}", largest(&char_list));

    let intPoint = Point{x: 1, y: 2};
    println!("X is {}", intPoint.x());

    let float = Point{x: 1.0, y: 3.0};
    println!("float is {}, {}", float.x, float.y);

    let both_int = Point2{x: 1, y: 2};
    let both_float = Point2{x: 1.0, y: 3.0};
    let int_float = Point2{x: 1.0, y: 2};

    
}