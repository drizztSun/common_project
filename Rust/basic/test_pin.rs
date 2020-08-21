#![feature(optin_builtin_traits, negative_impls)] // needed to implement `!Unpin`
use std::pin::Pin;
use std::marker::Unpin;
use std::marker::PhantomPinned;
use std::mem;


/*

Summary
1. If T: Unpin (which is the default), then Pin<'a, T> is entirely equivalent to &'a mut T.
    in other words: Unpin means it's OK for this type to be moved even when pinned, so Pin will have no effect on such a type.

2. Getting a &mut T to a pinned T requires unsafe if T: !Unpin.

3. Most standard library types implement Unpin. The same goes for most "normal" types you encounter in Rust. A Future generated by async/await is an exception to this rule.

4. You can add a !Unpin bound on a type on nightly with a feature flag, or by adding std::marker::PhantomPinned to your type on stable.

5. You can either pin data to the stack or to the heap.

6. Pinning a !Unpin object to the stack requires unsafe

7. Pinning a !Unpin object to the heap does not require unsafe. There is a shortcut for doing this using Box::pin.

8. For pinned data where T: !Unpin you have to maintain the invariant that its memory will not get invalidated or repurposed from the moment it gets pinned until when drop is called.
   This is an important part of the pin contract.


*/



/*lement a trait called Unpin. Pointers to Unpin types can be freely placed into or taken out of Pin.
For example, u8 is Unpin, so Pin<&mut u8> behaves just like a normal &mut u8.

However, types that can't be moved after they're pinned has a marker called !Unpin. Futures created by async/await is an example of this.

*/

#[derive(Debug)]
struct Test{
    a: String,
    b: *const String,
    _marker: PhantomPinned,
}

impl Test {

    fn new(txt: &str) -> Self {
        Test {
            a: String::from(txt),
            b: std::ptr::null(),
            _marker: PhantomPinned, // This makes our type '!Unpin'
        }
    }

    fn init<'a>(self: Pin<&'a mut Self>) {
        let self_ptr: *const String = &self.a;
        let this = unsafe { self.get_unchecked_mut() };
        this.b = self_ptr;
    }

    fn a<'a>(self: Pin<&'a Self>) -> &'a str {
        &self.get_ref().a
    }

    fn b<'a>(self: Pin<&'a Self>) -> &'a str {
        unsafe{ &*(self.b)}
    }
}

/*

Pinning an object to the stack will always be unsafe if our type implements !Unpin.
You can use a crate like pin_utils to avoid writing our own unsafe code when pinning to the stack.

*/
fn test_pin_on_stack() {

    {
        // test1 is safe to move before we initialize it
        let mut test1 = Test::new("test1");
        // Notice how we shadow `test1` to prevent it from being accessed again
        let mut test1 = unsafe { Pin::new_unchecked(&mut test1) };
        Test::init(test1.as_mut());

        let mut test2 = Test::new("test2");
        let mut test2 = unsafe { Pin::new_unchecked(&mut test2) };
        Test::init(test2.as_mut());

        println!("a: {}, b: {}", Test::a(test1.as_ref()), Test::b(test1.as_ref()));

        // `std::marker::PhantomPinned` cannot be unpinned, within `test_pin::Test`, the trait `std::marker::Unpin` is not implemented for `std::marker::PhantomPinned`
        // std::mem::swap(test1.get_mut(), test2.get_mut());

        println!("a: {}, b: {}", Test::a(test2.as_ref()), Test::b(test2.as_ref()));
    }


    {
        /*

        The type system prevents us from moving the data.

        It's important to note that stack pinning will always rely on guarantees you give when writing unsafe.
        While we know that the pointee of &'a mut T is pinned for the lifetime of 'a we can't know if the data &'a mut T points to isn't moved after 'a ends. If it does it will violate the Pin contract.

        A mistake that is easy to make is forgetting to shadow the original variable since you could drop the Pin and move the data after &'a mut T like shown below (which violates the Pin contract):

        */

        let mut test1 = Test::new("test1");
        let mut test1_pin = unsafe { Pin::new_unchecked(&mut test1) };
        Test::init(test1_pin.as_mut());
        drop(test1_pin);
        println!(r#"test1.b points to "test1": {:?}..."#, test1.b);
        let mut test2 = Test::new("test2");
        mem::swap(&mut test1, &mut test2);
        println!("... and now it points nowhere: {:?}", test1.b);
    }
}

/*

Pinning to the Heap
Pinning an !Unpin type to the heap gives our data a stable address so we know that the data we point to can't move after it's pinned.
In contrast to stack pinning, we know that the data will be pinned for the lifetime of the object.

*/

#[derive(Debug)]
struct TestH {
    a: String,
    b: *const String,
    _marker: PhantomPinned,  // *** This makes our type `!Unpin`
}

impl TestH {
    fn new(txt: &str) -> Pin<Box<Self>> {
        let t = TestH {
            a: String::from(txt),
            b: std::ptr::null(),
            _marker: PhantomPinned,
        };
        let mut boxed = Box::pin(t);
        let self_ptr: *const String = &boxed.as_ref().a;
        unsafe { boxed.as_mut().get_unchecked_mut().b = self_ptr };

        boxed
    }

    fn a<'a>(self: Pin<&'a Self>) -> &'a str {
        &self.get_ref().a
    }

    fn b<'a>(self: Pin<&'a Self>) -> &'a String {
        unsafe { &*(self.b) }
    }
}

