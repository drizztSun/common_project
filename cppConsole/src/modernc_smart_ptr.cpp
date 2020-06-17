
//#include <stdio.h>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
using namespace std;
/*
    smart pointer
 
 Smart pointers are wrappers around raw pointers that act much like the raw pointers they wrap, but that avoid many of their pitfalls.
 You should therefore prefer smart pointers to raw pointers. Smart pointers can do virtually everything raw pointers can, but with far fewer opportunities for error.
 
 There are four smart pointers in C++11:
 std::auto_ptr, std::unique_ptr, std::shared_ptr, and std::weak_ptr.
 All are designed to help manage the life‐times of dynamically allocated objects, i.e.,
 to avoid resource leaks by ensuring that such objects are destroyed in the appropriate manner at the appropriate time (including in the event of exceptions).
 
 std::auto_ptr is a deprecated leftover from C++98. It was an attempt to standard‐ ize what later became C++11’s std::unique_ptr.
 Doing the job right required move semantics, but C++98 didn’t have them. As a workaround, std::auto_ptr co-opted its copy operations for moves.
 This led to surprising code (copying a std::auto_ptr sets it to null!) and frustrating usage restrictions (e.g., it’s not possible to store std::auto_ptrs in containers).
 
 std::unique_ptr does everything std::auto_ptr does, plus more. It does it as efficiently, and it does it without warping what it means to copy an object.
 It’s better than std::auto_ptr in every way.
 The only legitimate use case for std::auto_ptr is a need to compile code with C++98 compilers.
 Unless you have that constraint, you should replace std::auto_ptr with std::unique_ptr and never look back.
 
 The C++ Standard says that an STL element must be "copy-constructible" and "assignable."
 In other words, an element must be able to be assigned or copied and the two elements are logically independent. std::auto_ptr does not fulfill this requirement.

 Take for example this code:

 class X {};

 std::vector<std::auto_ptr<X> > vecX;
 vecX.push_back(new X);

 std::auto_ptr<X> pX = vecX[0];  // vecX[0] is assigned NULL.
 To overcome this limitation, you should use the std::unique_ptr, std::shared_ptr or std::weak_ptr smart pointers or the boost equivalents if you don't have C++11.

*/

/*
 
    Item 18: Use std::unique_ptr for exclusive-ownership resource management.
 
 Things to Remember
 • std::unique_ptr is a small, fast, move-only smart pointer for managing resources with exclusive-ownership semantics.
 • By default, resource destruction takes place via delete, but custom deleters can be specified.
            Stateful deleters and function pointers as deleters increase the size of std::unique_ptr objects.
 • Converting a std::unique_ptr to a std::shared_ptr is easy.
 
 
 std::unique_ptr,  by default, std::unique_ptrs are the same size as raw pointers, and for most operations (including dereferencing), they execute exactly the same instructions.
 std::unique_ptr embodies exclusive ownership semantics. A non-null std:: unique_ptr always owns what it points to.
 Moving a std::unique_ptr transfers ownership from the source pointer to the destination pointer. (The source pointer is set to null.) Copying a std::unique_ptr isn’t allowed,
 because if you could copy a std::unique_ptr, you’d end up with two std::unique_ptrs to the same resource, each thinking it owned (and should therefore destroy) that resource.
 std::unique_ptr is thus a move-only type.
 
 Upon destruction, a non-null std::unique_ptr destroys its resource. By default, resource destruction is accom‐ plished by applying delete to the raw pointer inside the std::unique_ptr.
 Deleters that are function pointers generally cause the size of a std::unique_ptr to grow from one word to two.
 For deleters that are function objects, the change in size depends on how much state is stored in the function object. Stateless function objects
 (e.g., from lambda expressions with no captures) incur no size penalty, and this means that when a custom deleter can be implemented as either a function or a captureless lambda
 expression, the lambda is preferable:
 
 Function object deleters with extensive state can yield std::unique_ptr objects of significant size.
 If you find that a custom deleter makes your std::unique_ptrs unacceptably large, you probably need to change your design.
 
 std::unique_ptr comes in two forms, one for individual objects (std:: unique_ptr<T>) and one for arrays (std::unique_ptr<T[]>).
 As a result, there’s never any ambiguity about what kind of entity a std::unique_ptr points to. The std::unique_ptr API is designed to match the form you’re using.
 
 The existence of std::unique_ptr for arrays should be of only intellectual interest to you, because std::array, std::vector, and std::string are virtually always better data structure choices than raw arrays.
 About the only situation I can conceive of when a std::unique_ptr<T[]> would make sense would be when you’re using a C-like API that returns a raw pointer to a heap array that you assume ownership of.
 
 
 */

