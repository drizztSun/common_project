#include <stdlib.h>
#include <iostream>
#include <future>
#include <vector>
#include <atomic>

using namespace std;

/*
 
    The Concurrency API
 
 
 
 
 */


/*
 

    Item 35: Prefer task-based programming to thread- based.
 
 Things to Remember
 • The std::thread API offers no direct way to get return values from asynchronously run functions, and if those functions throw, the program is terminated.
 • Thread-based programming calls for manual management of thread exhaustion, oversubscription, load balancing, and adaptation to new platforms.
 • Task-based programming via std::async with the default launch policy handles most of these issues for you.
 
 In the Items that follow, bear in mind that the Standard Library has two templates for futures: std::future and std::shared_future.
 In many cases, the distinction is not important, so I often simply talk about futures, by which I mean both kinds.
 
 int doAsyncWork();
 
 ** thread-based approach:
 
    std::thread(doAsyncWork);
 
 ** task-based appoatch:
 
    auto fut = std::async(doAsyncWork);  / fut is a "future" obj
 
 
    # The task-based approach is typically superior to its thread-based counterpart, and the tiny amount of code we’ve seen already demonstrates some reasons why.
 
        1) With the task-based approach, it’s easy, because the future returned from std::async offers the get function. The get function is even more important if doAsyncWork emits an exception,
            because get provides access to that, too.
        2) With the thread-based approach, if doAsyncWork throws, the program dies (via a call to std::terminate).
 
    A more fundamental difference between thread-based and task-based programming is the higher level of abstraction that task-based embodies.
        It frees you from the details of thread management, an observation that reminds me that I need to summa‐ rize the three meanings of “thread” in concurrent C++ software:
    
            • Hardware threads are the threads that actually perform computation. Contempo‐ rary machine architectures offer one or more hardware threads per CPU core.
            
            • Software threads (also known as OS threads or system threads) are the threads that the operating system1 manages across all processes and schedules for execu‐ tion on hardware threads.
                    It’s typically possible to create more software threads than hardware threads, because when a software thread is blocked (e.g., on I/O or waiting for a mutex or condition variable), throughput can be improved by exe‐ cuting other, unblocked, threads.
            
            • std::threads are objects in a C++ process that act as handles to underlying software threads. Some std::thread objects represent “null” handles, i.e., corre‐ spond to no software thread, because they’re in a default-constructed state (hence have no function to execute), have been moved from (the moved-to std::thread then acts as the handle to the underlying software thread), have been joined (the function they were to run has finished), or have been detached (the connection between them and their underlying software thread has been severed).
 
    Software threads are a limited resource. If you try to create more than the system can provide, a std::system_error exception is thrown. This is true even if the function you want to run can’t throw.
    
    Even if you don’t run out of threads, you can have trouble with oversubscription. That’s when there are more ready-to-run (i.e., unblocked) software threads than hardware threads.
    When that happens, the thread scheduler (typically part of the OS) time-slices the software threads on the hardware. When one thread’s time-slice is finished and another’s begins, a context switch is performed.
    Such context switches increase the overall thread management overhead of the system,
        and they can be particularly costly when the hardware thread on which a software thread is scheduled is on a different core than was the case for the software thread during its last time-slice.
     In that case,
        (1) the CPU caches are typically cold for that software thread (i.e., they contain little data and few instructions useful to it) and
        (2) the running of the “new” software thread on that core “pollutes” the CPU caches for “old” threads that had been running on that core and are likely to be scheduled to run there again.
 
    Avoiding oversubscription is difficult, because the optimal ratio of software to hard‐ ware threads depends on how often the software threads are runnable, and that can change dynamically, e.g., when a program goes from an I/O-heavy region to a computation-heavy region.
    The best ratio of software to hardware threads is also dependent on the cost of context switches and how effectively the software threads use the CPU caches. Furthermore, the number of hardware threads and the details of the CPU caches
    (e.g., how large they are and their relative speeds) depend on the machine architecture, so even if you tune your application to avoid oversubscription
    (while still keeping the hardware busy) on one platform, there’s no guarantee that your solution will work well on other kinds of machines.
 
    With std::async, responsiveness on a GUI thread can still be problematic, because the scheduler has no way of knowing which of your threads has tight responsiveness requirements.
    In that case, you’ll want to pass the std::launch::async launch pol‐ icy to std::async. That will ensure that the function you want to run really executes on a different thread (see Item 36).

 
    Compared to thread-based programming, a task-based design spares you the travails of manual thread management, and it provides a natural way to examine the results of asynchronously executed functions (i.e., return values or exceptions).
    Nevertheless, there are some situations where using threads directly may be appropriate. They include:
    • You need access to the API of the underlying threading implementation. The C++ concurrency API is typically implemented using a lower-level platform- specific API, usually pthreads or Windows’ Threads. Those APIs are currently richer than what C++ offers. (For example, C++ has no notion of thread priori‐ ties or affinities.) To provide access to the API of the underlying threading implementation, std::thread objects typically offer the native_handle mem‐ ber function. There is no counterpart to this functionality for std::futures (i.e., for what std::async returns).
    • You need to and are able to optimize thread usage for your application. This could be the case, for example, if you’re developing server software with a known execution profile that will be deployed as the only significant process on a machine with fixed hardware characteristics.
    • You need to implement threading technology beyond the C++ concurrency API, e.g., thread pools on platforms where your C++ implementations don’t offer them.
    These are uncommon cases, however. Most of the time, you should choose task- based designs instead of programming with threads.
 
 */


