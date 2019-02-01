#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <fstream>
#include <cassert>
#include <functional>
#include <vector>

/*
	******* shared_ptr
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
	*******  Unique_Ptr *******

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
	virtual void bar() { std::cout << "B::bar()" << std::endl; }
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

void close_file(std::FILE* fp) { std::fclose(fp); }

/*
Custom deleter demo
x
Custom lambda - expression deleter demo
D::D
D::bar
destroying from a custom deleter...
D::~D

*/

void Test_unique_ptr() {

	std::cout << "unique ownership semantics demo\n";
	{
		auto p = std::make_unique<D>(); // p is a unique_ptr that owns a D
		auto q = pass_through(std::move(p));
		assert(!p); // now p owns nothing and holds a null pointer
		q->bar();   // and q owns the D object
	} // ~D called here

	//unique ownership semantics demo
	//	D::D
	//	D::bar
	//	D::bar
	//	D::~D

	std::cout << "Runtime polymorphism demo\n";
	{
		std::unique_ptr<B> p = std::make_unique<D>(); // p is a unique_ptr that owns a D
													  // as a pointer to base
		p->bar(); // virtual dispatch

		std::vector<std::unique_ptr<B>> v;  // unique_ptr can be stored in a container
		v.push_back(std::make_unique<D>());
		v.push_back(std::move(p));
		v.emplace_back(new D);
		for (auto& p : v) 
			p->bar(); // virtual dispatch
	} // ~D called 3 times

	//Runtime polymorphism demo
	//	D::D
	//	D::bar
	//	D::D
	//	D::D
	//	D::bar
	//	D::bar
	//	D::bar
	//	D::~D
	//	D::~D
	//	D::~D

	std::cout << "Custom deleter demo\n";
	std::ofstream("demo.txt") << 'x'; // prepare the file to read
	{
		std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("demo.txt", "r"),
			&close_file);
		if (fp) // fopen could have failed; in which case fp holds a null pointer
			std::cout << (char)std::fgetc(fp.get()) << '\n';
	} // fclose() called here, but only if FILE* is not a null pointer
	  // (that is, if fopen succeeded)

	std::cout << "Custom lambda-expression deleter demo\n";
	{
		std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
		{
			std::cout << "destroying from a custom deleter...\n";
			delete ptr;
		});  // p owns D
		p->bar();
	} // the lambda above is called and D is destroyed

	std::cout << "Array form of unique_ptr demo\n";
	{
		std::unique_ptr<D[]> p{ new D[3] };
	} // calls ~D 3 times

	//Array form of unique_ptr demo
	//	D::D
	//	D::D
	//	D::D
	//	D::~D
	//	D::~D
	//	D::~D

}

/* ******* weak_ptr *******
std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::shared_ptr. 
It must be converted to std::shared_ptr in order to access the referenced object.

std::weak_ptr models temporary ownership: when an object needs to be accessed only if it exists, 
and it may be deleted at any time by someone else, std::weak_ptr is used to track the object, 
and it is converted to std::shared_ptr to assume temporary ownership. 
If the original std::shared_ptr is destroyed at this time, the object's lifetime is extended until the temporary std::shared_ptr is destroyed as well.

Another use for std::weak_ptr is to break reference cycles formed by objects managed by std::shared_ptr. 
If such cycle is orphaned (i,e. there are no outside shared pointers into the cycle), 
the shared_ptr reference counts cannot reach zero and the memory is leaked. To prevent this, one of the pointers in the cycle can be made weak.

*/

std::weak_ptr<int> gw;

void observe() {
	std::cout << "use_count == " << gw.use_count() << " : ";
	if (auto p = gw.lock()) {
		std::cout << *p << std::endl;
	}
	else {
		std::cout << "gw is expired " << std::endl;
	}
}

//use_count == 1: 42
//use_count == 0 : gw is expired

void Test_weak_ptr() {

	{
		auto p = std::make_shared<int>(42);
		gw = p;

		observe();
	}

	observe();
}