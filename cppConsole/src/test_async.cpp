#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
#include <cmath>



/*
    
    Async C++
 
 template< class Function, class... Args>
 std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
     async( Function&& f, Args&&... args );
 (since C++11)
 (until C++17)
 template< class Function, class... Args>
 std::future<std::invoke_result_t<std::decay_t<Function>,
                                  std::decay_t<Args>...>>
     async( Function&& f, Args&&... args );
 (since C++17)
 (until C++20)
 template< class Function, class... Args>
 [[nodiscard]]
 std::future<std::invoke_result_t<std::decay_t<Function>,
                                  std::decay_t<Args>...>>
     async( Function&& f, Args&&... args );
 (since C++20)
 (2)
 template< class Function, class... Args >
 std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
     async( std::launch policy, Function&& f, Args&&... args );
 (since C++11)
 (until C++17)
 template< class Function, class... Args >
 std::future<std::invoke_result_t<std::decay_t<Function>,
                                  std::decay_t<Args>...>>
     async( std::launch policy, Function&& f, Args&&... args );
 (since C++17)
 (until C++20)
 template< class Function, class... Args >
 [[nodiscard]]
 std::future<std::invoke_result_t<std::decay_t<Function>,
                                  std::decay_t<Args>...>>
     async( std::launch policy, Function&& f, Args&&... args );
 
 
 The function template async runs the function f asynchronously (potentially in a separate thread which may be part of a thread pool) and returns a std::future that will eventually hold the result of that function call.

 1) Behaves as if (2) is called with policy being std::launch::async | std::launch::deferred. In other words, f may be executed in another thread or it may be run synchronously when the resulting std::future is queried for a value.
 2) Calls a function f with arguments args according to a specific launch policy policy:
 If the async flag is set (i.e. (policy & std::launch::async) != 0), then async executes the callable object f on a new thread of execution (with all thread-locals initialized) as if spawned by std::thread(std::forward<F>(f), std::forward<Args>(args)...), except that if the function f returns a value or throws an exception, it is stored in the shared state accessible through the std::future that async returns to the caller.
 If the deferred flag is set (i.e. (policy & std::launch::deferred) != 0), then async converts f and args... the same way as by std::thread constructor, but does not spawn a new thread of execution. Instead, lazy evaluation is performed: the first call to a non-timed wait function on the std::future that async returned to the caller will cause the copy of f to be invoked (as an rvalue) with the copies of args... (also passed as rvalues) in the current thread (which does not have to be the thread that originally called std::async). The result or exception is placed in the shared state associated with the future and only then it is made ready. All further accesses to the same std::future will return the result immediately.
 If both the std::launch::async and std::launch::deferred flags are set in policy, it is up to the implementation whether to perform asynchronous execution or lazy evaluation.
 If neither std::launch::async nor std::launch::deferred, nor any implementation-defined policy flag is set in policy, the behavior is undefined.
 
 (since C++14)
 In any case, the call to std::async synchronizes-with (as defined in std::memory_order) the call to f, and the completion of f is sequenced-before making the shared state ready. If the async policy is chosen, the associated thread completion synchronizes-with the successful return from the first function that is waiting on the shared state, or with the return of the last function that releases the shared state, whichever comes first.
 
 Parameters
 f    -
        Callable object to call
 
 args...    -
        parameters to pass to f
 
 policy    -
        bitmask value, where individual bits control the allowed methods of execution
 
 Bit    Explanation
        std::launch::async    enable asynchronous evaluation   ***  In that case, you’ll want to pass the std::launch::async launch pol‐ icy to std::async. That will ensure that the function you want to run really executes on a different thread
        std::launch::deferred    enable lazy evaluation
 
 
    • The std::launch::async launch policy means that f must be run asynchro‐ nously, i.e., on a different thread.
    • The std::launch::deferred launch policy means that f may run only when get or wait is called on the future returned by std::async.2
 
 
 auto fut1 = std::async(f);                     // run f using, default launch policy
 auto fut2 = std::async(std::launch::async | std::launch::deferred, f); // run f either async or  deferred


 Type requirements
 -Function, Args must meet the requirements of MoveConstructible.
 Return value
 std::future referring to the shared state created by this call to std::async.

 Exceptions
 Throws std::system_error with error condition std::errc::resource_unavailable_try_again if the launch policy equals std::launch::async and the implementation is unable to start a new thread (if the policy is async|deferred or has additional bits set, it will fall back to deferred or the implementation-defined policies in this case), or std::bad_alloc if memory for the internal data structures could not be allocated.

 Notes
 The implementation may extend the behavior of the first overload of std::async by enabling additional (implementation-defined) bits in the default launch policy.

 Examples of implementation-defined launch policies are the sync policy (execute immediately, within the async call) and the task policy (similar to async, but thread-locals are not cleared)

 If the std::future obtained from std::async is not moved from or bound to a reference, the destructor of the std::future will block at the end of the full expression until the asynchronous operation completes, essentially making code such as the following synchronous:

 std::async(std::launch::async, []{ f(); }); // temporary's dtor waits for f()
 std::async(std::launch::async, []{ g(); }); // does not start until f() completes
 (note that the destructors of std::futures obtained by means other than a call to std::async never block)
 
 */


