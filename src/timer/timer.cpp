#include "timer/timer.h"

namespace limb {

Timer::Timer()
	: m_time_ticks(0)
	, m_last_time(0)
	, m_fps_update_time(0.0)
	, m_frame_count(0)
	, m_delta(0.0)
	, m_fps(0)
{}

Timer::~Timer()
{}

#ifdef LIMB_WINDOWS
static int64_t GetTicks() {
	LARGE_INTEGER ticks;
	QueryPerformanceCounter(&ticks); // should work on Win >= WinXP
	return (int64_t) ticks.QuadPart;
}

static int64_t GetFrequency() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency); // should work on Win >= WinXP
	return (int64_t) frequency.QuadPart;
}

void Timer::Init() {
	m_time_ticks = GetTicks();
}

double Timer::GetTime() {
	static const double frequency = (double) GetFrequency(); // never changes
	static const int64_t start = GetTicks();
	const int64_t now = GetTicks();
	return (double)(now-start) / frequency;
}

double Timer::Step() {
	static const double frequency = (double) GetFrequency(); // never changes

	m_last_time = m_time_ticks;
	m_time_ticks = GetTicks();
	m_frame_count++;

	m_delta = (double)(m_time_ticks - m_last_time) / frequency;
	m_fps_update_time += m_delta;
	if (m_fps_update_time >= 1.0) {
		m_fps = int((m_frame_count/m_fps_update_time) + 0.5);
		m_fps_update_time = 0.0;
		m_frame_count = 0;
	}
	return m_delta;
}
#else
#error @TODO: Implement Timer::GetTime() and Timer::Step() for other platforms
#endif

double Timer::GetDelta() {
	return m_delta;
}

int Timer::GetFPS() {
	return m_fps;
}

} // namespace limb