/*
 
            Item 36: Specify std::launch::async if asynchronicity is essential.
 
    Things to Remember
    • The default launch policy for std::async permits both asynchronous and synchronous task execution.
    • This flexibility leads to uncertainty when accessing thread_locals, implies that the task may never execute, and affects program logic for timeout-based wait calls.
    • Specify std::launch::async if asynchronous task execution is essential.
 
    
    But that’s not necessarily what you’re asking std::async to do. You’re really requesting that the function be run in accord with a std::async launch policy. There are two standard policies, each
    represented by an enumerator in the std::launch scoped enum. (See Item 10 for information on scoped enums.) Assuming a function f is passed to std::async for execution,
 
    • The std::launch::async launch policy means that f must be run asynchro‐ nously, i.e., on a different thread.
 
    • The std::launch::deferred launch policy means that f may run only when get or wait is called on the future returned by std::async.
        That is, f’s execu‐ tion is deferred until such a call is made. When get or wait is invoked, f will execute synchronously, i.e., the caller will block until f finishes running. If nei‐ ther get nor wait is called, f will never run.
 
 
    But using std::async with the default launch policy has some interesting implications. Given a thread t executing this statement,
 
        auto fut = std::async(f);   // run f using default launch policy
    
        • It’s not possible to predict whether f will run concurrently with t, because f might be scheduled to run deferred.
        • It’s not possible to predict whether f runs on a thread different from the thread invoking get or wait on fut. If that thread is t, the implication is that it’s not possible to predict whether f runs on a thread different from t.
        • It may not be possible to predict whether f runs at all, because it may not be possible to guarantee that get or wait will be called on fut along every path through the program.
 
    The default launch policy’s scheduling flexibility often mixes poorly with the use of thread_local variables, because it means that if f reads or writes such thread-local storage (TLS), it’s not possible to predict which thread’s variables will be accessed:
 
 
    The upshot of these various considerations is that using std::async with the default launch policy for a task is fine as long as the following conditions are fulfilled:
     • The task need not run concurrently with the thread calling get or wait.
     • It doesn’t matter which thread’s thread_local variables are read or written.
     • Either there’s a guarantee that get or wait will be called on the future returned by std::async or it’s acceptable that the task may never execute.
     • Code using wait_for or wait_until takes the possibility of deferred status into account.
 
    If any of these conditions fails to hold, you probably want to guarantee that std::async will schedule the task for truly asynchronous execution. The way to do that is to pass std::launch::async as the first argument when you make the call:
        auto fut = std::async(std::launch::async, f);       // launch f
                                                            // asynchronously

    In C++14, the ability to deduce reallyAsync’s return type streamlines the function declaration:
    template<typename F, typename... Ts>
    inline
    auto // C++14
    reallyAsync(F&& f, Ts&&... params)
    {
         return std::async(std::launch::async,
                           std::forward<F>(f),
                           std::forward<Ts>(params)...);
    }
    This version makes it crystal clear that reallyAsync does nothing but invoke std::async with the std::launch::async launch policy.
 */

void fout() {
    std::this_thread::sleep_for(1s);
    std::cout << "calling fout " << std::endl;
}

