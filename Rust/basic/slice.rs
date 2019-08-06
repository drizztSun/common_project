use std::io;

fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[..i];
        }
    }
    &s[..]
}

fn test_slice_test() {

    let word = String::from("Hello world");

    let s = first_word(&word);
    println!("s = {}", s);

    let s = String::from("Hello world");
    let length = s.len();

    let hello = &s[0..5];
    let world = &s[6..length];

    println!("Hello {}, world {}", hello, world);

    let hello1 = &s[..5];
    println!(" {} == {} ", hello, hello1);

    let world1 = &s[6..];
    println!("{} == {}", world, world1);

    // whole word

    let wholeword = &s[0..length];
    let wholeword1 = &s[..];
    println!("{} == {}", wholeword, wholeword1);
}

fn test_slice() {

    test_slice_test();
}