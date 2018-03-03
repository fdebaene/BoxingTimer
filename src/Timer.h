#pragma once
#include <deque>
#include <mutex>
#include <array>
#include <chrono>
#include <thread>
class Timer
{
public:
	enum class Color
	{
		Red, Green, Blue
	};
	Timer();
	~Timer();
	void reset();
	void start();
	void stop();
	void clear();
	void addToStack(unsigned int second);
	void next();
	void setDisplayRate(unsigned int hertz);
	void debugSetToDisplay(const std::array<char, 4>& data);
	void debugSetDuration(int second);
	bool debugMutexValue();
//private:
	void display();
	void updateToDisplay();
	void run();
	void updateClock();

private:
	std::deque<int>								m_stack;
	std::chrono::system_clock::duration			m_defaultTimer;
	std::mutex									m_mutex;
	unsigned int								m_intervalTimer;//microsecond
	std::array<char, 4>							m_todisplay;
	bool										m_running;
	std::chrono::system_clock::time_point		m_lastMeasure;
	std::chrono::system_clock::duration			m_duration;
	std::array<char, 10>						m_convertArray;
	std::thread									m_displayThread;
	unsigned int								m_displayDigitCount;
	Color										m_color;
};

