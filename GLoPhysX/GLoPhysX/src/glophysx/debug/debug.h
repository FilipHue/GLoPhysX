#pragma once

#include "profiling/profiler.h"
#include "profiling/profiling_timer.h"

#define GLOP_PROFILER
	#ifdef GLOP_PROFILER
		#define GLOP_PROFILER_BEGIN_SESSION(name, file_path)	::GLOPHYSX::PROFILING::Profiler::Get().BeginSession(name, file_path)
		#define GLOP_PROFILER_END_SESSION()						::GLOPHYSX::PROFILING::Profiler::Get().EndSession()
		#define GLOP_PROFILE_SCOPE(name)						::GLOPHYSX::PROFILING::ProfilingTimer timer##__LINE__(name);
		#define GLOP_PROFILE_FUNCTION()							GLOP_PROFILE_SCOPE(__FUNCSIG__);
	#else
		#define GLOP_PROFILER_BEGIN_SESSION(name, file_path)
		#define GLOP_PROFILER_END_SESSION()
		#define GLOP_PROFILE_SCOPE(name)
		#define GLOP_PROFILE_FUNCTION()
#endif
