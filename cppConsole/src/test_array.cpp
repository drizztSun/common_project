#include <stdio.h>
#include <iostream>

#include <array>
using std::array;

/*
template < class T, size_t N > class array;
Array class
Arrays are fixed-size sequence containers: they hold a specific number of elements ordered in a strict linear sequence.

Internally, an array does not keep any data other than the elements it contains (not even its size, which is a template parameter, 
fixed on compile time). It is as efficient in terms of storage size as an ordinary array declared with the language's bracket syntax ([]). This class merely adds a layer of member and global functions to it, so that arrays can be used as standard containers.

Unlike the other standard containers, arrays have a fixed size and do not manage the allocation of its elements through an allocator: they are an aggregate type encapsulating a fixed-size array of elements. Therefore, they cannot be expanded or contracted dynamically (see vector for a similar container that can be expanded).

Zero-sized arrays are valid, but they should not be dereferenced (members front, back, and data).

Unlike with the other containers in the Standard Library, swapping two array containers is a linear operation that involves swapping all the elements in the ranges individually, which generally is a considerably less efficient operation. On the other side, this allows the iterators to elements in both containers to keep their original container association.

Another unique feature of array containers is that they can be treated as tuple objects: The <array> header overloads the get function to access the elements of the array as if it was a tuple, as well as specialized tuple_size and tuple_element types.

*/

void test_array_morden_cpp() {

	array<int, 6> myarray{ 1, 2, 3, 4, 5, 6 };

	//
	std::cout << "myarray contains:";
	for (auto it = myarray.begin(); it != myarray.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//
	std::cout << "myarray backwards:";
	for (auto it = myarray.rbegin(); it != myarray.rend(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//
	std::cout << "myarray contains:";
	for (auto it = myarray.cbegin(); it != myarray.cend(); ++it)
		std::cout << ' ' << *it;   // cannot modify *it
	std::cout << '\n';

	//
	std::cout << "myarray backwards:";
	for (auto rit = myarray.crbegin(); rit < myarray.crend(); ++rit)
		std::cout << ' ' << *rit;   // cannot modify *rit
	std::cout << '\n';


	std::array<int, 10> myarray1;

	// assign some values:
	for (int i = 0; i < 10; i++) myarray1.at(i) = i + 1;

	// print content:
	std::cout << "myarray contains:";
	for (int i = 0; i < 10; i++)
		std::cout << ' ' << myarray1.at(i);
	std::cout << '\n';

	// data()
	const char* cstr = "Test string";
	std::array<char, 12> charray;

	std::memcpy(charray.data(), cstr, 12);

	std::cout << charray.data() << '\n';


}