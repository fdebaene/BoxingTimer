#include "Timer.h"
#include <iostream>

int main()
{

	Timer time;
	std::array<char, 4> arr = { 'a','b','c','d' };

	//time.debugSetToDisplay(arr);
	time.start();
	std::cin.get();
	time.stop();
	std::cin.get();
	time.start();
	std::cin.get();
	time.stop();
	std::cin.get();
	return 0;
}

