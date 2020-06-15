
#include <stdio.h>
#include <iostream>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <array>
#include <atomic>

using namespace std;

/*
 
    *** Moving to Modern C++ ***
 When it comes to big-name features, C++11 and C++14 have a lot to boast of. auto, smart pointers, move semantics, lambdas, concurrency—each is so important, I devote a chapter to it.
 It’s essential to master those features, but becoming an effective modern C++ programmer requires a series of smaller steps, too.
 Each step answers specific questions that arise during the journey from C++98 to modern C++. When should you use braces instead of parentheses for object creation?
 Why are alias decla‐ rations better than typedefs? How does constexpr differ from const?
 What’s the relationship between const member functions and thread safety? The list goes on and on. And one by one, this chapter provides the answers.
 
 
 */

/*
 
    *** Item 7: Distinguish between () and {} when creating objects. ***
 
 Things to Remember
 • Braced initialization is the most widely usable initialization syntax, it prevents narrowing conversions, and it’s immune to C++’s most vexing parse.
 • During constructor overload resolution, braced initializers are matched to std::initializer_list parameters if at all possible,
    even if other constructors offer seemingly better matches.
 • An example of where the choice between parentheses and braces can make a significant difference is creating a std::vector<numeric type> with two arguments.
 • Choosing between parentheses and braces for object creation inside templates can be challenging.
 
 */
class Widget {
public:
    Widget(){}
    Widget(int, bool) {}
    Widget(int, double) {}
    Widget(std::initializer_list<long double>) {}
    
    operator float() const { return 1.0; }
    
    int getx() const { return x; }
    int getx() {
        std::cout << "call getx non-const" <<std::endl;
        return x;
    }
    
private:
    // Braces can also be used to specify default initialization values for non-static data members.
    int x{0};
    int y = 0;
    // int z(0); // error!
};

void test_basic() {
    
    Widget c;
    c.getx();
    
    const Widget b;
    b.getx();
}

void test_initilizer_list() {
    
    /*
     Widget w1; // call default constructor
     Widget w2 = w1; // not an assignment; calls copy ctor
     w1 = w2; // an assignment; calls copy operator=
    
     */
    {
        int x(0); // initializer is in parentheses
        int y = 0;    // initializer follows "="
        int z {0}; // initializer is in braces
        int z1 = { 0 }; // initializer uses "=" and braces
    }
    
    {
        // C++11 introduces "uniform initialization": a single initialization syntax that can, at least in concept, be used anywhere and express everything.
        // It’s based on braces, and for that reason I prefer the term braced initialization.
        // “Uniform initialization” is an idea. “Braced initialization” is a syntactic construct.
        std::vector<int> a{1, 2, 3};
        
        
        // A novel feature of braced initialization is that it prohibits implicit narrowing conver‐ sions among built-in types.
        // If the value of an expression in a braced initializer isn’t guaranteed to be expressible by the type of the object being initialized, the code won’t compile:
        double x, y, z;
        // *** int sum1{ x + y + z }; // error! sum of doubles may // not be expressible as int
        
        // Initialization using parentheses and “=” doesn’t check for narrowing conversions, because that could break too much legacy code:
        int sum2(x + y + z); // okay (value of expression // truncated to an int)
        int sum3 = x + y + z; // ditto
    }
    
    {
        // If, however, one or more constructors declare a parameter of type std::initial izer_list, calls using the braced initialization syntax strongly prefer the overloads taking
        // std::initializer_lists. Strongly. If there’s any way for compilers to con‐ strue a call using a braced initializer to be to a constructor taking a std::initial izer_list,
        // compilers will employ that interpretation. If the Widget class above is augmented with a constructor taking a std::initializer_list<long double>
    
        Widget w1(10, true); // uses parens and call Widget(int, bool), as before,
        
        Widget w2{10, true}; // uses braces, but now calls Widget(std::initializer_list<long double>), (10 and true convert to long double)
        
        Widget w3(10, 5.0); // uses parents and call Widget(int, double)
        
        Widget w4{10, 5.0}; // uses braces, but now calls Widget(std::initializer_list<long double>), (10 and 5.0 convert to long double)
        
        Widget w5(w4); // uses braces, call copy ctor
        
        Widget w6{w4}; // uses braces, calls
                       // std::initializer_list ctor
                      // (w4 converts to float, and float // converts to long double)
        
        Widget w7(std::move(w5)); // use braces, call move ctor
        
        Widget w8{std::move(w5)}; // uses braces, calls
                                  // std::initializer_list ctor
                                  // (for same reason as w6)
        
        // Compilers’ determination to match braced initializers with constructors taking std::initializer_lists is so strong,
        // it prevails even if the best-match std::ini tializer_list constructor can’t be called.
        
        // Only if there’s no way to convert the types of the arguments in a braced initializer to the type in a std::initializer_list do compilers fall back on normal overload resolution.
        // For example, if we replace the std::initializer_list<bool> construc‐ tor with one taking a std::initializer_list<std::string>,
        // the non- std::initializer_list constructors become candidates again, because there is no way to convert ints and bools to std::strings:
        
        // Widget w1(10, true);  // uses parens, still calls first ctor
        
        // Widget w2{10, true};  // uses braces, now calls first ctor
        
        // Widget w3(10, 5.0);   // uses parens, still calls second ctor
        
        // Widget w4{10, 5.0};   // uses braces, now calls second ctor
        
        
        // The rule is that you get default construction. Empty braces mean no arguments, not an empty std::initializer_list:
        
        Widget w9; // call default ctor
        
        Widget w10{}; // call default ctor
            
        // Widget w9(); This is function declaration
        
        
        // If you want to call a std::initializer_list constructor with an empty std::ini tializer_list,
        // you do it by making the empty braces a constructor argument—by putting the empty braces inside the parentheses or braces demarcating what you’re passing
        
        Widget w11({}); // call std::initializer_list ctor with empty list
        Widget w12{{}};
    }
    
    {
        std::vector<int> v1(10, 20); // use non-std::initializer_list
                                    // ctor: create 10-element
                                    // std::vector, all elements have
                                    // value of 20
        
        std::vector<int> v2{10, 20}; // use std::initializer_list ctor:
                                    // create 2-element std::vector,
                                    // element values are 10 and 20
        
        // The second lesson is that as a class client, you must choose carefully between paren‐ theses and braces when creating objects. Most developers end up choosing one kind
        // of delimiter as a default, using the other only when they have to. Braces-by-default folks are attracted by their unrivaled breadth of applicability,
        // their prohibition of nar‐ rowing conversions, and their immunity to C++’s most vexing parse. Such folks understand that in some cases (e.g., creation of a std::vector with a given size and initial element value),
        // parentheses are required. On the other hand, the go- parentheses-go crowd embraces parentheses as their default argument delimiter. They’re attracted to its consistency with the
        // C++98 syntactic tradition, its avoidance of the auto-deduced-a-std::initializer_list problem, and the knowledge that their object creation calls won’t be inadvertently waylaid by std::initial izer_list constructors.
        // They concede that sometimes only braces will do (e.g., when creating a container with particular values).
        // There’s no consensus that either approach is better than the other, so my advice is to pick one and apply it consis‐ tently.
    }
}

