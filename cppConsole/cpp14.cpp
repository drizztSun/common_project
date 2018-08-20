
#include <initializer_list>


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

// decltype
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

void testCpp14()
{
	// auto and initializer_list
	std::initializer_list<double> v1 = { 1, 2, 3.0 };
	
	auto v = { 1, 2, 3 };

	func({ 1, 2, 3 });


	A<int> a(1);
	func2(a);


	// error
	//func2({ 1,2,3 });

	//A<std::initializer_list<int>> a({ 1, 2, 3 });

	auto addVal = add(1, 2);
}





