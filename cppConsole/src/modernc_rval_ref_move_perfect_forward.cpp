
/*
 
    Rvalue References, Move Semantics, and Perfect Forwarding
 
 
 When you first learn about them, move semantics and perfect forwarding seem pretty straightforward:
 • Move semantics makes it possible for compilers to replace expensive copying operations with less expensive moves.
    In the same way that copy constructors and copy assignment operators give you control over what it means to copy objects, move constructors and move assignment operators offer control over the semantics of moving.
    Move semantics also enables the creation of move-only types, such as std::unique_ptr, std::future, and std::thread.
 • Perfect forwarding makes it possible to write function templates that take arbitrary arguments and forward them to other functions such that the target func‐ tions receive exactly the same arguments as were passed to the forwarding functions.
 
 
 Rvalue references are the glue that ties these two rather disparate features together. They’re the underlying language mechanism that makes both move semantics and perfect forwarding possible.
 
 The world of move semantics, perfect forwarding, and rvalue references is more nuanced than it appears. std::move doesn’t move anything, for example, and perfect forwarding is imperfect.
 Move operations aren’t always cheaper than copying; when they are, they’re not always as cheap as you’d expect; and they’re not always called in a context where moving is valid. The construct “type&&” doesn’t always represent an rvalue reference.
 
 
 */
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <set>
//#include <type_trait>

using namespace std;

namespace move_forward_rvalue {

/*
    Item 23: Understand std::move and std::forward.
 
 Things to Remember
 • std::move performs an unconditional cast to an rvalue. In and of itself, it doesn’t move anything.
 • std::forward casts its argument to an rvalue only if that argument is bound to an rvalue.
 • Neither std::move nor std::forward do anything at runtime.
 
 1) std::move and std::forward are merely functions (actually function templates) that perform casts. std::move unconditionally casts its argument to an rvalue, while
 2) std::forward performs this cast only if a particular condition is fulfilled. That’s it. The explanation leads to a new set of questions, but, fundamentally, that’s the com‐ plete story.
 
 
 template<typename T> // in namespace std
 typename remove_reference<T>::type&&
 move(T&& param)
 {
     using ReturnType = typename remove_reference<T>::type&&;  // alias declaration;
     return static_cast<ReturnType>(param);
 }
 
 The “&&” part of the function’s return type implies that std::move returns an rvalue reference, but, as Item 28 explains, if the type T happens to be an lvalue reference, T&& would become an lvalue reference.
 To prevent this from happening, the type trait (see Item 9) std::remove_reference is applied to T, thus ensuring that “&&” is applied to a type that isn’t a reference.
 That guarantees that std::move truly returns an rvalue reference, and that’s important, because rvalue references returned from func‐ tions are rvalues. Thus, std::move casts its argument to an rvalue, and that’s all it does.
 
 std::move does nothing but cast its argument to an rvalue.
 
 Of course, rvalues are candidates for moving, so applying std::move to an object tells the compiler that the object is eligible to be moved from.
 That’s why std::move has the name it does: to make it easy to designate objects that may be moved from.
 
 In truth, rvalues are only usually candidates for moving.
 
 *** std::forward is a conditional cast: it casts to an rvalue only if its argument was initialized with an rvalue.
 
 
 Given that both std::move and std::forward boil down to casts, the only difference being that std::move always casts, while std::forward only sometimes does,
 
 you might ask whether we can dispense with std::move and just use std::forward everywhere.
 From a purely technical perspective, the answer is yes: std::forward can do it all. std::move isn’t necessary.
 Of course, neither function is really neces‐ sary, because we could write casts everywhere, but I hope we agree that that would be, well, yucky.
 
 */


class Annotation {
    
    std::string value;
    
public:
    
    // To avoid paying for a copy operation when copying text into a data member, you remain true to the advice of Item 41 and apply std::move to text, thus producing an rvalue:
    explicit Annotation(const std::string text) // param to be copied, pass by value
    : value(std::move(text)) //  "move" text into value; this code doesn't do what it seems to!
    {}
    // The only thing separating this code from a perfect real‐ ization of your vision is that text is not moved into value, it’s copied. Sure, text is cast to an rvalue by std::move,
    // but text is declared to be a const std::string, so before the cast, text is an lvalue const std::string, and the result of the cast is an rvalue const std::string, but throughout it all, the constness remains.
    
