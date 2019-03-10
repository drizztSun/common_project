#include <stdio.h>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>


void test_asio() {

	boost::asio::io_service service;
	boost::asio::deadline_timer timer(service, boost::posix_time::seconds(5));

	timer.async_wait([](auto ... vn) {

		//std::cout << system_clock::now() << " : timer expired \n";

	});

	
}

