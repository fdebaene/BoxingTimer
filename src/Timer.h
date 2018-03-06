#pragma once
#include <deque>
#include <mutex>
#include <array>
#include <chrono>
#include <thread>
#include <vector>
#include <pistache/endpoint.h>

class Timer : public Pistache::Http::Handler
{
 public:
  HTTP_PROTOTYPE(Timer)
  enum class Color
  {
    Red, Green, Blue
      };
  Timer();
  ~Timer();
  void onRequest(const Pistache:: Http::Request& request, Pistache::Http::ResponseWriter response);
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
  void setStack(std::vector<int> stack);
  bool getTimeLeft(int& minutes, int& second);
  void runWebServer();
			
  //private:
  void display();
  void updateToDisplay();
  void run();
  void updateClock();

 private:
  std::deque<int>                               m_stack;
  std::deque<int>                               m_stackModel;
  std::chrono::system_clock::duration           m_defaultTimer;
  std::mutex                                    m_mutex;
  unsigned int                                  m_intervalTimer;//microsecond
  std::array<char, 4>                           m_todisplay;
  bool                                          m_running;
  std::chrono::system_clock::time_point         m_lastMeasure;
  std::chrono::system_clock::duration           m_duration;
  std::array<char, 10>                          m_convertArray;
  std::thread                                   m_displayThread;
  unsigned int                                  m_displayDigitCount;
  Color                                         m_color;
  std::thread                                   m_webThread;
};