/*
 
    *** Item 8: Prefer nullptr to 0 and NULL. ***
 
 Things to Remember
 • Prefernullptrto0andNULL.
 • Avoid overloading on integral and pointer types.
 
 */

int f1(std::shared_ptr<Widget> spw) { return 0; } // call these only when
double f2(std::unique_ptr<Widget> upw) { return 0.0; } // the appropriate
bool f3(Widget* pw) { return true; } // mutex is locked

using MuxGuard = std::lock_guard<std::mutex>;


template <typename FuncType, typename MutexType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MutexType& mutex, PtrType ptr) {
    
    MuxGuard g(mutex);
    return func(ptr);
}

void test_nullptr_vs_NULL() {
    
    // So here’s the deal: the literal 0 is an int, not a pointer. If C++ finds itself looking at 0 in a context where only a pointer can be used,
    // it’ll grudgingly interpret 0 as a null pointer, but that’s a fallback position. C++’s primary policy is that 0 is an int, not a pointer.
    //
    // In C++98, the primary implication of this was that overloading on pointer and integral types could lead to surprises.
    // Passing 0 or NULL to such overloads never called a pointer overload:
    // void f(int);  // three overloads of f
    // void f(bool);
    // void f(void*);
    // f(0);            // calls f(int), not f(void*)
    // f(NULL);         // might not compile, but typically calls, f(int). Never calls f(void*)
    
    // That guideline remains valid in C++11, because, the advice of this Item notwithstanding, it’s likely that some developers will continue to use 0 and NULL,
    // even though nullptr is a better choice.
    
    // nullptr’s advantage is that it doesn’t have an integral type. To be honest, it doesn’t have a pointer type, either, but you can think of it as a pointer of all types.
    // nullptr’s actual type is std::nullptr_t, and, in a wonderfully circular definition, std::nullptr_t is defined to be the type of nullptr.
    // The type std::nullptr_t implicitly converts to all raw pointer types, and that’s what makes nullptr act as if it were a pointer of all types.
    
    // f(nullptr);         // calls f(void*) overload
    
    // Using nullptr instead of 0 or NULL thus avoids overload resolution surprises, but that’s not its only advantage.
    // It can also improve code clarity, especially when auto variables are involved.
    
    // if (result == nullptr) { ...
    // }
    // there’s no ambiguity: result must be a pointer type.
    
    std::mutex mx1, mx2, mx3;
    
    {
        MuxGuard g(mx1);
        f1(0);
    }
    
    {
        MuxGuard g(mx2);
        f2(NULL);
    }
    
    {
        MuxGuard g(mx3);
        f3(nullptr);
    }
    // The failure to use nullptr in the first two calls in this code is sad, but the code works, and that counts for something.
    // However, the repeated pattern in the calling code—lock mutex, call function, unlock mutex—is more than sad. It’s disturbing.
    // This kind of source code duplication is one of the things that templates are designed to avoid, so let’s templatize the pattern:
    
    {
        auto res1 = lockAndCall(f1, mx1, nullptr); // fine
        
        // auto result1 = lockAndCall(f1, mx2, 0); // error!

        // auto result2 = lockAndCall(f2, f2m, NULL); // error!
        
        // Well, they can write it, but, as the comments indicate, in two of the three cases, the code won’t compile. The problem in the first call is that when 0 is passed to lockAnd Call, template type deduction kicks in to figure out its type.
        // The type of 0 is, was, and always will be int, so that’s the type of the parameter ptr inside the instantiation of this call to lockAndCall.
        // Unfortunately, this means that in the call to func inside lockAndCall, an int is being passed, and that’s not compatible with the std::shared_ptr<Widget> parameter that f1 expects.
        // The 0 passed in the call to lockAndCall was intended to represent a null pointer, but what actually got passed was a run-of-the-mill int.
        // Trying to pass this int to f1 as a std::shared_ptr <Widget> is a type error. The call to lockAndCall with 0 fails because inside the template, an int is being passed to a function that requires a std:: shared_ptr<Widget>
        // The analysis for the call involving NULL is essentially the same.
        
        // In contrast, the call involving nullptr has no trouble. When nullptr is passed to lockAndCall, the type for ptr is deduced to be std::nullptr_t.
        // When ptr is passed to f3, there’s an implicit conversion from std::nullptr_t to Widget*, because std::nullptr_t implicitly converts to all pointer types.
        
    }
}