class Investment {
public:
    
    virtual ~Investment(){};
};

class Stock: public Investment {
    
};

class Estate: public Investment {
    
};

class Bond: public Investment {
    
};

int investment_index = 0;

template <typename... Ts>
auto make_investment(Ts&&... params) {
    
    auto delInvmnt = [] (Investment* pInvestment) {
        delete pInvestment;
    };
    
    std::unique_ptr<Investment, decltype(delInvmnt)> pt(nullptr, delInvmnt);
    
    if (investment_index == 0) {
        pt.reset(new Stock());
    } else if (investment_index == 1) {
        pt.reset(new Estate());
    } else if (investment_index == 2) {
        pt.reset(new Bond());
    }
    
    return pt;
};

void test_uniptr_base() {
    
    std::shared_ptr<Investment> pt = make_investment(1);
    
}

/*
 
    Item 19: Use std::shared_ptr for shared-ownership resource management.
 
 Things to Remember
 • std::shared_ptrs offer convenience approaching that of garbage collection for the shared lifetime management of arbitrary resources.
 • Compared to std::unique_ptr, std::shared_ptr objects are typically twice as big, incur overhead for control blocks, and require atomic reference count manipulations.
 • Default resource destruction is via delete, but custom deleters are supported. The type of the deleter has no effect on the type of the std::shared_ptr.
 • Avoid creating std::shared_ptrs from variables of raw pointer type.
 
 std::shared_ptr is the C++11 way of binding these worlds together. An object accessed via std::shared_ptrs has its lifetime managed by those pointers through shared ownership.
 No specific std::shared_ptr owns the object. Instead, all std::shared_ptrs pointing to it collaborate to ensure its destruction at the point where it’s no longer needed.
 When the last std::shared_ptr pointing to an object stops pointing there (e.g., because the std::shared_ptr is destroyed or made to point to a different object),
 that std::shared_ptr destroys the object it points to.
 As with garbage collection, clients need not concern themselves with managing the life‐ time of pointed-to objects,
 but as with destructors, the timing of the objects’ destruc‐ tion is deterministic.
 
 A std::shared_ptr can tell whether it’s the last one pointing to a resource by con‐ sulting the resource’s reference count,
 a value associated with the resource that keeps track of how many std::shared_ptrs point to it.
 std::shared_ptr constructors increment this count (usually—see below), std::shared_ptr destructors decrement it, and copy assignment operators do both.
 (If sp1 and sp2 are std::shared_ptrs to different objects, the assignment “sp1 = sp2;” modifies sp1 such that it points to the object pointed to by sp2.
 The net effect of the assignment is that the reference count for the object originally pointed to by sp1 is decremented, while that for the object pointed to by sp2 is incremented.)
 
 If a std::shared_ptr sees a reference count of zero after performing a decrement, no more std::shared_ptrs point to the resource, so the std::shared_ptr destroys it.
 • std::shared_ptrs are twice the size of a raw pointer,
 • Memory for the reference count must be dynamically allocated.    Conceptually, the reference count is associated with the object being pointed to,
            but pointed-to objects know nothing about this. They thus have no place to store a reference count.
 • Increments and decrements of the reference count must be atomic,  because there can be simultaneous readers and writers in different threads.
 
 Move construction, that’s why. Move-constructing a std::shared_ptr from another std::shared_ptr sets the source std::shared_ptr to null,
    and that means that the old std::shared_ptr stops pointing to the resource at the moment the new std::shared_ptr starts.
 
 As a result, no reference count manipulation is required. Moving std::shared_ptrs is therefore faster than copying them: copying requires incrementing the reference count,
 but moving doesn’t. This is as true for assignment as for construction, so move construction is faster than copy construction, and move assignment is faster than copy assignment.
 
 Like std::unique_ptr (see Item 18), std::shared_ptr uses delete as its default resource-destruction mechanism, but it also supports custom deleters.
 The design of this support differs from that for std::unique_ptr, however.
 For std::unique_ptr, the type of the deleter is part of the type of the smart pointer. For std::shared_ptr, it’s not:
 
 shared_ptr:
 In another difference from std::unique_ptr, specifying a custom deleter doesn’t change the size of a std::shared_ptr object.
 Regardless of deleter, a std::shared_ptr object is two pointers in size. That’s great news, but it should make you vaguely uneasy.
 Custom deleters can be function objects, and function objects can contain arbitrary amounts of data. That means they can be arbitrarily large.
 
 shared_ptr:
 
 |      Ptr to T        |  --->  |  T Obj  |
                                    
 | Ptr to Control Block |  --->  {control block}    |  Reference Count  |
                                                    |  Weak Count       |
                                                    |  Other Data, (Customer deletor, allocator, etc) |
 
 How can a std::shared_ptr refer to a deleter of arbitrary size without using any more memory?
 
 It can’t. It may have to use more memory. However, that memory isn’t part of the std::shared_ptr object.
 It’s on the heap or, if the creator of the std::shared_ptr took advantage of std::shared_ptr support for custom allocators, it’s wherever the memory managed by the allocator is located.
 I remarked earlier that a std::shared_ptr object contains a pointer to the reference count for the object it points to.
 
 That’s true, but it’s a bit misleading, because the reference count is part of a larger data structure known as the control block.
 There’s a control block for each object managed by std::shared_ptrs.
 The control block contains, in addition to the reference count, a copy of the custom deleter, if one has been specified.
 If a custom allocator was specified, the control block contains a copy of that, too.
 The control block may also contain additional data, including, as Item 21 explains, a secondary reference count known as the weak count, but we’ll ignore such data in this Item.
 We can envision the memory associated with a std::shared_ptr<T> object as looking like this:
 
 
 An object’s control block is set up by the function creating the first std::shared_ptr to the object. At least that’s what’s supposed to happen.
 In general, it’s impossible for a function creating a std::shared_ptr to an object to know whether some other std::shared_ptr already points to that object, so the following rules for control block creation are used:
 
 • std::make_shared (see Item 21) always creates a control block.(It manufactures a new object to point to, so there is certainly no control block for that object at the time std::make_shared is called.)
 
 • A control block is created when a std::shared_ptr is constructed from a unique-ownership pointer (i.e., a std::unique_ptr or std::auto_ptr).  (Unique-ownership pointers don’t use control blocks, so there should be no con‐ trol block for the pointed-to object.)

 • When a std::shared_ptr constructor is called with a raw pointer, it creates a control block.
        (If you wanted to create a std::shared_ptr from an object that already had a control block, you’d presumably pass a std::shared_ptr or a std::weak_ptr (see Item 20) as a constructor argument, not a raw pointer. std::shared_ptr constructors taking std::shared_ptrs or std::weak_ptrs as constructor arguments don’t create new control blocks, because they can rely on the smart pointers passed to them to point to any necessary control blocks.)
 
 */

