

/*
 
    Tweaks
 
    For every general technique or feature in C++, there are circumstances where it’s rea‐ sonable to use it, and there are circumstances where it’s not.
    Describing when it makes sense to use a general technique or feature is usually fairly straightforward, but this chapter covers two exceptions. The general technique is pass by value, and the general feature is emplacement.
    The decision about when to employ them is affected by so many factors, the best advice I can offer is to consider their use. Nevertheless, both are important players in effective modern C++ programming,
    and the Items that follow provide the information you’ll need to determine whether using them is appropriate for your software.
 
 */

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

/*
 
    Item 41: Consider pass by value for copyable parameters that are cheap to move and always copied.
 
    Things to Remember
    • For copyable, cheap-to-move parameters that are always copied, pass by value may be nearly as efficient as pass by reference, it’s easier to implement, and it can generate less object code.
    • Copying parameters via construction may be significantly more expensive than copying them via assignment.
    • Pass by value is subject to the slicing problem, so it’s typically inappropriate for base class parameter types.
 
 
    Look again at this Item’s title:
        *** Consider pass by value for copyable parameters that are cheap to move and always copied.
 
    It’s worded the way it is for a reason. Four reasons, in fact:
    
    1. You should only consider using pass by value. Yes, it requires writing only one function. Yes, it generates only one function in the object code. Yes, it avoids the issues associated with universal references.
        But it has a higher cost than the alter‐ natives, and, as we’ll see below, in some cases, there are expenses we haven’t yet discussed.
 
    2. Consider pass by value only for copyable parameters. Parameters failing this test must have move-only types, because if they’re not copyable, yet the function always makes a copy, the copy must be created via the move constructor.
       Recall that the advantage of pass by value over overloading is that with pass by value, only one function has to be written.
       But for move-only types, there is no need to provide an overload for lvalue arguments, because copying an lvalue entails calling the copy constructor, and the copy constructor for move-only types is disabled.
       That means that only rvalue arguments need to be supported, and in that case, the “overloading” solution requires only one overload: the one taking an rvalue reference.
 
    3. Pass by value is worth considering only for parameters that are cheap to move.
        When moves are cheap, the cost of an extra one may be acceptable, but when they’re not, performing an unnecessary move is analogous to performing an unnecessary copy,
        and the importance of avoiding unnecessary copy operations is what led to the C++98 rule about avoiding pass by value in the first place!
 
    4. You should consider pass by value only for parameters that are always copied. To see why this is important, suppose that before copying its parameter into the names container,
        addName checks to see if the new name is too short or too long. If it is, the request to add the name is ignored. A pass-by-value implementation could be written like this:
 
 
 
        Interestingly, if the old password were shorter than the new one, it would typically be impossible to avoid an allocation-deallocation pair during the assignment, and in that case, pass by value would run at about the same speed as pass by reference.
        The cost of assignment-based parameter copying can thus depend on the values of the objects participating in the assignment! This kind of analysis applies to any parameter type that holds values in dynamically allocated memory.
        Not all types qualify, but many—including std::string and std::vector—do.
 
        This potential cost increase generally applies only when lvalue arguments are passed, because the need to perform memory allocation and deallocation typically occurs only when true copy operations (i.e., not moves) are performed.
        For rvalue argu‐ ments, moves almost always suffice.

        The upshot is that the extra cost of pass by value for functions that copy a parameter using assignment depends on the type being passed, the ratio of lvalue to rvalue argu‐ ments, whether the type uses dynamically allocated memory,
        and, if so, the implementation of that type’s assignment operators and the likelihood that the memory associated with the assignment target is at least as large as the memory associated with the assignment source.
        For std::string, it also depends on whether the imple‐ mentation uses the small string optimization (SSO—see Item 29) and, if so, whether the values being assigned fit in the SSO buffer.
   
        So, as I said, when parameters are copied via assignment, analyzing the cost of pass by value is complicated.
        Usually, the most practical approach is to adopt a “guilty until proven innocent” policy, whereby you use overloading or universal references instead of pass by value
        unless it’s been demonstrated that pass by value yields acceptably efficient code for the parameter type you need.
 
        When there are chains of function calls, each of which employs pass by value because “it costs only one inexpensive move,” the cost for the entire chain of calls may not be something you can tolerate.
        Using by-reference parameter passing, chains of calls don’t incur this kind of accumulated overhead.
        
        An issue unrelated to performance, but still worth keeping in mind, is that pass by value, unlike pass by reference, is susceptible to the slicing problem. This is well-trod C++98 ground,
        so I won’t dwell on it, but if you have a function that is designed to accept a parameter of a base class type or any type derived from it, you don’t want to declare a pass-by-value parameter of that type,
        because you’ll “slice off” the derived- class characteristics of any derived type object that may be passed in:
 
        C++11 doesn’t fundamentally change the C++98 wisdom regarding pass by value. In general, pass by value still entails a performance hit you’d prefer to avoid, and pass by value can still lead to the slicing problem.
        What’s new in C++11 is the distinction between lvalue and rvalue arguments. Implementing functions that take advantage of move semantics for rvalues of copyable types requires either overloading or using universal references, both of which have drawbacks.
        For the special case of copyable, cheap-to-move types passed to functions that always copy them and where slicing is not a concern, pass by value can offer an easy-to-implement alternative that’s nearly as efficient as its pass-by-reference competitors,
        but avoids their disadvantages.
        
 */

