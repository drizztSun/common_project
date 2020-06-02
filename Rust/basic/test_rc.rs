/*

Rc
When multiple ownership is needed, Rc(Reference Counting) can be used. Rc keeps track of the number of the references which means the number of owners of the value wrapped inside an Rc.

Reference count of an Rc increases by 1 whenever an Rc is cloned, and decreases by 1 whenever one cloned Rc is dropped out of the scope.
When an Rc's reference count becomes zero, which means there are no owners remained, both the Rc and the value are all dropped.

Cloning an Rc never do a deep copy. Cloning creates just another pointer to the wrapped value, and increments the count.


*** Module std::rc ***
[−]
Single-threaded reference-counting pointers. 'Rc' stands for 'Reference Counted'.

The type Rc<T> provides shared ownership of a value of type T, allocated in the *** heap ***.
Invoking clone on Rc produces a new pointer to the same allocation in the *** heap ***.

When the last Rc pointer to a given allocation is destroyed, the value stored in that allocation (often referred to as "inner value") is also dropped.

*** Shared references in Rust disallow mutation by default, and Rc is no exception: you cannot generally obtain a mutable reference to something inside an Rc.
If you need mutability, put a Cell or RefCell inside the Rc; see an example of mutability inside an Rc. ***

*** Rc uses non-atomic reference counting. This means that overhead is very low, but an Rc cannot be sent between threads, and consequently Rc does not implement Send.
As a result, the Rust compiler will check at compile time that you are not sending Rcs between threads.

*** If you need multi-threaded, atomic reference counting, use sync::Arc.

*** The downgrade method can be used to create a non-owning Weak pointer. A Weak pointer can be upgraded to an Rc, but this will return None if the value stored in the allocation has already been dropped.
In other words, Weak pointers do not keep the value inside the allocation alive; however, they do keep the allocation (the backing store for the inner value) alive.

A cycle between Rc pointers will never be deallocated. For this reason, Weak is used to break cycles.
For example, a tree could have strong Rc pointers from parent nodes to children, and Weak pointers from children back to their parents.

*** Rc<T> automatically dereferences to T (via the Deref trait), so you can call T's methods on a value of type Rc<T>. To avoid name clashes with T's methods,
the methods of Rc<T> itself are associated functions, called using function-like syntax:


Rc	A single-threaded reference-counting pointer. 'Rc' stands for 'Reference Counted'.
Weak	Weak is a version of Rc that holds a non-owning reference to the managed allocation. The allocation is accessed by calling upgrade on the Weak pointer, which returns an Option<Rc<T>>.

*/

use std::cell::RefCell;
use std::rc::{self, Rc, Weak};

struct Owner {
    name: String,
    // ...other fields
}

struct Gadget {
    id: i32,
    owner: Rc<Owner>,
    // ...other fields
}

/*
Consider a scenario where a set of Gadgets are owned by a given Owner. We want to have our Gadgets point to their Owner.
We can't do this with unique ownership, because more than one gadget may belong to the same Owner.
Rc allows us to share an Owner between multiple Gadgets, and have the Owner remain allocated as long as any Gadget points at it.
*/
fn test_basic_rc() {
    let gadget_owner: Rc<Owner> = Rc::new(Owner {
        name: "Gadget Man".to_string(),
    });

    // Create `Gadget`s belonging to `gadget_owner`. Cloning the `Rc<Owner>`
    // gives us a new pointer to the same `Owner` allocation, incrementing
    // the reference count in the process.
    let gadget1 = Gadget {
        id: 2,
        owner: Rc::clone(&gadget_owner),
    };

    let gadget2 = Gadget {
        id: 2,
        owner: Rc::clone(&gadget_owner),
    };

    // Dispose of our local variable `gadget_owner`.
    drop(gadget_owner);

    // Despite dropping `gadget_owner`, we're still able to print out the name
    // of the `Owner` of the `Gadget`s. This is because we've only dropped a
    // single `Rc<Owner>`, not the `Owner` it points to. As long as there are
    // other `Rc<Owner>` pointing at the same `Owner` allocation, it will remain
    // live. The field projection `gadget1.owner.name` works because
    // `Rc<Owner>` automatically dereferences to `Owner`.
    println!("Gadget {} owned by {}", gadget1.id, gadget1.owner.name);
    println!("Gadget {} owned by {}", gadget2.id, gadget2.owner.name);

    // At the end of the function, `gadget1` and `gadget2` are destroyed, and
    // with them the last counted references to our `Owner`. Gadget Man now
    // gets destroyed as well.
}

/*
If our requirements change, and we also need to be able to traverse from Owner to Gadget, we will run into problems. An Rc pointer from Owner to Gadget introduces a cycle.
This means that their reference counts can never reach 0, and the allocation will never be destroyed: a memory leak. In order to get around this, we can use Weak pointers.

Rust actually makes it somewhat difficult to produce this loop in the first place. In order to end up with two values that point at each other, one of them needs to be mutable.
This is difficult because Rc enforces memory safety by only giving out shared references to the value it wraps, and these don't allow direct mutation.
We need to wrap the part of the value we wish to mutate in a RefCell, which provides interior mutability: a method to achieve mutability through a shared reference. RefCell enforces Rust's borrowing rules at runtime.
*/

struct Gadget2 {
    id: i32,
    owner: Rc<Owen2>,
    // ...other fields
}

struct Owen2 {
    name: String,
    gadgets: RefCell<Vec<Weak<Gadget2>>>,
}

fn test_basic_weak() {
    let gadget_owners = Rc::new(Owen2 {
        name: "gadget_owner".to_string(),
        gadgets: RefCell::new(Vec::<Weak<Gadget2>>::new()),
        //gadgets: RefCell::new(vec![]),
    });

    let gadget1 = Rc::new(Gadget2 {
        id: 1,
        owner: Rc::clone(&gadget_owners),
    });

    let gadget2 = Rc::new(Gadget2 {
        id: 2,
        owner: Rc::clone(&gadget_owners),
    });

    // Add the `Gadget`s to their `Owner`.
    {
        let mut gadgets = gadget_owners.gadgets.borrow_mut();

        gadgets.push(Rc::downgrade(&gadget1));
        gadgets.push(Rc::downgrade(&gadget2));
        // `RefCell` dynamic borrow ends here.
    }

    // Iterate over our `Gadget`s, printing their details out.
    for gadget_weak in gadget_owners.gadgets.borrow().iter() {
        // `gadget_weak` is a `Weak<Gadget>`. Since `Weak` pointers can't
        // guarantee the allocation still exists, we need to call
        // `upgrade`, which returns an `Option<Rc<Gadget>>`.
        //
        // In this case we know the allocation still exists, so we simply
        // `unwrap` the `Option`. In a more complicated program, you might
        // need graceful error handling for a `None` result.

        let gadget = gadget_weak.upgrade().unwrap();
        println!("Gadget {} owned by {}", gadget.id, gadget.owner.name);
    }

    // At the end of the function, `gadget_owner`, `gadget1`, and `gadget2`
    // are destroyed. There are now no strong (`Rc`) pointers to the
    // gadgets, so they are destroyed. This zeroes the reference count on
    // Gadget Man, so he gets destroyed as well.
}

pub fn test_rc() {
    test_basic_rc();

    test_basic_weak();
}
