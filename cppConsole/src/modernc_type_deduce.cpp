
#include <stdio.h>
#include <utility>
#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

/*
 
 C++98 had a single set of rules for type deduction: the one for function templates.
 C++11 modifies that ruleset a bit and adds two more, one for "auto" and one for "decltype".
 C++14 then extends the usage contexts in which auto and decltype may be employed.
 
 The increasingly widespread application of type deduction frees you from the tyranny of spelling out types that are obvious or redundant.
 It makes C++ software more adaptable, because changing a type at one point in the source code automatically propagates through type deduction to other locations.
 However, it can render code more difficult to reason about, because the types deduced by compilers may not be as apparent as you’d like.
 
 The good news is that type deduction for templates is the basis for one of modern C++’s most compelling features: auto.
 The bad news is that when the template type deduction rules are applied in the context of auto, they sometimes seem less intuitive than when they’re applied to templates.
 
 template<typename T>
    void f(ParamType param);
 
 A call can look like this:
 
 f(expr);
 
 */

/*
    **** Item 1: Understand template type deduction. ***
 Case 1: ParamType is a Reference or Pointer, but not a Universal
 Reference
 The simplest situation is when ParamType is a reference type or a pointer type, but not a universal reference. In that case, type deduction works like this:
 1. If expr’s type is a reference, ignore the reference part.
 2. Then pattern-match expr’s type against ParamType to determine T.
 
 
 Case 2: ParamType is a Universal Reference
 Things are less obvious for templates taking universal reference parameters. Such parameters are declared like rvalue references
 (i.e., in a function template taking a type parameter T, a universal reference’s declared type is "T&&"), but they behave differ‐ ently when lvalue arguments are passed in
 
 • If expr is an lvalue, both T and ParamType are deduced to be lvalue references. That’s doubly unusual. First, it’s the only situation in template type deduction where T is deduced to be a reference. Second, although ParamType is declared using the syntax for an rvalue reference, its deduced type is an lvalue reference.
 • If expr is an rvalue, the “normal” (i.e., Case 1) rules apply.


 Case 3: ParamType is Neither a Pointer nor a Reference
 When ParamType is neither a pointer nor a reference, we’re dealing with pass-by-value:
 
 template<typename T>
 void f(T param); // param is now passed by value
 
 That means that param will be a copy of whatever is passed in—a completely new object.
 The fact that param will be a new object motivates the rules that govern how T is deduced from expr:
 
    1. As before, if expr’s type is a reference, ignore the reference part.
    2. If, after ignoring expr’s reference-ness, expr is const, ignore that, too.
        If it’s volatile, also ignore that. (volatile objects are uncommon. They’re generally used only for implementing device drivers. For details, see Item 40.)
    3. It’s important to recognize that const (and volatile) is ignored only for by-value parameters.
    4. case where expr is a const pointer to a const object, and expr is passed to a by- value param:

 
 
 Things to Remember
 • During template type deduction, arguments that are references are treated as non-references, i.e., their reference-ness is ignored.
 • When deducing types for universal reference parameters, lvalue arguments get special treatment.
 • When deducing types for by-value parameters, const and/or volatile argu‐ ments are treated as non-const and non-volatile.
 • During template type deduction, arguments that are array or function names decay to pointers, unless they’re used to initialize references.
 
 */


template <typename T>
void f(T) { }

template <typename T>
void f_lref(T& ) { }

template <typename T>
void f_const_lref(const T &) {}

template <typename T>
void f_ptr(T*) { }

template <typename T>
void f_rf(T&&) {}


// Interestingly, the ability to declare references to arrays enables creation of a template that deduces the number of elements that an array contains:
template <typename T, size_t N>
constexpr size_t f_array(T(&)[N]) noexcept { return 0; }
// constexpr, declaring this function constexpr makes its result available during compilation. compilor can figure out what it is.

void someFunc(int, double) {
    printf("some Func");
};

