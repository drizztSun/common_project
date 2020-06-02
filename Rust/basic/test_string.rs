use std::str;
use std::string;

/*
    *** Strings ***
There are two types of strings in Rust: String and &str.

A String is stored as a vector of bytes (Vec<u8>), but guaranteed to always be a valid UTF-8 sequence.
String is heap allocated, growable and not null terminated.

&str is a slice (&[u8]) that always points to a valid UTF-8 sequence, and can be used to view into a String, just like &[T] is a view into Vec<T>.

*/

fn test_string_basic1() {
    // (all the type annotations are superfluous)
    // A reference to a string allocated in read only memory
    let pangram: &'static str = "the quick brown fox jumps over the lazy dog";
    println!("Pangram: {}", pangram);

    // Iterate over words in reverse, no new string is allocated
    println!("Words in reverse");
    for word in pangram.split_whitespace().rev() {
        println!("> {}", word);
    }

    // Copy chars into a vector, sort and remove duplicates
    let mut chars: Vec<char> = pangram.chars().collect();
    chars.sort();
    chars.dedup();

    // Create an empty and growable `String`
    let mut string = String::new();
    for c in chars {
        // Insert a char at the end of string
        string.push(c);
        // Insert a string at the end of string
        string.push_str(", ");
    }

    // The trimmed string is a slice to the original string, hence no new
    // allocation is performed
    let chars_to_trim: &[char] = &[' ', ','];
    let trimmed_str: &str = string.trim_matches(chars_to_trim);
    println!("Used characters: {}", trimmed_str);

    // Heap allocate a string
    let alice = String::from("I like dogs");
    // Allocate new memory and store the modified string there
    let bob: String = alice.replace("dog", "cat");

    println!("Alice says: {}", alice);
    println!("Bob says: {}", bob);

    // *** Literals and escapes ***
    // There are multiple ways to write string literals with special characters in them.
    // All result in a similar &str so it's best to use the form that is the most convenient to write.
    // Similarly there are multiple ways to write byte string literals, which all result in &[u8; N].

    // Generally special characters are escaped with a backslash character: \.
    // This way you can add any character to your string, even unprintable ones and ones that you don't know how to type.
    // If you want a literal backslash, escape it with another one: \\

    // String or character literal delimiters occuring within a literal must be escaped: "\"", '\''.
    {
        // You can use escapes to write bytes by their hexadecimal values...
        let byte_escape = "I'm writing \x52\x75\x73\x74!";
        println!("What are you doing\x3F (\\x3F means ?) {}", byte_escape);

        // ...or Unicode code points.
        let unicode_codepoint = "\u{211D}";
        let character_name = "\"DOUBLE-STRUCK CAPITAL R\"";

        println!(
            "Unicode character {} (U+211D) is called {}",
            unicode_codepoint, character_name
        );

        let long_string = "String literals
                            can span multiple lines.
                            The linebreak and indentation here ->\
                            <- can be escaped too!";
        println!("{}", long_string);
    }

    // Sometimes there are just too many characters that need to be escaped or it's just much more convenient to write a string out as-is.
    // This is where raw string literals come into play.
    {
        let raw_str = r"Escapes don't work here: \x3F \u{211D}";
        println!("{}", raw_str);
        // If you need quotes in a raw string, add a pair of #s
        let quotes = r#"And then I said: "There is no escape!""#;
        println!("{}", quotes);
        // If you need "# in your string, just use more #s in the delimiter.
        // There is no limit for the number of #s you can use.
        let longer_delimiter = r###"A string with "# in it. And even "##!"###;
        println!("{}", longer_delimiter);
    }

    // Want a string that's not UTF-8? (Remember, str and String must be valid UTF-8).
    // Or maybe you want an array of bytes that's mostly text? Byte strings to the rescue!
    {
        // Note that this is not actually a `&str`
        let bytestring: &[u8; 21] = b"this is a byte string";

        // Byte arrays don't have the `Display` trait, so printing them is a bit limited
        println!("A byte string: {:?}", bytestring);

        // Byte strings can have byte escapes...
        let escaped = b"\x52\x75\x73\x74 as bytes";
        // ...but no unicode escapes
        // let escaped = b"\u{211D} is not allowed";
        println!("Some escaped bytes: {:?}", escaped);

        // Raw byte strings work just like raw strings
        let raw_bytestring = br"\u{211D} is not escaped here";
        println!("{:?}", raw_bytestring);

        // Converting a byte array to `str` can fail
        if let Ok(my_str) = str::from_utf8(raw_bytestring) {
            println!("And the same as text: '{}'", my_str);
        }

        let _quotes = br#"You can also use "fancier" formatting, \
                        like with normal raw strings"#;

        // Byte strings don't have to be UTF-8
        let shift_jis = b"\x82\xe6\x82\xa8\x82\xb1\x82"; // "ようこそ" in SHIFT-JIS

        // But then they can't always be converted to `str`
        match str::from_utf8(shift_jis) {
            Ok(my_str) => println!("Conversion successful: '{}'", my_str),
            Err(e) => println!("Conversion failed: {:?}", e),
        };
    }
}

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
        // note s1 has been moved here and can no longer be used
        // let s = s1.clone() + "-" + &s2 + "-" + &s3;
        // println!("s1 = {}", s1);
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
        // *** internal representation
        // A String is a wrapper over a Vec<u8>.
        // Let’s look at some of our properly encoded UTF-8 example strings from Listing 8-14. First, this one:
        let len = String::from("Hola").len();
        assert_eq!(len, 4);
        /*
        In this case, len will be 4, which means the vector storing the string “Hola” is 4 bytes long.
        Each of these letters takes 1 byte when encoded in UTF-8. But what about the following line?
        (Note that this string begins with the capital Cyrillic letter Ze, not the Arabic number 3.)
        */
        let len1 = String::from("Здравствуйте").len();
        assert_eq!(len1, 24);
        /*
        Asked how long the string is, you might say 12. However, Rust’s answer is 24:
        that’s the number of bytes it takes to encode “Здравствуйте” in UTF-8, because each Unicode scalar value in that string takes 2 bytes of storage.
        Therefore, an index into the string’s bytes will not always correlate to a valid Unicode scalar value. To demonstrate, consider this invalid Rust code:
        */
        let hello = "Здравствуйте";
        // let answer = &hello[0];
        // To avoid returning an unexpected value and causing bugs that might not be discovered immediately,
        // Rust doesn’t compile this code at all and prevents misunderstandings early in the development process.

        // *** Bytes and Scalar Values and Grapheme Clusters! Oh My!
        // Another point about UTF-8 is that there are actually three relevant ways to look at strings
        // from Rust’s perspective:
        //              as bytes,
        //              scalar values, and
        //              grapheme clusters (the closest thing to what we would call letters).

        // If we look at the Hindi word “नमस्ते” written in the Devanagari script, it is stored as a vector of u8 values that looks like this:
        // [224, 164, 168, 224, 164, 174, 224, 164, 184, 224, 165, 141, 224, 164, 164, 224, 165, 135]
        // That’s 18 bytes and is how computers ultimately store this data.

        //If we look at them as Unicode scalar values, which are what Rust’s char type is, those bytes look like this:
        // ['न', 'म', 'स', '्', 'त', 'े']
        // There are six char values here, but the fourth and sixth are not letters: they’re diacritics that don’t make sense on their own.

        // Finally, if we look at them as grapheme clusters, we’d get what a person would call the four letters that make up the Hindi word:
        // ["न", "म", "स्", "ते"]

        // Rust provides different ways of interpreting the raw string data that computers store so that each program can choose the interpretation it needs,
        // no matter what human language the data is in.

        // A final reason Rust doesn’t allow us to index into a String to get a character is that indexing operations are expected to always take constant time (O(1)).
        // But it isn’t possible to guarantee that performance with a String, because Rust would have to walk through the contents from the beginning to the index to determine how many valid characters there were.

        let s = &hello[0..4]; // s will be &str
        println!("{}", s);
        // What would happen if we used &hello[0..1]? The answer: Rust would panic at runtime in the same way as if an invalid index were accessed in a vector:
        // s = &hello[0..5] // it caused panic because it is not char boundary.
    }

    {
        /*
        *** Methods for Iterating Over Strings
        Fortunately, you can access elements in a string in other ways.
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