/*
        std::launch
 
 Defined in header <future>
 enum class launch :  {
     async =    ,
     deferred = ,
 };
 
 (since C++11)
 Specifies the launch policy for a task executed by the std::async function. std::launch is an enumeration used as BitmaskType.

 The following constants denoting individual bits are defined by the standard library:

 Constant    Explanation
 std::launch::async                     a new thread is launched to execute the task asynchronously
 std::launch::deferred                  the task is executed on the calling thread the first time its result is requested (lazy evaluation)
 
 In addition, implementations are allowed to:

 • define additional bits and bitmasks to specify restrictions on task interactions applicable to a subset of launch policies, and
 • enable those additional bitmasks for the first (default) overload of std::async.
 
 */


std::mutex m;
struct X {
    void foo(int i, const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << ' ' << i << '\n';
    }
    void bar(const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << '\n';
    }
    int operator()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};
 
template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);
 
    RandomIt mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                             parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
 
void test_async()
{
    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
 
    X x;
    // Calls (&x)->foo(42, "Hello") with default policy:
    // may print "Hello 42" concurrently or defer execution
    auto a1 = std::async(&X::foo, &x, 42, "Hello");
    // Calls x.bar("world!") with deferred policy
    // prints "world!" when a2.get() or a2.wait() is called
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
    // Calls X()(43); with async policy
    // prints "43" concurrently
    auto a3 = std::async(std::launch::async, X(), 43);
    
    
    if (a1.wait_for(std::chrono::seconds(1)) == std::future_status::deferred) {
        std::cout << "wait_for a deferred one" << std::endl;
    } else {
        while (a1.wait_for(std::chrono::seconds(1)) != std::future_status::ready) {
            std::cout << "You entered : " << 1 << std::endl;
        }
    }
    
    a2.wait();                     // prints "world!"
    std::cout << a3.get() << '\n'; // prints "53"
} // if a1 is not done at this point, destructor of a1 prints "Hello 42" here



/*
                std::promise
 

 
 Defined in header <future>
 template< class R > class promise;              (1)    (since C++11)

 template< class R > class promise<R&>;          (2)    (since C++11)

 template<>          class promise<void>;        (3)    (since C++11)

 1) base template
 2) non-void specialization, used to communicate objects between threads
 3) void specialization, used to communicate stateless events
 The class template std::promise provides a facility to store a value or an exception that is later acquired asynchronously via a std::future object created by the std::promise object.
 Note that the std::promise object is meant to be used only once.

 Each promise is associated with a shared state, which contains some state information and a result which may be not yet evaluated, evaluated to a value (possibly void) or evaluated to an exception.
 A promise may do three things with the shared state:

      • make ready: the promise stores the result or the exception in the shared state. Marks the state ready and unblocks any thread waiting on a future associated with the shared state.
      • release: the promise gives up its reference to the shared state. If this was the last such reference, the shared state is destroyed. Unless this was a shared state created by std::async which is not yet ready, this operation does not block.
      • abandon: the promise stores the exception of type std::future_error with error code std::future_errc::broken_promise, makes the shared state ready, and then releases it.
 
 The promise is the "push" end of the promise-future communication channel:
 the operation that stores a value in the shared state synchronizes-with (as defined in std::memory_order) the successful return from any function that is waiting on the shared state (such as std::future::get).
 Concurrent access to the same shared state may conflict otherwise: for example multiple callers of std::shared_future::get must either all be read-only or provide external synchronization.

 Member functions:
 
 (constructor)       constructs the promise object
                     (public member function)
  
 (destructor)        destructs the promise object
                     (public member function)
  
 operator=           assigns the shared state
                    (public member function)
  
 swap                swaps two promise objects
                     (public member function)
 
 Getting the result:
 
 get_future          swaps two promise objects
                    (public member function)
  

 Setting the result:
 
 set_value           sets the result to specific value
                    (public member function)
  
 set_value_at_thread_exit            sets the result to specific value
                                    (public member function)

 set_exception           sets the result to specific value
                        (public member function)

 set_exception_at_thread_exit        sets the result to specific value
                                    (public member function)

 Non-member functions:
 std::swap(std::promise)             specializes the std::swap algorithm
                                     (function template)
  
 Helper classes
 std::uses_allocator<std::promise>       specializes the std::uses_allocator type trait
                                        (class template specialization)

 */