namespace modern_cpp_tweak {


class Widget {
    
    vector<string> names;
    
public:
    // Furthermore, there will be two functions in the object code—something you might care about if you’re concerned about your program’s footprint.
    // In this case, both functions will probably be inlined, and that’s likely to eliminate any bloat issues related to the existence of two functions,
    // but if these functions aren’t inlined every‐ where, you really will get two functions in your object code.
    void addName(const string& name) { // take lvalue; copy it
        names.push_back(name);
    }
    
    void addName(string&& name) {   // take rvalue
        names.push_back(std::move(name));
    }
    
    // This reduces the source code you have to deal with, but the use of universal refer‐ ences leads to other complications. As a template, addName’s implementation must typically be in a header file.
    // It may yield several functions in object code, because it not only instantiates differently for lvalues and rvalues, it also instantiates differently for std::string and types that are convertible to std::string (see Item 25).
    // At the same time, there are argument types that can’t be passed by universal reference (see Item 30), and if clients pass improper argument types, compiler error messages can be intimidating (see Item 27).
    template<typename T>
    void addName1(T&& name) {   // take lvalues and rvalues; // copy lvalues, // move rvalues; or use of std::forward
        names.push_back(std::forward<T>(name));
    }
    
    // Wouldn’t it be nice if there were a way to write functions like addName such that lval‐ ues were copied, rvalues were moved, there was only one function to deal with (in both source and object code),
    // and the idiosyncrasies of universal references were avoided? As it happens, there is. All you have to do is abandon one of the first rules you probably learned as a C++ programmer. That rule was to avoid passing objects of

