/*

*** Characteristics of Object-Oriented Languages ***
There is no consensus in the programming community about what features a language must have to be considered object oriented. Rust is influenced by many programming paradigms, including OOP;

Arguably, OOP languages share certain common characteristics, namely objects, encapsulation, and inheritance. Let’s look at what each of those characteristics means and whether Rust supports it.


*** Objects Contain Data and Behavior ***
The book Design Patterns: Elements of Reusable Object-Oriented Software by Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides (Addison-Wesley Professional, 1994)
colloquially referred to as The Gang of Four book, is a catalog of object-oriented design patterns. It defines OOP this way:

Object-oriented programs are made up of objects. An object packages both data and the procedures that operate on that data. The procedures are typically called methods or operations.

*** Using this definition, Rust is object oriented: structs and enums have data, and impl blocks provide methods on structs and enums.
Even though structs and enums with methods aren’t called objects, they provide the same functionality, according to the Gang of Four’s definition of objects.


*** Encapsulation that Hides Implementation Details ***
Another aspect commonly associated with OOP is the idea of encapsulation, which means that the implementation details of an object aren’t accessible to code using that object.
Therefore, the only way to interact with an object is through its public API; code using the object shouldn’t be able to reach into the object’s internals and change data or behavior directly.
This enables the programmer to change and refactor an object’s internals without needing to change the code that uses the object.

We can use the pub keyword to decide which modules, types, functions, and methods in our code should be public, and by default everything else is private



*/

pub struct AveragedCollection {
    list: Vec<i32>,
    average: f64,
}


/*
The public methods add, remove, and average are the only ways to access or modify data in an instance of AveragedCollection.
When an item is added to list using the add method or removed using the remove method, the implementations of each call the private update_average method that handles updating the average field as well.

We leave the list and average fields private so there is no way for external code to add or remove items to the list field directly; otherwise, the average field might become out of sync when the list changes.
The average method returns the value in the average field, allowing external code to read the average but not modify it.
*/

impl AveragedCollection {
    pub fn add(&mut self, value: i32) {
        self.list.push(value);
        self.update_average();
    }

    pub fn remove(&mut self) -> Option<i32> {
        let result = self.list.pop();
        match result {
            Some(value) => {
                self.update_average();
                Some(value)
            }
            None => None,
        }
    }

    pub fn average(&self) -> f64 {
        self.average
    }

    fn update_average(&mut self) {
        let total: i32 = self.list.iter().sum();
        self.average = total as f64 / self.list.len() as f64;
    }
}

/*

*** Inheritance as a Type System and as Code Sharing ***
Inheritance is a mechanism whereby an object can inherit from another object’s definition, thus gaining the parent object’s data and behavior without you having to define them again.

**** If a language must have inheritance to be an object-oriented language, then Rust is not one.***

There is no way to define a struct that inherits the parent struct’s fields and method implementations.
However, if you’re used to having inheritance in your programming toolbox, you can use other solutions in Rust, depending on your reason for reaching for inheritance in the first place.

You choose inheritance for two main reasons. One is for reuse of code: you can implement particular behavior for one type, and inheritance enables you to reuse that implementation for a different type.
You can share Rust code using default trait method implementations instead, which you saw in Listing 10-14 when we added a default implementation of the summarize method on the Summary trait.
Any type implementing the Summary trait would have the summarize method available on it without any further code.
This is similar to a parent class having an implementation of a method and an inheriting child class also having the implementation of the method.
We can also override the default implementation of the summarize method when we implement the Summary trait, which is similar to a child class overriding the implementation of a method inherited from a parent class.

The other reason to use inheritance relates to the type system: to enable a child type to be used in the same places as the parent type.
This is also called polymorphism, which means that you can substitute multiple objects for each other at runtime if they share certain characteristics.

Polymorphism
To many people, polymorphism is synonymous with inheritance. But it’s actually a more general concept that refers to code that can work with data of multiple types.
For inheritance, those types are generally subclasses.

Rust instead uses generics to abstract over different possible types and trait bounds to impose constraints on what those types must provide.
This is sometimes called bounded parametric polymorphism.

Inheritance has recently fallen out of favor as a programming design solution in many programming languages because it’s often at risk of sharing more code than necessary.
Subclasses shouldn’t always share all characteristics of their parent class but will do so with inheritance.
This can make a program’s design less flexible. It also introduces the possibility of calling methods on subclasses that don’t make sense or that cause errors because the methods don’t apply to the subclass.
In addition, some languages will only allow a subclass to inherit from one class, further restricting the flexibility of a program’s design.

*** For these reasons, Rust takes a different approach, using trait objects instead of inheritance. Let’s look at how trait objects enable polymorphism in Rust.
*/

