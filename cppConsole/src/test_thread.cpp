#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <boost/asio.hpp>
using namespace boost;

void foo() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

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