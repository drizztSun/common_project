/*
Note: Traits are similar to a feature often called interfaces in other languages, although with some differences.

One restriction to note with trait implementations is that we can implement a trait on a type only if either the trait or the type is local to our crate.
For example, we can implement standard library traits like Display on a custom type like Tweet as part of our aggregator crate functionality,
because the type Tweet is local to our aggregator crate.
We can also implement Summary on Vec<T> in our aggregator crate, because the trait Summary is local to our aggregator crate.

But we can’t implement external traits on external types. For example, we can’t implement the Display trait on Vec<T> within our aggregator crate,
because Display and Vec<T> are defined in the standard library and aren’t local to our aggregator crate.
This restriction is part of a property of programs called coherence, and more specifically the orphan rule, so named because the parent type is not present.
This rule ensures that other people’s code can’t break your code and vice versa.
Without the rule, two crates could implement the same trait for the same type, and Rust wouldn’t know which implementation to use.
 */
// use std::fmt;

// trait with abstract method
pub trait Summary {
    fn summarize(&self) -> String;
}

// trait with default method Implementations
pub trait DefaultSummary {
    fn summarizing(&self) -> String {
        format!("Default summarizing method")
    }
}

pub struct NewsArticle {
    pub headline: String,
    pub location: String,
    pub author: String,
    pub content: String,
}

// returns type that impl traits
fn Create_News_Article() -> impl Summary {
    NewsArticle {
        headline: String::from("default"),
        location: String::from("default"),
        author: String::from("default"),
        content: String::from("default"),
    }
}

impl Summary for NewsArticle {
    fn summarize(&self) -> String {
        format!("{}, by {} ({})", self.headline, self.author, self.location)
    }
}

impl DefaultSummary for NewsArticle {
    fn summarizing(&self) -> String {
        format!(
            "Summarizing {}, {}, {}",
            self.headline, self.author, self.location
        )
    }
}

pub struct Tweet {
    pub username: String,
    pub content: String,
    pub reply: bool,
    pub retweet: bool,
}

// return a trait
fn create_tweet() -> impl Summary {
    Tweet {
        username: String::from("default"),
        content: String::from("default"),
        reply: true,
        retweet: true,
    }
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}, {}", self.username, self.content)
    }
}

impl DefaultSummary for Tweet {}

// trait inherit

// Trait inheritance in Rust differs from OOP inheritance.
// Trait inheritance is just a way to specify requirements. trait B: A does not imply that if a type implements B it will automatically implement A;
// it means that if a type implements B it must implement A. This also means that you will have to implement A separately if B is implemented.

trait A {}
trait B: A {}

struct S;

impl B for S {}

// Commenting this line will result in a "trait bound unsatisfied" error
impl A for S {}



trait OnOff{
    fn set_onoff(&self, b :bool){
       println!("OnOff Default");
    }
}

trait Brightness{
    fn set_brightness(&self, brightness: i32){
        println!("Brightness Default");
    }
}

//Now any type which implements 'Light' should implement 'OnOff' 
//& 'Brightness' as well 
trait Light: OnOff + Brightness{ }
      
struct MyLight{
    state: bool
}

//impl <MyLight: OnOff + Brightness>Light for MyLight{}
impl Light for MyLight{}

impl OnOff for MyLight{}

impl Brightness for MyLight{
    fn set_brightness(&self, brightness: i32){
        println!("Brightness = {}", brightness);
    }
}

fn test_trait_inheritance() {
    let _x: &dyn B = &S;

    let my_light = MyLight{state: false};
    
    my_light.set_onoff(true);
    my_light.set_brightness(100);
}

// #[stable(feature = "rust1", since = "1.0.0")]
// #[lang = "copy"]
// pub trait Copy: Clone {
    // Empty.
// }


// However, if want a type to automatically implement C if it implements A and B (and thereby avoiding manually implementing C for that type), then you can use a generic impl:
// impl<T: A + B> C for T {}




// trait as parameters
/*
Instead of a concrete type for the item parameter, we specify the impl keyword and the trait name.
This parameter accepts any type that implements the specified trait.
In the body of notify, we can call any methods on item that come from the Summary trait, such as summarize.
We can call notify and pass in any instance of NewsArticle or Tweet.
Code that calls the function with any other type, such as a String or an i32, won’t compile because those types don’t implement Summary.

Instead of a concrete type for the item parameter, we specify the impl keyword and the trait name. This parameter accepts any type that implements the specified trait.
 */
pub fn notify(item: impl Summary) {
    println!("Breaking news ! {}", item.summarize());
}

