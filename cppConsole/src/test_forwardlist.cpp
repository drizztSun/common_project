#include <stdio.h>
#include <iostream>

#include <forward_list>

/*
template < class T, class Alloc = allocator<T> > class forward_list;
Forward list
Forward lists are sequence containers that allow constant time insert and erase operations anywhere within the sequence.

Forward lists are implemented as singly-linked lists; Singly linked lists can store each of the elements they contain in different and unrelated storage locations. The ordering is kept by the association to each element of a link to the next element in the sequence.

The main design difference between a forward_list container and a list container is that the first keeps internally only a link to the next element, while the latter keeps two links per element: one pointing to the next element and one to the preceding one, allowing efficient iteration in both directions, 
but consuming additional storage per element and with a slight higher time overhead inserting and removing elements. forward_list objects are thus more efficient than list objects, although they can only be iterated forwards.

Compared to other base standard sequence containers (array, vector and deque), forward_list perform generally better in inserting, extracting and moving elements in any position within the container, and therefore also in algorithms that make intensive use of these, like sorting algorithms.

The main drawback of forward_lists and lists compared to these other sequence containers is that they lack direct access to the elements by their position; For example, to access the sixth element in a forward_list one has to iterate from the beginning to that position, 
which takes linear time in the distance between these. They also consume some extra memory to keep the linking information associated to each element (which may be an important factor for large lists of small-sized elements).

The forward_list class template has been designed with efficiency in mind: By design, 
it is as efficient as a simple handwritten C-style singly-linked list, and in fact is the only standard container to deliberately lack a size member function for efficiency considerations: 
due to its nature as a linked list, having a size member that takes constant time would require it to keep an internal counter for its size (as list does). This would consume some extra storage and make insertion and removal operations slightly less efficient. To obtain the size of a forward_list object, you can use the distance algorithm with its begin and end, which is an operation that takes linear time.
*/

void test_forward_list() {

	{
		std::forward_list<int> mylist = { 20, 30, 40, 50 };

		mylist.insert_after(mylist.before_begin(), 11);

		std::cout << "mylist contains:";
		for (int& x : mylist) std::cout << ' ' << x;
		std::cout << '\n';

		std::cout << "mylist contains:";
		for (auto it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;

		std::cout << '\n';
	}

	std::forward_list<std::pair<int, char>> mylist;

	auto it = mylist.before_begin();

	/*
	template <class... Args>
	  iterator emplace_after (const_iterator position, Args&&... args);
	Construct and insert element
	The container is extended by inserting a new element after the element at position. This new element is constructed in place using args as the arguments for its construction.

	This effectively increases the container size by one.

	Unlike other standard sequence containers, list and forward_list objects are specifically designed to be efficient inserting and removing elements in any position, even in the middle of the sequence.

	To emplace elements at the beginning of the forward_list, use member function emplace_front, or call this function with before_begin as position.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.

	A similar member function exists, insert_after, which either copies or moves existing objects into the container.
	*/
	it = mylist.emplace_after(it, 100, 'x');
	it = mylist.emplace_after(it, 200, 'y');
	it = mylist.emplace_after(it, 300, 'z');

	std::cout << "mylist contains:";
	for (auto& x : mylist)
		std::cout << " (" << x.first << "," << x.second << ")";

	std::cout << '\n';


	/*
	template <class... Args>
	  void emplace_front (Args&&... args);
	Construct and insert element at beginning
	Inserts a new element at the beginning of the forward_list, right before its current first element. This new element is constructed in place using args as the arguments for its construction.

	This effectively increases the container size by one.

	A similar member function exists, push_front, which either copies or moves an existing object into the container.
	*/
	mylist.emplace_front(10, 'a');
	mylist.emplace_front(20, 'b');
	mylist.emplace_front(30, 'c');

	std::cout << "mylist contains:";
	for (auto& x : mylist)
		std::cout << " (" << x.first << "," << x.second << ")";

	std::cout << std::endl;
}