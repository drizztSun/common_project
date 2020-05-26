// *** Unions ***
// Syntax
// Union :
//    union IDENTIFIER Generics? WhereClause? {StructFields }

// A union declaration uses the same syntax as a struct declaration, except with union in place of struct.

#[repr(C)]
union MyUnion {
    f1: u32,
    f2: u32,
    f3: u128,
}

// *** Pattern matching on unions ***
//

fn f(u: MyUnion) {
    unsafe {
        match u {
            MyUnion { f1: 10 } => {
                println!("ten");
            }
            MyUnion { f2 } => {
                println!("{}", f2);
            }
        }
    }
}

// Pattern matching may match a union as a field of a larger structure.
// In particular, when using a Rust union to implement a C tagged union via FFI, this allows matching on the tag and the corresponding field simultaneously:
#[repr(u32)]
enum Tag {
    I,
    F,
}

#[repr(C)]
union U {
    i: i32,
    f: f32,
}

#[repr(C)]
struct Value {
    tag: Tag,
    u: U,
}

fn is_zero(v: Value) -> bool {
    unsafe {
        match v {
            Value {
                tag: Tag::I,
                u: U { i: 0 },
            } => true,
            Value {
                tag: Tag::F,
                u: U { f: num },
            } if num == 0.0 => true,
            _ => false,
        }
    }
}

fn test_union_basic() {
    // Initialization of a union
    // A value of a union type can be created using the same syntax that is used for struct types, except that it must specify exactly one field:
    let u = MyUnion { f1: 32 };

    // *** Reading and writing union fields ***
    // Unions have no notion of an "active field". Instead, every union access just interprets the storage at the type of the field used for the access.
    // Reading a union field reads the bits of the union at the field's type. Fields might have a non-zero offset (except when #[repr(C)] is used);
    // in that case the bits starting at the offset of the fields are read. It is the programmer's responsibility to make sure that the data is valid at the field's type.
    // Failing to do so results in undefined behavior. For example, reading the value 3 at type bool is undefined behavior.

    // Effectively, writing to and then reading from a #[repr(C)] union is analogous to a transmute from the type used for writing to the type used for reading.
    // Consequently, all reads of union fields have to be placed in unsafe blocks:
    let f = unsafe { u.f1 };

    // Writes to Copy union fields do not require reads for running destructors, so these writes don't have to be placed in unsafe blocks
    u.f1 = 100;
    // Commonly, code using unions will provide safe wrappers around unsafe union field accesses.
}

// *** References to union fields ***
// Since union fields share common storage, gaining write access to one field of a union can give write access to all its remaining fields.
// Borrow checking rules have to be adjusted to account for this fact. As a result, if one field of a union is borrowed, all its remaining fields are borrowed as well for the same lifetime.
// ERROR: cannot borrow `u` (via `u.f2`) as mutable more than once at a time
fn test() {
    let mut u = MyUnion { f1: 1 };
    unsafe {
        let b1 = &mut u.f1;
        //                    ---- first mutable borrow occurs here (via `u.f1`)

        // ***  let b2 = &mut u.f2; ***
        //                    ^^^^ second mutable borrow occurs here (via `u.f2`)
        *b1 = 5;
    }
    //  - first borrow ends here
    assert_eq!(unsafe { u.f1 }, 5);
}

pub fn test_union() {
    test_union_basic();
}