// *** An especially surprising way that using raw pointer variables as std::shared_ptr constructor arguments can lead to multiple control blocks involves the this pointer. ***
// The std::shared_ptr API includes a facility for just this kind of situation. It has probably the oddest of all names in the Standard C++ Library: std:: enable_shared_from_this.
// That’s a template for a base class you inherit from if you want a class managed by std::shared_ptrs to be able to safely create a std::shared_ptr from a this pointer.
// In our example, Widget would inherit from std::enable_shared_from_this as follows:
class Widget{};

class Widget1 : public std::enable_shared_from_this<Widget1> {
    
    std::vector<std::shared_ptr<Widget1>> processedWidgets;
    
    Widget1();
    
    // Internally, shared_from_this looks up the control block for the current object, and it creates a new std::shared_ptr that refers to that control block.
    // The design relies on the current object having an associated control block. For that to be the case, there must be an existing std::shared_ptr
    // (e.g., one outside the member function calling shared_from_this) that points to the current object.
    // If no such std::shared_ptr exists (i.e., if the current object has no associated control block), behavior is undefined, although shared_from_this typically throws an exception.
    
public:
    
    // To prevent clients from calling member functions that invoke shared_from_this before a std::shared_ptr points to the object,
    // classes inheriting from std::enable_shared_from_this often declare their constructors private and have clients create objects by calling factory functions that return std:: shared_ptrs.
    template<typename... T>
    static std::shared_ptr<Widget1> create(T&&... params);
    
    void process() {
        // add std::shared_ptr to current object to processedWidgets
        processedWidgets.emplace_back(shared_from_this());
    }
};
// std::enable_shared_from_this is a base class template. Its type parame‐ ter is always the name of the class being derived, so Widget inherits from std::enable_shared_from_this<Widget>.
// std::enable_shared_from_this defines a member function "shared_from_this", that creates a std::shared_ptr to the current object, but it does it without duplicating control blocks.
// The member function is shared_from_this, and you use it in member func‐ tions whenever you want a std::shared_ptr that points to the same object as the this pointer.

//
// A control block is typically only a few words in size, although custom deleters and allocators may make it larger.
// The usual control block implementation is more sophisticated than you might expect. It makes use of inheritance, and there’s even a virtual function.
// (It’s used to ensure that the pointed-to object is properly destroyed.)
// That means that using std::shared_ptrs also incurs the cost of the machinery for the virtual function used by the control block.