    /*
     
        class string { // std::string is actually a
        public: // typedef for std::basic_string<char>
        ...
          string(const string& rhs);    // copy ctor
          string(string&& rhs);         // move ctor， it doesn't allow const, because rhs is gonna be changed.
          ...
        };
        
        In the Annotation constructor’s member initialization list, the result of std::move(text) is an rvalue of type const std::string.
        That rvalue can’t be passed to std::string’s move constructor, because the move constructor takes an rvalue reference to a non-conststd::string.
        The rvalue can, however, be passed to the copy constructor, because an lvalue-reference-to-const is permitted to bind to a const rvalue.
        The member initialization therefore invokes the copy constructor in std::string, even though text has been cast to an rvalue! Such behavior is essential to maintaining const-correctness.
        Moving a value out of an object generally modifies the object, so the language should not permit const objects to be passed to functions (such as move constructors) that could modify them.
     
        *** std::Move, There are two lessons to be drawn from this example.
        1) First, don’t declare objects const if you want to be able to move from them. Move requests on const objects are silently transformed into copy operations.
        2) Second, std::move not only doesn’t actually move anything, it doesn’t even guarantee that the object it’s casting will be eligible to be moved.
        The only thing you know for sure about the result of applying std::move to an object is that it’s an rvalue.
     */
};

// The story for std::forward is similar to that for std::move, but whereas std::move unconditionally casts its argument to an rvalue, std::forward does it only under certain conditions.

// *** std::forward is a conditional cast. ***
class Widget{};

void process(const Widget&){
    std::cout << "lval process called" <<std::endl;
};

void process(Widget&& ) {
    std::cout << "rval process called" <<std::endl;
};

template <typename T>
void logAndProcess(T&& p){
    // Inside logAndProcess, the parameter param is passed to the function process. process is overloaded for lvalues and rvalues.
    // When we call logAndProcess with an lvalue, we naturally expect that lvalue to be forwarded to process as an lvalue, and
    // when we call logAndProcess with an rvalue, we expect the rvalue overload of pro cess to be invoked.
    process(std::forward<T>(p));
    
    // But param, like all function parameters, is an lvalue (Because inside func, p is rvalue reference, itself is left-value).
    // Every call to process inside logAndProcess will thus want to invoke the lvalue overload for process.
    // To prevent this, we need a mechanism for param to be cast to an rvalue if and only if the argument with which param was initialized—the argument passed to logAndProcess— was an rvalue.
    // This is precisely what std::forward does.
    // *** That’s why std::forward is a conditional cast: it casts to an rvalue only if its argument was initialized with an rvalue.
    
}


void test_move_forward() {
    
    Widget w;
    
    // But param, like all function parameters, is an lvalue.
    // Every call to process inside logAndProcess will thus want to invoke the lvalue overload for process.
    // To prevent this, we need a mechanism for param to be cast to an rvalue if and only if the argu‐ ment with which param was initialized—the argument passed to logAndProcess— was an rvalue.
    
    logAndProcess(w); // lval
    
    logAndProcess(std::move(w)); //rval
    
}



/*
        Item 24: Distinguish universal references from rvalue references.
 
 Things to Remember
 • If a function template parameter has type T&& for a deduced type T, or if an object is declared using auto&&, the parameter or object is a universal reference.
 • If the form of the type declaration isn’t precisely type&&, or if type deduction does not occur, type&& denotes an rvalue reference.
 • Universal references correspond to rvalue references if they’re initialized with rvalues. They correspond to lvalue references if they’re initialized with lvalues.
 
 Item 25 explains that universal references should almost always have std::forward applied to them,
 
 void f(Widget&& param);         // rvalue reference
 Widget&& var1 = Widget();       // rvalue reference
 
 auto&& var2 = var1;             // not rvalue reference, var2 is a universal reference
 
 template<typename T>
 void f(std::vector<T>&& param);     // rvalue reference
 
 template<typename T>
 void f(T&& param);                  // not rvalue reference    param is a *** universal reference ***


 In fact, “T&&” has two different meanings.
 One is rvalue reference, of course. Such references behave exactly the way you expect: they bind only to rvalues, and their pri‐ mary raison d’être is to identify objects that may be moved from.
 The other meaning for “T&&” is either rvalue reference or lvalue reference. Such references look like rvalue references in the source code (i.e., “T&&”), but they can behave as if they were lvalue references (i.e., “T&”).
 Their dual nature permits them to bind to rvalues (like rvalue references) as well as lvalues (like lvalue references).
 Furthermore, they can bind to const or non-const objects, to volatile or non-volatile objects, even to objects that are both const and volatile.
 They can bind to virtually any‐ thing. Such unprecedentedly flexible references deserve a name of their own. I call them universal references.
 
 Universal references arise in two contexts. The most common is function template parameters, such as this example from the sample code above:
*/

template<typename T>
void f(T&& param) {}; // not rvalue reference    param is a *** universal reference ***

template<typename T>
void f_vec(std::vector<T>&& param){}; // param is an rvalue reference, std::vector<T>&&

// Even the simple presence of a const qualifier is enough to disqualify a reference from being universal:
template<typename T>
void f_const(const T&& param); // param is an rvalue reference

/*
 
  template<class T, class Allocator = allocator<T>>  // from C++
    class vector {                                     // Standards
    public:
         void push_back(T&& x);     // always be rvalue reference,
         ...
        // push_back’s parameter certainly has the right form for a universal reference, but there’s no type deduction in this case.
        // That’s because push_back can’t exist without a particular vector instantiation for it to be part of, and the type of that instantiation fully determines the declaration for push_back.
        // Now you can see clearly that push_back employs no type deduction. This push_back for vector<T> (there are two—the function is overloaded) always declares a parame‐ ter of type rvalue-reference-to-T.
    };
 
    template <class... Args>
    void emplace_back(Args&&... args);   // In contrast, the conceptually similar emplace_back member function in std::vec tor does employ type deduction:
 
    // Here, the type parameter Args is independent of vector’s type parameter T, so Args must be deduced each time emplace_back is called.
    // (Okay, Args is really a parameter pack, not a type parameter, but for purposes of this discussion, we can treat it as if it were a type parameter.)
 
    // The fact that emplace_back’s type parameter is named Args, yet it’s still a universal reference, reinforces my earlier comment that it’s the form of a universal reference that must be “T&&”.
 
 
 */


void test_distinguish_universal_references() {
    
    Widget w;
    
    f(w); // lvalue passed to f; param's type is
          // Widget& (i.e., an lvalue reference)
    
    f(std::move(w)); // rvalue passed to f; param's type is
                     // Widget&& (i.e., an rvalue reference)
    // For a reference to be universal, type deduction is necessary, but it’s not sufficient.
    // The form of the reference declaration must also be correct, and that form is quite constrained. It must be precisely “T&&”.
    
    std::vector<int> v;
    
    // f_vec(v);  error! can't bind lvalue to rvalue reference
    
    // C++14
    auto timeFuncInvocation = [](auto&& func, auto&&... params) {
        return std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...);
        
        // func is a universal reference that can be bound to any callable object, lvalue or rvalue.
        // args is zero or more universal references (i.e., a universal ref‐ erence parameter pack) that can be bound to any number of objects of arbitrary types.
        // The result, thanks to auto universal references, is that timeFuncInvocation can time pretty much any function execution.
    };
    
}

