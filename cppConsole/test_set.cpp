#include <stdio.h>
#include <iostream>

#include <set>
#include <string>

using std::string;
using std::set;

void test_set_morden_cpp() {

	set<string> myset;

	/*
	template <class... Args>
	  iterator emplace_hint (const_iterator position, Args&&... args);
	Construct and insert element with hint
	Inserts a new element in the set, if unique, with a hint on the insertion position. This new element is constructed in place using args as the arguments for its construction.

	The insertion only takes place if no other element in the container is equivalent to the one being emplaced (elements in a set container are unique).

	If inserted, this effectively increases the container size by one.

	The value in position is used as a hint on the insertion point. The element will nevertheless be inserted at its corresponding position following the order described by its internal comparison object, but this hint is used by the function to begin its search for the insertion point, speeding up the process considerably when the actual insertion point is either position or close to it.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.
	*/

	auto it = myset.cbegin();

	it = myset.emplace_hint(it, "alpha");
	it = myset.emplace_hint(it, "epsilon");
	it = myset.emplace_hint(it, "beta");

	/*
	template <class... Args>
	pair<iterator,bool> emplace (Args&&... args);
	Construct and insert element
	Inserts a new element in the set, if unique. This new element is constructed in place using args as the arguments for its construction.

	The insertion only takes place if no other element in the container is equivalent to the one being emplaced (elements in a set container are unique).

	If inserted, this effectively increases the container size by one.

	Internally, set containers keep all their elements sorted following the criterion specified by its comparison object. The element is always inserted in its respective position following this ordering.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.

	A similar member function exists, insert, which either copies or moves existing objects into the container.
	
	*/
	myset.emplace("foo");
	myset.emplace("bar");
	auto it1 = myset.emplace("foo");

	if (!it1.second) {
		std::cout << "foo already existed " << std::endl;
	}


	std::cout << "myset contains:";
	for (const std::string& x : myset)
		std::cout << ' ' << x;
	std::cout << '\n';

	{
		std::set<int> myset = { 50,20,60,10,25 };

		std::cout << "myset backwards:";
		for (auto rit = myset.crbegin(); rit != myset.crend(); ++rit)
			std::cout << ' ' << *rit;

		std::cout << '\n';

		std::cout << "myset contains:";
		for (auto it = myset.cbegin(); it != myset.cend(); ++it)
			std::cout << ' ' << *it;
	}


	std::cout << '\n';
}