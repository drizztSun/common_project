#include <stdio.h>
#include <iostream>
#include <vector>

using std::vector;

void print_log(char* s) {
	std::cout << s << std::endl;
}

struct S{

	explicit S(int n) {
		print_log("S()");
		s = n;
	}

	S(S&& a) {
		print_log("S(S&&)");
		s = a.s;
	}

	~S() {
		print_log("~S()");
	}

	S& operator=(const S&& a) {
		print_log("S operator=");
		s = a.s;
	}

	int s;
};


void test_vector_morden_cpp() {

	vector<S> buff;

	buff.push_back(S(5));
	/*
	S(int) => S(S&&) =>~S()
	1) first, it calls S(), because of creation of S(5) in buff.push_back()
	2) second, it calls S(S&&), because of creation of S obj in vector array buff
	3) then, it calls ~S(), because of destruction of tmp S(5)
	*/

	/*
		emplace_back optimize all of this into only one object creation directly on vector array buff
		S(int)

		Inserts a new element at the end of the vector, right after its current last element. This new element is constructed in place using args as the arguments for its constructor.
		This effectively increases the container size by one, which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
		The element is constructed in-place by calling allocator_traits::construct with args forwarded.
		A similar member function exists, push_back, which either copies or moves an existing object into the container.
	*/
	buff.emplace_back(5);
	buff.emplace_back(10);
	buff.emplace_back(15);
	buff.emplace_back(20);

	/*
	template <class... Args>
	iterator emplace (const_iterator position, Args&&... args);

	Construct and insert element
	The container is extended by inserting a new element at position. This new element is constructed in place using args as the arguments for its construction.

	This effectively increases the container size by one.
	An automatic reallocation of the allocated storage space happens if -and only if- the new vector size surpasses the current vector capacity.
	Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to shift all the elements that were after position by one to their new positions. This is generally an inefficient operation compared to the one performed by other kinds of sequence containers (such as list or forward_list). See emplace_back for a member function that extends the container directly at the end.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.

	A similar member function exists, insert, which either copies or moves existing objects into the container.
	template <class... Args>
	iterator emplace (const_iterator position, Args&&... args);
	Construct and insert element
	The container is extended by inserting a new element at position. This new element is constructed in place using args as the arguments for its construction.

	This effectively increases the container size by one.

	An automatic reallocation of the allocated storage space happens if -and only if- the new vector size surpasses the current vector capacity.

	Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to shift all the elements that were after position by one to their new positions. This is generally an inefficient operation compared to the one performed by other kinds of sequence containers (such as list or forward_list). See emplace_back for a member function that extends the container directly at the end.

	The element is constructed in-place by calling allocator_traits::construct with args forwarded.

	A similar member function exists, insert, which either copies or moves existing objects into the container.

	*/
	auto it = buff.emplace(buff.begin() + 1, 100);

	buff.emplace(it, 200);
	buff.emplace(buff.end(), 300);

	/*
	      value_type* data() noexcept;
		const value_type* data() const noexcept;
		Access data
		Returns a direct pointer to the memory array used internally by the vector to store its owned elements.

		Because elements in the vector are guaranteed to be stored in contiguous storage locations in the same order as represented by the vector, 
		the pointer retrieved can be offset to access any element in the array.
	*/

	S* p = buff.data();
	for (size_t i = 0; i < buff.size(); i++) {
		printf("%d, ", p->s);
		p++;
	}
	
	/*
	td::vector::cbegin
	const_iterator cbegin() const noexcept;
	Return const_iterator to beginning
	Returns a const_iterator pointing to the first element in the container.

	A const_iterator is an iterator that points to const content. 
	This iterator can be increased and decreased (unless it is itself also const), just like the iterator returned by vector::begin, 
	but it cannot be used to modify the contents it points to, even if the vector object is not itself const.

	If the container is empty, the returned iterator value shall not be dereferenced.
	*/
	std::vector<int> myvector{ 10, 20, 30, 40, 50 };
	std::cout << "myvector contains : ";
	for (auto it = myvector.cbegin(); it != myvector.cend(); it++) {
		std::cout << " " << *it;
	}
	std::cout << "\n";

	/*
	std::vector::crbegin
	const_reverse_iterator crbegin() const noexcept;
	Return const_reverse_iterator to reverse beginning
	Returns a const_reverse_iterator pointing to the last element in the container (i.e., its reverse beginning).
	*/
	std::cout << "myvector reverse contains : ";
	for (auto it = myvector.crbegin(); it != myvector.crend(); it++) {
		std::cout << " " << *it;
	}
	std::cout << "\n";

}