/*
 
    *** Item 9: Prefer alias declarations to typedefs. ***
 
 Things to Remember
 • typedefs don’t support templatization, but alias declarations do.
 • Alias templates avoid the “::type” suffix and, in templates, the “typename”
 prefix often required to refer to typedefs.
 • C++14 offers alias templates for all the C++11 type traits transformations.
 
 */

// my guess is that neither of us is fond of writing types like “std::unique_ptr<std::unor dered_map<std::string,std::string>>” more than once.
// Just thinking about it probably increases the risk of carpal tunnel syndrome.
// Avoiding such medical tragedies is easy. Introduce a typedef:
 
typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;

// But typedefs are soooo C++98. They work in C++11, sure, but C++11 also offers alias declarations:
using UPTRMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;


// alieas is easier than typedef
typedef void(*FP)(int, const std::string&);

// same above
using FP1 = void(*)(int, const std::string&);

// Of course, neither form is particularly easy to choke down, and few people spend much time dealing with synonyms for function pointer types, anyway, so this is hardly a compelling reason to choose alias declarations over typedefs.
// But a compelling reason does exist: templates. In particular, alias declarations may be templatized (in which case they’re called alias templates), while typedefs cannot.


template <typename T>
class MyAlloc;

template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;

// by tyoedef

template <typename T>
struct MyAllocListDef {
    typedef std::list<T, MyAlloc<T>> type;
};

// It gets worse. If you want to use the typedef inside a template for the purpose of creating a linked list holding objects of a type specified by a template parameter, you have to precede the typedef name with typename:
//  template<typename T>
//   class Widget {                         // Widget<T> contains
//   private:                               // a MyAllocList<T>
//      typename MyAllocListDef<T>::type list; // as a data member

        // Here, MyAllocList<T>::type refers to a type that’s dependent on a template type parameter (T).
        // MyAllocList<T>::type is thus a dependent type, and one of C++’s many endearing rules is that the names of dependent types must be preceded by type name.

//      ...
//      MyAllocList<T> list                 // no "typename", no "::type"
// };

// C++11 gives you the tools to perform these kinds of transformations in the form of type traits, an assortment of templates inside the header <type_traits>.
// There are dozens of type traits in that header, and not all of them perform type transforma‐ tions, but the ones that do offer a predictable interface.
// Given a type T to which you’d like to apply a transformation, the resulting type is std::transformation <T>::type.
/*
// #include <trait_type>
// The aliases have a common form: for each C++11 transformation std::transformation<T>::type, there’s a corresponding C++14 alias template named std::transformation_t. Examples will clarify what I mean:

 std::remove_const<T>::type std::remove_const_t<T>   // C++11: const T → T
                                                    // C++14 equivalent
 
 std::remove_reference<T>::type std::remove_reference_t<T>   // C++11: T&/T&& → T
                                                            // C++14 equivalent
 
 std::add_lvalue_reference<T>::type std::add_lvalue_reference_t<T>   // C++11: T → T&
                                                                     // C++14 equivalent
 

 template <class T>
 using remove_const_t = typename remove_const<T>::type;
 
 template <class T>
 using remove_reference_t = typename remove_reference<T>::type;
 
 template <class T>
 using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
*/

/*
    *** Item 10: Prefer scoped enums to unscoped enums. ***

 Things to Remember
 • C++98-style enums are now known as unscoped enums.
 • Enumerators of scoped enums are visible only within the enum. They convert to other types only with a cast.
 • Both scoped and unscoped enums support specification of the underlying type. The default underlying type for scoped enums is int. Unscoped enums have no default underlying type.
 • Scoped enums may always be forward-declared. Unscoped enums may be forward-declared only if their declaration specifies an underlying type.
 
 */

// But if compilers need to know the size of an enum before it’s used, how can C++11’s enums get away with forward declarations when C++98’s enums can’t? The answer is simple:
// the underlying type for a scoped enum is always known, and for unscoped enums, you can specify it.

// 3) It may seem that scoped enums have a third advantage over unscoped enums, because scoped enums may be forward-declared, i.e.,
// their names may be declared without specifying their enumerators:
enum class Color;

// As a general rule, declaring a name inside curly braces limits the visibility of that name to the scope defined by the braces.
// Not so for the enumerators declared in C++98-style enums.
// The names of such enumerators belong to the scope containing the enum, and that means that nothing else in that scope may have the same name:
enum color { black, red, white }; // black, white, red are
                                  // in same scope as Color
// auto white = false; // error! white already
                       // declared in this scope

// The fact that these enumerator names leak into the scope containing their enum definition gives rise to the official term for this kind of enum: unscoped.
// Their new C++11 counterparts, scoped enums, don’t leak names in this way:
enum class Color { Black, Red, White }; // black, white, red
                                        // are scoped to Color

/*
 
 By default, the underlying type for scoped enums is int:
    enum class Status; // underlying type is int
 
 If the default doesn’t suit you, you can override it:
    enum class Status: std::uint32_t; // underlying type for
 
 // Status is std::uint32_t  (from <cstdint>)
 
 // Either way, compilers know the size of the enumerators in a scoped enum.
 // To specify the underlying type for an unscoped enum, you do the same thing as for a
    
 // scoped enum, and the result may be forward-declared:
    enum Color: std::uint8_t; // fwd decl for unscoped enum; // underlying type is
 
 // std::uint8_t
 // Underlying type specifications can also go on an enum’s definition:
 */

enum class Status: std::uint32_t {
    good = 0,
    failed = 1,
    incomplete = 100,
    corrupt = 200,
    audited = 500,
    indeterminate = 0xFFFFFFFF
};

