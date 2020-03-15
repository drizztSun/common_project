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