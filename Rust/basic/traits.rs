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
use std::fmt;

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

// trait as parameters
/*
Instead of a concrete type for the item parameter, we specify the impl keyword and the trait name.
This parameter accepts any type that implements the specified trait.
In the body of notify, we can call any methods on item that come from the Summary trait, such as summarize.
We can call notify and pass in any instance of NewsArticle or Tweet.
Code that calls the function with any other type, such as a String or an i32, won’t compile because those types don’t implement Summary.
 */
pub fn notify(item: impl Summary) {
    println!("Breaking news ! {}", item.summarize());
}

// Trait Bound Syntax
/*
The impl Trait syntax works for straightforward cases but is actually syntax sugar for a longer form,
which is called a trait bound; it looks like this:
*/
pub fn notifyTemp<T: Summary>(item: &T) {
    println!("Breaking news !{}", item.summarize());
}

// Specifing multiple trait bounds with the + syntax
/*
We can also specify more than one trait bound.
Say we wanted notify to use display formatting on item as well as the summarize method:
we specify in the notify definition that item must implement both Display and Summary
*/
pub fn notify2(item: impl Summary + DefaultSummary) {
    println!("notify2 : {}, {}", item.summarize(), item.summarizing());
}

pub fn notify2Temp<T: Summary + DefaultSummary>(item: &T) {
    println!("notify2Temp : {}, {}", item.summarize(), item.summarizing());
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