/*
        Item 25: Use std::move on rvalue references, std::forward on universal references.
 
 Things to Remember
 • Apply std::move to rvalue references and std::forward to universal refer‐ ences the last time each is used.
 • Do the same thing for rvalue references and universal references being returned from functions that return by value.
 • Never apply std::move or std::forward to local objects if they would other‐ wise be eligible for the return value optimization.
 
 Rvalue references bind only to objects that are candidates for moving. If you have an rvalue reference parameter, you know that the object it’s bound to may be moved:
 
 using std::forward on rvalue references can be made to exhibit the proper behavior, but the source code is wordy, error-prone, and unidiomatic,
 so you should avoid using std::forward with rvalue references.
 Even worse is the idea of using std::move with universal references, because that can have the effect of unexpectedly modifying lvalues
 
 The most serious problem with overloading on lvalues and rvalues, however, isn’t the volume or idiomaticity of the source code, nor is it the code’s runtime performance.
 It’s the poor scalability of the design. Widget::setName takes only one parameter, so only two overloads are necessary, but for functions taking more parameters, each of which could be an lvalue or an rvalue,
 the number of overloads grows geometrically: n parameters necessitates 2n overloads. And that’s not the worst of it. Some functions —function templates, actually—take an unlimited number of parameters,
 each of which could be an lvalue or rvalue. The poster children for such functions are std::make_shared, and, as of C++14, std::make_unique (see Item 21). Check out the declarations of their most commonly used overloads:
 
 template<class T, class... Args>
 shared_ptr<T> make_shared(Args&&... args);      // from C++11
                                                    // Standard
 
 template<class T, class... Args>
 unique_ptr<T> make_unique(Args&&... args);      // from C++14
                                                    // Standard

 */

struct Impl {
    std::string name;
    int weight;
};

class Widget1 {
    
    std::string name;
    std::shared_ptr<Impl> pImpl;
public:
    Widget1() = default;
    
    Widget1(Widget1&& rhs) :
        name(std::move(rhs.name)),
        pImpl(std::move(rhs.pImpl))
    {}
    
    // A universal reference, on the other hand (see Item 24), might be bound to an object that’s eligible for moving.
    // Universal references should be cast to rvalues only if they were initialized with rvalues. Item 23 explains that this is precisely what std::for ward does:
    
    
    template <typename T>
    void SetName(T&& val) { name = std::forward<T>(val); } // val is universal reference
    
    // In short, 1) rvalue references should be unconditionally cast to rvalues (via std::move) when forwarding them to other functions, because they’re always bound to rvalues, and
    // 2) universal references should be conditionally cast to rvalues (via std::forward) when forwarding them, because they’re only sometimes bound to rvalues.
};

class Matrix {};

Matrix operator+(Matrix&& lhs, const Matrix& rhs) {
    // lhs += rhs;
    return std::move(lhs); // Assuming that the Matrix type supports move construction, which is more efficient than copy construction, using std::move in the return statement yields more efficient code.
    // If Matrix does not support moving, casting it to an rvalue won’t hurt, because the rvalue will simply be copied by Matrix’s copy constructor (see Item 23).
    // If Matrix is later revised to support moving, operator+ will automatically benefit the next time it is compiled.
    // That being the case, there’s nothing to be lost (and possibly much to be gained) by applying std::move to rvalue references being returned from functions that return by value.
    
    // return lhs; not best way, // the fact that lhs is an lvalue would force compilers to instead copy it into the return value location.
    // If the call to std::forward were omitted, frac would be unconditionally copied into reduceAndCopy’s return value.
}

class Fraction{};

template<typename T>
Fraction reduceAndCopy(T&& frac)
{
    //frac.reduce();
    return std::forward<T>(frac);
    // The situation is similar for universal references and std::forward. Consider a func‐ tion template reduceAndCopy that takes a possibly unreduced Fraction object,
    // reduces it, and then returns a copy of the reduced value. If the original object is an rvalue, its value should be moved into the return value (thus avoiding the expense of making a copy),
    // but if the original is an lvalue, an actual copy must be created.
}


Widget1 makeWidget1() { // "Copying" version of makeWidget
    
    Widget1 w;  // local variable
    
    return w;   // "copy" w into return value
    
    
/*
    *** RVO ***
 
    It was recognized long ago that the “copying” version of makeWidget can avoid the need to copy the local variable w by constructing it in the memory alloted for the function’s return value.
    This is known as the return value optimization (RVO), and it’s been expressly blessed by the C++ Standard for as long as there’s been one.

    this particular blessing says that compilers may elide the copying (or moving) of a local object2 in a function that returns by value if
     (1) the type of the local object is the same as that returned by the function and
     (2) the local object is what’s being returned.
     
     2 Eligible local objects include most local variables (such as w inside makeWidget) as well as temporary objects created as part of a return statement. Function parameters don’t qualify.
     Some people draw a distinction between application of the RVO to named and unnamed (i.e., temporary) local objects, limiting the term RVO to unnamed objects and calling its application to named objects the named return value optimization (NRVO).

    Both conditions are fulfilled here, and you can trust me when I tell you that for this code, every decent C++ compiler will employ the RVO to avoid copying w. That means that the “copying” version of makeWidget doesn’t, in fact, copy anything.
 */
    
    // return std::move(w); don't do this.
/*
    The moving version of makeWidget does just what its name says it does (assuming Widget offers a move constructor): it moves the contents of w into makeWidget’s return value location.
    But why don’t compilers use the RVO to eliminate the move, again constructing w in the memory alloted for the function’s return value? The answer is simple: they can’t. Condition
    (2) stipulates that the RVO may be performed only if what’s being returned is a local object, but that’s not what the moving version of makeWidget is doing. Look again at its return statement:
                
            return std::move(w);
    What’s being returned here isn’t the local object w, it’s a reference to w—the result of std::move(w).
    Returning a reference to a local object doesn’t satisfy the conditions required for the RVO, so compilers must move w into the function’s return value location.
    Developers trying to help their compilers optimize by applying std::move to a local variable that’s being returned are actually limiting the optimization options available to their compilers!
 
 
 
 But the RVO is an optimization. Compilers aren’t required to elide copy and move operations, even when they’re permitted to. Maybe you’re paranoid, and you worry that your compilers will punish you with copy operations, just because they can.
 Or perhaps you’re insightful enough to recognize that there are cases where the RVO is difficult for compilers to implement, e.g., when different control paths in a function return different local variables.
 (Compilers would have to generate code to construct the appropriate local variable in the memory allotted for the function’s return value, but how could compilers determine which local variable would be appropriate?)
 If so, you might be willing to pay the price of a move as insurance against the cost of a copy. That is, you might still think it’s reasonable to apply std::move to a local object you’re returning, simply because you’d rest easy knowing you’d never pay for a copy.
 
 In that case, applying std::move to a local object would still be a bad idea. The part of the Standard blessing the RVO goes on to say that if the conditions for the RVO are met, but compilers choose not to perform copy elision,
 the object being returned must be treated as an rvalue. In effect, the Standard requires that when the RVO is permitted, either copy elision takes place or std::move is implicitly applied to local objects being returned.
 
 This means that if you use std::move on a local object being returned from a func‐ tion that’s returning by value, you can’t help your compilers (they have to treat the local object as an rvalue if they don’t perform copy elision),
 but you can certainly hin‐ der them (by precluding the RVO). There are situations where applying std::move to a local variable can be a reasonable thing to do
 (i.e., when you’re passing it to a function and you know you won’t be using the variable any longer), but as part of a return statement that would otherwise qualify for the RVO or that returns a by- value parameter isn’t among them.
 */
    
 }

