#include "Timer.h"

Timer::Timer() {
	Reset();
}

void Timer::Reset() {
	m_start = std::chrono::system_clock::now();
}

double Timer::Get() {
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - m_start;

	return diff.count();
}