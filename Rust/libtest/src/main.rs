use crate::List2::{Cons2, Nil};
use std::cell::RefCell;
use std::rc::Rc;

#[derive(Debug)]
enum List2 {
    Cons2(i32, RefCell<Rc<List2>>),
    Nil,
}

impl List2 {

    fn tail(&self) -> Option<&RefCell<Rc<List2>>> {
        match self {
            Cons2(_, item) => Some(item),
            Nil => None,
        }
    }
}

pub fn test_reference_cycle() {
    let a = Rc::new(Cons2(5, RefCell::new(Rc::new(Nil))));

    println!("a initial rc count = {}", Rc::strong_count(&a));
    println!("a next item = {:?}", a.tail());

    let b = Rc::new(Cons2(6, RefCell::new(Rc::clone(&a))));

    println!("a rc count after b creation = {}", Rc::strong_count(&a));
    println!("b initial rc count = {}", Rc::strong_count(&b));
    println!("b next item ={:?}", b.tail());

    if let Some(link) = a.tail() {
        *link.borrow_mut() = Rc::clone(&b);
    }

    println!("b rc counter after changing a = {}", Rc::strong_count(&b));
    println!("a rc counter after changing b = {}", Rc::strong_count(&a));

    // Uncomment the next line to see that we have a cycle;
    // it will overflow the stack
    // println!("a next item = {:?}", a.tail());
}


fn main() {
    test_reference_cycle();
}