void print_int(std::future<int>& fut) {
    int x = fut.get();
    std::cout << "Value: " << x << std::endl;
}

void test_promise() {
    
    std::promise<int> prom; // create promise
    
    std::future<int> fut = prom.get_future();
    
    std::thread th1 (print_int, std::ref(fut));
    
    prom.set_value(10);
    
    th1.join();
}

void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);  // Notify future
}
 
void do_work(std::promise<void> barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();
}
 
void test_promise2()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                            std::move(accumulate_promise));
 
    // future::get() will wait until the future has a valid result and retrieves it.
    // Calling wait() before get() is not needed
    //accumulate_future.wait();  // wait for result
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join();  // wait for thread completion
 
    // Demonstrate using promise<void> to signal state between threads.
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();
    new_work_thread.join();
}
/*
        std::packaged_task
 
 Defined in header <future>
 template< class > class packaged_task;     //not defined       (1)    (since C++11)
 
 template< class R, class ...Args >
 class packaged_task<R(Args...)>;           // (2)    (since C++11)
 
 The class template std::packaged_task wraps any Callable target (function, lambda expression, bind expression, or another function object) so that it can be invoked asynchronously.
 Its return value or exception thrown is stored in a shared state which can be accessed through std::future objects.

 Just like std::function, std::packaged_task is a polymorphic, allocator-aware container: the stored callable target may be allocated on heap or with a provided allocator.

 (until C++17)
 Member functions
    (constructor)           constructs the task object
                            (public member function)
    (destructor)             destructs the task object
                            (public member function)
  

    operator=                   moves the task object
                                (public member function)
  

    valid                    checks if the task object has a valid function
                            (public member function)

    swap                     swaps two task objects
                            (public member function)
  
 Getting the result
  
    get_future               returns a std::future associated with the promised result
                            (public member function)
  

 Execution
    
    operator()               executes the function
                            (public member function)
  

 make_ready_at_thread_exit       executes the function ensuring that the result is ready only once the current thread exits
                                 (public member function)
  
 reset                           resets the state abandoning any stored results of previous executions
                                 (public member function)
  
 Non-member functions
 
    std::swap(std::packaged_task)        specializes the std::swap algorithm
                                          (function template)
   
 (C++11)
  

 Helper classes
 
        std::uses_allocator<std::packaged_task>   (C++11)(until C++17)         specializes the std::uses_allocator type trait
                                                        (class template specialization)

 
 */


// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) { return std::pow(x,y); }
 
void task_lambda()
{
    std::packaged_task<int(int,int)> task([](int a, int b) {
        return std::pow(a, b);
    });
    std::future<int> result = task.get_future();
 
    task(2, 9);
 
    std::cout << "task_lambda:\t" << result.get() << '\n';
}
 
void task_bind()
{
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();
 
    task();
 
    std::cout << "task_bind:\t" << result.get() << '\n';
}
 
void task_thread()
{
    std::packaged_task<int(int,int)> task(f);
    std::future<int> result = task.get_future();
 
    std::thread task_td(std::move(task), 2, 10);
    task_td.join();
 
    std::cout << "task_thread:\t" << result.get() << '\n';
}
 
void test_packed_task()
{
    task_lambda();
    task_bind();
    task_thread();
}


/*
 
 std::swap(std::promise)
 
 Defined in header <future>
 
 template< class R >
 void swap( promise<R> &lhs, promise<R> &rhs ) noexcept;        (since C++11)
 
 Specializes the std::swap algorithm for std::promise. Exchanges the shared state of lhs with that of rhs. Effectively calls lhs.swap(rhs).

 Parameters
        lhs, rhs    -    promises whose states to swap

 
 
 std::swap(std::packaged_task)

 template< class Function, class... Args >
 void swap( packaged_task<Function(Args...)> &lhs,  packaged_task<Function(Args...)> &rhs ) noexcept;           (since C++11)
 
 Specializes the std::swap algorithm for std::packaged_task. Exchanges the state of lhs with that of rhs. Effectively calls lhs.swap(rhs).

 Parameters
 lhs, rhs    -    packaged tasks whose states to swap
 
 
 */



void test_swap() {
    
    std::promise<int> a, b;
    
    std::swap(a, b);
    
    std::packaged_task<int(int,int)> task1([](int a, int b) {
        return std::pow(a, b);
    });
    
    std::packaged_task<int(int,int)> task2(f);
    
    std::swap(task1, task2);
}