fn test_pin_on_heap() {
    let mut test1 = TestH::new("test1");
    let mut test2 = TestH::new("test2");

    println!("a: {}, b: {}",test1.as_ref().a(), test1.as_ref().b());
    println!("a: {}, b: {}",test2.as_ref().a(), test2.as_ref().b());
}




pub fn test_generator() {
    let gen1 = GeneratorA::start();
    let gen2 = GeneratorA::start();
    // Before we pin the pointers, this is safe to do
    // std::mem::swap(&mut gen, &mut gen2);

    // constructing a `Pin::new()` on a type which does not implement `Unpin` is
    // unsafe. A value pinned to heap can be constructed while staying in safe
    // Rust so we can use that to avoid unsafe. You can also use crates like
    // `pin_utils` to pin to the stack safely, just remember that they use
    // unsafe under the hood so it's like using an already-reviewed unsafe
    // implementation.

    let mut pinned1 = Box::pin(gen1);
    let mut pinned2 = Box::pin(gen2);

    // Uncomment these if you think it's safe to pin the values to the stack instead 
    // (it is in this case). Remember to comment out the two previous lines first.
    //let mut pinned1 = unsafe { Pin::new_unchecked(&mut gen1) };
    //let mut pinned2 = unsafe { Pin::new_unchecked(&mut gen2) };

    if let GeneratorState::Yielded(n) = pinned1.as_mut().resume() {
        println!("Gen1 got value {}", n);
    }
    
    if let GeneratorState::Yielded(n) = pinned2.as_mut().resume() {
        println!("Gen2 got value {}", n);
    };

    // This won't work:
    // std::mem::swap(&mut gen, &mut gen2);
    // This will work but will just swap the pointers so nothing bad happens here:
    // std::mem::swap(&mut pinned1, &mut pinned2);

    let _ = pinned1.as_mut().resume();
    let _ = pinned2.as_mut().resume();
}

enum GeneratorState<Y, R> {
    Yielded(Y),  
    Complete(R), 
}

trait Generator {
    type Yield;
    type Return;
    fn resume(self: Pin<&mut Self>) -> GeneratorState<Self::Yield, Self::Return>;
}

enum GeneratorA {
    Enter,
    Yield1 {
        to_borrow: String,
        borrowed: *const String,
    },
    Exit,
}

impl GeneratorA {
    fn start() -> Self {
        GeneratorA::Enter
    }
}

// This tells us that the underlying pointer is not safe to move after pinning.
// In this case, only we as implementors "feel" this, however, if someone is
// relying on our Pinned pointer this will prevent them from moving it. You need
// to enable the feature flag ` #![feature(optin_builtin_traits)]` and use the
// nightly compiler to implement `!Unpin`. Normally, you would use
// `std::marker::PhantomPinned` to indicate that the struct is `!Unpin`.

// impl !Unpin for GeneratorA {}

impl Generator for GeneratorA {
    type Yield = usize;
    type Return = ();
    fn resume(self: Pin<&mut Self>) -> GeneratorState<Self::Yield, Self::Return> {
        // lets us get ownership over current state
        let this = unsafe { self.get_unchecked_mut() };
            match this {
            GeneratorA::Enter => {
                let to_borrow = String::from("Hello");
                let borrowed = &to_borrow;
                let res = borrowed.len();
                *this = GeneratorA::Yield1 {to_borrow, borrowed: std::ptr::null()};

                // Trick to actually get a self reference. We can't reference
                // the `String` earlier since these references will point to the
                // location in this stack frame which will not be valid anymore
                // when this function returns.
                if let GeneratorA::Yield1 {to_borrow, borrowed} = this {
                    *borrowed = to_borrow;
                }

                GeneratorState::Yielded(res)
            }

            GeneratorA::Yield1 {borrowed, ..} => {
                let borrowed: &String = unsafe {&**borrowed};
                println!("{} world", borrowed);
                *this = GeneratorA::Exit;
                GeneratorState::Complete(())
            }
            GeneratorA::Exit => panic!("Can't advance an exited generator!"),
        }
    }
}


pub fn test_pin() {

    test_pin_on_heap();

    test_pin_on_stack();
}