/*
A fixed-size array, denoted [T; N], for the element type, T, and the non-negative compile-time constant size, N.

There are two syntactic forms for creating an array:

A list with each element, i.e., [x, y, z].
A repeat expression [x; N], which produces an array with N copies of x. The type of x must be Copy.
Arrays of sizes from 0 to 32 (inclusive) implement the following traits if the element type allows it:

Debug
IntoIterator (implemented for &[T; N] and &mut [T; N])
PartialEq, PartialOrd, Eq, Ord
Hash
AsRef, AsMut
Borrow, BorrowMut
Default
This limitation on the size N exists because Rust does not yet support code that is generic over the size of an array type. 
[Foo; 3] and [Bar; 3] are instances of same generic type [T; 3], but [Foo; 3] and [Foo; 5] are entirely different types. 
As a stopgap, trait implementations are statically generated up to size 32.

Arrays of any size are Copy if the element type is Copy and Clone if the element type is Clone. 
This works because Copy and Clone traits are specially known to the compiler.

Arrays coerce to slices ([T]), so a slice method may be called on an array. 
Indeed, this provides most of the API for working with arrays. Slices have a dynamic size and do not coerce to arrays.

You can move elements out of an array with a slice pattern. If you want one element, see mem::replace.
*/

fn move_away(_: String) {

}

fn test_basic() {

    let mut array: [i32, 3] = [0, 3];

    array[1] = 1;
    array[2] = 2;

    assert_eq!([1, 2], &array[1..]);
    println!("array is {}", array);

    // An array itself is not iterable:
    // The solution is to coerce the array to a slice by calling a slice method:
    for x in array.iter() {
        println!("{}", x);
    }

    // If the array has 32 or fewer elements (see above), you can also use the array reference's IntoIterator implementation:
    for x in &array {
        println!("{}", x);
    }

    // You can use a slice pattern to move elements out of an array:
    let [john, roa] = ["John".to_string(), "Roa".to_string()];
    move_away(john);
    move_away(roa);
}

pub fn test_array() {

    test_array();
}