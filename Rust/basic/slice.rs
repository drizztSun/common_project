use std::io;

/*

The Slice Type
Another data type that does not have ownership is the slice.
Slices let you reference a contiguous sequence of elements in a collection rather than the whole collection.

*/

fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[..i];
        }
    }
    &s[..]
}

fn first_word_slice(s: &str) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[..i];
        }
    }
    &s[..]
}

fn test_slice_test() {
    /*
    String Slices
    A string slice is a reference to part of a String, and it looks like this:

    This is similar to taking a reference to the whole String but with the extra [0..5] bit.
    Rather than a reference to the entire String, it’s a reference to a portion of the String.

    We can create slices using a range within brackets by specifying [starting_index..ending_index],
    where starting_index is the first position in the slice and ending_index is one more than the last position in the slice.

    Internally, the slice data structure stores the starting position and the length of the slice, which corresponds to ending_index minus starting_index.
    */
    let word = String::from("Hello world");

    let s = first_word(&word);
    println!("s = {}", s);

    let s = String::from("Hello world");
    let length = s.len();

    let hello = &s[0..5];
    let world = &s[6..length];

    println!("Hello {}, world {}", hello, world);

    /*
    Note: String slice range indices must occur at valid UTF-8 character boundaries.
    If you attempt to create a string slice in the middle of a multibyte character, your program will exit with an error.
    */

    let hello1 = &s[..5];
    println!(" {} == {} ", hello, hello1);

    let world1 = &s[6..];
    println!("{} == {}", world, world1);

    // whole word

    let wholeword = &s[0..length];
    let wholeword1 = &s[..];
    println!("{} == {}", wholeword, wholeword1);

    // String Literals Are Slices
    // Recall that we talked about string literals being stored inside the binary. Now that we know about slices, we can properly understand string literals:
    let s = "Hello world";
    // The type of s here is &str: it’s a slice pointing to that specific point of the binary. This is also why string literals are immutable; &str is an immutable reference.

    // String Slices as Parameters
    // Knowing that you can take slices of literals and String values leads us to one more improvement on first_word, and that’s its signature:
    // A more experienced Rustacean would write the signature shown in Listing 4-9 instead because it allows us to use the same function on both &String values and &str values.

    // If we have a string slice, we can pass that directly. If we have a String, we can pass a slice of the entire String.
    // Defining a function to take a string slice instead of a reference to a String makes our API more general and useful without losing any functionality:
    {
        let my_string = String::from("hello world");

        // first_word works on slices of `String`s
        let word = first_word_slice(&my_string[..]);

        let my_string_literal = "hello world";

        // first_word works on slices of string literals
        let word = first_word_slice(&my_string_literal[..]);

        // Because string literals *are* string slices already,
        // this works too, without the slice syntax!
        let word = first_word_slice(my_string_literal);
    }

    // other slice
    // String slices, as you might imagine, are specific to strings. But there’s a more general slice type, too. Consider this array:
    let a = [1, 2, 3, 4, 5];

    // Just as we might want to refer to a part of a string, we might want to refer to part of an array.
    let slice = &a[1..3];

    println!("slice of a[1..3] is {:?} ", slice);

    // This slice has the type &[i32]. It works the same way as string slices do, by storing a reference to the first element and a length.
    // You’ll use this kind of slice for all sorts of other collections.
}

pub fn test_slice() {
    test_slice_test();
}
