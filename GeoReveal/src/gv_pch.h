#pragma once

#include "GeoReveal/Core/Core.h"

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <any>
#include <set>
#include <cstdlib>
#include <cstring>
#include <string>
#include <errno.h>
#include <sstream>
#include <array>
#include <vector>
#include <future>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <iomanip>
#include <xhash>
#include <numeric>
#include <filesystem>
#include <variant>

#include <stdlib.h>
#include <stdio.h>


#ifdef GV_PLATFORM_WINDOWS
	#include <Windows.h>
	#include <commdlg.h>
	#include <psapi.h>
	#include <shlobj_core.h>
#elif GV_PLATFORM_LINUX
	#include <posixver.h>
	#include <mkpath.h>
	#include <emalloc.h>
	#include <sysstat.h>
	#include <sys/types.h>
	#include <sys/sysinfo.h>
	#include <unistd.h>
	#include <linux/limits.h>
#endif