void test_move_on_rvalue_ref_forward_on_universal_ref() {}


/*
 
    Item 26: Avoid overloading on universal references.
 
 Things to Remember
 • Overloading on universal references almost always leads to the universal refer‐ ence overload being called more frequently than expected.
 • Perfect-forwarding constructors are especially problematic, because they’re typically better matches than copy constructors for non-const lvalues, and they can hijack derived class calls to base class copy and move constructors.
 
 because one of the overload-resolution rules in C++ is that in situations where a template instantiation and a non-template function (i.e., a “nor‐ mal” function) are equally good matches for a function call, the normal function is preferred.
 
 Per the normal overload resolution rules, an exact match beats a match with a promotion, so the universal reference overload is invoked.
 
 Functions taking universal references are the greediest functions in C++. They instantiate to create exact matches for almost any type of argument.
 (The few kinds of arguments where this isn’t the case are described in Item 30.) This is why combining overloading and universal references is almost always a bad idea:
                the universal refer‐ ence overload vacuums up far more argument types than the developer doing the overloading generally expects.
 
 I hope that by now I’ve convinced you that overloading on universal reference parameters is something you should avoid if at all possible.
 But if overloading on universal references is a bad idea, what do you do if you need a function that forwards most argument types, yet needs to treat some argument types in a special fashion? That egg can be unscrambled in a number of ways.
 So many, in fact, that I’ve devoted an entire Item to them. It’s Item 27. The next Item. Keep reading, you’ll bump right into it.
 
 */

std::multiset<std::string> names;

template <typename T>
void logAndAdd(T&& name) {
    // auto now = std::chrono::system_clock::now();
    // log(now, "logAndAdd")
    names.emplace(std::forward<T>(name));
    // names.emplace(name);
}

std::string nameFromIdx(int idx) {
    return "result";
}

void logAndAdd(int idx) // new overload
{
    // auto now = std::chrono::system_clock::now();
    // log(now, "logAndAdd");
    // names.emplace(nameFromIdx(idx));
}

// An easy way to topple into this pit is to write a perfect forwarding constructor.
// As was the case with logAndAdd, passing an integral type other than int (e.g., std::size_t, short, long, etc.) will call the universal reference constructor over‐
// load instead of the int overload, and that will lead to compilation failures. The prob‐ lem here is much worse, however, because there’s more overloading present in Person than meets the eye.
//

// Item 17 explains that under the appropriate conditions, C++ will generate both copy and move constructors, and this is true even if the class contains a templatized constructor
// that could be instantiated to produce the signa‐ ture of the copy or move constructor.


class Person {
    
    std::string name;
public:
    
    template<typename T>
    explicit Person(T&& n)          // perfect forwarding ctor;
    : name(std::forward<T>(n)){}    // initializes data member
    
    explicit Person(int index)      // int ctor
    :name(nameFromIdx(index)) {}
    
    // If the copy and move constructors for Person are thus generated, Person will effectively look like this:
    Person(const Person& ); // copy ctor
                          // (compiler-generated)

    Person(Person&& ); // move ctor
                      // (compiler-generated)
    
    
};

// The interaction among perfect-forwarding constructors and compiler-generated copy and move operations develops even more wrinkles when inheritance enters the picture.
// In particular, the conventional implementations of derived class copy and move operations behave quite surprisingly.

/*
class SpecialPerson: public Person {
public:
     SpecialPerson(const SpecialPerson& rhs)   // copy ctor; calls
        : Person(rhs) {}                    // base class
                                            // forwarding ctor!

      SpecialPerson(SpecialPerson&& rhs) :     // move ctor; calls
        Person(std::move(rhs)){}            // base class
                                            // forwarding ctor!
};*/

// As the comments indicate, the derived class copy and move constructors don’t call their base class’s copy and move constructors, they call the base class’s perfect-forwarding constructor!
// To understand why, note that the derived class functions are using arguments of type SpecialPerson to pass to their base class, then work through the template instantiation and overload-resolution consequences for the constructors in class Person.
// Ultimately, the code won’t compile, because there’s no std::string constructor taking a SpecialPerson.

