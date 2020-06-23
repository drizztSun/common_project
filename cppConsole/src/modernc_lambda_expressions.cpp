
#include <stdio.h>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

namespace lambda_expressions {


/*
    But lambdas are such a convenient way to create function objects, the impact on day- to-day C++ software development is enormous.
    Without lambdas, the STL “_if” algorithms (e.g., std::find_if, std::remove_if, std::count_if, etc.) tend to be employed with only the most trivial predicates, but when lambdas are available, use of these algorithms with nontrivial conditions blossoms.
 
    The same is true of algorithms that can be customized with comparison functions (e.g., std::sort, std::nth_element, std::lower_bound, etc.).
    Outside the STL, lambdas make it possible to quickly create custom deleters for std::unique_ptr and std::shared_ptr (see Items 18 and 19), and they make the specification of predicates for condition variables in the threading API equally straightforward (see Item 39).
    Beyond the Standard Library, lambdas facilitate the on-the-fly specification of callback functions, interface adaption functions, and context-specific functions for one-off calls. Lambdas really make C++ a more pleasant programming language.
   
 
    The vocabulary associated with lambdas can be confusing. Here’s a brief refresher:
 
    • A lambda expression is just that: an expression. It’s part of the source code. In
            std::find_if(container.begin(), container.end(),
                                    [](int val) { return 0 < val && val < 10; });
        the highlighted expression is the lambda.
 
    • A closure is the runtime object created by a lambda. Depending on the capture mode, closures hold copies of or references to the captured data. In the call to
        std::find_if above, the closure is the object that’s passed at runtime as the third argument to std::find_if.
    
    • A closure class is a class from which a closure is instantiated. Each lambda causes compilers to generate a unique closure class.
        The statements inside a lambda become executable instructions in the member functions of its closure class.
 
 
    A lambda is often used to create a closure that’s used only as an argument to a func‐ tion. That’s the case in the call to std::find_if above.
    However, closures may gen‐ erally be copied, so it’s usually possible to have multiple closures of a closure type corresponding to a single lambda. For example, in the following code,
    {
        int x;      // x is local variable
 
        auto c1 =                                   // c1 is copy of the
            [x](int y) { return x * y > 55; };      // closure produced
                                                    // by the lambda
 
        auto c2 = c1;                               // c2 is copy of c1
        
        auto c3 = c2;                               // c3 is copy of c2
    }

    c1, c2, and c3 are all copies of the closure produced by the lambda.
    
    Informally, it’s perfectly acceptable to blur the lines between lambdas, closures, and closure classes.
    But in the Items that follow, it’s often important to distinguish what exists during compilation (lambdas and closure classes), what exists at runtime (clo‐ sures), and how they relate to one another.
*/

/*
    Item 31: Avoid default capture modes.
 
     Things to Remember
     • Default by-reference capture can lead to dangling references.
     • Default by-value capture is susceptible to dangling pointers (especially this), and it misleadingly suggests that lambdas are self-contained.
 
    *** If you know that a closure will be used immediately (e.g., by being passed to an STL algorithm) and won’t be copied,
            there is no risk that references it holds will outlive the local variables and parameters in the environment where its lambda is created. ***
    *** Captures apply only to non-static local variables (including parameters, not incluing class member variable) visible in the scope where the lambda is created.
 
    There are two default capture modes in C++11: by-reference and by-value.
    Default by-reference capture can lead to dangling references.
    Default by-value capture lures you into thinking you’re immune to that problem (you’re not), and it lulls you into thinking your closures are self-contained (they may not be).
 
    A by-reference capture causes a closure to contain a reference to a local variable or to a parameter that’s available in the scope where the lambda is defined.
    If the lifetime of a closure created from that lambda exceeds the lifetime of the local variable or parameter, the reference in the closure will dangle.
*/

template <typename C>
void WorkWithContainer(const C& container)
{
    auto calc1 = 1;
    auto calc2 = 2;
    auto divisor = calc1 / calc2;
    
    using ContElem = typename C::value_type;
    using std::begin;
    using std::end;
    
    if (std::all_of(
            begin(container), end(container),
                    [&](const ContElem& val) { return val % divisor == 0;} )) {
        std::cout << "all_of true" << std::endl;
    };
    
    // If you know that a closure will be used immediately (e.g., by being passed to an STL algorithm) and won’t be copied,
    // there is no risk that references it holds will outlive the local variables and parameters in the environment where its lambda is created.
    // In that case, you might argue, there’s no risk of dangling references, hence no reason to avoid a default by-reference capture mode.
    
    // It’s true, this is safe, but its safety is somewhat precarious. If the lambda were found to be useful in other contexts
    // (e.g., as a function to be added to the filters con‐ tainer) and was copy-and-pasted into a context where its closure could outlive divisor,
    // you’d be back in dangle-city, and there’d be nothing in the capture clause to specifically remind you to perform lifetime analysis on divisor.
}


using FilterContainer = std::vector<std::function<bool(int)>>;

FilterContainer filters;


class Widget{
    
