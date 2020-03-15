#include <any>
#include <iostream>


/*
std::any
  C++  Utilities library std::any
Defined in header <any>
class any;  (since C++17)

The class any describes a type-safe container for single values of any type.

1) An object of class any stores an instance of any type that satisfies the constructor requirements or is empty, 
and this is referred to as the state of the class any object. The stored instance is called the contained object. 
Two states are equivalent if they are either both empty or if both are not empty and if the contained objects are equivalent.

2) The non-member any_cast functions provide type-safe access to the contained object.

Implementations are encouraged to avoid dynamic allocations for small objects, 
but such an optimization may only be applied to types for which std::is_nothrow_move_constructible returns true.

*/

void test_any()
{
	std::cout << std::boolalpha;

	// any type
	std::any a = 1;
	std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
	
	a = 3.14;
	std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
	
	a = true;
	std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';

	// bad type
	try {
		a = 1;
		std::cout << std::any_cast<float>(a) << '\n';
	}
	catch (const std::bad_cast& e) {
		std::cout << e.what() << '\n';
	}

	// hasValue
	a = 1;
	if (a.has_value()) {
		std::cout << a.type().name() << '\n';
	}

	a.reset();
	if (!a.has_value()) {
		std::cout << "no value\n";
	}

	// pointer to contain data
	a = 1;
	int* i = std::any_cast<int>(&a);
	std::cout << *i << '\n';

	//i: 1
	//d : 3.14
	//b : true
	//bad any_cast
	//i
	//no value
	//1
}