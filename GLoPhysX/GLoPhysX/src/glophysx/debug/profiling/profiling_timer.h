#pragma once

#include "profiler.h"

#include <thread>
#include <chrono>

namespace GLOPHYSX {

	namespace PROFILING {

		class ProfilingTimer {
		public:
			GLOP_API ProfilingTimer(const char* name)
				: m_Name(name), m_Stopped(false)
			{
				m_StartTimepoint = std::chrono::steady_clock::now();
			}

			~ProfilingTimer()
			{
				if (!m_Stopped)
					Stop();
			}

			void Stop()
			{
				auto endTimepoint = std::chrono::steady_clock::now();
				auto highResStart = std::chrono::duration<double, std::micro>{ m_StartTimepoint.time_since_epoch() };
				auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

				Profiler::Get().WriteBody({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

				m_Stopped = true;
			}
		private:
			const char* m_Name;
			std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
			bool m_Stopped;
		};
	}
}
