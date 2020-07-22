#include <iostream>
#include <future>
#include <thread>
#include <chrono>

#include <random>
#include <set>
#include <algorithm>
#include <iterator>
/**

std::future
  C++  Thread support library std::future

 Defined in header <future>

template< class T > class future; (1) (since C++11)

template< class T > class future<T&>;  (2)	(since C++11)

template<>          class future<void>; (3)	(since C++11)

The class template std::future provides a mechanism to access the result of asynchronous operations:

An asynchronous operation (created via std::async, std::packaged_task, or std::promise) 
can provide a std::future object to the creator of that asynchronous operation.

The creator of the asynchronous operation can then use a variety of methods to query, wait for, or extract a value from the std::future. 
These methods may block if the asynchronous operation has not yet provided a value.

When the asynchronous operation is ready to send a result to the creator, 
it can do so by modifying shared state (e.g. std::promise::set_value) that is linked to the creator's std::future.

Note that std::future references shared state that is not shared with any other asynchronous return objects (as opposed to std::shared_future).

 
 class template
 <future>
 std::future
 template <class T>  future;
 template <class R&> future<R&>;     // specialization : T is a reference type (R&)
 template <>         future<void>;   // specialization : T is void
 Future
 A future is an object that can retrieve a value from some provider object or function, properly synchronizing this access if in different threads.

 "Valid" futures are future objects associated to a shared state, and are constructed by calling one of the following functions:
 async
 promise::get_future
 packaged_task::get_future

 future objects are only useful when they are valid. Default-constructed future objects are not valid (unless move-assigned a valid future).

 Calling future::get on a valid future blocks the thread until the provider makes the shared state ready (either by setting a value or an exception to it). This way, two threads can be synchronized by one waiting for the other to set a value.

 The lifetime of the shared state lasts at least until the last object with which it is associated releases it or is destroyed. Therefore, if associated to a future, the shared state can survive the object from which it was obtained in the first place (if any).

 Member functions
 (constructor)      Construct future (public member function )
 (destructor)        Destroy future (public member function )
 operator=          Move-assign future (public member function )
 share                  Get shared future (public member function )
 get                        Get value (public member function )
 valid                      Check for valid shared state (public member function )
 wait                       Wait for ready (public member function )
 wait_for               Wait for ready during time span (public member function )
 wait_until             Wait for ready until time point (public member function )
 
*/

void test_future() {

	// future from a package_task

	std::packaged_task<int()> task([] {return 7; }); // wrap the function
	std::future<int> f1 = task.get_future(); // get a future
	std::thread t(std::move(task)); // launch a thread

	// future from an async()
	std::future<int> f2 = std::async(std::launch::async, [] {return 8; });

	// future from an promise
	std::promise<int> p;
	std::future<int> f3 = p.get_future();
	std::thread([&p] {p.set_value_at_thread_exit(9); }).detach();

	std::cout << "Waiting ... " << std::flush;
	f1.wait();
	f2.wait();
	f3.wait();

	std::cout << "Done \n Result are"
			  << f1.get() << ' '<< f2.get() << ' ' << f3.get() << '\n';

	t.join();

	// Waiting...Done!
	// Results are : 7 8 9
}

void test_future1() {

	std::future<int> future = std::async(std::launch::async, []() {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
	});

	std::cout << "Waiting ... \n";
	std::future_status status;

	do {
		status = future.wait_for(std::chrono::seconds(1));

		if (status == std::future_status::deferred) {
			std::cout << "deferred \n";
		}
		else if (status == std::future_status::timeout) {
			std::cout << "timeout \n";
		}
		else if (status == std::future_status::ready) {
			std::cout << "ready \n";
		}

	} while (status != std::future_status::ready);

	std::cout << "result is " << future.get() << "\n";

	// waiting...
	//	timeout
	//	timeout
	//	ready!
	//	result is 8
}


void test_future2() {

	std::chrono::system_clock::time_point two_seconds_passed
		= std::chrono::system_clock::now() + std::chrono::seconds(2);

	// Make a future that takes 1 second to completed
	std::promise<int> d;
	std::future<int> f_completes = d.get_future();
	std::thread([](std::promise<int> p) 
				{
					std::this_thread::sleep_for(std::chrono::seconds(1));
					p.set_value_at_thread_exit(9);
				}, 
				std::move(d)).detach();

	// Make a future that takes 5 seconds to completed
	std::promise<int> d2;
	std::future<int> f_time_out = d2.get_future();
	std::thread([](std::promise<int> p) {
					std::this_thread::sleep_for(std::chrono::seconds(5));
					p.set_value_at_thread_exit(8);
				}, std::move(d2)).detach();

	std::cout << "Waiting 2 seconds ... \n";

	if (std::future_status::ready == f_completes.wait_until(two_seconds_passed))
	{
		std::cout << "f_completes: " << f_completes.get() << "\n";
	}
	else
	{
		std::cout << "f_completes did not complete!\n";
	}

	if (std::future_status::ready == f_time_out.wait_until(two_seconds_passed))
	{
		std::cout << "f_times_out: " << f_time_out.get() << "\n";
	}
	else
	{
		std::cout << "f_times_out did not complete!\n";
	}

	std::cout << "Done!\n";

	//Waiting for 2 seconds...
	//	f_completes: 9
	//	f_times_out did not complete!
	//	Done!
}

