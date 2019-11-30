use std::fmt;
use std::ops::Add;

// *** Specifying Placeholder Types in Trait Definitions with Associated Types
// Associated types connect a type placeholder with a trait such that the trait method definitions can use these placeholder types in their signatures.
// The implementor of a trait will specify the concrete type to be used in this type’s place for the particular implementation.
// That way, we can define a trait that uses some types without needing to know exactly what those types are until the trait is implemented.
pub trait Iterator {
    type Item;
    fn next(&mut self) -> Option<Self::Item>;
}

// *** Default Generic Type Parameters and Operator Overloading
// When we use generic type parameters, we can specify a default concrete type for the generic type.
// This eliminates the need for implementors of the trait to specify a concrete type if the default type works.
// The syntax for specifying a default type for a generic type is <PlaceholderType=ConcreteType> when declaring the generic type.
// A great example of a situation where this technique is useful is with operator overloading.
// Operator overloading is customizing the behavior of an operator (such as +) in particular situations.
// Rust doesn’t allow you to create your own operators or overload arbitrary operators.
// But you can overload the operations and corresponding traits listed in std::ops by implementing the traits associated with the operator.
#[derive(Debug, PartialEq)]
struct Point {
    x: i32,
    y: i32,
}

impl Add for Point {
    type Output = Point;

    fn add(self, other: Point) -> Point {
        Point {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

/*
The default generic type in this code is within the Add trait. Here is its definition:

trait Add<RHS=Self> {
    type Output;

    fn add(self, rhs: RHS) -> Self::Output;
}
This code should look generally familiar: a trait with one method and an associated type.
The new part is RHS=Self: this syntax is called default type parameters.
The RHS generic type parameter (short for “right hand side”) defines the type of the rhs parameter in the add method.
If we don’t specify a concrete type for RHS when we implement the Add trait, the type of RHS will default to Self, which will be the type we’re implementing Add on.
*/
struct Millemeter(i32);
struct Meter(i32);

impl Add<Meter> for Millemeter {
    type Output = Millemeter;
    fn add(self, other: Meter) -> Self::Output {
        Millemeter(self.0 + other.0 * 1000)
    }
}

/*
To add Millimeters and Meters, we specify impl Add<Meters> to set the value of the RHS type parameter instead of using the default of Self.

You’ll use default type parameters in two main ways:

To extend a type without breaking existing code
To allow customization in specific cases most users won’t need
The standard library’s Add trait is an example of the second purpose:
usually, you’ll add two like types, but the Add trait provides the ability to customize beyond that.
Using a default type parameter in the Add trait definition means you don’t have to specify the extra parameter most of the time.
 In other words, a bit of implementation boilerplate isn’t needed, making it easier to use the trait.
*/

// *** Fully Qualified Syntax for Disambiguation: Calling Methods with the Same Name
// Nothing in Rust prevents a trait from having a method with the same name as another trait’s method,
// nor does Rust prevent you from implementing both traits on one type.
// It’s also possible to implement a method directly on the type with the same name as methods from traits.

// When calling methods with the same name, you’ll need to tell Rust which one you want to use.
// Consider the code in Listing 19-16 where we’ve defined two traits, Pilot and Wizard, that both have a method called fly.
// We then implement both traits on a type Human that already has a method named fly implemented on it.
// Each fly method does something different.
trait Pilot {
    fn fly(&self);
}

trait Wizard {
    fn fly(&self);
}

struct Human;

impl Pilot for Human {
    fn fly(&self) {
        println!("Pilot trait fly");
    }
}

impl Wizard for Human {
    fn fly(&self) {
        println!("Wizard trait fly");
    }
}

impl Human {
    fn fly(&self) {
        println!("Human trait fly")
    }
}

trait Animal {
    fn baby_animal() -> String;
}

struct Dog;

impl Dog {
    fn baby_animal() -> String {
        String::from("Dog Spot")
    }
}

impl Animal for Dog {
    fn baby_animal() -> String {
        String::from("Ainmal Spot")
    }
}

// *** Using Supertraits to Require One Trait’s Functionality Within Another Trait
// Sometimes, you might need one trait to use another trait’s functionality.
// In this case, you need to rely on the dependent trait also being implemented.
// The trait you rely on is a supertrait of the trait you’re implementing.

// *** Using the Newtype Pattern to Implement External Traits on External Types

struct Wrapper(Vec<String>);

impl fmt::Display for Wrapper {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "[{}]", self.0.join(", "))
    }
}

pub fn test_advance_trait() {
    assert_eq!(
        Point { x: 1, y: 0 } + Point { x: 0, y: 1 },
        Point { x: 1, y: 1 }
    );

    let person = Human;

    Wizard::fly(&person);
    Pilot::fly(&person);
    person.fly();

    println!("A baby dog is {}", Dog::baby_animal()); // Dog Spot
    println!("A baby dog is {}", <Dog as Animal>::baby_animal()); // Animal SPot

    let w = Wrapper(vec![String::from("Hello"), String::from("world")]);
    println!("w = {}", w);
}
