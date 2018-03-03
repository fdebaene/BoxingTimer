#include "Timer.h"
#include <thread>
#ifdef RPI
#else
#include <iostream>
#endif
#include <map>
std::map<char, int> reverse;
Timer::Timer() :
	m_defaultTimer(3 * 60),
	m_running(false),
	m_todisplay({ 0 }),
	m_displayDigitCount(0),
	m_intervalTimer(10000),
	m_duration(std::chrono::seconds(3 * 60))
{
	m_convertArray[0] = (char)0b11111101;//0
	m_convertArray[1] = (char)0b01100001;//1
	m_convertArray[2] = (char)0b11011011;//2
	m_convertArray[3] = (char)0b11110011;//3
	m_convertArray[4] = (char)0b01100111;//4
	m_convertArray[5] = (char)0b10110111;//5
	m_convertArray[6] = (char)0b10111111;//6
	m_convertArray[7] = (char)0b11100001;//7
	m_convertArray[8] = (char)0b11111111;//8
	m_convertArray[9] = (char)0b11110111;//9

	reverse[(char)0b11111101] = 0;
	reverse[(char)0b01100001] = 1;
	reverse[(char)0b11011011] = 2;
	reverse[(char)0b11110011] = 3;
	reverse[(char)0b01100111] = 4;
	reverse[(char)0b10110111] = 5;
	reverse[(char)0b10111111] = 6;
	reverse[(char)0b11100001] = 7;
	reverse[(char)0b11111111] = 8;
	reverse[(char)0b11110111] = 9;


}


Timer::~Timer()
{
}
void Timer::reset() 
{
	std::lock_guard<decltype(m_mutex)> lock(m_mutex);
}
void Timer::start() 
{
	std::unique_lock<decltype(m_mutex)> lock(m_mutex);
	if (m_running)
		return;
	m_running = true;
	m_lastMeasure = std::chrono::system_clock::now();
	lock.unlock();
	m_displayThread = std::thread(&Timer::run, this);
	
}
void Timer::stop() 
{
	std::unique_lock<decltype(m_mutex)> lock(m_mutex);
	if (!m_running)
		return;
	m_running = false;
	lock.unlock();
	m_displayThread.join();
}
void Timer::clear()
{
	std::lock_guard<decltype(m_mutex)> lock(m_mutex);
	m_stack.clear();
}
void Timer::addToStack(unsigned int second)
{
	std::lock_guard<decltype(m_mutex)> lock(m_mutex);
	m_stack.push_back(second);
}
void Timer::next() 
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (m_stack.size()!=0)
	{ 
		m_stack.push_back (m_stack.front());
		m_stack.pop_front();
	}
}
void Timer::display()
{
	m_displayDigitCount++;
	if (m_displayDigitCount > 3)
	{
		m_displayDigitCount = 0;
		updateToDisplay();
#ifndef RPI
		system("CLS");
#endif
	}
	std::unique_lock<decltype(m_mutex)> lock(m_mutex);
#ifdef RPI
	//Todo
#else //debug
	for (auto j = 0; j < 8; j++)
	{
		std::cout << ((m_todisplay[m_displayDigitCount] & (1 << (7-j))) ? "1" : "0");
	}

	std::cout<< " = "<<reverse[m_todisplay[m_displayDigitCount]]<< std::endl;
#endif

}
void Timer::setDisplayRate(unsigned int hertz)
{
	std::lock_guard<decltype(m_mutex)> lock(m_mutex);
	m_intervalTimer = 1000000 / hertz;
}
void Timer::updateToDisplay()
{
	std::unique_lock<decltype(m_mutex)> lock(m_mutex);
	unsigned int s =static_cast<unsigned int>( std::chrono::duration_cast<std::chrono::seconds>( m_duration).count());
	unsigned int min = s / 60;
	s %= 60;
	min %= 100;
	
	m_todisplay[0]= m_convertArray[min/10];
	m_todisplay[1] = m_convertArray[min % 10];
	m_todisplay[2] = m_convertArray[s / 10];
	m_todisplay[3] = m_convertArray[s % 10];
}

void Timer::debugSetToDisplay(const std::array<char, 4>& data)
{
	m_todisplay = data;
}
void Timer::debugSetDuration(int second)
{
	m_duration=std::chrono::seconds(125);
	
}

void Timer::run()
{
	std::unique_lock<decltype(m_mutex)> lock(m_mutex);
	auto running = m_running;
	lock.unlock();
	while (running)
	{
		updateClock();
		display();
		lock.lock();
		auto wait = std::chrono::microseconds(m_intervalTimer);
		lock.unlock();
		std::this_thread::sleep_for(wait);
		lock.lock();
		running = m_running; 
		lock.unlock();
	}
}

bool Timer::debugMutexValue()
{
	bool ret = m_mutex.try_lock();
	if (ret)
		m_mutex.unlock();
	return ret;

}

void Timer::updateClock()
{
	auto now = std::chrono::system_clock::now();
	auto delta = now - m_lastMeasure;
	if (delta < m_duration)
	{
		m_duration -= delta;
	}
	else
	{
		m_duration = std::chrono::seconds(0);
	}
	m_lastMeasure = now;
}