/*

*** Using Trait Objects That Allow for Values of Different Types ***

In Chapter 8, we mentioned that one limitation of vectors is that they can store elements of only one type.
We created a workaround in Listing 8-10 where we defined a SpreadsheetCell enum that had variants to hold integers, floats, and text.
This meant we could store different types of data in each cell and still have a vector that represented a row of cells.
This is a perfectly good solution when our interchangeable items are a fixed set of types that we know when our code is compiled.

However, sometimes we want our library user to be able to extend the set of types that are valid in a particular situation.
To show how we might achieve this, we’ll create an example graphical user interface (GUI) tool that iterates through a list of items, calling a draw method on each one to draw it to the screen—a common technique for GUI tools.
We’ll create a library crate called gui that contains the structure of a GUI library. This crate might include some types for people to use, such as Button or TextField.
In addition, gui users will want to create their own types that can be drawn: for instance, one programmer might add an Image and another might add a SelectBox.

We won’t implement a fully fledged GUI library for this example but will show how the pieces would fit together.
At the time of writing the library, we can’t know and define all the types other programmers might want to create.
But we do know that gui needs to keep track of many values of different types, and it needs to call a draw method on each of these differently typed values.
It doesn’t need to know exactly what will happen when we call the draw method, just that the value will have that method available for us to call.

To do this in a language with inheritance, we might define a class named Component that has a method named draw on it.
The other classes, such as Button, Image, and SelectBox, would inherit from Component and thus inherit the draw method.
They could each override the draw method to define their custom behavior, but the framework could treat all of the types as if they were Component instances and call draw on them.
But because Rust doesn’t have inheritance, we need another way to structure the gui library to allow users to extend it with new types.

*** Defining a Trait for Common Behavior ***
To implement the behavior we want gui to have, we’ll define a trait named Draw that will have one method named draw.
Then we can define a vector that takes a trait object. A trait object points to both an instance of a type implementing our specified trait as well as a table used to look up trait methods on that type at runtime.
We create a trait object by specifying some sort of pointer, such as a & reference or a Box<T> smart pointer, then the dyn keyword, and then specifying the relevant trait.
(We’ll talk about the reason trait objects must use a pointer in Chapter 19 in the section “Dynamically Sized Types and the Sized Trait.”) We can use trait objects in place of a generic or concrete type.
Wherever we use a trait object, Rust’s type system will ensure at compile time that any value used in that context will implement the trait object’s trait. Consequently, we don’t need to know all the possible types at compile time.

We’ve mentioned that in Rust, we refrain from calling structs and enums “objects” to distinguish them from other languages’ objects.
In a struct or enum, the data in the struct fields and the behavior in impl blocks are separated, whereas in other languages, the data and behavior combined into one concept is often labeled an object.
However, trait objects are more like objects in other languages in the sense that they combine data and behavior. But trait objects differ from traditional objects in that we can’t add data to a trait object.
Trait objects aren’t as generally useful as objects in other languages: their specific purpose is to allow abstraction across common behavior.


*/

pub trait Draw {
    fn draw(&self);
}

pub struct Screen {
    pub components: Vec<Box<dyn Draw>>, // This vector is of type Box<dyn Draw>, which is a trait object; it’s a stand-in for any type inside a Box that implements the Draw trait.
}

impl Screen {
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    }
}


// This works differently from defining a struct that uses a generic type parameter with trait bounds.
// A generic type parameter can only be substituted with one concrete type at a time, whereas trait objects allow for multiple concrete types to fill in for the trait object at runtime.

pub struct ScreenT<T: Draw> {
    pub components: Vec<T>,
}

impl<T> ScreenT<T>
where
    T: Draw,
{
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    }
}

/**
 *** Implementing the Trait ****




 */

pub struct Button {
    pub width: u32,
    pub height: u32,
    pub label: String,
}

impl Draw for Button {
    fn draw(&self) {
        println!("Button draw");
    }
}

struct SelectBox {
    width: u32,
    height: u32,
    options: Vec<String>,
}

impl Draw for SelectBox {
    fn draw(&self) {
        // code to actually draw a select box
        println!("SelectBox draw");
    }
}


pub fn test_object_orient() {
    let screen = Screen {
        components: vec![
            Box::new(SelectBox {
                width: 75,
                height: 10,
                options: vec![
                    String::from("Yes"),
                    String::from("Maybe"),
                    String::from("No"),
                ],
            }),
            Box::new(Button {
                width: 50,
                height: 10,
                label: String::from("OK"),
            }),
        ],
    };

    screen.run();
}