// Under typical conditions, where the default deleter and default allocator are used and where the std::shared_ptr is created by std::make_shared,
// the control block is only about three words in size, and its allocation is essentially free.

// Something else std::shared_ptrs can’t do is work with arrays.
// In yet another difference from std::unique_ptr, std::shared_ptr has an API that’s designed only for pointers to single objects.
// There’s no std::shared_ptr<T[]>. From time to time, “clever” programmers stumble on the idea of using a std::shared_ptr<T> to point to an array,
// specifying a custom deleter to perform an array delete

// This can be made to compile, but it’s a horrible idea.
// For one thing, std::shared_ptr offers no operator[], so indexing into the array requires awkward expressions based on pointer arithmetic.
// For another, std::shared_ptr supports derived-to-base pointer conversions that make sense for single objects, but that open holes in the type system when applied to arrays.
// (For this reason, the std::unique_ptr<T[]> API prohibits such conversions.)
// Most importantly, given the variety of C++11 alternatives to built-in arrays (e.g., std::array, std::vector, std::string),
// declaring a smart pointer to a dumb array is almost always a sign of bad design.


void test_share_ptr_basic1() {
    
    auto loggingDel = [](Widget *pw) {
            std::cout << "Delete Ptr " << pw << std::endl;
            delete pw;
        };  // custom deleter
    
    std::unique_ptr<Widget, decltype(loggingDel)> upw(new Widget, loggingDel); // deleter type is part of ptr type
    
    std::shared_ptr<Widget> spw(new Widget, loggingDel); // deleter type is not part of ptr type

    auto deletor1 = [](Widget* p) { delete p; };
    auto deletor2 = [](Widget* p) { delete p; };
    
    std::shared_ptr<Widget> pw1(new Widget, deletor1);
    std::shared_ptr<Widget> pw2(new Widget, deletor2);
    
    // Because pw1 and pw2 have the same type, they can be placed in a container of objects of that type:
    std::vector<std::shared_ptr<Widget>> vpw {pw1, pw2};
    
    
    
    // They could also be assigned to one another, and they could each be passed to a func‐ tion taking a parameter of type std::shared_ptr<Widget>.
    // None of these things can be done with std::unique_ptrs that differ in the types of their custom deleters,
    // because the type of the custom deleter would affect the type of the std::unique_ptr.
 
    auto p = new Widget;
    std::shared_ptr<Widget> p1(p, loggingDel); // create 1st control block
    // error:  std::shared_ptr<Widget> p2(p, loggingDel); // create another control block for p, error!
    std::shared_ptr<Widget> p2(new Widget, loggingDel);
    // or create one for shared_ptr
    std::shared_ptr<Widget> p3(p1);
    
    // *p thus has two reference counts, each of which will even‐ tually become zero, and that will ultimately lead to an attempt to destroy *pw twice.
    // The second destruction is responsible for the undefined behavior.
    // There are at least two lessons regarding std::shared_ptr use here.
    // 1) First, try to avoid passing raw pointers to a std::shared_ptr constructor. The usual alternative is to use std::make_shared
    // 2) Second, if you must pass a raw pointer to a std::shared_ptr constructor, pass the result of new directly instead of going through a raw pointer variable.
    //      If the first part of the code above were rewritten like this,
    // An especially surprising way that using raw pointer variables as std::shared_ptr constructor arguments can lead to multiple control blocks involves the this pointer.
    
    
}



