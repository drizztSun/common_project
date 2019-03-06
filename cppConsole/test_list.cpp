#include <stdio.h>
#include <iostream>

#include <list>

void test_list_mordern_cpp() {

	{
		std::list<int> mylist = { 5,10,15,20 };

		std::cout << "mylist contains:";
		for (auto it = mylist.cbegin(); it != mylist.cend(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';


		std::cout << "mylist backwards:";
		for (auto rit = mylist.crbegin(); rit != mylist.crend(); ++rit)
			std::cout << ' ' << *rit;
		std::cout << '\n';
	}

	{
		std::list<std::pair<int, char>> mylist;

		/*
		template <class... Args>
		  iterator emplace (const_iterator position, Args&&... args);

		Construct and insert element
		The container is extended by inserting a new element at position. 
		This new element is constructed in place using args as the arguments for its construction.

		This effectively increases the container size by one.

		Unlike other standard sequence containers, list and forward_list objects are specifically designed to be efficient inserting and removing elements in any position, even in the middle of the sequence.

		The element is constructed in-place by calling allocator_traits::construct with args forwarded.

		A similar member function exists, insert, which either copies or moves existing objects into the container.
		*/
		mylist.emplace(mylist.begin(), 100, 'x');
		mylist.emplace(mylist.begin(), 200, 'y');

		std::cout << "mylist contains:";
		for (auto& x : mylist)
			std::cout << " (" << x.first << "," << x.second << ")";

		std::cout << '\n';

		/*
		template <class... Args>
		  void emplace_front (Args&&... args);
		Construct and insert element at beginning
		Inserts a new element at the beginning of the list, right before its current first element. This new element is constructed in place using args as the arguments for its construction.

		This effectively increases the container size by one.

		The element is constructed in-place by calling allocator_traits::construct with args forwarded.

		A similar member function exists, push_front, which either copies or moves an existing object into the container.
		
		*/
		mylist.emplace_front(10, 'a');
		mylist.emplace_front(20, 'b');
		mylist.emplace_front(30, 'c');

		std::cout << "mylist contains:";
		for (auto& x : mylist)
			std::cout << " (" << x.first << "," << x.second << ")";

		std::cout << std::endl;

		/*
		template <class... Args>
		  void emplace_back (Args&&... args);
		Construct and insert element at the end
		Inserts a new element at the end of the list, right after its current last element. 
		This new element is constructed in place using args as the arguments for its construction.

		This effectively increases the container size by one.

		The element is constructed in-place by calling allocator_traits::construct with args forwarded.

		A similar member function exists, push_back, which either copies or moves an existing object into the container.
		*/

		mylist.emplace_back(10, 'a');
		mylist.emplace_back(20, 'b');
		mylist.emplace_back(30, 'c');

		std::cout << "mylist contains:";
		for (auto& x : mylist)
			std::cout << " (" << x.first << "," << x.second << ")";

		std::cout << std::endl;
	}

	
}