void test_type_template() {
    
    // template parametre deduce
    int x = 42;
    const int cx = x;
    const int& crx = x;
    int& rx = x;
    
    f_lref(x); // T is int, parameter is int&
    f_lref(rx); // T is int, parameter is int&
    
    // In the second and third calls, notice that because cx and rx designate const values,
    // T is deduced to be const int, thus yielding a parameter type of const int&. That’s important to callers.
    // When they pass a const object to a reference parameter, they expect that object to remain unmodifiable, i.e., for the parameter to be a reference-to- const.
    // That’s why passing a const object to a template taking a T& parameter is safe: the constness of the object becomes part of the type deduced for T.
    f_lref(cx); // T is const int, parameter is const int&
    f_lref(crx);// T is const int, parameter is const int&
    
    
    f_const_lref(x);    // T is int, param is const int&
    f_const_lref(cx);   // T is int, param is const int&
    f_const_lref(crx);  // T is int, param is const int&
    f_const_lref(rx);   // T is int, param is const int&
    
    f_rf(x); // lvalue, T is int&, parameter is int&
    f_rf(cx); // lvalue, T is const int&, parameter is const int&
    f_rf(rx); // lvaule, T is int&, parameter in in&
    f_rf(crx); // lvalue, T is const int& parameter is const int&
    f_rf(42); // rvalue, T is int, paraster is int &&
    
    
    // If param were a pointer (or a pointer to const) instead of a reference, things would work essentially the same way:
    const int *cpx = &x;
    int *px = &x;
    
    f_ptr(cpx); // T is const int, parameter is const int*
    f_ptr(px); // T is int, parameter is int*
    
    const char* const cps = "Helllo world";
    f(cps); // T and parameter is const char* constß
    // Here, the const to the right of the asterisk declares ptr to be const: ptr can’t be made to point to a different location, nor can it be set to null.
    // (The const to the left of the asterisk says that what ptr points to—the character string—is const, hence can’t be modified.) When ptr is passed to f,
    // the bits making up the pointer are copied into param. As such, the pointer itself (ptr) will be passed by value.
    // In accord with the type deduction rule for by-value parameters, the constness of ptr will be ignored, and the type deduced for param will be const char*, i.e.,
    // a modifiable pointer to a const character string
    
    
    f(x); // T and parameter both int
    f(cx); // T and parameter both int
    f(rx); // T and parameter both int
    f(crx); // T and parameter both int
    
    // Array
    // During template type deduction, arguments that are array or function names decay to pointers, unless they’re used to initialize references.
    const char name[] = "J. P. Briggs";
    const char *pTName = name;
    // the const char* pointer ptrToName is being initialized with name, which is a constchar[13].
    // These types (constchar*andconstchar[13]) are not the same, but because of the array-to-pointer decay rule, the code compiles.
    
    // This equivalence of array and pointer parameters is a bit of foliage springing from the C roots at the base of C++,
    // and it fosters the illusion that array and pointer types are the same.
    // Because array parameter declarations are treated as if they were pointer parameters, the type of an array that’s passed to a template function by value
    // is deduced to be a pointer type. That means that in the call to the template f, its type parameter T is deduced to be const char*:
    
    f_ptr(name); // T and parameter deduces as const char*
    
    f_lref(name); // T and parameter deduces as const char (&) [13]
    
    f(name); // T and parameter decuses as const char[13]
    
    // the type deduced for T is the actual type of the array! That type includes the size of the array,
    // so in this example, T is deduced to be const char [13], and the type of f’s parameter (a reference to this array) isconstchar(&)[13]
    
    int keyvals[] = {1, 2, 3, 4, 5, 6};  // keyVals has 7 elements
    int mappedvals[f_array(keyvals)]; // so does mappedVals
    
    
    
    // Function Arguments
    // Arrays aren’t the only things in C++ that can decay into pointers. Function types can decay into function pointers,
    // and everything we’ve discussed regarding type deduction for arrays applies to type deduction for functions and their decay into function pointers.
    f(someFunc); // T and parameter deduce void(*)(int, double);
    f_lref(someFunc); // T and parameter deduce void(&)(int, double);
}

/*
    *** Item 2: Understand auto type deduction. ***

    Item 1 divides template type deduction into three cases, based on the characteristics of ParamType, the type specifier for param in the general function template.
    In a variable declaration using auto, the type specifier takes the place of ParamType, so there are three cases for that, too:
    • Case 1: The type specifier is a pointer or reference, but not a universal reference.
    • Case 2: The type specifier is a universal reference.
    • Case 3: The type specifier is neither a pointer nor a reference.
 
    Things to Remember
    • auto type deduction is usually the same as template type deduction, but auto type deduction assumes
        that a braced initializer represents a std::initial izer_list, and template type deduction doesn’t.
    • auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.
 
    
 */
