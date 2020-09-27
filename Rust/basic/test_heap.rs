/*
A priority queue implemented with a binary heap.
This will be a max-heap.
It is a logic error for an item to be modified in such a way that the item's ORDERing relative to any other item,
as determined by the Ord trait, changes while it is in the heap.
This is normally only possible through Cell, RefCell, global state, I/O, or unsafe code.
*/
use std::cmp::Ordering;
use std::cmp::Reverse;
use std::collections::BinaryHeap;

fn test_binaryheap_basic() {
    // Type inference lets us omit an explicit type signature (which
    // would be `BinaryHeap<i32>` in this example).
    let mut heap = BinaryHeap::new();

    let mut heap1 = BinaryHeap::with_capacity(10);
    heap1.push(4);

    // We can use peek to look at the next item in the heap. In this case,
    // there's no items in there yet so we get None.
    assert_eq!(heap.peek(), None);

    // Let's add some scores...
    heap.push(1);
    heap.push(5);
    heap.push(2);

    // Now peek shows the most important item in the heap.
    assert_eq!(heap.peek(), Some(&5));

    // We can check the length of a heap.
    assert_eq!(heap.len(), 3);

    // capacity
    assert!(heap.capacity() >= 3);

    // We can iterate over the items in the heap, although they are returned in
    // a random order.
    for x in &heap {
        println!("{}", x);
    }

    // If we instead pop these scores, they should come back in order.
    assert_eq!(heap.pop(), Some(5));
    assert_eq!(heap.pop(), Some(2));
    assert_eq!(heap.pop(), Some(1));
    assert_eq!(heap.pop(), None);

    // We can clear the heap of any remaining items.
    heap.clear();

    // The heap should now be empty.
    assert!(heap.is_empty())
}

fn test_mini_heap() {
    // Either std::cmp::Reverse or a custom Ord implementation can be used to make BinaryHeap a min-heap.
    // This makes heap.pop() return the smallest value instead of the greatest one.

    let mut heap = BinaryHeap::new();

    // Wrap values in `Reverse`
    heap.push(Reverse(1));
    heap.push(Reverse(5));
    heap.push(Reverse(2));

    // If we pop these scores now, they should come back in the reverse order.
    assert_eq!(heap.pop(), Some(Reverse(1)));
    assert_eq!(heap.pop(), Some(Reverse(2)));
    assert_eq!(heap.pop(), Some(Reverse(5)));
    assert_eq!(heap.pop(), None);
}

fn test_binaryheap_advanced() {
    {
        // drain
        let mut heap = BinaryHeap::from(vec![1, 3]);
        assert!(!heap.is_empty());
        for x in heap.drain() {
            println!("{}", x);
        }
        assert!(heap.is_empty());
    }

    {
        // into_sorted_vec
        let mut heap = BinaryHeap::from(vec![1, 3, 4, 5, 2, 6]);

        heap.push(10);
        heap.push(7);

        assert_eq!(heap.into_sorted_vec(), [1, 2, 3, 4, 5, 6, 7, 10])
    }

    {
        // append
        let mut a = BinaryHeap::from(vec![-10, 1, 2, 3, 3, 3]);
        let mut b = BinaryHeap::from(vec![-20, 5, 43]);

        a.append(&mut b);
        let res = a.into_sorted_vec();

        assert_eq!(res, [-20, -10, 1, 2, 3, 3, 3, 5, 43]);
        assert!(b.is_empty());
    }

    {
        // into_vec
        let heap = BinaryHeap::from(vec![1, 2, 3, 4, 5, 6, 7]);
        let vec = heap.into_vec();

        // Will print in some order
        for x in vec {
            println!("{}", x);
        }
    }

    {
        // iter
        let heap = BinaryHeap::from(vec![1, 2, 3, 4]);

        // Print 1, 2, 3, 4 in arbitrary order
        for x in heap.iter() {
            println!("{}", x);
        }
    }

    {
        // peek_mut
        let mut heap = BinaryHeap::new();
        assert!(heap.peek_mut().is_none());

        heap.push(1);
        heap.push(5);
        heap.push(2);
        {
            let mut val = heap.peek_mut().unwrap();
            *val = 0;
        }
        assert_eq!(heap.peek(), Some(&2));
    }

    {
        // reverse
        let mut heap = BinaryHeap::new();
        heap.reserve(100);
        assert!(heap.capacity() >= 100);
        heap.push(4);
    }

    {
        // reserve_exact
        // Reserves the minimum capacity for exactly additional more elements to be inserted in the given BinaryHeap. Does nothing if the capacity is already sufficient.
        // Note that the allocator may give the collection more space than it requests. Therefore capacity can not be relied upon to be precisely minimal. Prefer reserve if future insertions are expected.
        let mut heap = BinaryHeap::new();
        heap.reserve_exact(100);
        assert!(heap.capacity() >= 100);
        heap.push(4);
    }

    {
        // shrink_to_fit
        let mut heap: BinaryHeap<i32> = BinaryHeap::with_capacity(100);

        assert!(heap.capacity() >= 100);
        heap.shrink_to_fit();
        assert!(heap.capacity() == 0);
    }

    {}
}

#[derive(Copy, Clone, Eq, PartialEq)]
struct skylinePos{
    pos: i32,
    height: i32,
}

// The priority queue depends on `Ord`.
// Explicitly implement the trait so the queue becomes a min-heap
// instead of a max-heap.
impl Ord for skylinePos {

    fn cmp(&self, other: &skylinePos) -> Ordering {
        self.height.cmp(&other.height).then_with(|| self.pos.cmp(&other.pos))
    }
}

impl PartialOrd for skylinePos {
    fn partial_cmp(&self, other: &skylinePos) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

pub fn doit_heap(buildings: Vec<Vec<i32>>) -> Vec<Vec<i32>> {

    let mut heap: BinaryHeap<skylinePos> = BinaryHeap::new();
    let mut i = 0;
    let mut skyline: Vec<Vec<i32>> = vec![];

    let mut buildings = buildings;
    buildings.sort_by(|a, b| a.partial_cmp(b).unwrap());


    while i < buildings.len() || ! heap.is_empty() {

        let mut x = 0;

        if heap.is_empty() || i < buildings.len() && heap.peek().unwrap().pos >= buildings[i][0] {

            x = buildings[i][0];
            while i < buildings.len() &&  buildings[i][0] <= x {
                heap.push(skylinePos{pos: buildings[i][1], height: buildings[i][2]});
                i += 1;
            }
        } else {

            x = heap.peek().unwrap().pos;
            while !heap.is_empty() && heap.peek().unwrap().pos <= x {
                heap.pop();
            }
        }

        let mut height = 0;
        if heap.len() > 0 {
            height = heap.peek().unwrap().height;
        }

        if skyline.is_empty() || height != skyline[skyline.len() - 1][1] {
            skyline.push(vec![x, height]);
        }
    }

    skyline
}

fn test_user_defined_heap() {
    doit_heap(vec![vec![2, 9, 10], vec![3, 7, 15], vec![5, 12, 12], vec![15, 20, 10], vec![19, 24, 8]]);
}

pub fn test_heap() {
    test_binaryheap_basic();

    test_mini_heap();

    test_binaryheap_advanced();

    test_user_defined_heap();
}
