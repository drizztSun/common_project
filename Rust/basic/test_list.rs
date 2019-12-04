// Allow Cons and Nil to be referred to without namespacing
use List::{Cons, Nil};

// A linked list node, which can take on any of these two variants
enum List {
    // Cons: Tuple struct that wraps an element and a pointer to the next node
    Cons(u32, Box<List>),
    // Nil: A node that signifies the end of the linked list
    Nil,
}

// Methods can be attached to an enum
impl List {
    // Create an empty list
    fn new() -> List {
        // `Nil` has type `List`
        Nil
    }

    // Consume a list, and return the same list with a new element at its front
    fn prepend(self, x: u32) -> List {
        // `Cons` also has type List
        Cons(x, Box::new(self))
    }

    // Return the length of the list
    fn len(&self) -> u32 {
        // `self` has to be matched, because the behavior of this method
        // depends on the variant of `self`
        // `self` has type `&List`, and `*self` has type `List`, matching on a
        // concrete type `T` is preferred over a match on a reference `&T`
        match *self {
            // Can't take ownership of the tail, because `self` is borrowed;
            // instead take a reference to the tail
            Cons(_, ref tail) => 1 + tail.len(),
            // Base Case: An empty list has zero length
            Nil => 0,
        }
    }

    // return representation of a list as a (HEAP allocated) string
    fn stringify(&self) -> String {
        match *self {
            Cons(header, ref tail) => {
                // 'format!' is similiar as 'print!', but return a heap
                format!("{}, {}", header, tail.stringify())
            }
            Nil => format!("Nil"),
        }
    }
}

pub fn test_list() {
    // create empty list
    let mut lt = List::new();

    // append some elements
    lt = lt.prepend(1);
    lt = lt.prepend(2);
    lt = lt.prepend(3);

    // show the final state of the list
    println!("linked list the length: {}, {}", lt.len(), lt.stringify())
}