auto w1 = false; // fine!
Color s = Color::White;
auto s1 = Color::White;
// Color s2 = White;   // error! no enumerator named
                        // "white" is in this scope


// 2) The reduction in namespace pollution offered by scoped enums is reason enough to prefer them over their unscoped siblings,
// but scoped enums have a second compelling advantage: their enumerators are much more strongly typed.

// Enumerators for unsco‐ ped enums implicitly convert to integral types (and, from there, to floating-point types).
// Semantic travesties such as the following are therefore completely valid:

using UserInfo = std::tuple<std::string, std::string, std::size_t>;
enum userInfo {uiName, uiEmail, uiReputation};


// In fact, it should really be a constexpr function template, because it should work with any kind of enum. And if we’re going to make that generalization, we should
// generalize the return type, too. Rather than returning std::size_t, we’ll return the enum’s underlying type.
//
// template<typename E>
// constexpr typename std::underlying_type<E>::type
//      toUType(E enumerator) noexcept
//   {
// return static_cast<typename std::underlying_type<E>::type>(enumerator);
// }


template<typename E> // C++14
constexpr auto toUType(E enumerator) noexcept {
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

void test_scope_unscoped_enum() {
    color c = red;
    
    if (c < 14.5) {
        std::cout << "unscoped enum can convert to integer and float" << std::endl;
    }
    
    Color c1 = Color::Red;
    // if (c < 1) {  // error! Color and double can't compare
    if (static_cast<double>(c) < 14.5) {
        std::cout << "scoeped enum can static_cast to a double" << std::endl;
    }
    
    // In view of the fact that scoped enums avoid namespace pollution and aren’t suscepti‐ ble to nonsensical implicit type conversions,
    // it may surprise you to hear that there’s at least one situation where unscoped enums may be useful. That’s when referring to fields within C++11’s std::tuples.
    
    UserInfo uInfo;
    
    // auto val = std::get<1>(uInfo);
    auto val = std::get<uiName>(uInfo);
    
    // The corresponding code with scoped enums is substantially more verbose:
    // auto val = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo);

    // The verbosity can be reduced by writing a function that takes an enumerator and returns its corresponding std::size_t value, but it’s a bit tricky. std::get is a template,
    // and the value you provide is a template argument (notice the use of angle brackets, not parentheses),
    // so the function that transforms an enumerator into a std::size_t has to produce its result during compilation.
    auto val1 = std::get<toUType(userInfo::uiName)>(uInfo);
}

/*
 
    Item 11: Prefer deleted functions to private undefined ones.
 
 Things to Remember
 • Prefer deleted functions to private undefined ones.
 • Any function may be deleted, including non-member functions and template instantiations.
 
 
 The difference between deleting these functions and declaring them private may seem more a matter of fashion than anything else, but there’s greater substance here than you might think.
 Deleted functions may not be used in any way, so even code that’s in member and friend functions will fail to compile if it tries to copy basic_ios objects.
 That’s an improvement over the C++98 behavior, where such improper usage wouldn’t be diagnosed until link-time.
 
 By convention, deleted functions are declared public, not private. There’s a reason for that. When client code tries to use a member function, C++ checks accessibility before deleted status.
 When client code tries to use a deleted private function, some compilers complain only about the function being private, even though the func‐ tion’s accessibility doesn’t really affect whether it can be used.
 
 
 An important advantage of deleted functions is that any function may be deleted, while only member functions may be private.
 
 if (isLucky('a')) ...           // is 'a' a lucky number?
 if (isLucky(true)) ...          // is "true"?
 if (isLucky(3.5)) ...           // should we truncate to 3
                                // before checking for luckiness?
 The truth is that the C++98 practice of declaring functions private and not defining them was really an attempt to achieve what C++11’s deleted functions actually accomplish.
 As an emulation, the C++98 approach is not as good as the real thing. It doesn’t work outside classes, it doesn’t always work inside classes, and when it does work, it may not work until link-time. So stick to deleted functions.
 */

class NoCopy {
public:
    
    NoCopy() {}
    ~NoCopy() {}
private:
    // C++98
    // NoCopy(const NoCopy&);
    // NoCopy& operator=(const NoCopy&);
public:
    // C++11 delete functions should be declared public, nor private.
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
};

bool isLucky(int number); // original function
bool isLucky(char) = delete; // reject chars
bool isLucky(bool) = delete; // reject bools


template<typename T>
void processPointer(T* ptr);

template<>
void processPointer<void>(void*) = delete;

template<>
void processPointer<char>(char*) = delete;

template<>
void processPointer<const void>(const void*) = delete;

template<>
void processPointer<const char>(const char*) = delete;



/*
 
 Item 12: Declare overriding functions override.

 Things to Remember
 • Declare overriding functions override.
 • Member function reference qualifiers make it possible to treat lvalue and rvalue objects (*this) differently.
 
 
 KeyWord :  override, final
 
 
 For overriding to occur, several requirements must be met:
 
 1) The base class function must be virtual.
 2) The base and derived function names must be identical (except in the case of destructors).
 3) The parameter types of the base and derived functions must be identical. The constness of the base and derived functions must be identical.
 4) The return types and exception specifications of the base and derived functions must be compatible.

 TO these constraints, which were also part of C++98, C++11 adds one more:
 
 5) The functions’ reference qualifiers must be identical. Member function reference qualifiers are one of C++11’s less-publicized features, so don’t be surprised if you’ve never heard of them.
    They make it possible to limit use of a member func‐ tion to lvalues only or to rvalues only.
    
 Because declaring derived class overrides is important to get right, but easy to get wrong, C++11 gives you a way to make explicit that a derived class function is
    supposed to override a base class version: declare it {"override"}.
 
 A policy of using override on all your derived class overrides can do more than just enable compilers to tell you when would-be overrides aren’t overriding anything.
 It can also help you gauge the ramifications if you’re contemplating changing the signa‐ ture of a virtual function in a base class.
 If derived classes use override everywhere, you can just change the signature, recompile your system, see how much damage you’ve caused (i.e., how many derived classes fail to compile), then decide whether the signature change is worth the trouble.
 
 C++ has always had keywords, but C++11 introduces two contextual keywords, over ride and final.2 These keywords have the characteristic that they are reserved, but
 only in certain contexts. In the case of override, it has a reserved meaning only when it occurs at the end of a member function declaration.
 */

class Base {
public:
    virtual void doWork() {
        std::cout << "base case doworks" << std::endl;
    }
    
    virtual void mf1() const;
    virtual void mf2(int x);
    virtual void mf3() &;
    void mf4() const;
};

class Derived: public Base {
public:
    virtual void doWork() override /*keyword, to say override a function in base class, if can't find, it will be error */ {
        std::cout << "Derived case doworks " << std::endl;
    }
    
    virtual void mf1();                     // • mf1 is declared const in Base, but not in Derived.
    virtual void mf2(unsigned int x);       // • mf2 takes an int in Base, but an unsigned int in Derived.
    virtual void mf3() &&;                  // • mf3 is lvalue-qualified in Base, but rvalue-qualified in Derived.
    void mf4() const;                       // • mf4 isn’t declared virtual in Base.
    
    
    void doWork1() &; // this version of doWork applies
                      // only when *this is an lvalue
    
    void doWork1() &&;  // this version of doWork applies
                        // only when *this is an rvalue
};



/*
    Item 13: Prefer const_iterators to iterators.
 
    Things to Remember
 • Prefer const_iterators to iterators.
 • In maximally generic code, prefer non-member versions of begin, end, rbegin, etc., over their member function counterparts.
 
 That’s as true for C++98 as for C++11, but in C++98, const_iterators had only halfhearted support. It wasn’t that easy to create them, and once you had one, the ways you could use it were limited.
 
 All that changed in C++11. Now const_iterators are both easy to get and easy to use. The container member functions cbegin and cend produce const_iterators, even for non-const containers, and STL member functions that use iterators to iden‐ tify positions
 (e.g., insert and erase) actually use const_iterators. Revising the original C++98 code that uses iterators to use const_iterators in C++11 is truly trivial:
 
 
 */

void test_prefer_const_iterator() {
    
    std::vector<int> values;
    {
        // C++ 98
        typedef std::vector<int>::const_iterator ConstIter;
        ConstIter it = std::find(static_cast<ConstIter>(values.begin()), static_cast<ConstIter>(values.end()), 1983);
    }

    {
        // C++ 11
        auto it = std::find(values.cbegin(), values.cend(), 1983);
        values.insert(it, 1998);
    }
    
    {
        // C++ 14
        // This works fine in C++14, but, sadly, not in C++11. Through an oversight during standardization, C++11 added the non-member functions begin and end, but it failed to add cbegin, cend, rbegin, rend, crbegin, and crend. C++14 rectifies that oversight.
        auto it = std::find(std::cbegin(values), std::cend(values), 1993);
        
        values.insert(it, 1998);
    }
}


/*
 
    Item 14: Declare functions noexcept if they won’t emit exceptions.
 
    Things to Remember
    • noexcept is part of a function’s interface, and that means that callers may depend on it.
    • noexcept functions are more optimizable than non-noexcept functions.
    • noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.
    • Most functions are exception-neutral rather than noexcept.
 
 
 In C++98, exception specifications were rather temperamental beasts. You had to summarize the exception types a function might emit, so if the function’s implemen‐ tation was modified, the exception specification might require revision, too.
 Changing an exception specification could break client code, because callers might be dependent on the original exception specification.
 Compilers typically offered no help in maintaining consistency among function implementations, exception specifi‐ cations, and client code. Most programmers ultimately decided that C++98 exception specifications weren’t worth the trouble.
 
 
 int f(int x) throw(); // no exceptions from f: C++98 style
 int f(int x) noexcept; // no exceptions from f: C++11 style
 
 If, at runtime, an exception leaves f, f’s exception specification is violated. With the C++98 exception specification, the call stack is unwound to f’s caller, and, after some
 actions not relevant here, program execution is terminated. With the C++11 excep‐ tion specification, runtime behavior is slightly different: the stack is only possibly unwound before program execution is terminated.

 The difference between unwinding the call stack and possibly unwinding it has a sur‐ prisingly large impact on code generation. In a noexcept function, optimizers need not keep the runtime stack in an unwindable state if an exception would propagate out of the function, nor must they ensure that objects in a noexcept function are destroyed in the inverse order of construction should an exception leave the function.
 Functions with “throw()” exception specifications lack such optimization flexibility, as do functions with no exception specification at all. The situation can be summar‐ ized this way:
 
ReturnType function(params)  // most optimizable
ReturnType function(params)  // less optimizable
ReturnType function(params)  // less optimizable

 Therefore, C++11 implementations
 can’t silently replace copy operations inside push_back with moves unless it’s known that the move operations won’t emit exceptions.
 In that case, having moves replace copies would be safe, and the only side effect would be improved performance.
 
 std::vector::push_back takes advantage of this “move if you can, but copy if you must” strategy, and it’s not the only function in the Standard Library that does.
 Other functions sporting the strong exception safety guarantee in C++98 (e.g., std::vec tor::reserve, std::deque::insert, etc.) behave the same way.
 All these functions replace calls to copy operations in C++98 with calls to move operations in C++11 only if the move operations are known to not emit exceptions.
 
 
 *** These functions are conditionally noexcept: whether they are noexcept depends on whether the expressions inside the noexcept clauses are noexcept.
 
 // By default, all memory deallocation functions and all destructors—both user-defined and compiler- generated—are implicitly noexcept. There’s thus no need to declare them noexcept. (Doing so doesn’t hurt anything, it’s just unconventional.)
 The only time a destructor is not implicitly noexcept is when a data member of the class (including inherited members and those contained inside other data members) is of a type that expressly states that its destructor may emit exceptions
 (e.g., declares it “noexcept(false)”).
 
 // Because there are legitimate reasons for noexcept functions to rely on code lacking the noexcept guarantee, C++ permits such code, and compilers generally don’t issue warnings about it.
 
 
 */
template <class T, size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));

