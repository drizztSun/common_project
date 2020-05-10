use std::string;

fn test_string_basic() {
    {
        // str => String
        let data = "initial strings";
        let s = data.to_string(); // anything with 'Display' function has this

        let s1 = "initial strings".to_string(); // the method also works on a literal directly:
        let s2 = String::from("initial strings");
    }

    // Remember that st rings are UTF-8 encoded, so we can include any properly encoded data in them,
    /*
    let hello = String::from("السلام عليكم");
    let hello = String::from("Dobrý den");
    let hello = String::from("Hello");
    let hello = String::from("שָׁלוֹם");
    let hello = String::from("नमस्ते");
    let hello = String::from("こんにちは");
    let hello = String::from("안녕하세요");
    let hello = String::from("你好");
    let hello = String::from("Olá");
    let hello = String::from("Здравствуйте");
    let hello = String::from("Hola");
     */

    {
        // Appending to a String with push_str and push
        let mut s = String::new();
        s.push_str("hello ");
        s.push_str("world");

        println!("s is {}", s);

        s.push('N');
    }

    {
        // concatenation with + Operator or the format! Macro
        let s1 = String::from("tic");
        let s2 = String::from("tac");
        let s3 = String::from("toe");

        let s = s1 + "-" + &s2 + "-" + &s3;
        println!("s = {}", s);

        let mut s4 = String::from("tic");
        let f = format!("{}-{}-{}", s4, s2, s3);
        println!("f = {}", f);

        /*
        The string s3 will contain Hello, world! as a result of this code. The reason s1 is no longer valid after the addition and the reason we used a reference to s2 has to do with the signature of the method that gets called when we use the + operator. The + operator uses the add method, whose signature looks something like this:


        fn add(self, s: &str) -> String {
        This isn’t the exact signature that’s in the standard library: in the standard library, add is defined using generics.
        Here, we’re looking at the signature of add with concrete types substituted for the generic ones, which is what happens when we call this method with String values. We’ll discuss generics in Chapter 10. This signature gives us the clues we need to understand the tricky bits of the + operator.

        First, s2 has an &, meaning that we’re adding a reference of the second string to the first string because of the s parameter in the add function:
        we can only add a &str to a String; we can’t add two String values together. But wait—the type of &s2 is &String, not &str,
        as specified in the second parameter to add. So why does Listing 8-18 compile?

        The reason we’re able to use &s2 in the call to add is that the compiler can coerce the &String argument into a &str.
        When we call the add method, Rust uses a deref coercion, which here turns &s2 into &s2[..].
        We’ll discuss deref coercion in more depth in Chapter 15. Because add does not take ownership of the s parameter,
        s2 will still be a valid String after this operation.

        Second, we can see in the signature that add takes ownership of self, because self does not have an &.
        This means s1 in Listing 8-18 will be moved into the add call and no longer be valid after that.
        So although let s3 = s1 + &s2; looks like it will copy both strings and create a new one,
        this statement actually takes ownership of s1, appends a copy of the contents of s2, and then returns ownership of the result.
        In other words, it looks like it’s making a lot of copies but isn’t; the implementation is more efficient than copying.
        */
    }

    {
        // ***
        // index in strings
        /*
        n many other programming languages, accessing individual characters in a string by referencing them by index is a valid and common operation. However, if you try to access parts of a String using indexing syntax in Rust, you’ll get an error. Consider the invalid code in Listing 8-19.


        let s1 = String::from("hello");
        let h = s1[0];
        Listing 8-19: Attempting to use indexing syntax with a String

        This code will result in the following error:


        error[E0277]: the trait bound `std::string::String: std::ops::Index<{integer}>` is not satisfied
        -->
        |
        3 |     let h = s1[0];
        |             ^^^^^ the type `std::string::String` cannot be indexed by `{integer}`
        |
        = help: the trait `std::ops::Index<{integer}>` is not implemented for `std::string::String`

        */
    }

    {
        // internal representation
        // A String is a wrapper over a Vec<u8>. Let’s look at some of our properly encoded UTF-8 example strings from Listing 8-14. First, this one:
        let len = String::from("Hola").len();
        /*
        In this case, len will be 4, which means the vector storing the string “Hola” is 4 bytes long.
        Each of these letters takes 1 byte when encoded in UTF-8. But what about the following line?
        (Note that this string begins with the capital Cyrillic letter Ze, not the Arabic number 3.)
        */
        let len1 = String::from("Здравствуйте").len();
        /*
        Asked how long the string is, you might say 12. However, Rust’s answer is 24:
        that’s the number of bytes it takes to encode “Здравствуйте” in UTF-8, because each Unicode scalar value in that string takes 2 bytes of storage.
        Therefore, an index into the string’s bytes will not always correlate to a valid Unicode scalar value. To demonstrate, consider this invalid Rust code:
        */
    }

    {
        /*
        Methods for Iterating Over Strings Fortunately, you can access elements in a string in other ways.
        If you need to perform operations on individual Unicode scalar values, the best way to do so is to use the chars method.
        Calling chars on “नमस्ते” separates out and returns six values of type char, and you can iterate over the result to access each element:
         */
        for c in "नमस्ते".chars() {
            println!("{}", c);
        }

        /*
        The bytes method returns each raw byte, which might be appropriate for your domain:
        */
        for b in "नमस्ते".bytes() {
            println!("{}", b);
        }
    }
}

fn test_string_to_int() {
    let s = String::from("123");

    // s is parsed to 32-bits signed integer here (change number type if needed).
    // -1 is used here as a fallback value, but any error handling instructions can be used.
    let i = match s.parse::<i32>() {
        Ok(i) => i,
        Err(_e) => -1,
    };
    println!("what is in s {} ", i);

    // This explicitly sets the value to 0 if it can't be parsed to an integer.
    let i: i32 = s.parse().unwrap_or(0);
    println!("what is in s {} ", i);

    //
    // This panics if s is not a valid number.
    // s is parsed to 32-bits signed integer here (change number type if needed).
    let i = s.parse::<i32>().unwrap();
    println!("what is in s {} ", i);
    //
    let num: i32 = s.trim().parse().expect("Except error happened");
    println!("What is in s {}", num);
}

pub fn test_string() {
    test_string_basic();

    test_string_to_int();
}
