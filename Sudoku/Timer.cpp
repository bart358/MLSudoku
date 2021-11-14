#include <chrono>
#include <iostream>

#include <Timer.h>

Timer::Timer()
	:start(std::chrono::high_resolution_clock::now())
{
}

Timer::~Timer()
{
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<float>(stop - start).count();
	std::cout << "Elapsed time: " << duration << "s." << std::endl;
}