void test_donot_overload_universal_referece() {
    
    std::string petName("Darla");  // as before
    
    logAndAdd(petName); // as before, copy
                        // lvalue into multiset
    
    logAndAdd(std::string("Persephone")); // move rvalue instead
                                         // of copying it
    
    logAndAdd("Patty Dog");   // create std::string
                              // in multiset instead
                              // of copying a temporary
                              // std::string
    
    short nameIndex = 2;
    
    // logAndAdd(nameIndex);  // error! no ctor of string, from short into string
    
    // There are two logAndAdd overloads. The one taking a universal reference can deduce T to be short, thus yielding an exact match. The overload with an int parameter can
    // match the short argument only with a promotion. Per the normal overload resolution rules, an exact match beats a match with a promotion, so the universal reference overload is invoked.
    
    // Within that overload, the parameter name is bound to the short that’s passed in. name is then std::forwarded to the emplace member function on names (a std::multiset<std::string>),
    // which, in turn, dutifully forwards it to the std::string constructor. There is no constructor for std::string that takes a short,
    // so the std::string constructor call inside the call to multiset::emplace inside the call to logAndAdd fails.
    // All because the universal reference overload was a better match for a short argument than an int.
    
    // but this doesn’t matter, because one of the overload-resolution rules in C++ is that in situations where a template instantiation and a non-template function
    // (i.e., a “nor‐ mal” function) are equally good matches for a function call, the normal function is preferred.
    // The copy constructor (a normal function) thereby trumps an instantiated template with the same signature.
}


/*
    Item 27: Familiarize yourself with alternatives to overloading on universal references.
 
 Things to Remember
 • Alternatives to the combination of universal references and overloading include the use of distinct function names, passing parameters by lvalue-reference-to-const, passing parameters by value, and using tag dispatch.
 • Constraining templates via std::enable_if permits the use of universal ref‐ erences and overloading together, but it controls the conditions under which compilers may use the universal reference overloads.
 • Universal reference parameters often have efficiency advantages, but they typ‐ ically have usability disadvantages.
 
 1) Abandon overloading
 
 2) Pass by const T&
    An alternative is to revert to C++98 and replace pass-by-universal-reference with pass-by-lvalue-reference-to-const.
 
 3) Pass by value
    An approach that often allows you to dial up performance without any increase in complexity is to replace pass-by-reference parameters with, counterintuitively, pass by value.
    class Person {
        public:
            explicit Person(std::string n):
            name(std::move(n)) {}
    }
 
 4) Use Tag dispatch
    Neither pass by lvalue-reference-to-const nor pass by value offers support for perfect forwarding. If the motivation for the use of a universal reference is perfect forwarding, we have to use a universal reference; there’s no other choice.
 
    A universal reference parameter generally provides an exact match for whatever’s passed in, but if the universal reference is part of a param‐ eter list containing other parameters that are not universal references,
    sufficiently poor matches on the non-universal reference parameters can knock an overload with a universal reference out of the running. That’s the basis behind the tag dispatch approach, and an example will make the foregoing description easier to understand.

    In this design, the types std::true_type and std::false_type are “tags” whose only purpose is to force overload resolution to go the way we want. Notice that we don’t even name those parameters. They serve no purpose at runtime,
    and in fact we hope that compilers will recognize that the tag parameters are unused and will opti‐ mize them out of the program’s execution image.
   (Some compilers do, at least some of the time.) The call to the overloaded implementation functions inside logAndAdd “dispatches” the work to the correct overload by causing the proper tag object to be created.
    Hence the name for this design: tag dispatch. It’s a standard building block of template metaprogramming, and the more you look at code inside contemporary C++ libraries, the more often you’ll encounter it.
 
  5) Constraining templates that take universal references
    A keystone of tag dispatch is the existence of a single (unoverloaded) function as the client API. This single function dispatches the work to be done to the implementation functions.
    Creating an unoverloaded dispatch function is usually easy, but the second problem case Item 26 considers, that of a perfect-forwarding constructor for the Person class (shown on page 178), is an exception.
    Compilers may generate copy and move constructors themselves, so even if you write only one constructor and use tag dispatch within it, some constructor calls may be handled by compiler-generated functions that bypass the tag dispatch system.
 
    In truth, the real problem is not that the compiler-generated functions sometimes bypass the tag dispatch design, it’s that they don’t always pass it by.
    
    You virtually always want the copy constructor for a class to handle requests to copy lvalues of that type, but, as Item 26 demonstrates, providing a constructor taking a universal refer‐ ence causes the universal reference constructor
    (rather than the copy constructor) to be called when copying non-const lvalues. That Item also explains that when a base class declares a perfect-forwarding constructor,
    that constructor will typically be called when derived classes implement their copy and move constructors in the con‐ ventional fashion, even though the correct behavior is for the base class’s copy and move constructors to be invoked.
    
    std::enable_if gives you a way to force compilers to behave as if a particular template didn’t exist. Such templates are said to be disabled. By default, all templates are enabled,
    but a template using std::enable_if is enabled only if the condition speci‐ fied by std::enable_if is satisfied.
 
    class Person1 {
    public:
        template <typename T, typename = typename std::enable_if<!std::is_same<Person1, typename std::decay<T>::type>::value>::type>
        explicit Person(T&& n);
    };
 
 5) Trade-offs
 
    The first three techniques considered in this Item—abandoning overloading, passing by const T&, and passing by value—specify a type for each parameter in the function(s) to be called.
    The last two techniques—tag dispatch and constraining template eligibility—use perfect forwarding, hence don’t specify types for the parameters. This fundamental decision—to specify a type or not—has consequences.
 
    As a rule, perfect forwarding is more efficient, because it avoids the creation of tem‐ porary objects solely for the purpose of conforming to the type of a parameter decla‐ ration.
    
    But perfect forwarding has drawbacks. One is that some kinds of arguments can’t be perfect-forwarded, even though they can be passed to functions taking specific types. Item 30 explores these perfect forwarding failure cases.
 
    A second issue is the comprehensibility of error messages when clients pass invalid arguments.
 
 */

template <typename T>
void logAndAddImpl(T&& name, std::false_type)
{
    // auto now = std::chrono::system_clock::now();
    // log(now, "logAndAdd");
    names.emplace(std::forward<T>(name));
}

