#include <stdlib.h>
#include <iostream>

#include <string>
#include <map>
#include <thread>
#include <mutex>

std::mutex mux;
std::map<std::string, std::string> pages;


//void update(const std::string& key, const std::string& value, std::map<std::string, std::string>& pages, std::mutex& mux) 
void update(const std::string& key, const std::string& value) //, std::map<std::string, std::string>& pages, std::mutex& mux)
{

	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::lock_guard<std::mutex> guard(mux);

	pages[key] = value;
}

void test_mutex() {

	std::thread t1(update, "google", "www.google.com"); // , pages, mux);
	std::thread t2(update, "baidu", "www.baidu.com"); // , pages, mux);

	t1.join();
	t2.join();

	std::cout << "End of the mutex logicl " << std::endl;
}