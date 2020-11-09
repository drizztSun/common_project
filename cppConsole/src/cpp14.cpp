
#include <initializer_list>  // define a class initializer_list<T>  C11
#include <vector>
#include <iostream>

using namespace std;

/******* initializer list ********/
/* 
	initializer list 
	uniform initialization
*/

class Bo {

	vector<int> m_vec;

public:
	// Initilizer_list constructor
	Bo(const initializer_list<int>& v) {
		for (initializer_list<int>::iterator a = v.begin(); a != v.end(); a++) {
			m_vec.push_back(*a);
		}
	}
};

/*
*	Uniform Initilization Search order:
*	1. Initilizer_list constructor 
*	2. regular constructor takes the appropriate parameter
*	3. Aggregate initializer_list
*/
class fish {
public:

	int _a;
	string _b;

	fish(int i, string c) {
		// second one for initialization
		_a = i;
		_b = c;
	}

	fish(const initializer_list<int>& v) {
		// first prioirty for initialization 
	}

};

void Test_Initializer_list() {


	Bo b{ 1, 2, 3, 4 };
	Bo b1 = { 1, 2, 3, 4 };  // bot them will call 'initializer_list constructor'

	fish a = { 1, "tuna" };  // Aggregate initializer_list
	fish a1{ 2, "Salmon" };

	
}

/******* initializer list ********/


/******* RightValue reference  ********/

// rvalue and lvalue
// rvalue, 2, 2.4, dog(), sum(1, 2), 1 + 2, x + y // only could be '=' right side
// lvalue, x, y  // could be on '=' left and right side
void Test_RightValue_reference()
{

}


/******* RightValue reference  ********/

/******* final override ********/
/*
// #pragma error(push)
// 'override' keyword
class dog {
public:
	virtual void A(int) = 0;
	virtual void B() const = 0;

};


class YellowDog : public dog {
public:
	virtual void A(float) override {}; // without override, it defined a new function A(float); or it report an error. 
									//so override reports an error and make syntax more clear

	virtual void B() override {}; // error 'override' doesnt override a function

	void C() override {}; // error 'override' doesnt override a function
};

// 'final' keyword
class cat final {
	
};

class OrgCat : public cat {
	// Error, it is final, so cat can't be derived
};

class duck {
public:
	virtual void C() final;
};

class GrayDuck : public duck {
public:
	virtual void C(); // error C() is final, so reported "can't not override final function"
};

// #pragma error(pop)
*/
/******* final override ********/

/******* delete *******/
class DB {
public:

	// use = delete to remove those two default functions, CCompile made
	DB(const DB&) = delete;
	DB& operator = (const DB&) = delete;

	int i = 0;
};
/******* delete *******/

/******* for each *******/

void Test_foreach() {

	vector<int> v{ 1, 2, 3, 4, 5, 6 };
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		*it++;
	}

	for (auto it = v.begin(); it != v.end(); it++) {
		*it++;
	}

	// for each : works on any class that has begin() and end()
	for (auto i : v) {
		cout << i; // read-only, it just copy the element in v to i
	}

	for (auto& i : v) {
		i++; // because if ref &, we can change i and also change the element in v
	}

	for (const auto& c : v) {
		cout << c << ' '; // because if const ref &, we can't change the value in v
	}
}

/******* for each *******/


/******* auto ********/

// Auto and Template
template<typename T>
void func2(T a)
{

}

template<typename T>
void func(std::initializer_list<T> Param) {

}

template <typename T>
class A {
public:
	A(T a) {
		_a = a;
	}

	T _a;
};

//C++14
auto add(int a, int b) {
	return a + b;
}

struct B {
	double x;
};

const B* b;

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u)
// return type depends on template parameters
// return type can be deduced since C++14
{
	return t + u;
}

void Test_auto() {

	// 'auto'
	auto i1 = 6;  // i1 is int
	auto i2 = 2.4;	 // i2 is double
	auto i3 = i1; // i3 is int

	vector<int> v{ 1, 2, 3, 4, 5, 6 };
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		*it++;
	}

	for (auto it = v.begin(); it != v.end(); it++) {
		*it++;
	}


	decltype(b->x) y; // type of y is double (declared type) 
	decltype((b->x)) z = y; // type of z is const double& (lvalue expression)


	auto f = [](int a, int b) ->int
	{
		return a * b;
	};

	decltype(f) g = f; // the type of a lambda function is unique and unnamed

	auto i = f(2, 2);
	auto i4 = g(3, 3);
	std::cout << "i1 = " << i1 << ", " << " j = " << i4 << std::endl;
}



/* decltype */
// return T
template<typename container, typename index>
auto authAndAccess(container& c, index i) 
	-> decltype(c[i])
{
	return c[i];
}

// return T& C++14
template<typename container, typename index>
decltype(auto) authAndAcce(container& c, index i)
{
	return c[i];
}



/******* auto ********/


/******* nullptr *******/
void foo(int) {}
void foo(char*) {}

void Test_nullptr() {


	/* nullptr */
	char * a = nullptr; 
	
	// nullptr will be the new value to pointer, instead of NULL. because of NULL is also 0, which made Ambigurity
	// foo(NULL); // Ambigurity

	foo(nullptr); // correctly hit the foo(char*)
}
/******* nullptr *******/

/*******  enum class *******/
// enum is a class-level, not an old-style integer 
enum apple {green_a, red_a};
enum orange {big_o, small_o};

void Test_enum() {

	apple a = apple::green_a;
	orange o = orange::big_o;

	if (a == o) {
		// it happend before C11, because enum is int type, but not class
		cout << "green apple and big orange are the same " << endl;
	}
	else {
		// right now, enum is updated to a 'class', so it check 'type' and 'value'
		cout << " green apple and big orange are not the same " << endl;
	}

}
/*******  enum class *******/

void testCpp14()
{
	Test_Initializer_list();

	Test_auto();

	Test_foreach();

	Test_nullptr();

	Test_enum();

	// run-time assert
	char * a = "a";
	// assert(a != nullptr);

	// Compile time assert (C++ 11)
	// static_assert(sizeof(int) == 4);
}