void logAndAddImpl(int index, std::true_type) {
    logAndAdd(nameFromIdx(index));
}

class Person1 {
public:
    template<
        typename T,
        typename = typename std::enable_if<
                            !std::is_same<Person1,
                                        typename std::decay<T>::type
                                        >::value>::type>
    explicit Person1(T&& n);
    // Given the declaration above, constructing a Person from another Person— lvalue or rvalue, const or non-const, volatile or non-volatile—will never invoke the constructor taking a universal reference.
};

class SpecialPerson1 : public Person1 {
public:
    SpecialPerson1(SpecialPerson1&& rhs)
    : Person1(std::move(rhs))       // copy ctor, base class forwarding ctor!
    {}
    
    SpecialPerson1(const SpecialPerson1& rhs)
    : Person1(rhs)                  // move ctor, base class forwarding ctor!
    {}
};

class Person2 {
    std::string name;
public:
    template<
        typename T,
        typename = std::enable_if_t<
            !std::is_base_of<Person2, std::decay_t<T>>::value
            &&
            !std::is_integral<std::remove_reference_t<T>>::value> >
    explicit Person2(T&& n)
    : name(std::forward<T>(n)) // ctor for std::string and args convertible to std::strings
    {
        // assert that a std::string can be created from a T object
        static_assert(
            std::is_constructible<std::string, T>::value, "Parameter n can't be used to construct a std::string"
        );
    };
    
    explicit Person2(int idx)
    : name(nameFromIdx(idx))    // ctor for integral args
    {}
    
    //  It’s called std::is_base_of. std::is_base_of<T1, T2>::value is true if T2 is derived from T1. Types are con‐ sidered to be derived from themselves, so std::is_base_of<T, T>::value is true.
    // This is handy, because we want to revise our condition controlling Person’s perfect- forwarding constructor such that the constructor is enabled only if the type T, after stripping it of references and cv-qualifiers,
    // is neither Person nor a class derived from Person. Using std::is_base_of instead of std::is_same gives us what we need:
};

template <typename T>
void logAndAdd1(T&& name)
{
    logAndAddImpl(std::forward<T>(name), std::is_integral<typename std::remove_reference<T>::type>());
    
    // std::is_integral<T>() doesn't work.
    // For integral arguments that are rvalues, it’s also what it does. But, as Item 28 explains, if an lvalue argument is passed to the universal reference name, the type deduced for T will be an lvalue reference.
    // So if an lvalue of type int is passed to logAndAdd, T will be deduced to be int&. That’s not an integral type, because refer‐ ences aren’t integral types.
    // That means that std::is_integral<T> will be false for any lvalue argument, even if the argument really does represent an integral value.
    
    // Recognizing the problem is tantamount to solving it, because the ever-handy Stan‐ dard C++ Library has a type trait (see Item 9), std::remove_reference,
    // that does both what its name suggests and what we need: remove any reference qualifiers from a type. The proper way to write logAndAdd is therefore:
    
    // Conceptually, logAndAdd passes a boolean to logAndAddImpl indicating whether an integral type was passed to logAndAdd, but true and false are runtime values, and we need to use overload resolution—a compile-time phenomenon—to choose the correct logAndAddImpl overload.
    // That means we need a type that corresponds to true and a different type that corresponds to false. This need is common enough that the Standard Library provides what is required under the names std::true_type and std::false_type.
    // The argument passed to logAndAd dImpl by logAndAdd is an object of a type that inherits from std::true_type if T is integral and from std::false_type if T is not integral.
}


