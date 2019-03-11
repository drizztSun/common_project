#include <stdlib.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

/*
The condition_variable class is a synchronization primitive that can be used to block a thread, or multiple threads at the same time, until another thread both modifies a shared variable (the condition), and notifies the condition_variable.

The thread that intends to modify the variable has to

acquire a std::mutex (typically via std::lock_guard)
perform the modification while the lock is held
execute notify_one or notify_all on the std::condition_variable (the lock does not need to be held for notification)
Even if the shared variable is atomic, it must be modified under the mutex in order to correctly publish the modification to the waiting thread.

Any thread that intends to wait on std::condition_variable has to

acquire a std::unique_lock<std::mutex>, on the same mutex as used to protect the shared variable
execute wait, wait_for, or wait_until. The wait operations atomically release the mutex and suspend the execution of the thread.
When the condition variable is notified, a timeout expires, or a spurious wakeup occurs, the thread is awakened, and the mutex is atomically reacquired. The thread should then check the condition and resume waiting if the wake up was spurious.
std::condition_variable works only with std::unique_lock<std::mutex>; this restriction allows for maximal efficiency on some platforms. std::condition_variable_any provides a condition variable that works with any BasicLockable object, such as std::shared_lock.

Condition variables permit concurrent invocation of the wait, wait_for, wait_until, notify_one and notify_all member functions.

The class std::condition_variable is a StandardLayoutType. It is not CopyConstructible, MoveConstructible, CopyAssignable, or MoveAssignable.
*/


std::mutex mux;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread() {

	// Wait until main() sends data
	std::unique_lock<std::mutex> lk(mux);
	cv.wait(lk, [] {return ready; });

	// after the wait, we own the lock.
	std::cout << "Worker thread is processing data\n";
	data += " after processing";

	// Send data back to main()
	processed = true;
	std::cout << "Worker thread signals data processing completed\n";

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
	lk.unlock();
	cv.notify_one();
}

void test_condition_variable_basic() {

	std::thread worker(worker_thread);

	data = "Example data";
	// send data to the worker thread
	{
		std::lock_guard<std::mutex> lk(mux);
		ready = true;
		std::cout << "main() signals data ready for processing\n";
	}
	cv.notify_one();

	// wait for the worker
	{
		std::unique_lock<std::mutex> lk(mux);
		cv.wait(lk, [] {return processed; });
	}
	std::cout << "Back in main(), data = " << data.c_str() << '\n';

	worker.join();
}





//std::condition_variable cv;
std::mutex cv_m; // This mutex is used for three purposes:
				 // 1) to synchronize accesses to i
				 // 2) to synchronize accesses to std::cerr
				 // 3) for the condition variable cv
int i = 0;

void waits()
{
	std::unique_lock<std::mutex> lk(cv_m);
	std::cerr << "Waiting... \n";
	cv.wait(lk, [] {return i == 1; });
	std::cerr << "...finished waiting. i == 1\n";
}

void signals()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lk(cv_m);
		std::cerr << "Notifying...\n";
	}
	cv.notify_all();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	{
		std::lock_guard<std::mutex> lk(cv_m);
		i = 1;
		std::cerr << "Notifying again...\n";
	}
	cv.notify_all();
}

int main()
{
	std::thread t1(waits), t2(waits), t3(waits), t4(signals);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}