void test_type_auto() {
    
    // auto <=> template<T>
    
    // When a variable is declared using auto, auto plays the role of T in the template, and the type specifier for the variable acts as ParamType.
    auto x = 27;        // case 3 (x is neither ptr nor reference)
    const auto cx = x;  // case 3 (cx isn't either)
    
    auto& rx = x; // case 1 (rx is a non-universal ref.)
    const auto& crx = x; // case 1 (rx is a non-universal ref.)
    
    // Case 2 works as you’d expect:
    auto&& uref1 = x;   // x is int and lvalue,
                        // so uref1's type is int&
    auto&& uref2 = cx;  // cx is const int and lvalue,
                        // so uref2's type is const int&
    auto&& uref3 = 27;  // 27 is int and rvalue,
                        // so uref3's type is int&&
    
    
    const char name[] = "Hello world";
    
    auto arr1_name = name; // arr1 type is const char*
    
    auto& arr2_name = name; // arr2 type is const char[11];
    
    int nums[] = {1, 2, 3}; // int[3] decay int*
    
    
    auto func1 = someFunc; // void(*)(int, double)
    auto& func2 = someFunc; // void(&)(int, double)
    
    func1(1, 2.718); // someFunc(1, 2.718)
    
    // *** As you can see, auto type deduction works like template type deduction. They’re essentially two sides of the same coin.
    // Except for the one way they differ. We’ll start with the observation that if you want to declare an int with an initial value of 27,
    // C++98 gives you two syntactic choices:
    int x1 = 27;
    int x2(27);
    
    // C++11, through its support for uniform initialization, adds these:
    int x3 = { 27 };
    int x4{ 27 };
    
    // so it’d be nice to replace int with auto in the above variable declara‐ tions. Straightforward textual substitution yields this code:
    {
        auto x1 = 27;    // type is int, value is 27
        auto x2(27);    // ditto
        
        auto x4{ 27 }; // ditto
        
        // error! can't deduce T for // std::initializer_list<T>
        // auto x3 = { 27 }; // type is std::initializer_list<int>, // value is { 27 }
        // This is due to a special type deduction rule for auto. When the initializer for an auto-declared variable is enclosed in braces, the deduced type is a std::initial izer_list.
        // If such a type can’t be deduced (e.g., because the values in the braced ini‐ tializer are of different types), the code will be rejected
    
        
    }
}

/*
    *** Item 3: Understand decltype. ***
 
    decltype is an odd creature. Given a name or an expression, decltype tells you the name’s or the expression’s type. Typically, what it tells you is exactly what you’d predict
 
    Things to Remember
    • decltype almost always yields the type of a variable or expression without any modifications.
    • For lvalue expressions of type T other than names, decltype always reports a type of T&.
    • C++14 supports decltype(auto), which, like auto, deduces a type from its initializer, but it performs the type deduction using the decltype rules.
 */


/*
 
 
    Things to Remember
 • Deduced types can often be seen using IDE editors, compiler error messages, and the Boost TypeIndex library.
 • The results of some tools may be neither helpful nor accurate, so an under‐ standing of C++’s type deduction rules remains essential.

 */


// The use of auto before the function name has nothing to do with type deduction. Rather, it indicates that C++11’s trailing return type syntax is being used, i.e.,
// that the function’s return type will be declared following the parameter list (after the “->”).
// A trailing return type has the advantage that the function’s parameters can be used in the specification of the return type.
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i) -> decltype(c[i])  // called, trailing return value
{
  // authenticateUser();
  return c[i];
}



// C++11 permits return types for single-statement lambdas to be deduced, and C++14 extends this to both all lambdas and all functions, including those with multiple statements.
template<typename Container, typename Index>
decltype(auto) authAndAccess(/*Container& c*/ Container&& c, Index i) // C++14; not quite correct
// The container is passed by lvalue-reference-to-non-const, because returning a refer‐ ence to an element of the container permits clients to modify that container.
// But this means it’s not possible to pass rvalue containers to this function.
// Rvalues can’t bind to lvalue references (unless they’re lvalue-references-to-const, which is not the case here).