/*
 
    Item 28: Understand reference collapsing.
 
    Things to Remember
    • Reference collapsing occurs in four contexts: template instantiation, auto type generation, creation and use of typedefs and alias declarations, and decltype.
    • When compilers generate a reference to a reference in a reference collapsing context, the result becomes a single reference. If either of the original refer‐ ences is an lvalue reference, the result is an lvalue reference. Otherwise it’s an rvalue reference.
    • Universal references are rvalue references in contexts where type deduction distinguishes lvalues from rvalues and where reference collapsing occurs.
 
    Item 23 remarks that when an argument is passed to a template function, the type deduced for the template parameter encodes whether the argument is an lvalue or an rvalue.
    The answer is reference collapsing.
 
    There are two kinds of references (lvalue and rvalue), so there are four possible reference-reference combinations (lvalue to lvalue, lvalue to rvalue, rvalue to lvalue, and rvalue to rvalue).
    If a reference to a reference arises in a context where this is per‐ mitted (e.g., during template instantiation),
    the references collapse to a single refer‐ ence according to this rule:
    
    *** If either reference is an lvalue reference, the result is an lvalue reference. Otherwise (i.e., if both are rvalue references) the result is an rvalue reference ***.
 
    type deduced on univeral reference, reference collapsing.
    T& & => T&
    T& && => T&
    T& && +> T&
    T&& && => T&& (Only Right-Reference)
 
    Reference collapsing is a key part of what makes std::forward work. As explained in Item 25, std::forward is applied to universal reference parameters,
 
    template<typename T>
       T&& forward(typename  remove_reference<T>::type& param)
    {
        return static_cast<T&&>(param);
    }
 
    *** Suppose that the argument passed to f is an lvalue of type Widget. T will be deduced as Widget&, and the call to std::forward will instantiate as std::forward <Widget&>.

    Widget& && forward(typename remove_reference<Widget&>::type& param)
        { return static_cast<Widget& &&>(param); }
 
    The type trait std::remove_reference<Widget&>::type yields Widget (see
    Item 9), so std::forward becomes:
        
    Widget& && forward(Widget& param)
        { return static_cast<Widget& &&>(param); }
    
    Reference collapsing is also applied to the return type and the cast, and the result is the final version of std::forward for the call:
        
    Widget& forward(Widget& param) // still in
        { return static_cast<Widget&>(param); } // namespace std
 
    As you can see, when an lvalue argument is passed to the function template f, std::forward is instantiated to take and return an lvalue reference.
 
    As you can see, when an lvalue argument is passed to the function template f, std::forward is instantiated to take and return an lvalue reference.
    The cast inside std::forward does nothing, because param’s type is already Widget&, so casting it to Widget& has no effect. An lvalue argument passed to std::forward will thus return an lvalue reference.
    By definition, lvalue references are lvalues, so passing an lvalue to std::forward causes an lvalue to be returned, just like it’s supposed to.
 
 
    *** Now suppose that the argument passed to f is an rvalue of type Widget. In this case, the deduced type for f’s type parameter T will simply be Widget.
 
    Widget&& forward(typename remove_reference<Widget>::type& param)
            { return static_cast<Widget&&>(param); }
    
    Applying std::remove_reference to the non-reference type Widget yields the
    same type it started with (Widget), so std::forward becomes this:
    
    Widget&& forward(Widget& param)
            { return static_cast<Widget&&>(param); }
    
    There are no references to references here, so there’s no reference collapsing, and this is the final instantiated version of std::forward for the call.
 
    Rvalue references returned from functions are defined to be rvalues, so in this case, std::forward will turn f’s parameter fParam (an lvalue) into an rvalue.
    The end result is that an rvalue argument passed to f will be forwarded to someFunc as an rvalue, which is precisely what is supposed to happen.
 
 
    In C++14, the existence of std::remove_reference_t makes it possible to imple‐ ment std::forward a bit more concisely:
 
        template<typename T>                                    // C++14; still in
            T&& forward(remove_reference_t<T>& param) {         // namespace std
                return static_cast<T&&>(param);
            }
    
    Reference collapsing occurs in four contexts. The first and most common is template instantiation. The second is type generation for auto variables. The details are essen‐
    tially the same as for templates, because type deduction for auto variables is essen‐ tially the same as type deduction for templates (see Item 2).
    
    *** We’re now in a position to truly understand the universal references introduced in Item 24. A universal reference isn’t a new kind of reference,
    it’s actually an rvalue ref‐ erence in a context where two conditions are satisfied:
        
        • Type deduction distinguishes lvalues from rvalues. Lvalues of type T are deduced to have type T&, while rvalues of type T yield T as their deduced type.
        • Reference collapsing occurs.
    
    I said there were four such contexts, but we’ve discussed only two: "template instantiation" and "auto type generation".
    The third is the generation and use of "typedefs" and "alias declarations" (see Item 9).
    If, during creation or evaluation of a typedef, references to references arise, reference collapsing intervenes to eliminate them. For example, suppose we have a Widget class template with an embedded typedef for an rvalue reference type,
 
       template<typename T>
       class Widget {
        public:
            typedef T&& RvalueRefToT;
            ...
        };
    and suppose we instantiate Widget with an lvalue reference type:
        Widget<int&> w;
    
    Substituting int& for T in the Widget template gives us the following typedef:
        typedef int& && RvalueRefToT;
    
    Reference collapsing reduces it to this,
        typedef int& RvalueRefToT;
    
    which makes clear that the name we chose for the typedef is perhaps not as descrip‐ tive as we’d hoped: RvalueRefToT is a typedef for an lvalue reference when Widget is instantiated with an lvalue reference type.
 
 
    
 */



/*
 
        Item 29: Assume that move operations are not present, not cheap, and not used.
 
    Things to Remember
    • Assume that move operations are not present, not cheap, and not used.
    • In code with known types or support for move semantics, there is no need for assumptions.
 
    Move semantics is arguably the premier feature of C++11. “Moving containers is now as cheap as copying pointers!” you’re likely to hear, and “Copying temporary objects is now so efficient, coding to avoid it is tantamount to premature optimization!” Such sentiments are easy to understand.
    Move semantics is truly an important feature. It doesn’t just allow compilers to replace expensive copy operations with comparatively cheap moves, it actually requires that they do so (when the proper conditions are ful‐ filled).
    Take your C++98 code base, recompile with a C++11-conformant compiler and Standard Library, and—shazam!—your software runs faster.
 
    So std::array certainly offers move support. Yet both moving and copying a std::array have linear-time computational com‐ plexity, because each element in the container must be copied or moved.
    This is far from the “moving a container is now as cheap as assigning a couple of pointers” claim that one sometimes hears.
 
    On the other hand, std::string offers constant-time moves and linear-time copies. That makes it sound like moving is faster than copying, but that may not be the case.
    Many string implementations employ the small string optimization (SSO). With the SSO, “small” strings (e.g., those with a capacity of no more than 15 characters) are stored in a buffer within the std::string object; no heap-allocated storage is used.
 
     Moving small strings using an SSO-based implementation is no faster than copying them, because the copy-only-a-pointer trick that generally underlies the performance advantage of moves over copies isn’t applicable.
     The motivation for the SSO is extensive evidence that short strings are the norm for many applications. Using an internal buffer to store the contents of such strings eliminates the need to dynamically allocate memory for them,
     and that’s typically an effi‐ ciency win. An implication of the win, however, is that moves are no faster than copies, though one could just as well take a glass-half-full approach and say that for such strings, copying is no slower than moving.
 
    Even for types supporting speedy move operations, some seemingly sure-fire move situations can end up making copies.
    
    There are thus several scenarios in which C++11’s move semantics do you no good:
        • No move operations: The object to be moved from fails to offer move opera‐ tions. The move request therefore becomes a copy request.
        • Move not faster: The object to be moved from has move operations that are no faster than its copy operations.
        • Move not usable: The context in which the moving would take place requires a move operation that emits no exceptions, but that operation isn’t declared noex cept.
                    It’s worth mentioning, too, another scenario where move semantics offers no effi‐ ciency gain:
        • Source object is lvalue: With very few exceptions (see e.g., Item 25) only rvalues may be used as the source of a move operation.
 
 */