    int divisor;
    
public:
    
    void addFilter() const {
        
        // filters.emplace_back([](int value) { return value % divisor == 0;});    // error 'this' cann't be capture by default;
        // Captures apply only to non-static local variables (including parameters) visible in the scope where the lambda is created.
        // divisor is not a local variable, it’s a data member of the Widget class. It can’t be captured. Yet if the default capture mode is eliminated, the code won’t compile:
        
        // filters.emplace_back([divisor](int value) { return value % divisor == 0;}); // error! no local divisor to capture
        // Furthermore, if an attempt is made to explicitly capture divisor (either by value or by reference—it doesn’t matter), the capture won’t compile,
        // because divisor isn’t a local variable or a parameter
        
        // The explanation hinges on the implicit use of a raw pointer: this. Every non-static member function has a this pointer,
        // and you use that pointer every time you mention a data member of the class.
        filters.emplace_back([=](int value) { return value % divisor == 0;});
        
        // what’s being captured is the Widget’s this pointer, not divisor. Compilers treat the code as if it had been written as follows:
        auto curObj = this;
        filters.emplace_back([curObj] (int value){ return value % curObj->divisor == 0;});
        
        // This particular problem can be solved by making a local copy of the data member you want to capture and then capturing the copy:
        auto divisorCopy = divisor;
        filters.emplace_back([divisorCopy](int val) { return val % divisorCopy == 9; });
        
        // To be honest, if you take this approach, default by-value capture will work, too,
        filters.emplace_back([=](int val) { return val % divisorCopy == 0; });
        
        // In C++14, a better way to capture a data member is to use generalized lambda cap‐ ture (see Item 32):
        filters.emplace_back( // C++14:
            [divisor = divisor](int value) // copy divisor to closure
                { return value % divisor == 0; } // use the copy
        );
        
        // There’s no such thing as a default capture mode for a generalized lambda capture, however, so even in C++14, the advice of this Item—to avoid default capture modes —stands.
        // An additional drawback to default by-value captures is that they can suggest that the corresponding closures are self-contained and insulated from changes to data outside

        // the closures. In general, that’s not true, because lambdas may be dependent not just on local variables and parameters (which may be captured), but also on objects with static storage duration.
        // Such objects are defined at global or namespace scope or are declared static inside classes, functions, or files.
        // These objects can be used inside lambdas, but they can’t be captured. Yet specification of a default by-value capture mode can lend the impression that they are.
        
        
    };
    
