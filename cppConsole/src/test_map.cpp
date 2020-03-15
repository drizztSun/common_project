#include <stdio.h>
#include <iostream>

#include<string>
#include <map>
using std::map;
using std::string;
using std::cout;

void test_map_modern_cpp() {


	map<string, int> mymap{ {"alpha", 0}, {"beta", 0}, {"gamma", 0} };


	/*
	  mapped_type& at (const key_type& k);
		const mapped_type& at (const key_type& k) const;
	Access element
	Returns a reference to the mapped value of the element identified with key k.

	If k does not match the key of any element in the container, the function throws an out_of_range exception.
	*/
	mymap["alpha"] = 10;
	mymap["beta"] = 20;
	mymap["gamma"] = 30;

	for (auto& c : mymap) {
		cout << c.first << " : " << c.second << std::endl;
	}

	// print content:
	std::cout << "mymap contains:";
	for (auto it = mymap.cbegin(); it != mymap.cend(); ++it)
		std::cout << " [" << (*it).first << ':' << (*it).second << ']';
	std::cout << '\n';


	std::cout << "mymap backwards:";
	for (auto rit = mymap.crbegin(); rit != mymap.crend(); ++rit)
		std::cout << " [" << rit->first << ':' << rit->second << ']';
	std::cout << '\n';

	/*
	template <class... Args>
	  pair<iterator,bool> emplace (Args&&... args);
	Construct and insert element
	Inserts a new element in the map if its key is unique. This new element is constructed in place using args as the arguments for the construction of a value_type (which is an object of a pair type).

	The insertion only takes place if no other element in the container has a key equivalent to the one being emplaced (keys in a map container are unique).

	If inserted, this effectively increases the container size by one.

	Internally, map containers keep all their elements sorted by their key following the criterion specified by its comparison object. The element is always inserted in its respective position following this ordering.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.

	A similar member function exists, insert, which either copies or moves existing objects into the container.
	*/
	mymap.emplace("x", 100);
	mymap.emplace("y", 200);
	mymap.emplace("z", 100);

	std::cout << "mymap contains:";
	for (auto& x : mymap)
		std::cout << " [" << x.first << ':' << x.second << ']';
	std::cout << '\n';

	/*
	template <class... Args>
	  iterator emplace_hint (const_iterator position, Args&&... args);
	Construct and insert element with hint
	Inserts a new element in the map if its key is unique, with a hint on the insertion position. This new element is constructed in place using args as the arguments for the construction of a value_type (which is an object of a pair type).

	The insertion only takes place if no other element in the container has a key equivalent to the one being emplaced (elements in a map container are unique).

	If inserted, this effectively increases the container size by one.

	The value in position is used as a hint on the insertion point. The element will nevertheless be inserted at its corresponding position following the order described by its internal comparison object, but this hint is used by the function to begin its search for the insertion point, speeding up the process considerably when the actual insertion point is either position or close to it.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.
	*/
	auto it = mymap.end();

	it = mymap.emplace_hint(it, "b", 10);
	mymap.emplace_hint(it, "a", 12);
	mymap.emplace_hint(mymap.end(), "c", 14);

	std::cout << "mymap contains:";
	for (auto& x : mymap)
		std::cout << " [" << x.first << ':' << x.second << ']';
	std::cout << '\n';


	/*
	(1)	
	iterator  erase (const_iterator position);
	(2)	
	size_type erase (const key_type& k);
	(3)	
	iterator  erase (const_iterator first, const_iterator last);
	Erase elements
	Removes from the map container either a single element or a range of elements ([first,last)).

	This effectively reduces the container size by the number of elements removed, which are destroyed.
	*/
	it = mymap.find("b");
	mymap.erase(it);                   // erasing by iterator

	mymap.erase("c");                  // erasing by key

	it = mymap.find("e");
	mymap.erase(it, mymap.end());    // erasing by range



	while (!mymap.empty()) {
		cout << mymap.begin()->first << " : " << mymap.begin()->second << std::endl;
		mymap.erase(mymap.begin());
	}

}