/*
 
    Item 20: Use std::weak_ptr for std::shared_ptr- like pointers that can dangle.
 
 Things to Remember
 • Use std::weak_ptr for std::shared_ptr-like pointers that can dangle.
 • Potential use cases for std::weak_ptr include caching, observer lists, and the prevention of std::shared_ptr cycles.
 
 
 In other words, a pointer like std::shared_ptr that doesn’t affect an object’s reference count. This kind of smart pointer has to contend with a problem unknown to std::shared_ptrs: the possibility that what it points to has been destroyed.
 A truly smart pointer would deal with this problem by tracking when it dangles, i.e., when the object it is supposed to point to no longer exists. That’s precisely the kind of smart pointer std::weak_ptr is.
 
 std::weak_ptrs can’t be dereferenced, nor can they be tested for nullness. That’s because std::weak_ptr isn’t a standalone smart pointer. It’s an augmentation of std::shared_ptr.

 The relationship begins at birth. std::weak_ptrs are typically created from std::shared_ptrs. They point to the same place as the std::shared_ptrs initializing them, but they don’t affect the reference count of the object they point to:v

 Because std::weak_ptrs lack dereferencing operations, there’s no way to write the code. Even if there were, separating the check and the dereference would introduce a race condition:
 between the call to expired and the dereferencing action, another thread might reassign or destroy the last std::shared_ptr pointing to the object, thus causing that object to be destroyed. In that case, your dereference would yield undefined behavior.

 
 From an efficiency perspective, the std::weak_ptr story is essentially the same as that for std::shared_ptr. std::weak_ptr objects are the same size as std:: shared_ptr objects, they make use of the same control blocks as std:: shared_ptrs (see Item 19),
 and operations such as construction, destruction, and assignment involve atomic reference count manipulations.
 That probably surprises you, because I wrote at the beginning of this Item that std::weak_ptrs don’t participate in reference counting.
 Except that’s not quite what I wrote. What I wrote was that std::weak_ptrs don’t participate in the shared ownership of objects and hence don’t affect the pointed-to object’s reference count.
 There’s actually a second reference count in the control block, and it’s this second reference count that std::weak_ptrs manipulate. For details, continue on to Item 21.
 
 */

void test_weak_ptr() {
    
    auto spw = std::make_shared<Widget>(); // after spw is constructed, the pointed-to Widget's ref count (RC) is 1.
    
    std::weak_ptr<Widget> wpw(spw); // wpw points to same Widget as spw. RC remains 1
    
    spw = nullptr;
    
    if (wpw.expired()) {
        // but often what you desire is a check to see if a std::weak_ptr has expired and, if it hasn’t (i.e., if it’s not dangling), to access the object it points to. This is easier desired than done.
        std::cout << "weak ptr has been expird and is pointing to nullptr" << std::endl;
    }
    
    // Because std::weak_ptrs lack dereferencing operations, there’s no way to write the code. Even if there were, separating the check and the dereference would introduce a race condition:
    // between the call to expired and the dereferencing action, another thread might reassign or destroy the last std::shared_ptr pointing to the object, thus causing that object to be destroyed. In that case, your dereference would yield undefined behavior.

    // What you need is an atomic operation that checks to see if the std::weak_ptr has expired and, if not, gives you access to the object it points to. This is done by creating a std::shared_ptr from the std::weak_ptr.
    {
        auto spw = std::make_shared<Widget>();
        std::weak_ptr<Widget> wpw(spw);
        
        {
            // 1) using lock()
            std::shared_ptr<Widget> spw1 = wpw.lock();
            if (spw1) {
                std::cout << "If lock() returns non-nullptr pointer, the expired() is false. Or lock() return nullptr, if true" << std::endl;
            }
            
            spw = nullptr;
            
            // 2) The other form is the std::shared_ptr constructor taking a std::weak_ptr as an argument. In this case, if the std::weak_ptr has expired, an exception is thrown:
            try {
                std::shared_ptr<Widget> spw3(wpw); // if wpw's expired, throw std::bad_weak_ptr
                
            } catch (std::bad_weak_ptr& a) {
                std::cout << "bad weak pointer" << std::endl;
            }
        }
    }
    
}

using WidgetId = int;

std::unique_ptr<const Widget> loadWidget(WidgetId id) {
    return std::unique_ptr<const Widget>(new Widget);
}

std::shared_ptr<const Widget> fastLoadWidget(WidgetId id) {
    
    static std::unordered_map<WidgetId, std::weak_ptr<const Widget>> cache;
    
    auto objPtr = cache[id].lock();
    
    if (!objPtr) {
        objPtr = loadWidget(id);
        cache[id] = objPtr;
    }
    return objPtr;
}


