#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer{
public:
	Timer();

	void Reset();
	double Get();
protected:
	std::chrono::time_point<std::chrono::system_clock> m_start;
};

#endif // !TIMER_H