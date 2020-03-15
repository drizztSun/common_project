#include <stdlib.h>
#include <iostream>
#include <atomic>

struct A {
	int a;
};

struct B {
	B(): x(0), y(0) {

	}
	int x, y;
};

void test_atomic_basic() {

	//std::atomic<A> a;
	//std::atomic<B> b;

	//std::cout << std::boolalpha <<
	//	"std::atomic<A> is lock_free ? " << a.is_lock_free() << '\n';
	// Checks whether the atomic operations on all objects of this type are lock-free.
	//std::cout << std::boolalpha <<
	//	"std::atomic<B> is lock_free ? " << b.is_lock_free() << '\n';


	std::atomic_int num;
	num.is_lock_free();
	
	std::cout << "std::atomic_int is_lock_free() : " << std::boolalpha << num.is_lock_free() << std::endl;

}