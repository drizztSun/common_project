#include <stdio.h>
#include <iostream>

#include <stack>

using std::stack;
using std::cout;

void test_stack_mordern_cpp() {

	std::stack<std::string> mystack;

	/*
	template <class... Args> void emplace (Args&&... args);
	Construct and insert element
	Adds a new element at the top of the stack, above its current top element. This new element is constructed in place passing args as the arguments for its constructor.

	This member function effectively calls the member function emplace_back of the underlying container, forwarding args.
	*/
	mystack.emplace("First sentence");
	mystack.emplace("Second sentence");

	mystack.push("Third sentence");
	mystack.push("Forth sentence");


	std::cout << "mystack contains:\n";
	while (!mystack.empty())
	{
		std::cout << mystack.top().c_str() << '\n';
		mystack.pop();
	}




	



}

void test_stack() {
    
    test_stack_mordern_cpp();
}
