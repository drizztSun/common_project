/*
A hash set implemented as a HashMap where the value is ().

As with the HashMap type, a HashSet requires that the elements implement the Eq and Hash traits. This can frequently be achieved by using #[derive(PartialEq, Eq, Hash)]. If you implement these yourself, it is important that the following property holds:

k1 == k2 -> hash(k1) == hash(k2)
In other words, if two keys are equal, their hashes must be equal.

It is a logic error for an item to be modified in such a way that the item's hash, as determined by the Hash trait, or its equality, as determined by the Eq trait, changes while it is in the set. This is normally only possible through Cell, RefCell, global state, I/O, or unsafe code.
*/

use std::collections::HashSet;
use std::collections::hash_map::RandomState;


fn test_hashset_basic() {

    { // create
        let mut books = HashSet::new();
        books.insert("A Dance With Dragons".to_string());


        let viking_names: HashSet<&'static str> =
            [ "Einar", "Olaf", "Harald" ].iter().cloned().collect();
        
        let set: HashSet<i32> = HashSet::with_capacity(10);
        assert!(set.capacity() >= 10);

        // Creates an empty HashSet with the specified capacity, using hasher to hash the keys.
        // The hash set will be able to hold at least capacity elements without reallocating. If capacity is 0, the hash set will not allocate.
        let s = RandomState::new();
        let mut set = HashSet::with_capacity_and_hasher(10, s);
        set.insert(1);

        // Creates a new empty hash set which will use the given hasher to hash keys.
        // The hash set is also created with the default initial capacity.
        // Warning: hasher is normally randomly generated, and is designed to allow HashSets to be resistant to attacks that cause many collisions and very poor performance. 
        // Setting it manually using this function can expose a DoS attack vector.
        let s = RandomState::new();
        let mut set = HashSet::with_hasher(s);
        set.insert(2);
    }

    {   // insert
        let mut set = HashSet::new();

        assert_eq!( set.insert(2), true);
        assert_eq!( set.insert(2), false);
        assert_eq!( set.len(), 1);

        let set: HashSet<_> = [1, 2, 3].iter().cloned().collect();
        assert_eq!( set.get(&2), Some(&2));
        assert_eq!( set.get(&4), None);

        assert_eq!( set.len(), 3);
        // assert_eq!( set.get_or_insert(2), &2);
        // assert_eq!( set.get_or_insert(100), &100);
        assert_eq!( set.len(), 4); // 100 was inserted
    }

    {
        // contain
        let set: HashSet<_> = [1, 2, 3].iter().cloned().collect();
        assert_eq!( set.contains(&1), true);
        assert_eq!( set.contains(&4), false);
    }

    {
        // difference
        // Visits the values representing the difference, i.e., the values that are in self but not in other.
        let a: HashSet<_> = [1, 2, 3].iter().cloned().collect();
        let b: HashSet<_> = [4, 2, 3, 4].iter().cloned().collect();

        // Can be seen as `a - b`.
        for x in a.difference(&b) {
            println!("{}", x); // Print 1
        }

        let diff: HashSet<_> = a.difference(&b).collect();
        assert_eq!(diff, [1].iter().collect());

        // Note that difference is not symmetric,
        // and `b - a` means something else:
        let diff: HashSet<_> = b.difference(&a).collect();
        assert_eq!(diff, [4].iter().collect());
    }

    {
        // intersection
        // Visits the values representing the intersection, i.e., the values that are both in self and other.
        let a: HashSet<_> = [1, 2, 3].iter().cloned().collect();
        let b: HashSet<_> = [4, 2, 3, 4].iter().cloned().collect();

        // Print 2, 3 in arbitrary order.
        for x in a.intersection(&b) {
            println!("{}", x);
        }

        let intersection: HashSet<_> = a.intersection(&b).collect();
        assert_eq!(intersection, [2, 3].iter().collect());
    }

    {
        // union
        // Visits the values representing the union, i.e., all the values in self or other, without duplicates.
        let a: HashSet<_> = [1, 2, 3].iter().cloned().collect();
        let b: HashSet<_> = [4, 2, 3, 4].iter().cloned().collect();

        // Print 1, 2, 3, 4 in arbitrary order.
        for x in a.union(&b) {
            println!("{}", x);
        }

        let union: HashSet<_> = a.union(&b).collect();
        assert_eq!(union, [1, 2, 3, 4].iter().collect());
    }

    {
        // is_disjoint
        // Returns true if self has no elements in common with other. This is equivalent to checking for an empty intersection

        let a: HashSet<_> = [1, 2, 3].iter().cloned().collect();
        let mut b = HashSet::new();

        assert_eq!(a.is_disjoint(&b), true);
        b.insert(4);
        assert_eq!(a.is_disjoint(&b), true);
        b.insert(1);
        assert_eq!(a.is_disjoint(&b), false);
    }

    {
        // is_subset
        // Returns true if the set is a subset of another, i.e., other contains at least all the values in self.
        let sup: HashSet<_> = [1, 2, 3].iter().cloned().collect();
        let mut set = HashSet::new();

        assert_eq!(set.is_subset(&sup), true);
        set.insert(2);
        assert_eq!(set.is_subset(&sup), true);
        set.insert(4);
        assert_eq!(set.is_subset(&sup), false);
    }

    {
        // is_subset
        // Returns true if the set is a superset of another, i.e., self contains at least all the values in other.
        let sub: HashSet<_> = [1, 2].iter().cloned().collect();
        let mut set = HashSet::new();

        assert_eq!(set.is_superset(&sub), false);

        set.insert(0);
        set.insert(1);
        assert_eq!(set.is_superset(&sub), false);

        set.insert(2);
        assert_eq!(set.is_superset(&sub), true);
    }

    {
        // iter
        // An iterator visiting all elements in arbitrary order. The iterator element type is &'a T.
        let mut set = HashSet::new();
        set.insert("a");
        set.insert("b");

        // Will print in an arbitrary order.
        for x in set.iter() {
            println!("{}", x);
        }
    }

    {
        
    }

    {
        // drain
        // Clears the set, returning all elements in an iterator.

        let mut set: HashSet<_> = [1, 2, 3].iter().cloned().collect();
        assert_eq!( set.is_empty(), false);

        for i in set.drain() {
            println!("{}", i);
        }

        assert_eq!( set.is_empty(), true);
    }

    {
        // hasher
        let hasher = RandomState::new();
        let set: HashSet<i32> = HashSet::with_hasher(hasher);
        let hasher: &RandomState = set.hasher();
    }

} 