/*
 
    Item 21: Prefer std::make_unique and std::make_shared to direct use of new.
 
 Things to Remember
 • Compared to direct use of new, make functions eliminate source code duplication, improve exception safety, and, for std::make_shared (once memory alocation)and std::allo cate_shared, generate code that’s smaller and faster.
 • Situations where use of make functions is inappropriate include the need to specify custom deleters and a desire to pass braced initializers.
 • For std::shared_ptrs, additional situations where make functions may be ill-advised include (1) classes with custom memory management and (2) sys‐ tems with memory concerns, very large objects, and std::weak_ptrs that outlive the corresponding std::shared_ptrs.
 
 "std::make_unique" and "std::make_shared" are two of the three make functions: functions that take an arbitrary set of arguments, perfect-forward them to the constructor for a dynamically allocated object, and return a smart pointer to that object.
 The third make function is "std::allocate_shared". It acts just like std::make_shared, except its first argument is an allocator object to be used for the dynamic memory allocation.

 *** Shared_Ptr Contorl BLock***
 
 As I noted, the control block contains bookkeeping information beyond just the ref‐ erence count itself.
 The reference count tracks how many std::shared_ptrs refer to the control block, but the control block contains a second reference count, one that tallies how many std::weak_ptrs refer to the control block.
 This second reference count is known as the weak count.4 When a std::weak_ptr checks to see if it has expired (see Item 19), it does so by examining the reference count (not the weak count) in the control block that it refers to.
 If the reference count is zero (i.e., if the pointed-to object has no std::shared_ptrs referring to it and has thus been destroyed), the std::weak_ptr has expired. Otherwise, it hasn’t.
 
 As long as std::weak_ptrs refer to a control block (i.e., the weak count is greater than zero), that control block must continue to exist.
 And as long as a control block exists, the memory containing it must remain allocated. The memory allocated by a std::shared_ptr make function,
 then, can’t be deallocated until the last std::shared_ptr and the last std::weak_ptr referring to it have been destroyed.
 
 If the object type is quite large and the time between destruction of the last std::shared_ptr and the last std::weak_ptr is significant,
 a lag can occur between when an object is destroyed and when the memory it occupied is freed:
 */