// *** Trait Bound Syntax ***
/*
The impl Trait syntax works for straightforward cases but is actually syntax sugar for a longer form,
which is called a trait bound; it looks like this:

This longer form is equivalent to the example in the previous section but is more verbose.
We place trait bounds with the declaration of the generic type parameter after a colon and inside angle brackets.

The impl Trait syntax is convenient and makes for more concise code in simple cases. The trait bound syntax can express more complexity in other cases.
For example, we can have two parameters that implement Summary. Using the impl Trait syntax looks like this:


pub fn notify(item1: impl Summary, item2: impl Summary) {
If we wanted this function to allow item1 and item2 to have different types, using impl Trait would be appropriate (as long as both types implement Summary).
If we wanted to force both parameters to have the same type, that’s only possible to express using a trait bound, like this:


pub fn notify<T: Summary>(item1: T, item2: T) {
The generic type T specified as the type of the item1 and item2 parameters constrains the function such that the concrete type of the value passed as an argument for item1 and item2 must be the same.
*/
pub fn notifyTemp<T: Summary>(item: &T) {
    println!("Breaking news !{}", item.summarize());
}

/*

*** Specifing multiple trait bounds with the + syntax ***

We can also specify more than one trait bound.
Say we wanted notify to use display formatting on item as well as the summarize method:
    *** we specify in the notify definition that item must implement both Display and Summary
*/
pub fn notify2(item: impl Summary + DefaultSummary) {
    println!("notify2 : {}, {}", item.summarize(), item.summarizing());
}

pub fn notify2Temp<T: Summary + DefaultSummary>(item: T) {
    println!("notify2Temp : {}, {}", item.summarize(), item.summarizing());
}

trait Display {}
trait Debug {}
/*

*** Clearer Trait Bounds with where Clauses

Using too many trait bounds has its downsides.
Each generic has its own trait bounds, so functions with multiple generic type parameters can contain lots of trait bound information between the function’s name and its parameter list,
making the function signature hard to read. For this reason, Rust has alternate syntax for specifying trait bounds inside a where clause after the function signature.

like:
fn some_function<T: Display + Clone, U: Clone + Debug>(t: T, u: U) -> i32 {
*/
fn some_function<T, U>(t: T, u: U) -> i32
where
    T: Display + Clone,
    U: Clone + Debug,
{
    return 0;
}

/*

Returning Types that Implement Traits
We can also use the impl Trait syntax in the return position to return a value of some type that implements a trait, as shown here:

The ability to return a type that is only specified by the trait it implements is especially useful in the context of closures and iterators,

Closures and iterators create types that only the compiler knows or types that are very long to specify.
The impl Trait syntax lets you concisely specify that a function returns some type that implements the Iterator trait without needing to write out a very long type.
*/
fn returns_summarizable() -> impl Summary {
    Tweet {
        username: String::from("horse_ebooks"),
        content: String::from("of course, as you probably already know, people"),
        reply: false,
        retweet: false,
    }
}

pub fn test_traits() {
    let tweet = Tweet {
        username: String::from("host_ebooks"),
        content: String::from("of course, aka people"),
        reply: false,
        retweet: false,
    };

    println!("new tweet: {}", tweet.summarize());

    println!("tweet call default implementation: {}", tweet.summarizing());

    let nart = NewsArticle {
        headline: String::from("new headline"),
        location: String::from("new location"),
        author: String::from("new author"),
        content: String::from("new content"),
    };

    println!("nart: {}", nart.summarize());

    println!("nart: {}", nart.summarizing());

    let article = Create_News_Article();
    println!("article summarize : {}", article.summarize());

    let tweet = create_tweet();
    println!("tweet summarzie : {}", tweet.summarize());
    // println!("tweet summarizing in (defaultSummary): {}", tweet.summarizing());

    notify(article);

    notify(tweet);

    notify(nart);

    // template

    //notifyTemp(tweet);
}

/*

Traits and trait bounds let us write code that uses generic type parameters to reduce duplication but also specify to the compiler that we want the generic type to have particular behavior.
The compiler can then use the trait bound information to check that all the concrete types used with our code provide the correct behavior.
In dynamically typed languages, we would get an error at runtime if we called a method on a type which didn’t implement the type which defines the method.
But Rust moves these errors to compile time so we’re forced to fix the problems before our code is even able to run.
Additionally, we don’t have to write code that checks for behavior at runtime because we’ve already checked at compile time.
Doing so improves performance without having to give up the flexibility of generics.

Another kind of generic that we’ve already been using is called lifetimes.
Rather than ensuring that a type has the behavior we want, lifetimes ensure that references are valid as long as we need them to be. Let’s look at how lifetimes do that.
*/
