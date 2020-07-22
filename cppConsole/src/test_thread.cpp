#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <boost/asio.hpp>
using namespace boost;

void foo() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

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
            if (action == DtorAction::join) { t.join();
                } else { t.detach();
            }
        }
     }
    
    ThreadRAII(ThreadRAII&&) = default;
    ThreadRAII& operator=(ThreadRAII&&) = default;
     
    std::thread& get() { return t; }
private:
  DtorAction action;
  std::thread t;
};

constexpr auto tenMillion = 10'000'000;
bool doWork( std::function<bool(int)> filter, int maxVal = tenMillion) {
    
    std::vector<int> goodVals;
    
    // std::thread t( [&filter, maxVal, &goodVals] {
    ThreadRAII t(
        std::thread([&filter, maxVal, &goodVals] {
        for (auto i = 0; i <= maxVal; ++i) {
            if (filter(i))
                goodVals.push_back(i);
        }
    }),
    ThreadRAII::DtorAction::join);
    
    auto nh = t.get().native_handle();
    //auto nh = t.native_handle();    // use t's native
                                    // handle to set
                                    // t's priority
    
    t.get().join(); // the std::thread object t will be joinable when its destructor is called at the end of doWork. That would cause program execu‐ tion to be terminated.ßß
    return true;
}

/*
 
 
        Things to Remember
 • Make std::threads unjoinable on all paths.
 • join-on-destruction can lead to difficult-to-debug performance anomalies. • detach-on-destruction can lead to difficult-to-debug undefined behavior.
 • Declare std::thread objects last in lists of data members.
 
 
 
 The std::thread object t will be joinable when its destructor is called at the end of doWork. That would cause program execu‐ tion to be terminated.
 You might wonder why the std::thread destructor behaves this way. It’s because the two other obvious options are arguably worse. They are:
 
 • An implicit join. In this case, a std::thread’s destructor would wait for its underlying asynchronous thread of execution to complete. That sounds reason‐ able, but it could lead to performance anomalies that would be difficult to track down.
 
 • An implicit detach. In this case, a std::thread’s destructor would sever the connection between the std::thread object and its underlying thread of execu‐ tion. The underlying thread would continue to run.
    This sounds no less reasonable than the join approach, but the debugging problems it can lead to are worse.
 
 The Standardization Committee decided that the consequences of destroying a joina‐ ble thread were sufficiently dire that they essentially banned it (by specifying that destruction of a joinable thread causes program termination).
 
 
 This puts the onus on you to ensure that if you use a std::thread object, it’s made unjoinable on every path out of the scope in which it’s defined. But covering every path can be complicated.
 It includes flowing off the end of the scope as well as jump‐ ing out via a return, continue, break, goto or exception. That can be a lot of paths.
 
 */






void test_thread_basic() {

	unsigned int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported.\n";

	std::thread t1;
	std::cout << "std::thread t1 joinable " << std::boolalpha << t1.joinable() << std::endl;

	t1 = std::thread(foo);
	std::thread::id t1_id = t1.get_id();
	std::cout << "std::thread t1 id : " << t1.get_id();
	std::cout << "std::thread t1 joinable " << std::boolalpha << t1.joinable() << std::endl;

	// Separates the thread of execution from the thread object, allowing execution to continue independently.
	// Any allocated resources will be freed once the thread exits.
	// After calling detach *this no longer owns any thread.
	t1.detach();
	
	{
		std::thread t1(foo);
		std::thread t2(foo);

		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		std::swap(t1, t2);

		std::cout << "after std::swap(t1, t2):" << std::endl;
		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		t1.swap(t2);

		std::cout << "after t1.swap(t2):" << std::endl;
		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		t1.join();
		t2.join();

		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void timer_expired(std::string id) {
	std::cout << /*now_time() <<*/ " " << id << " enter \n";
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << " " << id << " leave \n";

}

void test_thread() {

	asio::io_service service;

	asio::deadline_timer timer1(service, posix_time::seconds(5));
	asio::deadline_timer timer2(service, posix_time::seconds(5));

	timer1.async_wait([](auto ... v) {timer_expired("time1"); });
	timer2.async_wait([](auto ... v) {timer_expired("time2"); });

	std::thread ta([&]() {service.run(); });
	std::thread tb([&]() {service.run(); });

	ta.join();
	tb.join();

	std::cout << "done." << std::endl;

}