void test_smart_ptr_creation() {
    
    // Even the most trivial comparison of smart pointer creation using and not using a make function reveals the first reason why using such functions is preferable. Con‐ sider:
    auto upw1(std::make_unique<Widget>());  // with make func
    std::unique_ptr<Widget> upw2(new Widget);   // without make func
    
    auto spw1(std::make_shared<Widget>());  // with make func
    std::shared_ptr<Widget> spw2(new Widget);   // without make func
    // a key tenet of software engineering: code duplication should be avoided.
    
    // The second reason to prefer make functions has to do with exception safety.
    // As the comment indicates, this code could leak the Widget conjured up by new. But how?
    // processWidget(std::shared_ptr<Widget>(new Widget), computePriority()); // potential, resource leak!
    /*
     

     1) Repeating types runs afoul of a key tenet of software engineering: code duplication should be avoided.
     2) The second reason to prefer make functions has to do with exception safety. Both the calling code and the called function are using std::shared_ptrs, and std::shared_ptrs are designed to prevent resource leaks.
     
     
     The answer has to do with compilers’ translation of source code into object code.
     At runtime, the arguments for a function must be evaluated before the function can be invoked, so in the call to processWidget, the following things must occur before processWidget can begin execution:
        • The expression “new Widget” must be evaluated, i.e., a Widget must be created on the heap.
        • The constructor for the std::shared_ptr<Widget> responsible for managing the pointer produced by new must be executed.
        • computePriority must run.
     Compilers are not required to generate code that executes them in this order. “new Widget” must be executed before the std::shared_ptr constructor may be called, because the result of that new is used as an argument to that constructor,
     but compute Priority may be executed before those calls, after them, or, crucially, between them. That is, compilers may emit code to execute the operations in this order:
         1. Perform “new Widget”.
         2. ExecutecomputePriority.
         3. Runstd::shared_ptrconstructor.
     If such code is generated and, at runtime, computePriority produces an exception, the dynamically allocated Widget from Step 1 will be leaked,
     because it will never be stored in the std::shared_ptr that’s supposed to start managing it in Step 3.
     
     Using std::make_shared avoids this problem. Calling code would look like this:
            processWidget(std::make_shared<Widget>(), // no potential
                            computePriority());           // resource leak
     
     At runtime, either std::make_shared or computePriority will be called first. If it’s std::make_shared, the raw pointer to the dynamically allocated Widget is safely stored in the returned std::shared_ptr before computePriority is called.
     If compu tePriority then yields an exception, the std::shared_ptr destructor will see to it that the Widget it owns is destroyed.
     And if computePriority is called first and yields an exception, std::make_shared will not be invoked, and there will hence be no dynamically allocated Widget to worry about.
     */

    // ii
    // A special feature of std::make_shared (compared to direct use of new) is improved efficiency. Using std::make_shared allows compilers to generate smaller, faster code that employs leaner data structures.
    
    // It’s obvious that this code entails a memory allocation, but it actually performs two.
    std::shared_ptr<Widget> spw(new Widget);
    // Direct use of new, then, requires one memory allocation for the Widget and a second allocation for the control block.
    
    auto spw3 = std::make_shared<Widget>();
    // one allocation suffices. That’s because std::make_shared allocates a single chunk of memory to hold both the Widget object and the control block. This optimization
    // reduces the static size of the program, because the code contains only one memory allocation call, and it increases the speed of the executable code, because memory is allocated only once.
    // Furthermore, using std::make_shared obviates the need for some of the bookkeeping information in the control block, potentially reducing the total memory footprint for the program.
    // The efficiency analysis for std::make_shared is equally applicable to std::allo cate_shared, so the performance advantages of std::make_shared extend to that function, as well.
    
    
    // The arguments for preferring make functions over direct use of new are strong ones. Despite their software engineering, exception safety, and efficiency advantages, how‐ ever, this Item’s guidance is to prefer the make functions, not to rely on them exclu‐ sively.
    // That’s because there are circumstances where they can’t or shouldn’t be used.
    // For example, none of the make functions permit the specification of custom deleters (see Items 18 and 19), but both std::unique_ptr and std::shared_ptr have con‐ structors that do. Given a custom deleter for a Widget,
    // *** 1) have to use smart_ptr ctor and new ***
    {
        auto widgetDeleter = [](Widget* pw) {  };
        std::unique_ptr<Widget, decltype(widgetDeleter)> upw(new Widget, widgetDeleter);
        std::shared_ptr<Widget> spw(new Widget, widgetDeleter);
        // There’s no way to do the same thing with a make function.
    }
    
    {
        // A second limitation of make functions stems from a syntactic detail of their imple‐ mentations.
        // Item 7 explains that when creating an object whose type overloads con‐ structors both with and without std::initializer_list parameters, creating the object using braces prefers the std::initializer_list constructor,
        // while creating the object using parentheses calls the non-std::initializer_list constructor.
        // The make functions perfect-forward their parameters to an object’s constructor, but do they do so using parentheses or using braces? For some types, the answer to this question makes a big difference.
        
        auto upv = std::make_unique<std::vector<int>>(10, 20);
        auto spv = std::make_shared<std::vector<int>>(10, 20);
        
        // The good news is that it’s not indeterminate: both calls create std::vectors of size 10 with all values set to 20. That means that within the make functions, the perfect forwarding code uses parentheses, not braces.
        // The bad news is that if you want to construct your pointed-to object using a braced initializer, you must use new directly.
        // Using a make function would require the ability to perfect-forward a braced initial‐ izer, but, as Item 30 explains, braced initializers can’t be perfect-forwarded.
        // However, Item 30 also describes a workaround: use auto type deduction to create a std::ini tializer_list object from a braced initializer (see Item 2), then pass the auto- created object through the make function:
        // create std::initializer_list
        auto initList = { 10, 20 };
        // create std::vector using std::initializer_list ctor
        auto spv1 = std::make_shared<std::vector<int>>(initList);
    }
    
    // *** 2) use new not make_func, For std::unique_ptr, these two scenarios (custom deleters and braced initializers) are the only ones where its make functions are problematic. ***
    // For std::shared_ptr and its make functions, there are two more. Both are edge cases, but some developers live on the edge, and you may be one of them.
    
    // Some classes define their own versions of operator new and operator delete. The presence of these functions implies that the global memory allocation and deallocation routines for objects of these types are inappropriate.
    // Often, class-specific rou‐ tines are designed only to allocate and deallocate chunks of memory of precisely the size of objects of the class, e.g., operator new and operator delete
    // for class Widget are often designed only to handle allocation and deallocation of chunks of memory of exactly size sizeof(Widget).
    
    // Some classes define their own versions of operator new and operator delete. The presence of these functions implies that the global memory allocation and dealloca‐ tion routines for objects of these types are inappropriate.
    // Often, class-specific rou‐ tines are designed only to allocate and deallocate chunks of memory of precisely the size of objects of the class, e.g.,
    // operator new and operator delete for class Widget are often designed only to handle allocation and deallocation of chunks of memory of exactly size sizeof(Widget).
    
    // Such routines are a poor fit for std::shared_ptr’s support for custom allocation (via std::allocate_shared) and deallocation (via custom deleters), because the amount of memory that std::allocate_shared requests isn’t the size of the dynamically allocated object,
    // it’s the size of that object plus the size of a control block. Consequently, using make functions to create objects of types with class-specific versions of operator new and operator delete is typi‐ cally a poor idea.
    
    // The size and speed advantages of std::make_shared vis-à-vis direct use of new stem from std::shared_ptr’s control block being placed in the same chunk of memory
    // as the managed object. When that object’s reference count goes to zero, the object is destroyed (i.e., its destructor is called).
    // However, the memory it occupies can’t be released until the control block has also been destroyed, because the same chunk of dynamically allocated memory contains both.
    
    //*** 3) use for large object***
    // If the object type is quite large and the time between destruction of the last std::shared_ptr and the last std::weak_ptr is significant, a lag can occur between when an object is destroyed and when the memory it occupied is freed:
    
}