/*

*** Trait Objects Perform Dynamic Dispatch ***
Recall in the “Performance of Code Using Generics” section in Chapter 10 our discussion on the monomorphization process performed by the compiler when we use trait bounds on generics:
the compiler generates nongeneric implementations of functions and methods for each concrete type that we use in place of a generic type parameter.
The code that results from monomorphization is doing static dispatch, which is when the compiler knows what method you’re calling at compile time.
This is opposed to dynamic dispatch, which is when the compiler can’t tell at compile time which method you’re calling.
In dynamic dispatch cases, the compiler emits code that at runtime will figure out which method to call.

When we use trait objects, Rust must use dynamic dispatch. The compiler doesn’t know all the types that might be used with the code that is using trait objects,
so it doesn’t know which method implemented on which type to call.
Instead, at runtime, Rust uses the pointers inside the trait object to know which method to call. There is a runtime cost when this lookup happens that doesn’t occur with static dispatch.
Dynamic dispatch also prevents the compiler from choosing to inline a method’s code, which in turn prevents some optimizations.
However, we did get extra flexibility in the code that we wrote in Listing 17-5 and were able to support in Listing 17-9, so it’s a trade-off to consider.


*** Object Safety Is Required for Trait Objects ***
You can only make object-safe traits into trait objects. Some complex rules govern all the properties that make a trait object safe, but in practice, only two rules are relevant.
A trait is object safe if all the methods defined in the trait have the following properties:

1) The return type isn’t Self.
2) There are no generic type parameters.

The Self keyword is an alias for the type we’re implementing the traits or methods on. Trait objects must be object safe because once you’ve used a trait object, Rust no longer knows the concrete type that’s implementing that trait.
If a trait method returns the concrete Self type, but a trait object forgets the exact type that Self is, there is no way the method can use the original concrete type.
The same is true of generic type parameters that are filled in with concrete type parameters when the trait is used: the concrete types become part of the type that implements the trait.
When the type is forgotten through the use of a trait object, there is no way to know what types to fill in the generic type parameters with.




An example of a trait whose methods are not object safe is the standard library’s Clone trait. The signature for the clone method in the Clone trait looks like this:
pub trait Clone {
    fn clone(&self) -> Self;
}


*/

/*

*** Implementing an Object-Oriented Design Pattern ***
The state pattern is an object-oriented design pattern.
The crux of the pattern is that a value has some internal state, which is represented by a set of state objects, and the value’s behavior changes based on the internal state.
The state objects share functionality:
    in Rust, of course, we use structs and traits rather than objects and inheritance. Each state object is responsible for its own behavior and for governing when it should change into another state.
    The value that holds a state object knows nothing about the different behavior of the states or when to transition between states.

Using the state pattern means when the business requirements of the program change, we won’t need to change the code of the value holding the state or the code that uses the value.
We’ll only need to update the code inside one of the state objects to change its rules or perhaps add more state objects. Let’s look at an example of the state design pattern and how to use it in Rust.

We’ll implement a blog post workflow in an incremental way. The blog’s final functionality will look like this:

1) A blog post starts as an empty draft.
2) When the draft is done, a review of the post is requested.
3) When the post is approved, it gets published.
4) Only published blog posts return content to print, so unapproved posts can’t accidentally be published.
Any other changes attempted on a post should have no effect. For example, if we try to approve a draft blog post before we’ve requested a review, the post should remain an unpublished draft.

*/



pub struct Post {
    state: Option<Box<dyn State>>, //  a private State trait. Then Post will hold a trait object of Box<dyn State> inside an Option<T> in a private field named state.
    content: String,
}

impl Post {
    pub fn new() -> Post {
        Post {
            state: Some(Box::new(Draft {})),
            content: String::new(),
        }
    }

    pub fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }

    // --snip--
    pub fn request_review(&mut self) {
        if let Some(s) = self.state.take() {
            self.state = Some(s.request_review())
        }
    }
}

trait State {
    fn request_review(self: Box<Self>) -> Box<dyn State>;
    fn approve(self: Box<Self>) -> Box<dyn State>;
}

struct Draft {}

impl State for Draft {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        Box::new(PendingReview {})
    }
    fn approve(self: Box<Self>) -> Box<dyn State> {
        self
    }
}

struct PendingReview {}

impl State for PendingReview {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }
    fn approve(self: Box<Self>) -> Box<dyn State> {
        Box::new(Published {})
    }
}

struct Published {}

impl State for Published {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }

    fn approve(self: Box<Self>) -> Box<dyn State> {
        self
    }
}

fn test_object_orient() {
    let mut post = Post::new();

    post.add_text("I ate a salad for lunch today");
    assert_eq!("", post.content());

    post.request_review();
    assert_eq!("", post.content());

    post.approve();
    assert_eq!("I ate a salad for lunch today", post.content());
}

/*

*** Requesting a Review of the Post Changes Its State ***

*** Adding the approve Method that Changes the Behavior of content ***
The approve method will be similar to the request_review method: it will set state to the value that the current state says it should have when that state is approved,
*/