// template <class T1, class T2>
// struct pair {
//     void swap(pair& p) noexcept(noexcept(swap(first, p.first) && noexcept(swap(secomd, p.second)));
// }

// he fact of the matter is that most functions are exception-neutral. Such functions throw no exceptions themselves, but functions they call might emit one.

// Exception-neutral functions are never noexcept, because they may emit such “just passing through” exceptions. Most functions, therefore, quite properly lack the noexcept designation.

/*
 
    Item 15: Use constexpr whenever possible.
 
 Things to Remember
 • constexpr objects are const and are initialized with values known during "compilation".
 • constexpr functions can produce compile-time results when called with arguments whose values are known during compilation.
 • constexpr objects and functions may be used in a wider range of contexts than non-constexpr objects and functions.
 • constexpr is part of an object’s or function’s interface.
 

 If there were an award for the most confusing new word in C++11, "constexpr" would probably win it.
 Conceptually, constexpr indicates a value that’s not only constant, it’s known during compilation.
 
 But let’s begin with constexpr objects. Such objects are, in fact, const, and they do, in fact, have values that are known at compile time.
 (Technically, their values are determined during translation, and translation consists not just of compilation but also of linking.
 Unless you write compilers or linkers for C++, however, this has no effect on you, so you can blithely program as if the values of constexpr objects were determined during compilation.)
 Values known during compilation are privileged. They may be placed in read-only memory,
 
 Simply put, all constexpr objects are const, but not all const objects are con stexpr.
 If you want compilers to guarantee that a variable has a value that can be used in contexts requiring compile-time constants, the tool to reach for is con stexpr, not const.
 
 Usage scenarios for constexpr objects become more interesting when constexpr functions are involved. Such functions produce compile-time constants when they are called with compile-time constants.
 
 • constexpr functions can be used in contexts that demand compile-time con‐ stants. If the values of the arguments you pass to a constexpr function in such a context are known during compilation, the result will be computed during compilation.
    If any of the arguments’ values is not known during compilation, your code will be rejected.
 
 • When a constexpr function is called with one or more values that are not known during compilation, it acts like a normal function, computing its result at runtime.
    This means you don’t need two functions to perform the same opera‐ tion, one for compile-time constants and one for all other values. The constexpr function does it all.

 
 */