// *** c is now a universal reference
{
    //authenticateUser();
    // return c[i]; // return type deduced from c[i] }
    
    
    // In this template, we don’t know what type of container we’re operating on, and that means we’re equally ignorant of the type of index objects it uses. Employing pass-by- value
    // for objects of an unknown type generally risks the performance hit of unneces‐ sary copying, the behavioral problems of object slicing (see Item 41),
    // and the sting of our coworkers’ derision, but in the case of container indices, following the example of the Standard Library for index values
    // (e.g., in operator[] for std::string, std::vector, and std::deque) seems reasonable, so we’ll stick with pass-by-value for them.
    
    //return std::forward<Container>(c)[i];
    return std::forward<Container>(c)[i];
    // As we’ve discussed, operator[] for most containers-of-T returns a T&, but Item 1 explains that during
    // template type deduction, the reference-ness of an initializing expression is ignored.
    // std::deque<int> d;
    // authAndAccess(d, 5) = 100; // error, won't work
    // That int, being the return value of a function, is an rvalue, and the code above thus attempts to assign 10 to an rvalue int. That’s forbidden in C++, so the code won’t compile.
    
    // To get authAndAccess to work as we’d like, we need to use decltype type deduction for its return type, i.e., to specify that authAndAccess should return exactly the same type that the expression c[i] returns.
    // The guardians of C++, anticipating the need to use decltype type deduction rules in some cases where types are inferred, make this possible in C++14 through the decltype(auto) specifier.
    
    // using decltype(auto)
}

class Widget {};

void test_type_decltype() {
    
    /*
     const int i = 0;  // decltype(i) is const int
     bool f(const Widget& w);       // decltype(w) is const Widget&
                                    // decltype(f) is bool(const Widget&)
     
     struct Point {
       int x, y;
     };                 // decltype(Point::x) is int
                        // decltype(Point::y) is int
     
     Widget w;          // // decltype(w) is Widget
     
     if (f(w)) ...      // // decltype(f(w)) is bool
     
     template<typename T> // simplified version of std::vector
     class vector {
     public:
     ...
        T& operator[](std::size_t index);
     ...
     };
     
     vector<int> v; ... // decltype(v) is vector<int>
     if (v[0] == 0) ... // decltype(v[0]) is int&
     
     In C++11, perhaps the primary use for decltype is declaring function templates where the function’s return type depends on its parameter types.
     */
    
    
    // The use of decltype(auto) is not limited to function return types. It can also be convenient for declaring variables
    // when you want to apply the decltype type deduction rules to the initializing expression:
    Widget m;
    const Widget& cm = m;
    
    auto myWidget1 = cm; // Widget
    
    decltype(auto) myWidget2 = cm; // const Widget&
}


/*
    *** Item 4: Know how to view deduced types. ***
    The choice of tools for viewing the results of type deduction is dependent on the phase of the software development process where you want the information.
    We’ll explore three possibilities:
 
 
        1) getting type deduction information as you edit your code,
            Code editors in IDEs often show the types of program entities (e.g., variables, param‐ eters, functions, etc.
 
        2) getting it during compilation
            An effective way to get a compiler to show a type it has deduced is to use that type in a way that leads to compilation problems.
            The error message reporting the problem is virtually sure to mention the type that’s causing it.
 
        3) getting it at runtime.
            
 
    Things to Remember
    • Deduced types can often be seen using IDE editors, compiler error messages, and the Boost TypeIndex library.
    • The results of some tools may be neither helpful nor accurate, so an under‐ standing of C++’s type deduction rules remains essential.
*/

struct Base { virtual ~Base() = default; };
struct Derived : Base {};


void test_type_output() {
        
    const int A = 43;
    auto x = A;
    auto y = &A;
    auto& z = A;
    auto* p = &A;
    
    std::cout << typeid(A).name() << std::endl;
    std::cout << typeid(x).name() << std::endl;
    std::cout << typeid(y).name() << std::endl;
    std::cout << typeid(z).name() << std::endl;
    std::cout << typeid(p).name() << std::endl;
    // This approach relies on the fact that invoking typeid on an object such as x or y yields a std::type_info object, and std::type_info
    // has a member function, name, that produces a C-style string (i.e., a const char*) representation of the name of the type.
    
    // Calls to std::type_info::name are not guaranteed to return anything sensible, but implementations try to be helpful.
    // The level of helpfulness varies. The GNU and Clang compilers report that the type of x is “i”, and the type of y is “PKi”, for exam‐ ple
    
    
    Base b1;
    Derived d1;

    const Base *pb = &b1;
    std::cout << typeid(*pb).name() << '\n';
    pb = &d1;
    std::cout << typeid(*pb).name() << '\n';
}

