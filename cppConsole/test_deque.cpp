#include <stdio.h>
#include <iostream>

#include <deque>
#include <string>

using std::deque;
using std::string;

void test_deque_morden_cpp() {

	std::cout << "--- test_deque_morden_cpp ---" << std::endl;

	deque<string> mydeque;
	/*
	template <class... Args>
	  void emplace_back (Args&&... args);
	Construct and insert element at the end
	Inserts a new element at the end of the deque, right after its current last element. 
	This new element is constructed in place using args as the arguments for its construction.

	This effectively increases the container size by one.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.

	A similar member function exists, push_back, which either copies or moves an existing object into the container.
	*/
	mydeque.emplace_back("first");
	mydeque.emplace_back("second");

	/*
	template <class... Args>
	  void emplace_front (Args&&... args);
	Construct and insert element at beginning
	Inserts a new element at the beginning of the deque, right before its current first element. 
	This new element is constructed in place using args as the arguments for its construction.

	This effectively increases the container size by one.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.

	A similar member function exists, push_front, which either copies or moves an existing object into the container.
	*/
	mydeque.emplace_front("reverse first");
	mydeque.emplace_front("reverse second");

	std::cout << "mydeque contains:";
	for (auto& x : mydeque)
		std::cout << ' ' << x;
	std::cout << '\n';


	std::deque<int> mydeque = { 10,20,30,40,50 };

	// cbegin/cend
	std::cout << "mydeque contains:";
	for (auto it = mydeque.cbegin(); it != mydeque.cend(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	// crbegin/crend
	std::cout << "mydeque backwards:";
	for (auto rit = mydeque.crbegin(); rit != mydeque.crend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';

	std::cout << "--- test_deque_morden_cpp end---" << std::endl;
}