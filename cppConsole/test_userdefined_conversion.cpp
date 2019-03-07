
/*
user-defined conversion
  C++  C++ language  Expressions 
Enables implicit conversion or explicit conversion from a class type to another type.

Syntax
Conversion function is declared like a non-static member function or member function template with no parameters, no explicit return type, and with the name of the form:

operator conversion-type-id	(1)	
explicit operator conversion-type-id	(2)	(since C++11)
1) Declares a user-defined conversion function that participates in all implicit and explicit conversions
2) Declares a user-defined conversion function that participates in direct-initialization and explicit conversions only.
conversion-type-id is a type-id except that function and array operators [] or () are not allowed in its declarator (thus conversion to types such as pointer to array requires a type alias/typedef or an identity template: see below). Regardless of typedef, conversion-type-id cannot represent an array or a function type.

Although the return type is not allowed in the declaration of a user-defined conversion function, the decl-specifier-seq of the declaration grammar may be present and may include any specifier other than type-specifier or the keyword static, In particular, besides explicit, the specifiers inline, virtual, constexpr, and friend are also allowed (note that friend requires a qualified name: friend A::operator B();).

When such member function is declared in class X, it performs conversion from X to conversion-type-id:
*/

struct X {
    //implicit conversion
    operator int() const { return 7; }
 
    // explicit conversion
    explicit operator int*() const { return nullptr; }
 
//   Error: array operator not allowed in conversion-type-id
//   operator int(*)[3]() const { return nullptr; }
    using arr_t = int[3];
    operator arr_t*() const { return nullptr; } // OK if done through typedef
//  operator arr_t () const; // Error: conversion to array not allowed in any case
};


int main1()
{
    X x;
 
    int n = static_cast<int>(x);   // OK: sets n to 7
    int m = x;                     // OK: sets m to 7
 
    int* p = static_cast<int*>(x);  // OK: sets p to null
//  int* q = x; // Error: no implicit conversion
 
    int (*pa)[3] = x;  // OK
}

/*
Explanation
User-defined conversion function is invoked on the second stage of the implicit conversion, 
which consists of zero or one converting constructor or zero or one user-defined conversion function.

If both conversion functions and converting constructors can be used to perform some user-defined conversion, 
the conversion functions and constructors are both considered by overload resolution in copy-initialization and reference-initialization contexts, but only the constructors are considered in direct-initialization contexts.
*/
struct To {
    To() = default;
    To(const struct From&) {} // converting constructor
};
 
struct From {
    operator To() const {return To();} // conversion function
};
 
int main2()
{
    From f;
    To t1(f); // direct-initialization: calls the constructor
// (note, if converting constructor is not available, implicit copy constructor
//  will be selected, and conversion function will be called to prepare its argument)
    To t2 = f; // copy-initialization: ambiguous
// (note, if conversion function is from a non-const type, e.g.
//  From::operator To();, it will be selected instead of the ctor in this case)
    To t3 = static_cast<To>(f); // direct-initialization: calls the constructor
    const To& r = f; // reference-initialization: ambiguous

    /*
    more than one user-defined conversion from "From" to "const To" applies: -- function "From::operator To() const" 
    -- function "To::To(const From &)"
    */
}

/*
Conversion function to its own (possibly cv-qualified) class (or to a reference to it), 
to the base of its own class (or to a reference to it), and to the type void can be defined, 
but can not be executed as part of the conversion sequence, except, in some cases, through virtual dispatch:
*/
struct D;
struct B {
    virtual operator D() = 0;
};
struct D : B
{
     operator D() override { return D(); }
};
 
int main3()
{
    D obj;
    D obj2 = obj; // does not call D::operator D()
    B& br = obj;
    D obj3 = br; // calls D::operator D() through virtual dispatch
}

// It can also be called using member function call syntax:

struct B {};
struct X1 : B {
    operator B&() { return *this; };
};
 
int main4()
{
	X1 x;
    B& b1 = x;                  // does not call X::operatorB&()
    B& b2 = static_cast<B&>(x); // does not call X::operatorB&
    B& b3 = x.operator B&();    // calls X::operatorB&
}

// When making an explicit call to the conversion function, the type-id is greedy: 
// it is the longest possible sequence of tokens that is a valid type id (including attributes, if any):
/*
& x.operator int * a; // parsed as & (x.operator int*) a
                      // not as & (x.operator int) * a
The placeholder auto can be used in conversion-type-id, indicating a deduced return type:

struct X {
    operator int(); // OK
    operator auto() -> short;  // error: trailing return type not part of syntax
    operator auto() const { return 10; } // OK: deduced return type
};
*/