/*
    *** auto ***
    In concept, auto is as simple as simple can be, but it’s more subtle than it looks. Using it saves typing, sure,
    but it also prevents correctness and performance issues that can bedevil manual type declarations.
    Furthermore, some of auto’s type deduc‐ tion results, while dutifully conforming to the prescribed algorithm, are, from the perspective of a programmer, just wrong.
    When that’s the case, it’s important to know how to guide auto to the right answer, because falling back on manual type declarations is an alternative that’s often best avoided.
 
    *** Item 5: Prefer auto to explicit type declarations. ***
 
    auto variables have their type deduced from their initializer, so they must be initial‐ ized. That means you can wave goodbye to a host of uninitialized variable problems
 
    Things to Remember
    • auto variables must be initialized, are generally immune to type mismatches that can lead to portability or efficiency problems,
      can ease the process of refactoring, and typically require less typing than variables with explicitly specified types.
    • auto-typed variables are subject to the pitfalls described in Items 2 and 6.
 
 
    *** Item 6: Use the explicitly typed initializer idiom when auto deduces undesired types.  ***
 
 
    Things to Remember
    • “Invisible” proxy types can cause auto to deduce the “wrong” type for an ini‐ tializing expression.
    • The explicitly typed initializer idiom forces auto to deduce the type you want it to have.
 */

vector<bool> feature() {
    return vector<bool>(100);
}

void test_auto_vs_explicit_type() {
    
    // Though std::vector<bool> conceptually holds bools, operator[] for std::vector<bool> doesn’t return a reference to an element of the container
    // (which is what std::vector::operator[] returns for every type except bool).
    // Instead, it returns an object of type std::vector<bool>::reference (a class nested inside std::vector<bool>).
    
    // std::vector<bool>::reference exists because std::vector<bool> is specified to represent its bools in packed form, one bit per bool.
    // That creates a problem for std::vector<bool>’s operator[], because operator[] for std::vector<T> is supposed to return a T&, but C++ forbids references to bits.
    // Not being able to return a bool&, operator[] for std::vector<bool> returns an object that acts like a bool&.
    // For this act to succeed, std::vector<bool>::reference objects must be usable in essentially all contexts where bool&s can be.
    
    // Among the features in std::vec tor<bool>::reference that make this work is an implicit conversion to bool. (Not to bool&, to bool.
    {
        // explicit specified type
        bool high = feature()[5];
        
        // Here, features returns a std::vector<bool> object, on which operator[] is invoked. operator[] returns a std::vector<bool>::reference object,
        // which is then implicitly converted to the bool that is needed to initialize highPriority.
        // high Priority thus ends up with the value of bit 5 in the std::vector<bool> returned by features, just like it’s supposed to.
    }
    
    {
        auto high = feature()[5];
        // Again, features returns a std::vector<bool> object, and, again, operator[] is invoked on it.
        // operator[] continues to return a std::vector<bool>::reference object,
        // but now there’s a change, because auto deduces that as the type of highPriority.
        // highPriority doesn’t have the value of bit 5 of the std::vector<bool> returned by features at all.
        
        // *** fix it, by explicit cast
        
        auto high1 = static_cast<bool>(feature()[5]);
    }
    
    // Some proxy classes are designed to be apparent to clients. That’s the case for std::shared_ptr and std::unique_ptr, for example.
    // Other proxy classes are designed to act more or less invisibly.
    // std::vector<bool>::reference is an exam‐ ple of such “invisible” proxies, as is its std::bitset compatriot, std::bitset::ref erence.
    
    
    
}

void Test_type_deduce() {
    
    std::cout << "*** start type deduce ***" << std::endl;
    
    test_type_output();
    
    test_type_auto();
    
    test_type_template();
    
    test_auto_vs_explicit_type();
    
    std::cout << "*** end type deduce ***" << std::endl;
}