    bool isValidated() const;
    bool isProcessed() const;
    bool isArchived() const;
};

void test_lambda_expressions() {
    

    
    filters.emplace_back( [](int value) { return value % 5 == 0; });
    
    auto calc1 = 1;
    auto calc2 = 2;
    auto divisor = calc1 / calc2;
    
    filters.emplace_back([&](int value) { return value % divisor == 0; }); // danger! ref to divisor will dangle
    
    filters.emplace_back( [&divisor](int value) { return value % divisor == 0; } ); // danger! ref to divisor will still dangle!
    
    // This code is a problem waiting to happen. The lambda refers to the local variable divisor, but that variable ceases to exist when addDivisorFilter returns.
    // That’s immediately after filters.emplace_back returns, so the function that’s added to filters is essentially dead on arrival.
    // Using that filter yields undefined behavior from virtually the moment it’s created.
    
    // but with an explicit capture, it’s easier to see that the viability of the lambda is depen‐ dent on divisor’s lifetime.
    // Also, writing out the name, “divisor,” reminds us to ensure that divisor lives at least as long as the lambda’s closures.
    // That’s a more spe‐ cific memory jog than the general “make sure nothing dangles” admonition that “[&]” conveys.
    
    
    filters.emplace_back([=](int value) { return value % divisor == 0; }); // One way to solve our problem with divisor would be a default by-value capture mode.
    // This suffices for this example, but, in general, default by-value capture isn’t the anti- dangling elixir you might imagine.
    // The problem is that if you capture a pointer by value, you copy the pointer into the closures arising from the lambda,
    // but you don’t prevent code outside the lambda from deleteing the pointer and causing your copies to dangle.
    
    // “That could never happen!” you protest. “Having read Chapter 4, I worship at the house of smart pointers. Only loser C++98 programmers use raw pointers and delete.”
    // That may be true, but it’s irrelevant because you do, in fact, use raw point‐ ers, and they can, in fact, be deleted out from under you.
    // It’s just that in your modern C++ programming style, there’s often little sign of it in the source code.
    
    
}

/*
 
    Item 32: Use init capture to move objects into closures.
 
     Things to Remember
     • Use C++14’s init capture to move objects into closures.
     • In C++11, emulate init capture via hand-written classes or std::bind.
 
    Sometimes neither by-value capture nor by-reference capture is what you want. If you have a move-only object (e.g., a std::unique_ptr or a std::future) that you
    want to get into a closure, C++11 offers no way to do it. If you have an object that’s expensive to copy but cheap to move (e.g., most containers in the Standard Library),
    and you’d like to get that object into a closure, you’d much rather move it than copy it. Again, however, C++11 gives you no way to accomplish that.
 
    But that’s C++11. C++14 is a different story. It offers direct support for moving objects into closures. If your compilers are C++14-compliant, rejoice and read on.
    If you’re still working with C++11 compilers, you should rejoice and read on, too, because there are ways to approximate move capture in C++11.
 
    The new capability is called init capture. It can do virtually everything the C++11 capture forms can do, plus more. The one thing you can’t express with an init capture is a default capture mode,
    but Item 31 explains that you should stay away from those, anyway.
    (For situations covered by C++11 captures, init capture’s syntax is a bit wordier, so in cases where a C++11 capture gets the job done, it’s perfectly reasonable to use it.)
    
    Using an init capture makes it possible for you to specify
    1. the name of a data member in the closure class generated from the lambda and
    2. an expression initializing that data member.
 
    Remember that a lambda expression is simply a way to cause a class to be generated and an object of that type to be created. There is nothing you can do with a lambda that you can’t do by hand.
 
    because C++11 no init capture support
    If you want to stick with lambdas (and given their convenience, you probably do), move capture can be emulated in C++11 by
    1. moving the object to be captured into a function object produced by std::bind and
    2. giving the lambda a reference to the “captured” object.
 
    By default, the operator() member function inside the closure class generated from a lambda is const. That has the effect of rendering all data members in the closure const within the body of the lambda.
 
    If this is your first exposure to std::bind, you may need to consult your favorite C++11 reference before all the details of the foregoing discussion fall into place. Even if that’s the case, these fundamental points should be clear:
    • It’s not possible to move-construct an object into a C++11 closure, but it is possi‐ ble to move-construct an object into a C++11 bind object.
    • Emulating move-capture in C++11 consists of move-constructing an object into a bind object, then passing the move-constructed object to the lambda by refer‐ ence.
    • Because the lifetime of the bind object is the same as that of the closure, it’s pos‐ sible to treat objects in the bind object as if they were in the closure.
 */

void test_init_capture() {
    
    auto pw = std::make_unique<Widget>();
    
    
    auto func = [pw = std::move(pw)]() {
        return pw->isValidated() && pw->isArchived();
    };
    
    // The highlighted text comprises the init capture. To the left of the “=” is the name of the data member in the closure class you’re specifying, and to the right is the initializing expression.
    // Interestingly, the scope on the left of the “=” is different from the scope on the right. The scope on the left is that of the closure class. The scope on the right is the same as where the lambda is being defined.
    // In the example above, the name pw on the left of the “=” refers to a data member in the closure class, while the name pw on the right refers to the object declared above the lambda, i.e.,
    // the variable initialized by the call to std::make_unique.
    // So “pw = std::move(pw)” means “create a data member pw in the closure, and initialize that data member with the result of applying std::move to the local variable pw.”
    
    // As usual, code in the body of the lambda is in the scope of the closure class, so uses of pw there refer to the closure class data member.
    
    //
    auto func1 = [pw = std::make_unique<Widget>()] {
        return pw->isValidated() && pw->isArchived();
    };
    
    // This should make clear that the C++14 notion of “capture” is considerably general‐ ized from C++11, because in C++11, it’s not possible to capture the result of an expression.
    // As a result, another name for init capture is "generalized lambda capture".
    
    {
        // Suppose you’d like to create a local std::vector, put an appropriate set of values into it, then move it into a closure. In C++14, this is easy:
        std::vector<double> data;
        
        auto func = [data = std::move(data)]() // C++14 init capture, object to be moved into closure
        {  return; };
        
        // C++11 move simulate init capture
        // the type of object you want to move (std::vector<double>), the name of that object (data), and the initializing expres‐ sion for the init capture (std::move(data)).
        // The C++11 equivalent is as follows, where I’ve highlighted the same key things:
    
        auto func1 = std::bind(                             // C++11 emulation
                    [](const std::vector<double>& data)     //
                        {},
                     std::move(data));
        
        // Like lambda expressions, std::bind produces function objects. I call function objects returned by std::bind bind objects.
        // The first argument to std::bind is a callable object. Subsequent arguments represent values to be passed to that object.
        
        // A bind object contains copies of all the arguments passed to std::bind. For each lvalue argument, the corresponding object in the bind object is copy constructed. For each rvalue, it’s move constructed.
        // This move construction is the crux of move capture emulation, because mov‐ ing an rvalue into a bind object is how we work around the inability to move an rvalue into a C++11 closure.
        
        // When a bind object is “called” (i.e., its function call operator is invoked) the argu‐ ments it stores are passed to the callable object originally passed to std::bind.
        // In this example, that means that when func (the bind object) is called, the move- constructed copy of data inside func is passed as an argument to the lambda that was passed to std::bind.
        
        // This lambda is the same as the lambda we’d use in C++14, except a parameter, data, has been added to correspond to our pseudo-move-captured object.
        // This parameter is an lvalue reference to the copy of data in the bind object. (It’s not an rvalue reference,
        // because although the expression used to initialize the copy of data (“std::move(data)”) is an rvalue, the copy of data itself is an lvalue.)
        // Uses of data inside the lambda will thus operate on the move-constructed copy of data inside the bind object.
        
        // The move-constructed copy of data inside the bind object is not const, however, so to prevent that copy of data from being modified inside the lambda, the lambda’s parameter is declared reference-to-const.
        // If the lambda were declared mutable, operator() in its closure class would not be declared const, and it would be appropriate to omit const in the lambda’s parame‐ ter declaration:
         auto func2 =
             std::bind(                                             // C++11 emulation
                [](std::vector<double>& data) mutable               // of init capture
                       { /* uses of data */ },                         // for mutable lambda
            std::move(data)
        );
    }

    {
        // As a second example of using std::bind to emulate move capture, here’s the C++14 code we saw earlier to create a std::unique_ptr in a closure:
        auto func = [pw = std::make_unique<Widget>()] {
            return pw->isValidated() && pw->isArchived(); };
        
        // And here’s the C++11 emulation:
        auto func1 = std::bind(
                              [](const std::unique_ptr<Widget>& pw)
                                { return pw->isValidated() && pw->isArchived(); },
                            std::make_unique<Widget>());

    }
}

/*
        Item 33: Use decltype on auto&& parameters to std::forward them.
 
                Things to Remember
        • Use decltype on auto&& parameters to std::forward them.
        
    One of the most exciting features of C++14 is "generic lambdas" —lambdas that use auto in their parameter specifications.
    The implementation of this feature is straight‐forward: operator() in the lambda’s closure class is a template.
 
 

    auto f = [](auto x){ return func(normalize(x)); };
    // the closure class’s function call operator looks like this:

    class SomeCompilerGeneratedClassName {
    public:
         template<typename T>
         auto operator()(T x) const
         { return func(normalize(x)); }
 
    *** If normalize treats lvalues differently from rvalues, this lambda isn’t written properly, because it always passes an lvalue (the parameter x) to normalize,
        even if the argument that was passed to the lambda was an rvalue.
        
        The correct way to write the lambda is to have it perfect-forward x to normalize.
    ***
 
 
    Item 28 explains that
    if an lvalue argument is passed to a universal reference parameter, the type of that parameter becomes an lvalue reference.
    If an rvalue is passed, the parameter becomes an rvalue reference.
    
    This means that in our lambda, we can determine whether the argument passed was an lvalue or an rvalue by inspecting the type of the parameter x. decltype gives us a way to do that (see Item 3).
    If an lvalue was passed in, decltype(x) will produce a type that’s an lvalue reference.
    If an rvalue was passed, decltype(x) will produce an rvalue reference type.
    
    when calling std::forward, convention dictates that the type argument be an lvalue reference to indicate an lvalue and a non-reference to indicate an rvalue.
 
    But look at the sample C++14 implementation for std::forward from Item 28:
    
    template<typename T> // in namespace
        T&& forward(remove_reference_t<T>& param) // std
        {
            return static_cast<T&&>(param);
         }
 
    *** That means that instanti‐ ating std::forward with an rvalue reference type yields the same result as instantiat‐ ing it with a non-reference type.
 
    ***
     auto f =
            [](auto&&... params) {
                return
                func(normalize(std::forward<decltype(params)>(params)...));
    };
     
*/

void test_decltype_auto_param_to_forward() {
    
    // *** So for both lvalues and rvalues, passing decltype(x) to std::forward gives us the result we want. Our perfect- forwarding lambda can therefore be written like this:
    
    auto f = [](auto&& x) {
        return func(normalize(std::forward<decltype(x)>(x)));
    };
    // If normalize treats lvalues differently from rvalues, this lambda isn’t written properly, because it always passes an lvalue (the parameter x) to normalize, even if the argument that was passed to the lambda was an rvalue.
    
    // In our lambda, if x is bound to an lvalue, decltype(x) will yield an lvalue reference. That conforms to convention.
    // However, if x is bound to an rvalue, decltype(x) will yield an rvalue reference instead of the customary non- reference.
    
    // That’s wonderful news, because decltype(x) yields an rvalue reference type when an rvalue is passed as an argument to our lambda’s parameter x.
    // We established above that when an lvalue is passed to our lambda, decltype(x) yields the custom‐ ary type to pass to std::forward, and now we realize that for rvalues, decltype(x) yields a type to pass to std::forward that’s not conventional,
    // but that nevertheless yields the same outcome as the conventional type.
}

/*
 
        Item 34: Prefer lambdas to std::bind.
 
                Things to Remember
        • Lambdas are more readable, more expressive, and may be more efficient than using std::bind.
        • In C++11 only, std::bind may be useful for implementing move capture or for binding objects with templatized function call operators.
 
    Compared to lambdas, then, code using std::bind is less readable, less expressive, and possibly less efficient.
    In C++14, there are no reasonable use cases for std::bind. In C++11, however, std::bind can be justified in two constrained situa‐ tions:

    • Move capture. C++11 lambdas don’t offer move capture, but it can be emulated through a combination of a lambda and std::bind.
            For details, consult Item 32, which also explains that in C++14, lambdas’ support for init capture eliminates the need for the emulation.
 
    • Polymorphic function objects. Because the function call operator on a bind object uses perfect forwarding, it can accept arguments of any type (modulo the restrictions on perfect forwarding described in Item 30).
            This can be useful when you want to bind an object with a templatized function call operator.
 
*/

using Time = std::chrono::steady_clock::time_point;
using Duration = std::chrono::steady_clock::duration;
enum class Sound { Beep, Siren, Whistle };
enum class Volume { Normal, Loud, LoudPlusPlus };

void setAlarm(Time t, Sound s, Duration d) {}
void setAlarm(Time t, Sound s, Duration d, Volume v) {}

class PolyWidget {
public:
    
