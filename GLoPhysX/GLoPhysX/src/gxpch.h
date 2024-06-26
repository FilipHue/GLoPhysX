#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include <string>

#include <memory>
#include <functional>
#include <algorithm>
#include <utility>

#include <thread>

#include <chrono>

#if defined(GLOP_PLATFORM_WINDOWS)
	#include <Windows.h>
	
	// For ENTT
	#undef min
	#undef max
#endif
