use std::collections::BTreeMap;

/*
A map based on a B-Tree.

B-Trees represent a fundamental compromise between cache-efficiency and actually minimizing the amount of work performed in a search.
In theory, a binary search tree (BST) is the optimal choice for a sorted map, as a perfectly balanced BST performs the theoretical minimum amount of comparisons necessary to find an element (log2n). However, in practice the way this is done is very inefficient for modern computer architectures. In particular, every element is stored in its own individually heap-allocated node. This means that every single insertion triggers a heap-allocation, and every single comparison should be a cache-miss. Since these are both notably expensive things to do in practice, we are forced to at very least reconsider the BST strategy.

A B-Tree instead makes each node contain B-1 to 2B-1 elements in a contiguous array.
By doing this, we reduce the number of allocations by a factor of B, and improve cache efficiency in searches. However, this does mean that searches will have to do more comparisons on average. The precise number of comparisons depends on the node search strategy used. For optimal cache efficiency, one could search the nodes linearly. For optimal comparisons, one could search the node using binary search. As a compromise, one could also perform a linear search that initially only checks every ith element for some choice of i.

Currently, our implementation simply performs naive linear search. This provides excellent performance on small nodes of elements which are cheap to compare. However in the future we would like to further explore choosing the optimal search strategy based on the choice of B, and possibly other factors. Using linear search, searching for a random element is expected to take O(B logBn) comparisons, which is generally worse than a BST. In practice, however, performance is excellent.

It is a logic error for a key to be modified in such a way that the key's ordering relative to any other key, as determined by the Ord trait, changes while it is in the map. This is normally only possible through Cell, RefCell, global state, I/O, or unsafe code.
*/

fn test_btree_basic() {
    // type inference lets us omit an explicit type signature (which
    // would be `BTreeMap<&str, &str>` in this example).
    let mut movie_reviews = BTreeMap::new();

    // review some movies.
    movie_reviews.insert("Office Space", "Deals with real issues in the workplace.");
    movie_reviews.insert("Pulp Fiction", "Masterpiece.");
    movie_reviews.insert("The Godfather", "Very enjoyable.");
    movie_reviews.insert("The Blues Brothers", "Eye lyked it a lot.");

    // check for a specific one.
    if !movie_reviews.contains_key("Les Misérables") {
        println!(
            "We've got {} reviews, but Les Misérables ain't one.",
            movie_reviews.len()
        );
    }

    // oops, this review has a lot of spelling mistakes, let's delete it.
    movie_reviews.remove("The Blues Brothers");

    // look up the values associated with some keys.
    let to_find = ["Up!", "Office Space"];
    for movie in &to_find {
        match movie_reviews.get(movie) {
            Some(review) => println!("{}: {}", movie, review),
            None => println!("{} is unreviewed.", movie),
        }
    }

    // Look up the value for a key (will panic if the key is not found).
    println!("Movie review: {}", movie_reviews["Office Space"]);

    // iterate over everything.
    for (movie, review) in &movie_reviews {
        println!("{}: \"{}\"", movie, review);
    }

    movie_reviews.clear();
    assert!(movie_reviews.is_empty());
}

fn test_btree_entryapi() {
    // type inference lets us omit an explicit type signature (which
    // would be `BTreeMap<&str, u8>` in this example).
    let mut player_stats = BTreeMap::new();

    fn random_stat_buff() -> u8 {
        // could actually return some random value here - let's just return
        // some fixed value for now
        42
    }

    // insert a key only if it doesn't already exist
    player_stats.entry("health").or_insert(100);

    // insert a key using a function that provides a new value only if it
    // doesn't already exist
    player_stats
        .entry("defence")
        .or_insert_with(random_stat_buff);

    // update a key, guarding against the key possibly not being set
    let stat = player_stats.entry("attack").or_insert(100);
    *stat += random_stat_buff();
}

pub fn test_btree() {
    test_btree_basic();

    test_btree_entryapi();
}