// Because constexpr functions must be able to return compile-time results when called with compile-time values, restrictions are imposed on their implementations. The restrictions differ between C++11 and C++14.
// In C++11, constexpr functions may contain no more than a single executable statement: a return.
// That sounds more limiting than it is, because two tricks can be used to extend the expressiveness of constexpr functions beyond what you might think.
// First, the conditional “?:” operator can be used in place of if-else statements, and second, recursion can be used instead of loops.
constexpr int pow11(int base, int exp) noexcept { // C++ 11 support
    return (exp == 0 ? 1 : base * pow(base, exp - 1));
}
// In C++14, the restrictions on constexpr func‐ tions are substantially looser,
constexpr int pow14(int base, int exp) noexcept { // C++ 14 support
    auto res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

// constexpr functions are limited to taking and returning literal types, which essen‐ tially means types that can have values determined during compilation.
// In C++11, all built-in types except void qualify, but user-defined types may be literal, too, because constructors and other member functions may be constexpr

class Point {
public:
    
    constexpr Point(double xVal = 0, double yVal = 0) noexcept
    : x(xVal), y(yVal){}
    
    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }

    // In C++11, two restrictions prevent Point’s member functions setX and setY from being declared constexpr. First, they modify the object they operate on,
    // and in C++11, constexpr member functions are implicitly const. Second, they have void return types, and void isn’t a literal type in C++11.
    // Both these restrictions are lifted in C++14, so in C++14, even Point’s setters can be constexpr:
    constexpr void setX(double newX) noexcept { x = newX; } // C++14
    constexpr void setY(double newY) noexcept { y = newY; } // C++14
private:
    double x, y;
};

constexpr Point
midPoint(const Point& p1, const Point& p2) noexcept {
    return {(p1.xValue() + p2.xValue()) / 2,
            (p1.yValue() + p2.yValue()) / 2};
}

void test_constexpr() {
    
    int sz; // non-constexpr variable
    
    // constexpr auto arraysize = sz;   // error! sz's value not known at compilation
    
    constexpr auto array_size = 10; // fine 10 is a constexpr variable.
    
    std::array<int, array_size> data2; // fine array_size is constexpr
    
    constexpr auto numConds = 5;
    
    std::array<int, pow14(3, numConds)> results; // results has 3^numConds elements
    
    
    // Recall that the constexpr in front of pow doesn’t say that pow returns a const value, it says that if base and exp are compile-time constants, pow’s result may be used as a compile-time constant.
    // If base and/or exp are not compile-time constants, pow’s result will be computed at runtime.
    auto base = 3;
    auto exp = 4;
    auto baseToExp = pow14(base, exp); // call pow function at runtime
    
    constexpr Point p1(9.4, 27.7);  // fine, "run" constexpr ctor duing compilation
    constexpr Point p2(28.8, 5.3); // alse fine
    
    constexpr auto mid = midPoint(p1, p2);
}