void test_async_launch() {
    
    auto f1 = std::async(fout); // future obj, run fout using default launch policy
    
    auto f2 = std::async(std::launch::async |
                         std::launch::deferred,
                         fout);    // run f either async or defered.

    // The default policy thus permits f to be run either asynchronously or synchronously.
    // As Item 35 points out, this flexibility permits std::async and the thread-management components of the Standard Library to assume responsibility for thread creation and destruction,
    // avoidance of oversubscription, and load balancing. That’s among the things that make concurrent programming with std::async so convenient.

    
    // But using std::async with the default launch policy has some interesting implica‐ tions. Given a thread t executing this statement,
    {
        // The default launch policy’s scheduling flexibility often mixes poorly with the use of thread_local variables,
        // because it means that if f reads or writes such thread-local storage (TLS), it’s not possible to predict which thread’s variables will be accessed:
        auto fut = std::async(fout);    // TLS for f possibly for
                                        // independent thread, but
                                        // possibly for thread
                                        // invoking get or wait on fut
        
        // It also affects wait-based loops using timeouts, because calling wait_for or wait_until on a task (see Item 35) that’s deferred yields the value std::launch::deferred.
        // This means that the following loop, which looks like it should eventually terminate, may, in reality, run forever:
        
        // If f runs concurrently with the thread calling std::async (i.e., if the launch policy chosen for f is std::launch::async), there’s no problem here (assuming f eventually finishes),
        // but if f is deferred, fut.wait_for will always return std:: future_status::deferred. That will never be equal to std::future_status:: ready, so the loop will never terminate.
        while ( fut.wait_for(100ms) != std::future_status::ready) {
            std::cout << "Waiting for future status is ready" << std::endl;
        }
        
    }
    
    {
        // The fix is simple: just check the future corresponding to the std::async call to see whether the task is deferred, and, if so, avoid entering the timeout-based loop. Unfortunately, there’s no direct way to ask a future whether its task is deferred.
        // Instead, you have to call a timeout-based function—a function such as wait_for. In this case, you don’t really want to wait for anything, you just want to see if the return value is std::future_status::deferred,
        // so stifle your mild disbelief at the neces‐ sary circumlocution and call wait_for with a zero timeout:
        auto fut = std::async(fout);
        if (fut.wait_for(0s) == std::future_status::deferred) // // if task is // deferred...
        {
            // ...use wait or get on fut ..., to call f synchronously
            fut.get();
        } else { // task isn't deferred
            while (fut.wait_for(100ms) !=                   // infinite loop not
                            std::future_status::ready) {      // possible (assuming
                                                           // f finishes)
                            // task is neither deferred nor ready,
                            // so do concurrent work until it's ready
                            // fut is ready
                std::cout << "Waiting for future status is ready" << std::endl;
            }
            fut.get();
        }
    }
}

/*
 
        Item 37: Make std::threads unjoinable on all paths.
 
        Things to Remember
        • Make std::threads unjoinable on all paths.
        • join-on-destruction can lead to difficult-to-debug performance anomalies. • detach-on-destruction can lead to difficult-to-debug undefined behavior.
        • Declare std::thread objects last in lists of data members.
 
 
    Every std::thread object is in one of two states: joinable or unjoinable. A joinable std::thread corresponds to an underlying asynchronous thread of execution that is or could be running.
    A std::thread corresponding to an underlying thread that’s blocked or waiting to be scheduled is joinable, for example. std::thread objects cor‐ responding to underlying threads that have run to completion are also considered joinable.
 
    An unjoinable std::thread is what you’d expect: a std::thread that’s not joinable. Unjoinable std::thread objects include:
    • Default-constructed std::threads. Such std::threads have no function to execute, hence don’t correspond to an underlying thread of execution.
    • std::thread objects that have been moved from. The result of a move is that the underlying thread of execution a std::thread used to correspond to (if any) now corresponds to a different std::thread.
    • std::threads that have been joined. After a join, the std::thread object no longer corresponds to the underlying thread of execution that has finished run‐ ning.
    • std::threads that have been detached. A detach severs the connection between a std::thread object and the underlying thread of execution it corre‐ sponds to.
 
    ** One reason a std::thread’s joinability is important is that if the destructor for a joinable thread is invoked, execution of the program is terminated.
 
    *** the std::thread object t will be joinable when its destructor is called at the end of doWork. That would cause program execu‐ tion to be terminated.
    You might wonder why the std::thread destructor behaves this way. It’s because the two other obvious options are arguably worse. They are:
 
    • An implicit join. In this case, a std::thread’s destructor would wait for its underlying asynchronous thread of execution to complete. That sounds reason‐ able, but it could lead to performance anomalies that would be difficult to track down.
    
    • An implicit detach. In this case, a std::thread’s destructor would sever the connection between the std::thread object and its underlying thread of execu‐ tion. The underlying thread would continue to run. This sounds no less reason‐
    able than the join approach, but the debugging problems it can lead to are worse.
 
    The Standardization Committee decided that the consequences of destroying a joina‐ ble thread were sufficiently dire that they essentially banned it (by specifying that destruction of a joinable thread causes program termination).
    This puts the onus on you to ensure that if you use a std::thread object, it’s made unjoinable on every path out of the scope in which it’s defined. But covering every path can be complicated.
    It includes flowing off the end of the scope as well as jump‐ ing out via a return, continue, break, goto or exception. That can be a lot of paths.
 
    Any time you want to perform some action along every path out of a block, the nor‐ mal approach is to put that action in the destructor of a local object.
    Such objects are known as RAII objects, and the classes they come from are known as RAII classes. (RAII itself stands for “Resource Acquisition Is Initialization,” although the crux of the technique is destruction, not initialization).
    RAII classes are common in the Stan‐ dard Library.
 
 
 
 */

