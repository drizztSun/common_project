use std::ops::{
    Add, Mul, Sub, AddAssign, MulAssign, SubAssign,
    BitAnd, BitAndAssign, BitOr, BitOrAssign, BitXor, BitXorAssign,
    Deref, DerefMut, Index, IndexMut,
    Drop,
};

#[derive(Debug, Copy, Clone, PartialEq)]
struct Point<T> {
    x: T,
    y: T,
}

impl<T> Point<T>
where T: Add + Mul + Sub + AddAssign + MulAssign + SubAssign {
    fn new(x: T, y: T)  -> Self {
        Self {
            x,
            y,
        }
    }
}

impl<T: Add<Output = T>> Add for Point<T> {
    type Output = Self;

    fn add(self, other: Self) -> Self {
        Self {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

impl<T: Mul<Output = T>> Mul for Point<T> {
    type Output = Self;
    fn mul(self, other: Self) -> Self {
        Self {
            x: self.x * other.x,
            y: self.y * other.y,
        }
    }
}

impl<T: Sub<Output = T>> Sub for Point<T> {
    type Output = Self;
    fn sub(self, other: Self) -> Self {
        Self {
            x: self.x - other.x,
            y: self.y - other.y,
        }
    }
}

impl<T: AddAssign> AddAssign for Point<T> {

    fn add_assign(&mut self, other: Self) {
        self.x += other.x;
        self.y += other.y;
    }
}

impl<T: MulAssign> MulAssign for Point<T> {
    fn mul_assign(&mut self, other:Self) {
        self.x *= other.x;
        self.y *= other.y;
    }
}

impl<T: SubAssign> SubAssign for Point<T> {
    fn sub_assign(&mut self, other:Self) {
        self.x -= other.x;
        self.y -= other.y;
    }
}


#[derive(Debug, PartialEq)]
struct Scalar(bool);

impl BitAnd for Scalar {
    type Output = Self;

    // rhs is the "right-hand side" of the expression `a & b`
    fn bitand(self, rhs: Self) -> Self::Output {
        Scalar(self.0 & rhs.0)
    }
}

impl BitAndAssign for Scalar {
    // rhs is the "right-hand side" of the expression `a &= b`
    fn bitand_assign(&mut self, rhs: Self) {
        *self = Scalar(self.0 & rhs.0)
    }
}

impl BitOr for Scalar {
    type Output = Self;

    // rhs is the "right-hand side" of the expression `a | b`
    fn bitor(self, rhs: Self) -> Self {
        Scalar(self.0 | rhs.0)
    }
}

impl BitOrAssign for Scalar {
    // rhs is the "right-hand side" of the expression `a |= b`
    fn bitor_assign(&mut self, rhs: Self) {
        *self = Scalar(self.0 | rhs.0)
    }
}

impl BitXor for Scalar {
    type Output = Self;

    // rhs is the "right-hand side" of the expression `a ^ b`
    fn bitxor(self, rhs: Self) -> Self::Output {
        Scalar(self.0 ^ rhs.0)
    }
}

#[derive(Debug, PartialEq)]
struct Personality {
    has_soul: bool,
    likes_knitting: bool,
}

impl BitXorAssign for Personality {
    fn bitxor_assign(&mut self, rhs: Self) {
        self.has_soul ^= rhs.has_soul;
        self.likes_knitting ^= rhs.likes_knitting;
    }
}

#[derive(Debug, PartialEq)]
struct BooleanVector(Vec<bool>);

impl BitOr for BooleanVector {
    type Output = Self;

    fn bitor(self, BooleanVector(rhs): Self) -> Self::Output {
        let BooleanVector(lhs) = self;
        assert_eq!(lhs.len(), rhs.len());
        BooleanVector(lhs.iter().zip(rhs.iter()).map(|(x, y)| *x || *y).collect())
    }
}

impl BitAnd for BooleanVector {
    type Output = Self;

    fn bitand(self, BooleanVector(rhs): Self) -> Self::Output {
        let BooleanVector(lhs) = self;
        assert_eq!(lhs.len(), rhs.len());
        BooleanVector(lhs.iter().zip(rhs.iter()).map(|(x, y)| *x && *y).collect())
    }
}

// Deref
struct DerefMutExample<T> {
    value: T
}

impl<T> Deref for DerefMutExample<T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        &self.value
    }
}
// DerefMux
impl<T> DerefMut for DerefMutExample<T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.value
    }
}

// Drop
struct HasDrop;

impl Drop for HasDrop {
    fn drop(&mut self) {
        println!("Dropping HasDrop!");
    }
}

struct HasTwoDrops {
    one: HasDrop,
    two: HasDrop,
}

impl Drop for HasTwoDrops {
    fn drop(&mut self) {
        println!("Dropping HasTwoDrops!");
    }
}

// Index
enum Nucleotide {
    A,
    C,
    G,
    T,
}