/*
 
    Item 16: Make const member functions thread safe.
 
 Things to Remember
 • Make const member functions thread safe unless you’re certain they’ll never be used in a concurrent context.
 • Use of std::atomic variables may offer better performance than a mutex, but they’re suited for manipulation of only a single variable or memory location.
 
 
 */

class Polynomial {
public:
    
    using RootsType = std::vector<double>;
    
    RootsType roots() const {
        
        // roots is a const member function, and that means it represents a read operation.
        // Having multiple threads perform a read opera‐ tion without synchronization is safe.
        // n this case, it’s not, because inside roots, one or both of these threads might try to modify the data members rootsAreValid and rootVals.
        // That means that this code could have different threads reading and writing the same memory without synchronization, and that’s the definition of a data race. This code has undefined behavior.
        
        // The std::mutex m is declared mutable, because locking and unlocking it are non- const member functions, and within roots (a const member function), m would otherwise be considered a const object.
        // It’s worth noting that because std::mutex is a move-only type (i.e., a type that can be moved, but not copied), a side effect of adding m to Polynomial is that Polynomial loses the ability to be copied. It can still be moved, however.
        std::lock_guard<std::mutex> g(m);
        
        // In some situations, a mutex is overkill. For example, if all you’re doing is counting how many times a member function is called, a std::atomic counter will often be a less expensive way to go.
        ++callcount;
        
        if (!rootsAreValid) {
            rootsAreValid = true;
        }
        return rootvals;
    }
    
private:
    mutable std::mutex m;
    mutable bool rootsAreValid{false};
    mutable RootsType rootvals{};
    
    mutable std::atomic<unsigned> callcount{0};
};


/*
 
    Item 17: Understand special member function generation.
 
 Things to Remember
 • The special member functions are those compilers may generate on their own: default constructor, destructor, copy operations, and move operations.
 • Move operations are generated only for classes lacking explicitly declared move operations, copy operations, and a destructor.
 • The copy constructor is generated only for classes lacking an explicitly declared copy constructor, and it’s deleted if a move operation is declared.
        The copy assignment operator is generated only for classes lacking an explic‐ itly declared copy assignment operator,
        and it’s deleted if a move operation is declared. Generation of the copy operations in classes with an explicitly declared destructor is deprecated.
 • Member function templates never suppress generation of special member functions.
 
 In official C++ parlance, the special member functions are the ones that C++ is willing to generate on its own. C++98 has four such functions:
        the default constructor, the destructor, the copy constructor, and the copy assignment operator.
 
 These functions are generated only if they’re needed, i.e., if some code uses them without their being expressly declared in the class.
 A default constructor is generated only if the class declares no constructors at all.
 
 Generated special member functions are implicitly public and inline, and they’re nonvirtual
 unless the function in question is a destructor in a derived class inheriting from a base class with a virtual destructor.
 In that case, the compiler-generated destructor for the derived class is also virtual.
 
 
 The C++11 rules governing the special member functions are thus:
 • Default constructor: Same rules as C++98. Generated only if the class contains no user-declared constructors.
 • Destructor: Essentially same rules as C++98; sole difference is that destructors are noexcept by default (see Item 14).
    As in C++98, virtual only if a base class destructor is virtual.
 • Copy constructor: Same runtime behavior as C++98: memberwise copy con‐ struction of non-static data members. Generated only if the class lacks a user- declared copy constructor.
    Deleted if the class declares a move operation. Generation of this function in a class with a user-declared copy assignment oper‐ ator or destructor is deprecated.
 • Copy assignment operator: Same runtime behavior as C++98: memberwise copy assignment of non-static data members.
    Generated only if the class lacks a user-declared copy assignment operator.
    Deleted if the class declares a move operation. Generation of this function in a class with a user-declared copy con‐ structor or destructor is deprecated.
 • Move constructor and move assignment operator: Each performs memberwise moving of non-static data members.
    Generated only if the class contains no user- declared copy operations, move operations, or destructor.

 Now, when I refer to a move operation move-constructing or move-assigning a data member or base class, there is no guarantee that a move will actually take place.
 “Memberwise moves” are, in reality, more like memberwise move requests, because types that aren’t move-enabled (i.e., that offer no special support for move operations, e.g.,
 most C++98 legacy classes) will be “moved” via their copy operations.
 The heart of each memberwise “move” is application of std::move to the object to be moved from, and
 the result is used during function overload resolution to determine whether a move or a copy should be performed.
 
 The two copy operations are independent: declaring one doesn’t prevent compilers from generating the other.
 So if you declare a copy constructor, but no copy assign‐ ment operator, then write code that requires copy assignment, compilers will generate the copy assignment operator for you.
 Similarly, if you declare a copy assignment operator, but no copy constructor, yet your code requires copy construction, compilers will generate the copy constructor for you.
 That was true in C++98, and it’s still true in C++11.
 
 The two move operations are not independent. If you declare either, that prevents compilers from generating the other.
 The rationale is that if you declare, say, a move constructor for your class, you’re indicating that there’s something about how move construction should be implemented that’s different
 from the default memberwise move that compilers would generate.
 And if there’s something wrong with memberwise move construction, there’d probably be something wrong with memberwise move assignment, too.
 So declaring a move constructor prevents a move assignment operator from being generated, and declaring a move assignment operator prevents compilers from generating a move constructor.

 Furthermore, move operations won’t be generated for any class that explicitly declares a copy operation. The justification is that declaring a copy operation (construction or assignment)
 indicates that the normal approach to copying an object (memberwise copy) isn’t appropriate for the class, and compilers figure that if mem‐ berwise copy isn’t appropriate for the copy
 operations, memberwise move probably isn’t appropriate for the move operations.
 
 Perhaps you’ve heard of a guideline known as the Rule of Three. The Rule of Three states that if you declare any of a copy constructor, copy assignment operator, or destructor,
 you should declare all three.
 It grew out of the observation that the need to take over the meaning of a copy operation almost always stemmed from the class performing some kind of resource management,
 and that almost always implied that
 (1) whatever resource management was being done in one copy operation probably needed to be done in the other copy operation and
 (2) the class destructor would also be participating in management of the resource (usually releasing it).
       The classic resource to be managed was memory, and this is why all Standard Library classes that manage memory
       (e.g., the STL containers that perform dynamic memory manage‐ ment) all declare “the big three”: both copy operations and a destructor.
 
 A consequence of the Rule of Three is that the presence of a user-declared destructor indicates that simple memberwise copy is unlikely to be appropriate for the copying operations in the class.
 That, in turn, suggests that if a class declares a destructor, the copy operations probably shouldn’t be automatically generated, because they wouldn’t do the right thing.
 At the time C++98 was adopted, the significance of this line of reasoning was not fully appreciated, so in C++98, the existence of a user- declared destructor had no impact on compilers’ willingness to generate copy operations.
 That continues to be the case in C++11, but only because restricting the conditions under which the copy operations are generated would break too much legacy code.
 
 The reasoning behind the Rule of Three remains valid, however, and that, combined with the observation that declaration of a copy operation p
 recludes the implicit generation of the move operations, motivates the fact that C++11 does not generate move operations for a class with a user-declared destructor.
 
 So move operations are generated for classes (when needed) only if these three things are true:
 • No copy operations are declared in the class.
 • No move operations are declared in the class.
 • No destructor is declared in the class.
 
 This looks reasonable, but declaring a destructor has a potentially significant side effect: it prevents the move operations from being generated. However, creation of the class’s copy operations is unaffected.
 
 Now, having endured my endless blathering about the rules governing the copy and move operations in C++11, you may wonder when I’ll turn my attention to the two other special member functions,
 the default constructor and the destructor. That time is now, but only for this sentence, because almost nothing has changed for these member functions: the rules in C++11 are nearly the same as in C++98.
 
 The C++11 rules governing the special member functions are thus:
 • Default constructor: Same rules as C++98. Generated only if the class contains no user-declared constructors.
 
 • Destructor: Essentially same rules as C++98; sole difference is that destructors are noexcept by default (see Item 14). As in C++98, virtual only if a base class destructor is virtual.
 
 • Copy constructor: Same runtime behavior as C++98: memberwise copy con‐ struction of non-static data members. Generated only if the class lacks a user- declared copy constructor. Deleted if the class declares a move operation.
        Generation of this function in a class with a user-declared copy assignment oper‐ ator or destructor is deprecated.
 
 • Copy assignment operator: Same runtime behavior as C++98: memberwise copy assignment of non-static data members. Generated only if the class lacks a user-declared copy assignment operator. Deleted if the class declares a move
        operation. Generation of this function in a class with a user-declared copy con‐ structor or destructor is deprecated.

 • Move constructor and move assignment operator: Each performs memberwise moving of non-static data members. Generated only if the class contains no user- declared copy operations, move operations, or destructor.
 
 
 */