/*
 •
 •
 • The constructor accepts only std::thread rvalues, because we want to move the passed-in std::thread into the ThreadRAII object. (Recall that std::thread objects aren’t copyable.)
 • The parameter order in the constructor is designed to be intuitive to callers (specifying the std::thread first and the destructor action second makes more sense than vice versa), but the member initialization list is designed to match the order of the data members’ declarations. That order puts the std::thread object last. In this class, the order makes no difference, but in general, it’s possible for the initialization of one data member to depend on another, and because std::thread objects may start running a function immediately after they are initialized, it’s a good habit to declare them last in a class. That guarantees that at the time they are constructed, all the data members that precede them have already been initialized and can therefore be safely accessed by the asynchro‐ nously running thread that corresponds to the std::thread data member.
 • ThreadRAII offers a get function to provide access to the underlying std::thread object. This is analogous to the get functions offered by the stan‐ dard smart pointer classes that give access to their underlying raw pointers. Pro‐ viding get avoids the need for ThreadRAII to replicate the full std::thread interface, and it also means that ThreadRAII objects can be used in contexts where std::thread objects are required.
 • Before the ThreadRAII destructor invokes a member function on the std::thread object t, it checks to make sure that t is joinable. This is necessary, because invoking join or detach on an unjoinable thread yields undefined behavior. It’s possible that a client constructed a std::thread, created a ThreadRAII object from it, used get to acquire access to t, and then did a move from t or called join or detach on it. Each of those actions would render t unjoinable.
 */
class ThreadRAII {
public:
     enum class DtorAction { join, detach };    // see Item 10 for
                                                // enum class info
     ThreadRAII(std::thread&& t, DtorAction a)  // in dtor, take
        : action(a), t(std::move(t)) {}
     
     ~ThreadRAII() {
        if (t.joinable()) {
            // action a on t
            // see below for
            // joinability test
            if (action == DtorAction::join) {
                t.join();
            } else {
                t.detach();
            }
        }
         
     }
  
    std::thread& get() { return t; }
    
    ThreadRAII(ThreadRAII&&) = default;
    ThreadRAII& operator=(ThreadRAII&&) = default;
     
private:
  DtorAction action;
  std::thread t;
};

/*
 
 
        Item 38: Be aware of varying thread handle destructor behavior.
 
        Things to Remember
        • Future destructors normally just destroy the future’s data members.
        • The final future referring to a shared state for a non-deferred task launched via std::async blocks until the task completes.
 
 
    Item 37 explains that a joinable std::thread corresponds to an underlying system thread of execution. A future for a non-deferred task (see Item 36) has a similar relationship to a system thread.
    As such, both std::thread objects and future objects can be thought of as handles to system threads.
 
    Yet the destructor for a future sometimes behaves as if it did an implicit join, sometimes as if it did an implicit detach, and sometimes neither.
    It never causes program termina‐ tion. This thread handle behavioral bouillabaisse deserves closer examination.
 
    But where is the callee’s result stored? The callee could finish before the caller invokes get on a corresponding future, so the result can’t be stored in the callee’s std::promise.
    That object, being local to the callee, would be destroyed when the callee finished.
    
    The result can’t be stored in the caller’s future, either, because (among other reasons) a std::future may be used to create a std::shared_future
    (thus transferring ownership of the callee’s result from the std::future to the std::shared_future), which may then be copied many times after the original std::future is destroyed.
 

    Because neither objects associated with the callee nor objects associated with the caller are suitable places to store the callee’s result, it’s stored in a location outside both.
    This location is known as the shared state. The shared state is typically repre‐ sented by a heap-based object, but its type, interface, and implementation are not specified by the Standard.
    Standard Library authors are free to implement shared states in any way they like.
 
    The existence of the shared state is important, because the behavior of a future’s destructor—the topic of this Item—is determined by the shared state associated with the future. In particular,
    • The destructor for the last future referring to a shared state for a non- deferred task launched via std::async blocks until the task completes.
                    In essence, the destructor for such a future does an implicit join on the thread on which the asynchronously executing task is running.
 
    • The destructor for all other futures simply destroys the future object. For asynchronously running tasks, this is akin to an implicit detach on the underlying thread.
                For deferred tasks for which this is the final future, it means that the deferred task will never run.
 
 
    The exception to this normal behavior arises only for a future for which all of the following apply:
 
    • It refers to a shared state that was created due to a call to std::async.
    • The task’s launch policy is std::launch::async (see Item 36), either because that was chosen by the runtime system or because it was specified in the call to std::async.
    • The future is the last future referring to the shared state. For std::futures, this will always be the case. For std::shared_futures, if other std::shared_ futures refer to the same shared state as the future being destroyed,
            the future being destroyed follows the normal behavior (i.e., it simply destroys its data members).
 

    The API for futures offers no way to determine whether a future refers to a shared state arising from a call to std::async, so given an arbitrary future object,
    it’s not possible to know whether it will block in its destructor waiting for an asynchronously running task to finish.
 
    only shared states arising from calls to std::async qualify for the special behavior, but there are other ways that shared states get created. One is the use of std::packaged_task.
    A std::packaged_task object prepares a function (or other callable object) for asyn‐ chronous execution by wrapping it such that its result is put into a shared state.
    A future referring to that shared state can then be obtained via std::packaged_task’s get_future function:
 
    
 */