std::set<int> make_sorted_random(size_t number) 
{
	std::set<int> retval;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, number - 1);

	std::generate_n(std::inserter(retval, retval.end()), number, [&]() { return dis(gen); });

	// throw std::runtime_error("Hello world");
	return retval;
}

void test_future3() 
{
	try {

		auto f1 = std::async(std::launch::async, make_sorted_random, 10000);
		auto f2 = std::async(std::launch::async, make_sorted_random, 10000);

		/*
		generic template (1)			T get();
		reference specialization (2)	R& future<R&>::get();       // when T is a reference type (R&)
		void specialization (3)			void future<void>::get();   // when T is void

		Get value
		Returns the value stored in the shared state (or throws its exception) when the shared state is ready.

		If the shared state is not yet ready (i.e., the provider has not yet set its value or exception), the function blocks the calling thread and waits until it is ready.

		Once the shared state is ready, the function unblocks and returns (or throws) releasing its shared state. 
		This makes the future object no longer valid: this member function shall be called once at most for every future shared state.

		All visible side effects are synchronized between the point the provider makes the shared state ready and the return of this function.

		The member of the void specialization (3) does not return any value, but still waits for the shared state to become ready and releases it.
		*/

		std::cout << f1.get().size() << ' ' << f2.get().size() << '\n';
	}
	catch (std::exception& e) {
		std::cout << "Exception : " << e.what() << '\n';
	}

}


/*
 
 std::shared_future
  C++ Thread support library std::shared_future
 
 Defined in header <future>
 template< class T > class shared_future;
 (1)    (since C++11)
 template< class T > class shared_future<T&>;
 (2)    (since C++11)
 template<>          class shared_future<void>;
 (3)    (since C++11)
 The class template std::shared_future provides a mechanism to access the result of asynchronous operations,
 similar to std::future, except that multiple threads are allowed to wait for the same shared state. Unlike std::future, which is only moveable (so only one instance can refer to any particular asynchronous result),
 std::shared_future is copyable and multiple shared future objects may refer to the same shared state.

 Access to the same shared state from multiple threads is safe if each thread does it through its own copy of a shared_future object.

 Member functions
 (constructor)
  
                     constructs the future object
                     (public member function)
 (destructor)
  
                     destructs the future object
                     (public member function)
 operator=
  
                     assigns the contents
                     (public member function)
 
 Getting the result
 get
  
                     returns the result
                     (public member function)
 
 State
 valid
  
                         checks if the future has a shared state
                         (public member function)
 wait
  
                         waits for the result to become available
                         (public member function)
 wait_for
  
                         waits for the result, returns if it is not available for the specified timeout duration
                         (public member function)
 wait_until
  
                         waits for the result, returns if it is not available until specified time point has been reached
                         (public member function)
 Example
 A shared_future may be used to signal multiple threads simultaneously, similar to std::condition_variable::notify_all()
 
 */


void test_share_future()
{
    std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
    std::shared_future<void> ready_future(ready_promise.get_future());
 
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
 
    auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
    {
        t1_ready_promise.set_value();
        ready_future.wait(); // waits for the signal from main()
        return std::chrono::high_resolution_clock::now() - start;
    };
 
 
    auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
    {
        t2_ready_promise.set_value();
        ready_future.wait(); // waits for the signal from main()
        return std::chrono::high_resolution_clock::now() - start;
    };
 
    auto fut1 = t1_ready_promise.get_future();
    auto fut2 = t2_ready_promise.get_future();
 
    auto result1 = std::async(std::launch::async, fun1);
    auto result2 = std::async(std::launch::async, fun2);
 
    // wait for the threads to become ready
    fut1.wait();
    fut2.wait();
 
    // the threads are ready, start the clock
    start = std::chrono::high_resolution_clock::now();
 
    // signal the threads to go
    ready_promise.set_value();
 
    std::cout << "Thread 1 received the signal "
              << result1.get().count() << " ms after start\n"
              << "Thread 2 received the signal "
              << result2.get().count() << " ms after start\n";
}