struct NucleotideCount {
    a: usize,
    c: usize,
    g: usize,
    t: usize,
}

impl Index<Nucleotide> for NucleotideCount {
    type Output = usize;

    fn index(&self, nucleotide: Nucleotide) -> &Self::Output {
        match nucleotide {
            Nucleotide::A => &self.a,
            Nucleotide::C => &self.c,
            Nucleotide::G => &self.g,
            Nucleotide::T => &self.t,
        }
    }
}

// IndexMut
#[derive(Debug)]
enum Side {
    Left,
    Right,
}

#[derive(Debug, PartialEq)]
enum Weight {
    Kilogram(f32),
    Pound(f32),
}

struct Balance {
    pub left: Weight,
    pub right: Weight,
}

impl Index<Side> for Balance {
    type Output = Weight;

    fn index(&self, index: Side) -> &Self::Output {
        println!("Accessing {:?}-side of balance immutably", index);
        match index {
            Side::Left => &self.left,
            Side::Right => &self.right,
        }
    }
}

impl IndexMut<Side> for Balance {
    fn index_mut(&mut self, index: Side) -> &mut Self::Output {
        println!("Accessing {:?}-side of balance mutably", index);
        match index {
            Side::Left => &mut self.left,
            Side::Right => &mut self.right,
        }
    }
}

fn test_ops_basic() {

    assert_eq!(Point::new(1, 0) + Point::new(2, 3), Point::new(3, 3));

    assert_eq!(Point::new(1, 0) * Point::new(2, 3), Point::new(3, 3));

    let mut p = Point::new(1, 1);
    p += Point::new(2, 2);
    assert_eq!(p, Point::new(3, 3));

    p *= Point::new(2, 2);
    assert_eq!(p, Point::new(6, 6));


    {
        assert_eq!(Scalar(true) & Scalar(true), Scalar(true));
        assert_eq!(Scalar(true) & Scalar(false), Scalar(false));
        assert_eq!(Scalar(false) & Scalar(true), Scalar(false));
        assert_eq!(Scalar(false) & Scalar(false), Scalar(false));
    
        assert_eq!(Scalar(true) | Scalar(true), Scalar(true));
        assert_eq!(Scalar(true) | Scalar(false), Scalar(true));
        assert_eq!(Scalar(false) | Scalar(true), Scalar(true));
        assert_eq!(Scalar(false) | Scalar(false), Scalar(false));
    }

    {
        let mut scalar = Scalar(true);
        scalar &= Scalar(true);
        assert_eq!(scalar, Scalar(true));
    
        let mut scalar = Scalar(true);
        scalar &= Scalar(false);
        assert_eq!(scalar, Scalar(false));
    
        let mut scalar = Scalar(false);
        scalar &= Scalar(true);
        assert_eq!(scalar, Scalar(false));
    
        let mut scalar = Scalar(false);
        scalar &= Scalar(false);
        assert_eq!(scalar, Scalar(false));
    }

    {
        assert_eq!(Scalar(true) ^ Scalar(true), Scalar(false));
        assert_eq!(Scalar(true) ^ Scalar(false), Scalar(true));
        assert_eq!(Scalar(false) ^ Scalar(true), Scalar(true));
        assert_eq!(Scalar(false) ^ Scalar(false), Scalar(false));
    }

    {
        let mut personality = Personality { has_soul: false, likes_knitting: true };
        personality ^= Personality { has_soul: true, likes_knitting: true };
        assert_eq!(personality, Personality { has_soul: true, likes_knitting: false});
    }

    {
        let x = DerefMutExample { value: 'a' };
        assert_eq!('a', *x);
    }

    {
        let mut x = DerefMutExample { value: 'a' };
        *x = 'b';
        assert_eq!('b', *x);
    }


    {
        let _x = HasTwoDrops { one: HasDrop, two: HasDrop };
        println!("Running!");
    }

    {
        let nucleotide_count = NucleotideCount {a: 14, c: 9, g: 10, t: 12};
        assert_eq!(nucleotide_count[Nucleotide::A], 14);
        assert_eq!(nucleotide_count[Nucleotide::C], 9);
        assert_eq!(nucleotide_count[Nucleotide::G], 10);
        assert_eq!(nucleotide_count[Nucleotide::T], 12);
    }

    {
        let mut balance = Balance {
            right: Weight::Kilogram(2.5),
            left: Weight::Pound(1.5),
        };
        
        // In this case, `balance[Side::Right]` is sugar for
        // `*balance.index(Side::Right)`, since we are only *reading*
        // `balance[Side::Right]`, not writing it.
        assert_eq!(balance[Side::Right], Weight::Kilogram(2.5));
        
        // However, in this case `balance[Side::Left]` is sugar for
        // `*balance.index_mut(Side::Left)`, since we are writing
        // `balance[Side::Left]`.
        balance[Side::Left] = Weight::Kilogram(3.0);
    }
}

pub fn test_ops() {

    test_ops_basic();
}