int calculate() { return 1; }

void test_beaware_thread_handle_destructor() {
    
    // At this point, we know that the future fut doesn’t refer to a shared state created by a call to std::async, so its destructor will behave normally.
    std::packaged_task<int()> pt(calculate);
    
    auto fu = pt.get_future();
    
    // Once created, the std::packaged_task pt can be run on a thread. (It could be run via a call to std::async, too, but if you want to run a task using std::async,
    //  there’s little reason to create a std::packaged_task, because std::async does everything std::packaged_task does before it schedules the task for execution.)
    // std::packaged_tasks aren’t copyable, so when pt is passed to the std::thread constructor, it must be cast to an rvalue (via std::move—see Item 23):
    std::thread t(std::move(pt));
        
    /*
     
     The most interesting code here is the “...” that follows creation of the std::thread object t and precedes the end of the block. What makes it interesting is what can happen to t inside the “...” region.
     There are three basic possibilities:
    • Nothing happens to t. In this case, t will be joinable at the end of the scope. That will cause the program to be terminated (see Item 37).
    • A join is done on t. In this case, there would be no need for fut to block in its destructor, because the join is already present in the calling code.
    • A detach is done on t. In this case, there would be no need for fut to detach in its destructor, because the calling code already does that.
     
    In other words, when you have a future corresponding to a shared state that arose due to a std::packaged_task, there’s usually no need to adopt a special destruction policy,
            because the decision among termination, joining, or detaching will be made in the code that manipulates the std::thread on which the std::packaged_task is typically run.
    */
}


/*
 
        Item 39: Consider void futures for one-shot event communication.
    
    Things to Remember
    • For simple event communication, condvar-based designs require a superfluous mutex,
                impose constraints on the relative progress of detecting and reacting tasks, and require reacting tasks to verify that the event has taken place.
    • Designs employing a flag avoid those problems, but are based on polling, not blocking.
    • A condvar and flag can be used together, but the resulting communications mechanism is somewhat stilted.
    • Using std::promises and futures dodges these issues, but the approach uses heap memory for shared states, and it’s limited to one-shot communication.
 
 
    An obvious approach is to use a condition variable (condvar). If we call the task that detects the condition the detecting task and the task reacting to the condition the
    reacting task, the strategy is simple: the reacting task waits on a condition variable, and the detecting thread notifies that condvar when the event occurs. Given
        std::condition_variable cv;         // condvar for event
        std::mutex m;           // mutex for use with cv the code in the detecting task is as simple as simple can be:
                    ... // detect event
        cv.notify_one(); // tell reacting task
 
    If there were multiple reacting tasks to be notified, it would be appropriate to replace notify_one with notify_all, but for now, we’ll assume there’s only one reacting task.
 
    Even if you look past that, there are two other problems you should definitely pay attention to:
    • If the detecting task notifies the condvar before the reacting task waits, the reacting task will hang. In order for notification of a condvar to wake another task, the other task must be waiting on that condvar.
                If the detecting task hap‐ pens to execute the notification before the reacting task executes the wait, the reacting task will miss the notification, and it will wait forever.
 
    • The wait statement fails to account for spurious wakeups. A fact of life in threading APIs (in many languages—not just C++) is that code waiting on a con‐ dition variable may be awakened even if the condvar wasn’t notified.
        Such awakenings are known as spurious wakeups. Proper code deals with them by confirming that the condition being waited for has truly occurred, and it does this as its first action after waking.
        The C++ condvar API makes this exception‐ ally easy, because it permits a lambda (or other function object) that tests for the waited-for condition to be passed to wait. That is, the wait call in the reacting task could be written like this:
            cv.wait(lk,
            []{ return whether the event has occurred; });
    Taking advantage of this capability requires that the reacting task be able to determine whether the condition it’s waiting for is true.
    But in the scenario we’ve been considering, the condition it’s waiting for is the occurrence of an event that the detecting thread is responsible for recognizing.
    The reacting thread may have no way of determining whether the event it’s waiting for has taken place. That’s why it’s waiting on a condition variable!
    
    *** What we need for the std::promise and future templates is a type that indicates that no data is to be conveyed across the communications channel.
    That type is void. The detecting task will thus use a std::promise<void>, and the react‐ ing task a std::future<void> or std::shared_future<void>.
 
    *** Perhaps more importantly, a std::promise may be set only once. The communica‐ tions channel between a std::promise and a future is a one-shot mechanism: it can’t
    be used repeatedly. This is a notable difference from the condvar- and flag-based designs, both of which can be used to communicate multiple times. (A condvar can be repeatedly notified, and a flag can always be cleared and set again.)
 
    *** The C++ concurrency API offers no way to do those things, but std::thread objects offer the native_handle member function, the result of which is intended to give you access to the platform’s underlying threading API
    (usually POSIX threads or Windows threads). The lower-level API often makes it possible to configure thread characteristics such as priority and affinity.
 
    
 */
