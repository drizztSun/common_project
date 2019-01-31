#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

/*
	**** shared_ptr
std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer. 
Several shared_ptr objects may own the same object. The object is destroyed and its memory deallocated 
when either of the following happens:

the last remaining shared_ptr owning the object is destroyed;
the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset().
The object is destroyed using delete-expression or a custom deleter that is supplied to shared_ptr during construction.

A shared_ptr can share ownership of an object while storing a pointer to another object. This feature can be used to point to member objects while owning the object they belong to. 
The stored pointer is the one accessed by get(), the dereference and the comparison operators. The managed pointer is the one passed to the deleter when use count reaches zero.

A shared_ptr may also own no objects, in which case it is called empty (an empty shared_ptr may have a non-null stored pointer if the aliasing constructor was used to create it).

All specializations of shared_ptr meet the requirements of CopyConstructible, CopyAssignable, and LessThanComparable and are contextually convertible to bool.

All member functions (including copy constructor and copy assignment) can be called by multiple threads on different instances of shared_ptr 
without additional synchronization even if these instances are copies and share ownership of the same object. 
If multiple threads of execution access the same shared_ptr without synchronization and any of those accesses uses a non-const member function of shared_ptr then a data race will occur; 
the shared_ptr overloads of atomic functions can be used to prevent the data race.
*/
struct Base {
	Base() { std::cout << "base constrcutor" << std::endl; }
	~Base() { std::cout << "base deconstrcutor" << std::endl; }
};

struct Derived : public Base{
	Derived() { std::cout << "derived constructor " << std::endl; }
	~Derived() { std::cout << "derived deconstructor " << std::endl; }
};

void thfunc(std::shared_ptr<Base> p) {
	
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::shared_ptr<Base> lp = p; // thread-safe, even though the
                                  // shared use_count is incremented

	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);

		std::cout << "local pointer in a thread \n"
			<< " lp.get = " << lp.get()
			<< " , lp.use_count() " << lp.use_count() << std::endl;
	}
}
/*
	Base::Base()
	Derived::Derived()
	Created a shared Derived(as a pointer to Base)
	p.get() = 0xc99028, p.use_count() = 1
	Shared ownership between 3 threads and released
	ownership from main :
	p.get() = (nil), p.use_count() = 0
	local pointer in a thread :
	lp.get() = 0xc99028, lp.use_count() = 3
	local pointer in a thread :
	lp.get() = 0xc99028, lp.use_count() = 4
	local pointer in a thread :
	lp.get() = 0xc99028, lp.use_count() = 2
	Derived::~Derived()
	Base::~Base()
	All threads completed, the last one deleted Derived
*/
void Test_shared_ptr() {

	std::cout << " ------------- Test sharedptr  ------------------" << std::endl;

	std::shared_ptr<Base> p = std::make_shared<Derived>();
	std::cout << "Created a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';




	std::thread th1(thfunc, p), th2(thfunc, p), th3(thfunc, p);
	p.reset();

	std::cout << "Shared ownership between 3 threads and released\n"
		<< "ownership from main:\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	th1.join(); th2.join(); th3.join();
	std::cout << "All threads completed, the last one deleted Derived\n";

	std::cout << " ------------- Test sharedptr  ------------------" << std::endl;
}


/*
	*****  Unique_Ptr *******

std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.

The object is disposed of using the associated deleter when either of the following happens:

the managing unique_ptr object is destroyed
the managing unique_ptr object is assigned another pointer via operator= or reset().
The object is disposed of using a potentially user-supplied deleter by calling get_deleter()(ptr). The default deleter uses the delete operator, 
which destroys the object and deallocates the memory.

A unique_ptr may alternatively own no object, in which case it is called empty.

There are two versions of std::unique_ptr:

1) Manages a single object (e.g. allocated with new)
2) Manages a dynamically-allocated array of objects (e.g. allocated with new[])
The class satisfies the requirements of MoveConstructible and MoveAssignable, but not the requirements of either

*/

struct B {
	virtual void bar() { std::cout << "B::bar()" << std::endl};
	virtual ~B() = default;
};

struct D : public B {
	D() { std::cout << "D::D " << std::endl;  }
	~D() { std::cout << "D::~D" << std::endl;  }

	void bar() override { std::cout << "D::bar() " << std::endl;  }
};

std::unique_ptr<D> pass_through(std::unique_ptr<D> p) {
	p->bar();
	return p;
}

void Test_unique_ptr() {

	std::cout << 
}