/*
    Item 22: When using the Pimpl Idiom, define special member functions in the implementation file.
 
 Things to Remember
 • The Pimpl Idiom decreases build times by reducing compilation dependencies between class clients and class implementations.
 • For std::unique_ptr pImpl pointers, declare special member functions in the class header, but implement them in the implementation file. Do this even if the default function implementations are acceptable.
 • The above advice applies to std::unique_ptr, but not to std::shared_ptr.
 
 *** A type that has been declared, but not defined, is known as an incomplete type.
 There are very few things you can do with an incom‐ plete type, but declaring a pointer to it is one of them. The Pimpl Idiom takes advan‐ tage of that.***
 
 This apparent failure of the Pimpl Idiom using std::unique_ptrs is alarming, because (1) std::unique_ptr is advertised as supporting incomplete types, and (2)
 the Pimpl Idiom is one of std::unique_ptrs most common use cases. Fortunately, getting the code to work is easy. All that’s required is a basic understanding of the cause of the problem.
 
 pImpl is a std::unique_ptr<Widget::Impl>, i.e., a std::unique_ptr using the default deleter. The default deleter is a function that uses delete on the raw pointer inside the std::unique_ptr.
 Prior to using delete, however, implementa‐ tions typically have the default deleter employ C++11’s static_assert to ensure that the raw pointer doesn’t point to an incomplete type.
 When the compiler gener‐ ates code for the destruction of the Widget w, then, it generally encounters a static_assert that fails, and that’s usually what leads to the error message. This message is associated with the point where w is destroyed,
 
 To fix the problem, you just need to make sure that at the point where the code to destroy the std::unique_ptr<Widget::Impl> is generated, Widget::Impl is a complete type.
 The type becomes complete when its definition has been seen, and Widget::Impl is defined inside widget.cpp.
 * The key to successful compilation, then, is to have the compiler see the body of Widget’s destructor (i.e., the place where the compiler will generate code to destroy the std::unique_ptr data member) only inside widget.cpp after Widget::Impl has been defined.
 
 */

// suppose it is in another head file  'Widget2.h'
class Widget2 {
    
    
public:
    Widget2();
    ~Widget2();
    
    // This approach leads to the same kind of problem as declaring the class without a destructor, and for the same fundamental reason.
    Widget2(Widget2&&); // = default;
    Widget2& operator=(Widget2&&); // = default;
    // if without move destructor or with =default, This approach leads to the same kind of problem as declaring the class without a destructor, and for the same fundamental reason.
    // with '=default' is definition, without '=default' is declarations.
    
    Widget2(const Widget2&);
    Widget2& operator=(const Widget2&);
    
private:
    struct Impl;  // declaration, not definition. It is called imcomplete type
                  // Move the detail member out of header file, is able to move the dependency of detail type.
                // so other file, include 'Widget' doesn't need to include detial dependency files.
    std::unique_ptr<Impl> impl;
};

// here is cpp implemation file. 'widget2.cpp'


struct Widget2::Impl {
    std::string name;
    std::vector<int> numbers;
};

Widget2::Widget2() : impl(std::make_unique<Widget2::Impl>()){}

Widget2::~Widget2() = default; // Dctor made by Compilor is good enough. It shows here because if we let Compilor add default one, it will put it into 'inline', other files, place destruct Widget2 instance.
                            // ** it will make unique_ptr call default deleter, which has static_assert to check if type is incomplete type. Then report error.

Widget2::Widget2(Widget2&&) = default;
Widget2& Widget2::operator=(Widget2&&) = default;
// The Pimpl Idiom is a way to reduce compilation dependencies between a class’s implementation and the class’s clients, but, conceptually, use of the idiom doesn’t change what the class represents.

// The original Widget class contained std::string, std::vector, and Gadget data members, and, assuming that Gadgets, like std::strings and std::vectors, can be copied, it would make sense for Widget to support the copy operations.
// We have to write these functions ourselves, because
//      (1) compilers won’t generate copy operations for classes with move-only types like std::unique_ptr and
//      (2) even if they did, the generated functions would copy only the std::unique_ptr (i.e., perform a shallow copy), and we want to copy what the pointer points to (i.e., perform a deep copy).

Widget2::Widget2(const Widget2& lhs)
: impl(std::make_unique<Impl>(*lhs.impl))
{}

Widget2& Widget2::operator=(const Widget2& lhs) {
    *impl = *lhs.impl;
    return *this;
}


void test_piml() {
    
    
    
}
