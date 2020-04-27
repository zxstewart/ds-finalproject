#include <iostream>
#include <chrono>
#include <unistd.h>
#include <thread>

using namespace std;

// C++ program to find the execution time of code
int main()
{
	using namespace std::chrono;
	
	auto start = steady_clock::now();

	// do some stuff here
	this_thread::sleep_for (seconds(2));
	sleep(2);

	auto end = steady_clock::now();

	cout << "Elapsed time in nanoseconds : " 
		<< duration_cast<nanoseconds>(end - start).count()
		<< " ns" << endl;

	cout << "Elapsed time in microseconds : " 
		<< duration_cast<microseconds>(end - start).count()
		<< " µs" << endl;

	cout << "Elapsed time in milliseconds : " 
		<< duration_cast<milliseconds>(end - start).count()
		<< " ms" << endl;

	cout << "Elapsed time in seconds : " 
		<< duration_cast<seconds>(end - start).count()
		<< " sec";

	return 0;
}