void react() {}

void test_void_future_for_one_shot_event() {
    
    
    // If there were multiple reacting tasks to be notified, it would be appropriate to replace notify_one with notify_all, but for now, we’ll assume there’s only one reacting task.
    // The code for the reacting task is a bit more complicated, because before calling wait on the condvar, it must lock a mutex through a std::unique_lock object.
    // (Locking a mutex before waiting on a condition variable is typical for threading libraries. The need to lock the mutex through a std::unique_lock object is simply part of the C++11 API.) Here’s the conceptual approach:
    
    
    // An alternative is to avoid condition variables, mutexes, and flags by having the react‐ ing task wait on a future that’s set by the detecting task. This may seem like an odd idea.
    // After all, Item 38 explains that a future represents the receiving end of a com‐ munications channel from a callee to a (typically asynchronous) caller, and here there’s no callee-caller relationship between the detecting and reacting tasks.
    
    // How‐ ever, Item 38 also notes that a communications channel whose transmitting end is a std::promise and whose receiving end is a future can be used for more than just callee-caller communication.
    // Such a communications channel can be used in any sit‐ uation where you need to transmit information from one place in your program to another.
    
    // The design is simple. The detecting task has a std::promise object (i.e., the writing end of the communications channel), and the reacting task has a corresponding future.
    
    // When the detecting task sees that the event it’s looking for has occurred, it sets the std::promise (i.e., writes into the communications channel). Meanwhile, the reacting task waits on its future.
    // That wait blocks the reacting task until the std::promise has been set.
    
    // Now, both std::promise and futures (i.e., std::future and std::shared_future) are templates that require a type parameter. That parameter indicates the type of data to be transmitted through the communications channel.
    // In our case, however, there’s no data to be conveyed. The only thing of interest to the reacting task is that its future has been set.
    
    // The detecting task will set its std::promise<void> when the event of interest occurs, and the reacting task will wait on its future.
    // Even though the reacting task won’t receive any data from the detecting task, the communications channel will permit the reacting task to know when the detecting task has “written” its void data by calling set_value on its std::promise.
    
    std::promise<void> p;  // promise for
                           // communications channel
    
    {
        //  the detecting task’s code is trivial,
        
        p.set_value();
    }
    
    {
        // the reacting task’s code is equally simple:
        p.get_future().wait();   // wait on future
                                // corresponding to p
                                // react to event
    }
    
    // Like the approach using a flag, this design requires no mutex, works regardless of whether the detecting task sets its std::promise before the reacting task waits, and is immune to spurious wakeups.
    // (Only condition variables are susceptible to that problem.) Like the condvar-based approach, the reacting task is truly blocked after making the wait call, so it consumes no system resources while waiting.
    // Perfect, right?

    // Item 38 explains that between a std::promise and a future is a shared state, and shared states are typically dynamically allocated. You should therefore assume that this design incurs the cost of heap-based allocation and deallocation.
    
    
    
    {
      ThreadRAII tr(            // use RAII object
        std::thread([&p]
                    {
                        p.get_future().wait();
                        react();
                    }),
         ThreadRAII::DtorAction::join);  // risky! (see below)
                    
                        // thread inside tr
        // ...                // is suspended here
        
        
         p.set_value();     // unsuspend thread
                            // inside tr
                        
        // ...
                 
        // This looks safer than it is. The problem is that if in the first “...” region (the one with the “thread inside tr is suspended here” comment), an exception is emitted,
        // set_value will never be called on p. That means that the call to wait inside the lambda will never return.
        // That, in turn, means that the thread running the lambda will never finish, and that’s a problem, because the RAII object tr has been config‐ ured to perform a join on that thread in tr’s destructor.
        // In other words, if an excep‐ tion is emitted from the first “...” region of code, this function will hang, because tr’s destructor will never complete.
    }
    
    {
        // It’s a simple generalization, because the key is to use std::shared_futures instead of a std::future in the react code.
        // Once you know that the std::future’s share member function transfers ownership of its shared state to the std::shared_future object produced by share, the code nearly writes itself.
        // The only subtlety is that each reacting thread needs its own copy of the std::shared_future that refers to the shared state, so the std::shared_future obtained from share is captured by value by the lambdas running on the reacting threads:
        

        auto sf = p.get_future().share();   // container for
                                            // reacting threads
        
        std::vector<std::thread> vt;         // container for
                                            // reacting threads
        
        
        for (int i = 0; i < 5; ++i) {
            vt.emplace_back([sf]{
                    sf.wait();
                    react();
            });
        }
        
    }
}

