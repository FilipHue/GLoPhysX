#pragma once

#include <gxpch.h>

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	namespace PROFILING {

		struct ProfileResult
		{
			std::string Name;

			std::chrono::duration<double, std::micro> Start;
			std::chrono::microseconds ElapsedTime;

			std::thread::id ThreadID;
		};

		struct ProfilerSession {
			std::string name;
		};

		class Profiler {
		public:
			Profiler(): m_current_session(nullptr), m_profile_count(0) {}

			GLOP_API void BeginSession(const std::string& name, const std::string& file_path = "results.json") {
				m_output_stream.open(file_path, std::ostream::trunc);

				if (m_output_stream.is_open()) {
					m_current_session = new ProfilerSession{ name };
					WriteHeader();
				}
				else {
					GLOP_CORE_WARN("Profiler couldn't open result file: {0}", file_path);
				}

			}

			GLOP_API void EndSession() {
				if (m_current_session) {
					WriteFooter();
					m_output_stream.close();

					delete m_current_session;
					m_current_session = nullptr;
					m_profile_count = 0;
				}
			}

			static Profiler& Get() {
				static Profiler instance;

				return instance;
			}

			void WriteHeader() {
				m_output_stream << "{\"otherData\": {},\"traceEvents\":[{}";
				m_output_stream.flush();
			};

			void WriteBody(const ProfileResult& result) {
				std::stringstream json;

				json << std::setprecision(3) << std::fixed;
				json << ",{";
				json << "\"cat\":\"function\",";
				json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
				json << "\"name\":\"" << result.Name << "\",";
				json << "\"ph\":\"X\",";
				json << "\"pid\":0,";
				json << "\"tid\":" << result.ThreadID << ",";
				json << "\"ts\":" << result.Start.count();
				json << "}";

				if (m_current_session) {
					m_output_stream << json.str();
					m_output_stream.flush();
				}
			};

			void WriteFooter() {
				m_output_stream << "]}";
				m_output_stream.flush();
			};

		private:
			std::ofstream m_output_stream;
			ProfilerSession* m_current_session;
			int m_profile_count;
		};
	}
}
