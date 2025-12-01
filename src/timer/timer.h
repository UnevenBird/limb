#ifndef LIMB_TIMER_H
#define LIMB_TIMER_H

#include "common/config.h"

#ifdef LIMB_WINDOWS
#include <stdint.h>
#include <windows.h>
#endif

namespace limb {

class Timer {
public:
	Timer();
	~Timer();
	
	void Init();
	double GetTime();
	double Step();
	double GetDelta();
	int GetFPS();

private:
	int m_frame_count, m_fps;
	int64_t m_time_ticks, m_last_time;
	double m_delta, m_fps_update_time;
};

} // namespace limb

#endif // LIMB_TIMER_H