/*
 
            Item 40: Use std::atomic for concurrency, volatile for special memory.
 
    Things to Remember
    • std::atomic is for data accessed from multiple threads without using mutexes. It’s a tool for writing concurrent software.
    • volatile is for memory where reads and writes should not be optimized away. It’s a tool for working with special memory.
 
    The C++ feature that programmers sometimes confuse volatile with—the feature that definitely does belong in this chapter—is the std::atomic template.
    Instantiations of this template (e.g., std::atomic<int>, std::atomic<bool>, std::atomic<Widget*>, etc.) offer operations that are guaranteed to be seen as atomic by other threads.
    Once a std::atomic object has been constructed, operations on it behave as if they were inside a mutex-protected critical section,
    but the operations are generally implemented using special machine instructions that are more efficient than would be the case if a mutex were employed.
 
    but all compilers see is a pair of assignments to independent variables.
    As a general rule, compilers are permitted to reorder such unrelated assignments. That is, given this sequence of assignments (where a, b, x, and y correspond to independent variables),
 
    the use of std::atomics imposes restrictions on how code can be reordered, and one such restriction is that no code that,
    in the source code, precedes a write of a std::atomic variable may take place (or appear to other cores to take place) afterwards.
 
    These two issues—no guarantee of operation atomicity and insufficient restrictions on code reordering—explain why volatile’s not useful for concurrent programming, but it doesn’t explain what it is useful for.
    In a nutshell, it’s for telling compilers that they’re dealing with memory that doesn’t behave normally.
    
    “Normal” memory has the characteristic that if you write a value to a memory loca‐ tion, the value remains there until something overwrites it.
 
    *** volatile is the way we tell compilers that we’re dealing with special memory. Its meaning to compilers is “Don’t perform any optimizations on operations on this memory.” So if x corresponds to special memory, it’d be declared volatile:
 
    ***  I remarked earlier that one of the best things about std::atomics is that all their operations are atomic, but in order for the copy construction of y from x to be atomic, compilers would have to generate code to read x and write y in a single atomic operation.
        Hardware generally can’t do that, so copy construction isn’t sup‐ ported for std::atomic types. Copy assignment is deleted for the same reason, which is why the assignment from x to y won’t compile.
        (The move operations aren’t explicitly declared in std::atomic, so, per the rules for compiler-generated special functions described in Item 17, std::atomic offers neither move construction nor move assignment.)
 
    
 
 
     The result, as you can see, reads from x only once, and that’s the kind of optimization that must be avoided when dealing with special memory. (The optimization isn’t per‐ mitted for volatile variables.)
     The situation should thus be clear:
     • std::atomic is useful for concurrent programming, but not for accessing special memory.
     • volatile is useful for accessing special memory, but not for concurrent programming.

     Because std::atomic and volatile serve different purposes, they can even be used together:
     volatile std::atomic<int> vai; // operations on vai are
                                    // atomic and can't be
                                    // optimized away
 
     This could be useful if vai corresponded to a memory-mapped I/O location that was concurrently accessed by multiple threads.
     As a final note, some developers prefer to use std::atomic’s load and store mem‐ ber functions even when they’re not required, because it makes explicit in the source code that the variables involved aren’t “normal.” Emphasizing that fact isn’t unrea‐ sonable. Accessing a std::atomic is typically much slower than accessing a non- std::atomic, and we’ve already seen that the use of std::atomics prevents compilers from performing certain kinds of code reorderings that would otherwise be permitted.
 
 
 As a final note, some developers prefer to use std::atomic’s load and store mem‐ ber functions even when they’re not required, because it makes explicit in the source code that the variables involved aren’t “normal.” Emphasizing that fact isn’t unrea‐ sonable. Accessing a std::atomic is typically much slower than accessing a non- std::atomic, and we’ve already seen that the use of std::atomics prevents compilers from performing certain kinds of code reorderings that would otherwise be permitted. Calling out loads and stores of std::atomics can therefore help iden‐ tify potential scalability chokepoints. From a correctness perspective, not seeing a call to store on a variable meant to communicate information to other threads (e.g., a flag indicating the availability of data) could mean that the variable wasn’t declared std::atomic when it should have been.
 This is largely a style issue, however, and as such is quite different from the choice between std::atomic and volatile.
 
 */