    template<typename T>
    void operator()(const T& param) {};
};

void test_lambdas_to_std_bind() {
    
    using namespace std::chrono;
    using namespace std::literals;
    using namespace std::placeholders;   // needed for use of "_1"
    
    using SetAlarm3ParamType = void(*)(Time, Sound, Duration);
    
    auto setSoundL = [](Sound s){
        setAlarm(steady_clock::now() + 1h, s, 30s);
    };
    
    // The setAlarm example involves only a simple function call. If you want to do any‐ thing more complicated, the scales tip even further in favor of lambdas. For example, consider this C++14 lambda,
    // which returns whether its argument is between a mini‐ mum value (lowVal) and a maximum value (highVal), where lowVal and highVal are local variables:
    auto lowVal = 2, highVal = 100;
    auto betweenL = [lowVal, highVal]  (const auto& val)                          // C++14
        { return lowVal <= val && val <= highVal; };
    
    
    {
        auto setSoundB =    // "B" for "bind"
                std::bind( static_cast<SetAlarm3ParamType> (setAlarm), // setAlarm, overload funtion generate this error: No matching function for call to 'bind'
                    steady_clock::now() + 1h, // incorrect! see below
                    _1,
                    30s);
        // The code isn’t quite right. In the lambda, it’s clear that the expression “steady_clock::now()+1h” is an argument tosetAlarm. It will be evaluated when setAlarm is called.
        // That makes sense: we want the alarm to go off an hour after invoking setAlarm. In the std::bind call, however, “steady_clock::now() + 1h” is passed as an argument to std::bind, not to setAlarm.
        
        // In the std::bind call, however, “steady_clock::now() + 1h” is passed as an argument to std::bind, not to setAlarm.
        // That means that the expression will be evaluated when std::bind is called, and the time resulting from that expression will be stored inside the resulting bind object.
    }

    {
        // Fixing the problem requires telling std::bind to defer evaluation of the expression until setAlarm is called, and the way to do that is to nest a second call to std::bind inside the first one:
        // C++14
         auto setSoundB =
             std::bind( static_cast<SetAlarm3ParamType> (setAlarm),
                        std::bind(std::plus<>(), steady_clock::now(), 1h),
                       _1,
                       30s);
        
        // If you’re familiar with the std::plus template from C++98, you may be surprised to see that in this code, no type is specified between the angle brackets, i.e., the code contains “std::plus<>”, not “std::plus<type>”.
        // In C++14, the template type argument for the standard operator templates can generally be omitted, so there’s no need to provide it here.
        
        // C++11 offers no such feature, so the C++11 std::bind equivalent to the lambda is:
        auto setSoundB1 =
             std::bind( static_cast<SetAlarm3ParamType> (setAlarm),
                        std::bind(std::plus<steady_clock::time_point>(), steady_clock::now(),
                                 hours(1)),
                        -1,
                        seconds(30));
    }
    
    //
    {
        // • Polymorphic function objects. Because the function call operator on a bind object uses perfect forwarding, it can accept arguments of any type (modulo the restrictions on perfect forwarding described in Item 30).
        PolyWidget pw;
        auto boundPw = std::bind(pw, _1);
        
        boundPw(1930);   // pass int to
                        // PolyWidget::operator()
        
        boundPw(nullptr);   // pass nullptr to
                            // PolyWidget::operator()
        
        boundPw("Rosebud");     // pass string literal to
                                // PolyWidget::operator()
        
        // There is no way to do this with a C++11 lambda.
        // In C++14, however, it’s easily achieved via a lambda with an auto parameter:
        auto boundPW1 = [pw](const auto& param) // C++14
            { pw(param); };
    }
}


}