    // user-defined types by value. For parameters like newName in functions like addName, pass by value may be an entirely reasonable strategy.
    // Before we discuss why pass-by-value may be a good fit for newName and addName, let’s see how it would be implemented:
    void addName2(string name) {     // take lvalue or rvalue; move it
        names.push_back(std::move(name));
        // The only non-obvious part of this code is the application of std::move to the param‐ eter newName. Typically, std::move is used with rvalue references, but in this case,
        // we know that (1) newName is a completely independent object from whatever the caller passed in, so changing newName won’t affect callers and (2) this is the final use of newName, so moving from it won’t have any impact on the rest of the function.
    }
    
    
};


void test_prefer_value_copy() {
    
    Widget w;
    
    std::string name("Bart");
    
    w.addName(name);
    
    w.addName(name + "Jenne");
    
    /*
    Now consider the cost, in terms of copy and move operations, of adding a name to a Widget for the two calling scenarios and each of the three addName implementations
    we’ve discussed. The accounting will largely ignore the possibility of compilers opti‐ mizing copy and move operations away, because such optimizations are context- and compiler-dependent and, in practice, don’t change the essence of the analysis.
     
    • Overloading: Regardless of whether an lvalue or an rvalue is passed, the caller’s argument is bound to a reference called newName. That costs nothing, in terms of copy and move operations. In the lvalue overload, newName is copied into Widget::names.
            In the rvalue overload, it’s moved. Cost summary: one copy for lvalues, one move for rvalues.
     
    • Using a universal reference: As with overloading, the caller’s argument is bound to the reference newName. This is a no-cost operation. Due to the use of std::forward, lvalue std::string arguments are copied into Widget::names,
            while rvalue std::string arguments are moved. The cost summary for std::string arguments is the same as with overloading: one copy for lvalues, one move for rvalues.
     
    Item 25 explains that if a caller passes an argument of a type other than std::string, it will be forwarded to a std::string constructor, and that could
    cause as few as zero std::string copy or move operations to be performed. Functions taking universal references can thus be uniquely efficient.
            However, that doesn’t affect the analysis in this Item, so we’ll keep things simple by assuming that callers always pass std::string arguments.
     
    • Passing by value: Regardless of whether an lvalue or an rvalue is passed, the parameter newName must be constructed. If an lvalue is passed, this costs a copy construction. If an rvalue is passed, it costs a move construction.
            In the body of the function, newName is unconditionally moved into Widget::names. The cost summary is thus one copy plus one move for lvalues, and two moves for rvalues. Compared to the by-reference approaches, that’s one extra move for both lvalues and rvalues.

     
     */
}



/*
 
        Item 42: Consider emplacement instead of insertion.

 
    Things to Remember
    • In principle, emplacement functions should sometimes be more efficient than their insertion counterparts, and they should never be less efficient.
 
    • In practice, they’re most likely to be faster when
            (1) the value being added is constructed into the container, not assigned;
 
            (2) the argument type(s) passed differ from the type held by the container; and
 
            (3) the container won’t reject the value being added due to it being a duplicate.
 
    • Emplacement functions may perform type conversions that would be rejected by insertion functions.
 
 
    emplace_back is available for every standard container that supports push_back. Similarly, every standard container that supports push_front supports emplace_front.
    And every standard container that supports insert (which is all but std::forward_list and std::array) supports emplace.
    The associative con‐ tainers offer emplace_hint to complement their insert functions that take a “hint” iterator, and std::forward_list has emplace_after to match its insert_after.
 
    What makes it possible for emplacement functions to outperform insertion functions is their more flexible interface. Insertion functions take objects to be inserted,
    while emplacement functions take constructor arguments for objects to be inserted. This dif‐ ference permits emplacement functions to avoid the creation and destruction of temporary objects that insertion functions can necessitate.
 
   
    Emplacement functions can thus do everything insertion functions can. They some‐ times do it more efficiently, and, at least in theory, they should never do it less effi‐ ciently. So why not use them all the time?
 
    Because, as the saying goes, in theory, there’s no difference between theory and practice, but in practice, there is. With current implementations of the Standard Library, there are situations where, as expected, emplacement outperforms insertion, but, sadly,
    there are also situations where the insertion functions run faster. Such situa‐ tions are not easy to characterize, because they depend on the types of arguments being passed, the containers being used,
    the locations in the containers where insertion or emplacement is requested, the exception safety of the contained types’ constructors, and, for containers where duplicate values are prohibited (i.e., std::set, std::map, std::unordered_set, std::unordered_map),
    whether the value to be added is already in the container. The usual performance-tuning advice thus applies: to determine whether emplacement or insertion runs faster, benchmark them both.
    
    That’s not very satisfying, of course, so you’ll be pleased to learn that there’s a heuris‐ tic that can help you identify situations where emplacement functions are most likely to be worthwhile.
    If all the following are true, emplacement will almost certainly out‐ perform insertion:
    
        • The value being added is constructed into the container, not assigned.
                The only ones that aren’t are std::vector, std::deque, and std::string. (std::array isn’t, either, but it doesn’t support insertion or emplacement,
                so it’s not relevant here.) Within the non-node-based containers, you can rely on emplace_back to use construction instead of assignment to get a new value into place, and for std::deque, the same is true of emplace_front.
 
        • The argument type(s) being passed differ from the type held by the container.
                Again, emplacement’s advantage over insertion generally stems from the fact that its interface doesn’t require creation and destruction of a temporary object when the argument(s) passed are of a type other than that held by the container.
                When an object of type T is to be added to a container<T>, there’s no reason to expect emplacement to run faster than insertion, because no temporary needs to be cre‐ ated to satisfy the insertion interface.
 
        • The container is unlikely to reject the new value as a duplicate.
                This means that the container either permits duplicates or that most of the values you add will be unique.
                The reason this matters is that in order to detect whether a value is already in the container, emplacement implementations typically create a node with the new value so that they can compare the value of this node with existing container nodes.
                If the value to be added isn’t in the container, the node is linked in.
                However, if the value is already present, the emplacement is aborted and the node is destroyed, meaning that the cost of its construction and destruction was wasted. Such nodes are created for emplacement functions more often than for insertion functions.
 
    
    In calls to the insertion functions of containers holding resource-managing objects (e.g., std::list<std::shared_ptr<Widget>>), the functions’ parameter types generally ensure that nothing gets between acquisition of a resource (e.g., use of new)
    and construction of the object managing the resource.
    In the emplacement functions, perfect-forwarding defers the creation of the resource-managing objects until they can be constructed in the container’s memory, and that opens a window during which exceptions can lead to resource leaks.
    
    All standard containers are susceptible to this problem. When working with containers of resource-managing objects, you must take care to ensure that if you choose an emplacement function over its inser‐ tion counterpart,
    you’re not paying for improved code efficiency with diminished exception safety.
    
 */
void killWidget(Widget* pWidget) {
    return delete pWidget;
}

void test_considler_emplacement_instead() {
    
    std::vector<std::string> vs;
    
    vs.push_back("xxyyzz"); // create temp. std::string
                            // and pass it to push_back
    
    /*
            The code compiles and runs, and everybody goes home happy. Everybody except the performance freaks, that is, because the performance freaks recognize that this code isn’t as efficient as it should be.
            To create a new element in a container of std::strings, they understand, a std::string constructor is going to have to be called, but the code above doesn’t make just one constructor call. It makes two.
            And it calls the std::string destruc‐ tor, too. Here’s what happens at runtime in the call to push_back:
        
            1. A temporary std::string object is created from the string literal "xyzzy". This object has no name; we’ll call it temp.
                Construction of temp is the first std::string construction. Because it’s a temporary object, temp is an rvalue.
     
            2. temp is passed to the rvalue overload for push_back, where it’s bound to the rvalue reference parameter x. A copy of x is then constructed in the memory for the std::vector.
               This construction—the second one—is what actually creates a new object inside the std::vector.
               (The constructor that’s used to copy x into the std::vector is the move constructor, because x, being an rvalue reference, gets cast to an rvalue before it’s copied. For information about the casting of rvalue reference parameters to rvalues, see Item 25.)
     
            3. Immediately after push_back returns, temp is destroyed, thus calling the std::string destructor.
     
            
         The performance freaks can’t help but notice that if there were a way to take the string literal and pass it directly to the code in step 2 that constructs the std::string
         object inside the std::vector, we could avoid constructing and destroying temp. That would be maximally efficient, and even the performance freaks could contentedly decamp.
     */
    
    
    /*
        there is a way to do exactly what is needed for maximal efficiency in the call to push_back. It’s to not call push_back. push_back is the wrong function. The function you want is emplace_back.
    
        emplace_back does exactly what we desire: it uses whatever arguments are passed to it to construct a std::string directly inside the std::vector. No temporaries are involved:
    */
    
    vs.emplace_back("xxyyzz");
    
    // emplace_back uses perfect forwarding, so, as long as you don’t bump into one of perfect forwarding’s limitations (see Item 30), you can pass any number of arguments of any combination of types through emplace_back.
    // For example, if you’d like to create a std::string in vs via the std::string constructor taking a character and a repeat count, this would do it:
    
    vs.emplace_back(50, 'x');
    
    
    //  Because an argument of the type held by the container can be passed to an emplace‐ ment function (the argument thus causes the function to perform copy or move construction),
    //  emplacement can be used even when an insertion function would require no temporary. In that case, insertion and emplacement do essentially the same thing. For example, given
    
    std::string queenOfDisco("Donna Summer");
    
    // both of the following calls are valid, and both have the same net effect on the con‐ tainer:
    
    vs.push_back(queenOfDisco);     // copy-construct queenOfDisco
                                    // at end of vs
    
    vs.emplace_back(queenOfDisco);  // ditto
    
    
    std::list<std::shared_ptr<Widget>> pts;
    
    /*
     
        explains that you should use std::make_shared to create std::shared_ptrs whenever you can, but it also concedes that there are situations where you can’t.
        One such situation is when you want to specify a custom deleter. In that case, you must use new directly to get the raw pointer to be managed by the std::shared_ptr.
     */
    
    pts.push_back(std::shared_ptr<Widget>(new Widget, killWidget));
    
    // it also look like this, though the meaning whould be the same:
    pts.push_back({new Widget, killWidget});
    
    /*
     
        Either way, a temporary std::shared_ptr would be constructed before calling push_back.
        push_back’s parameter is a reference to a std::shared_ptr, so there has to be a std::shared_ptr for this parameter to refer to.
        
        The creation of the temporary std::shared_ptr is what emplace_back would avoid,
        *** but in this case, that temporary is worth far more than it costs. Consider the following potential sequence of events:
     
        1. In either call above, a temporary std::shared_ptr<Widget> object is construc‐ ted to hold the raw pointer resulting from “new Widget”. Call this object temp.
        2. push_back takes temp by reference. During allocation of a list node to hold a copy of temp, an out-of-memory exception gets thrown.
        3. As the exception propagates out of push_back, temp is destroyed. Being the sole std::shared_ptr referring to the Widget it’s managing, it automatically relea‐ ses that Widget, in this case by calling killWidget.
     
        Even though an exception occurred, nothing leaks: the Widget created via “new Widget” in the call to push_back is released in the destructor of the std::shared_ptr that was created to manage it (temp). Life is good.
     */
    
    // Now consider what happens if emplace_back is called instead of push_back:
    pts.emplace_back(new Widget, killWidget);
    
    /*

        1. The raw pointer resulting from “newWidget” is perfect-forwarded to the point inside emplace_back where a list node is to be allocated. That allocation fails, and an out-of-memory exception is thrown.
        
        2. As the exception propagates out of emplace_back, the raw pointer that was the only way to get at the Widget on the heap is lost. That Widget (and any resources it owns) is leaked.
     
        In this scenario, life is not good, and the fault doesn’t lie with std::shared_ptr. The same kind of problem can arise through the use of std::unique_ptr with a custom deleter.
        Fundamentally, the effectiveness of resource-managing classes like std::shared_ptr and std::unique_ptr is predicated on resources (such as raw pointers from new) being immediately passed to constructors for resource-managing objects.
        The fact that functions like std::make_shared and std::make_unique automate this is one of the reasons they’re so important.
     
     
        Frankly, you shouldn’t be passing expressions like “new Widget” to emplace_back or push_back or most any other function, anyway, because, as Item 21 explains, this leads to the possibility of exception safety problems of the kind we just examined.
        Closing the door requires taking the pointer from “newWidget” and turning it over to a resource-managing object in a standalone statement, then passing that object as an rvalue to the function you originally wanted to pass “newWidget” to.
        (Item 21 covers this technique in more detail.) The code using push_back should therefore be written more like this:
     
        Either way, the approach incurs the cost of creating and destroying spw. Given that the motivation for choosing emplacement over insertion is to avoid the cost of a tem‐

        porary object of the type held by the container, yet that’s conceptually what spw is, emplacement functions are unlikely to outperform insertion functions when you’re adding resource-managing objects to
        a container and you follow the proper practice of ensuring that nothing can intervene between acquiring a resource and turning it over to a resource-managing object.
     */
    
    std::shared_ptr<Widget> p(new Widget, killWidget);
    
    pts.push_back(std::move(p));
    
    // the emplace version is similiar:
    
    pts.emplace_back(std::move(p));
    
    
    
    /*
        A second noteworthy aspect of emplacement functions is their interaction with explicit constructors. In honor of C++11’s support for regular expressions, sup‐ pose you create a container of regular expression objects:
        
     */
    
    
}

}