class BaseC {
public:
    
    BaseC(); // if needed and without it, default one create
    virtual ~BaseC() = default; // if has derivd class, default dctor will be virual

    BaseC(const BaseC&) = default; // copy ctor
    BaseC& operator=(const BaseC&) = default; //copy assignment operator
    
    //  The move operations are generated only if they’re needed, and if they are generated, they perform “memberwise moves” on the non-static data members of the class.
    // That means that the move constructor move-constructs each non-static data member of the class from the corresponding member of its parameter rhs,
    //          and the move assignment operator move-assigns each non-static data member from its parameter.
    // The move constructor also move-constructs its base class parts (if there are any), and the move assignment operator move-assigns its base class parts.
    
    BaseC(BaseC&& rhs) = default; // move ctor
    BaseC& operator=(BaseC&& rhs) = default; // move assignment operator
    // Now, when I refer to a move operation move-constructing or move-assigning a data member or base class, there is no guarantee that a move will actually take place.
    // “Memberwise moves” are, in reality, more like memberwise move requests, because types that aren’t move-enabled (i.e., that offer no special support for move operations, e.g.,
    // most C++98 legacy classes) will be “moved” via their copy operations.
    
};

// This approach is often useful in polymorphic base classes, i.e., classes defining inter‐ faces through which derived class objects are manipulated.
// Polymorphic base classes normally have virtual destructors, because if they don’t, some operations (e.g., the use of delete or typeid on a derived class object through a base class pointer or refer‐ ence) yield undefined or misleading results.
// Unless a class inherits a destructor that’s already virtual, the only way to make a destructor virtual is to explicitly declare it that way.
// Often, the default implementation would be correct, and “=default” is a good way to express that.
// However, a user-declared destructor suppresses generation of the move operations, so if movability is to be supported, “=default” often finds a sec‐ ond application.
// Declaring the move operations disables the copy operations, so if copyability is also desired, one more round of “=default” does the job:

class DerivedC: public BaseC{
public:
    
    ~DerivedC();
    
    // At some point, analogous rules may be extended to the copy operations, because C++11 deprecates the automatic generation of copy operations for classes declaring copy operations or a destructor.
    // This means that if you have code that depends on the generation of copy operations in classes declaring a destructor or one of the copy operations, you should consider upgrading these classes to eliminate the dependence.
    // Provided the behavior of the compiler-generated functions is correct (i.e, if member‐ wise copying of the class’s non-static data members is what you want),
    // your job is easy, because C++11’s “=default” lets you say that explicitly:
    DerivedC(const DerivedC& ) = default;     // default copy ctor
    DerivedC& operator=(const DerivedC&) = default; // default copy assignment
    
};