fn test_hashset_example() {
    // Type inference lets us omit an explicit type signature (which
    // would be `HashSet<String>` in this example).
    let mut books = HashSet::new();

    // Add some books.
    books.insert("A Dance With Dragons".to_string());
    books.insert("To Kill a Mockingbird".to_string());
    books.insert("The Odyssey".to_string());
    books.insert("The Great Gatsby".to_string());

    // Check for a specific one.
    if !books.contains("The Winds of Winter") {
        println!("We have {} books, but The Winds of Winter ain't one.",
                books.len());
    }

    // Remove a book.
    books.remove("The Odyssey");

    // Iterate over everything.
    for book in &books {
        println!("{}", book);
    }


    let mut vikings = HashSet::new();

    vikings.insert(Viking { name: "Einar".to_string(), power: 9 });
    vikings.insert(Viking { name: "Einar".to_string(), power: 9 });
    vikings.insert(Viking { name: "Olaf".to_string(), power: 4 });
    vikings.insert(Viking { name: "Harald".to_string(), power: 8 });

    // Use derived implementation to print the vikings.
    for x in &vikings {
        println!("{:?}", x);
    }

    // A HashSet with fixed list of elements can be initialized from an array:
    let viking_names: HashSet<&'static str> =
        [ "Einar", "Olaf", "Harald" ].iter().cloned().collect();
    // use the values stored in the set
}

// The easiest way to use HashSet with a custom type is to derive Eq and Hash.
// We must also derive PartialEq, this will in the future be implied by Eq.
#[derive(Hash, Eq, PartialEq, Debug)]
struct Viking {
    name: String,
    power: usize,
}




pub fn test_hashset() {

    test_hashset_basic();

    test_hashset_example();

}