/*
        Item 30: Familiarize yourself with perfect forwarding failure cases.
    
    Things to Remember
    • Perfect forwarding fails when template type deduction fails or when it deduces the wrong type.
    • The kinds of arguments that lead to perfect forwarding failure are braced ini‐ tializers, null pointers expressed as 0 or NULL,
            declaration-only integral const static data members, template and overloaded function names, and bitfields.
 
    
    Perfect forwarding means we don’t just forward objects, we also forward their salient characteristics: their types, whether they’re lvalues or rvalues, and whether they’re const or volatile.
    In conjunction with the observation that we’ll be dealing with reference parameters, this implies that we’ll be using universal references (see Item 24),
    because only universal reference parameters encode information about the lvalueness and rvalueness of the arguments that are passed to them.
 
 
    1) Braced initializers
 
    2) 0 or NULL as null pointers

    3) Declaration-only integral static const data members
 
    4) Overloaded function names and template names
 
    5) Bitfields
 
    6) Upshot
 
 */

void f(const std::vector<int>& v) {
    
}

template<typename... Ts>
void fwd(Ts&&... params) {
    f(std::forward<Ts>(params)...);
}

// bitfield is used as a function argument
struct IPv4Header {
    std::uint32_t version:4,
                 IHL:4,
                 DSCP:6,
                 ECN:2,
                 totalLength:16;
};

void test_perfect_forwarding_failure_cases() {
    
    f({1, 2, 3});
    
    auto il = {1, 2, 3};       // il's type deduced to be
                              // std::initializer_list<int>
    
    fwd(il);                    // fine, perfect-forwards il to f
    
    // fwd({1, 2, 3});  // error! doesn't compile
    /*
    // All such failure cases have the same cause. In a direct call to f (such as f({ 1, 2, 3})), compilers see the arguments passed at the call site, and they see the types of the parameters declared by f.
    // They compare the arguments at the call site to the parame‐ ter declarations to see if they’re compatible, and, if necessary, they perform implicit conversions to make the call succeed.
    // In the example above, they generate a tempo‐ rary std::vector<int> object from { 1, 2, 3 } so that f’s parameter v has a std::vector<int> object to bind to.
    
    
    When calling f indirectly through the forwarding function template fwd, compilers no longer compare the arguments passed at fwd’s call site to the parameter declara‐ tions in f.
    Instead, they deduce the types of the arguments being passed to fwd, and
    they compare the deduced types to f’s parameter declarations. Perfect forwarding fails when either of the following occurs:
    
    • Compilers are unable to deduce a type for one or more of fwd’s parameters. In this case, the code fails to compile.
    • Compilers deduce the “wrong” type for one or more of fwd’s parameters. Here, “wrong” could mean that fwd’s instantiation won’t compile with the types that were deduced,
        but it could also mean that the call to f using fwd’s deduced types behaves differently from a direct call to f with the arguments that were passed to fwd.
        One source of such divergent behavior would be if f were an overloaded function name, and, due to “incorrect” type deduction, the overload of f called inside fwd were different from the overload that would be invoked if f were called directly.

     In the “fwd({1,2,3})” call above, the problem is that passing a braced initializer to a function template parameter that’s not declared to be a std::initial izer_list is decreed to be, as the Standard puts it, a “non-deduced context.”
     In plain English, that means that compilers are forbidden from deducing a type for the expression { 1, 2, 3 } in the call to fwd, because fwd’s parameter isn’t declared to be a std::initializer_list.
     Being prevented from deducing a type for fwd’s parame‐ ter, compilers must understandably reject the call.

     
     
     */

    // Bitfields
    
    /*
     
        void f(std::size_t sz); // function to call
        IPv4Header h;
        ...
        f(h.totalLength); // fine
        Trying to forward h.totalLength to f via fwd, however, is a different story: fwd(h.totalLength); // error!

        The problem is that fwd’s parameter is a reference, and h.totalLength is a non- const bitfield. That may not sound so bad, but the C++ Standard condemns the
        combination in unusually clear prose: “A non-const reference shall not be bound to a bit-field.” There’s an excellent reason for the prohibition.
        Bitfields may consist of arbitrary parts of machine words (e.g., bits 3-5 of a 32-bit int), but there’s no way to directly address such things.
        I mentioned earlier that references and pointers are the same thing at the hardware level, and just as there’s no way to create a pointer to arbitrary bits (C++ dictates that the smallest thing you can point to is a char),
        there’s no way to bind a reference to arbitrary bits, either.
     
     
        Working around the impossibility of perfect-forwarding a bitfield is easy, once you realize that any function that accepts a bitfield as an argument will receive a copy of the bitfield’s value. After all, no function can bind a reference to a bitfield,
      nor can any function accept pointers to bitfields, because pointers to bitfields don’t exist. The only kinds of parameters to which a bitfield can be passed are by-value parameters and, interestingly, references-to-const. In the case of by-value parameters, the called
     function obviously receives a copy of the value in the bitfield, and it turns out that in the case of a reference-to-const parameter, the Standard requires that the reference actually bind to a copy of the bitfield’s value that’s stored in an object of some stan‐
     dard integral type (e.g., int). References-to-const don’t bind to bitfields, they bind to “normal” objects into which the values of the bitfields have been copied.
        The key to passing a bitfield into a perfect-forwarding function, then, is to take advantage of the fact that the forwarded-to function will always receive a copy of the bitfield’s value. You can thus make a copy yourself and call the forwarding function with the copy. In the case of our example with IPv4Header, this code would do the trick:
        
        // copy bitfield value; see Item 6 for info on init. form
                auto length = static_cast<std::uint16_t>(h.totalLength);
                fwd(length);        // forward the copy
     
        *** Upshot
        In most cases, perfect forwarding works exactly as advertised. You rarely have to think about it. But when it doesn’t work—when reasonable-looking code fails to compile or, worse, compiles, but doesn’t behave the way you anticipate—it’s impor‐ tant to know about perfect forwarding’s imperfections. Equally important is knowing how to work around them. In most cases, this is straightforward.
     
     */

}

}