void test_volatile_for_special_memory() {
    
    std::atomic<int> ai(0); // initialize ai to 0
    
    ai = 10;                // atomically set ai to 10
    
    std::cout << ai;          // atomically read ai's value
    
    // Two aspects of this example are worth noting. First, in the “std::cout<<ai;” state‐ ment, the fact that ai is a std::atomic guarantees only that the read of ai is atomic.
    // There is no guarantee that the entire statement proceeds atomically. Between the time ai’s value is read and operator<< is invoked to write it to the standard output, another thread may have modified ai’s value.
    // That has no effect on the behavior of the statement, because operator<< for ints uses a by-value parameter for the int to output (the outputted value will therefore be the one that was read from ai),
    // but it’s important to understand that what’s atomic in that statement is nothing more than the read of ai.
    
    ++ai;                   // atomically increment ai to 11
    
    --ai;                   // atomically decrement ai to 10
    
    // The second noteworthy aspect of the example is the behavior of the last two state‐ ments—the increment and decrement of ai.
    // These are each read-modify-write (RMW) operations, yet they execute atomically. This is one of the nicest characteris‐ tics of the std::atomic types:
    // once a std::atomic object has been constructed, all member functions on it, including those comprising RMW operations, are guaran‐ teed to be seen by other threads as atomic.
    
    // In contrast, the corresponding code using volatile guarantees virtually "nothing" in a multithreaded context:
    // Each read-modify-write (RMW) operations, But these three operations are not guaranteed to pro‐ ceed atomically for volatile objects, so it’s possible that the component parts of the two increments of vc are interleaved as follows:
    // The use of RMW operations isn’t the only situation where std::atomics comprise a concurrency success story and volatiles suffer failure.
    volatile int vi(0);     // initialize vi to 0
    
    vi = 10;                // set vi to 10
    
    std::cout << vi;        // read vi's value
    
    ++vi;                   // increment vi to 11
    
    --vi;                   // decrement vi to 10
    
    // vi’s final value is therefore 1, even though it was incremented twice.
    
    // Normal memory also has the characteristic that if you write a value to a memory location, never read it, and then write to that memory location again, the first write can be eliminated, because it was never used.
    // So given these two adjacent statements,
    int x = 0;
    x = 10;               // write x
    x = 20;               // write x again
    
    {
        // volatile is the way we tell compilers that we’re dealing with special memory. Its meaning to compilers is “Don’t perform any optimizations on operations on this memory.”
        // So if x corresponds to special memory, it’d be declared volatile:
        volatile int x;
        
        auto y = x;
        // y’s type is auto-deduced, so it uses the rules described in Item 2. Those rules dictate that for the declaration of non-reference non-pointer types (which is the case for y), const and volatile qualifiers are dropped.
        // y’s type is therefore simply int. This means that redundant reads of and writes to y can be eliminated.
        // In the example, compilers must perform both the initialization of and the assignment to y, because x is volatile, so the second read of x might yield a different value from the first one.
        y = x;
        
        x = 10;
        x = 20;
    }
    
    
    {
        // The fact that seemingly redundant loads and dead stores must be preserved when dealing with special memory explains, by the way, why std::atomics are unsuitable for this kind of work.
        // Compilers are permitted to eliminate such redundant opera‐ tions on std::atomics. The code isn’t written quite the same way it is for vola tiles,
        // but if we overlook that for a moment and focus on what compilers are permitted to do, we can say that, conceptually, compilers may take this,
        std::atomic<int> x = 100;
        
        
        // auto y = x;         // conceptually read x (see below)
        // error, That’s because the copy operations for std::atomic are deleted (see Item 11). And with good reason. Consider what would happen if the initialization of y with x compiled.
        //
        
        //y = x;              // conceptually read x again (see below)
        
        //x = 10;             // write x
        //x = 20;             // write x again
        
        //
        
        
        // conceptually read x (see below) // write x
        
        // It’s possible to get the value of x into y, but it requires use of std::atomic’s member functions load and store. The load member function reads a std::atomic’s value atomically, while the store member function writes it atomically.
        // To initialize y with x, followed by putting x’s value in y, the code must be written like this:
        std::atomic<int> y(x.load());
        
        y.store(x.load());
        
        /*
         
         This compiles, but the fact that reading x (via x.load()) is a separate function call from initializing or storing to y makes clear that there is no reason to expect either statement as a whole to execute as a single atomic operation.
         Given that code, compilers could “optimize” it by storing x’s value in a register instead of reading it twice:
         
             register = x.load();               // read x into register
             std::atomic<int> y(register);      // init y with register value
             y.store(register);                 // store register value into y
         
         */
        
        
        
        
    }
}

/*
class Quataoe {};

class Parallel_Qua: public Quataoe{};


class Recangle: public Parallel_Qua {};

class Diamond: public Parallel_Qua {};

class Square: public Recangle, public Diamond {};
*/
