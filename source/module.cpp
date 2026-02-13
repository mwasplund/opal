module;

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <functional>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <locale>
#include <map>
#include <optional>
#include <queue>
#include <sstream>
#include <string>

#if defined(_WIN32)

#include <Windows.h>
#include <shlobj.h>
#include <psapi.h>

#undef min
#undef max
#undef CreateDirectory
#undef CreateProcess
#undef GetCurrentTime
#undef GetCurrentDirectory

#elif defined(__linux__)

#include <spawn.h>
#include <sys/wait.h>

#include "utilities/environment.h"

#else
#error Uknown Platform
#endif

export module Opal;

#define OPAL_IMPLEMENTATION

#include "utilities/path.h"
#include "utilities/semantic-version.h"

#include "io/system-console-manager.h"
#include "io/mock-console-manager.h"
#include "io/scoped-console-manager-register.h"

#include "logger/log.h"
#include "logger/console-trace-listener.h"
#include "logger/scoped-trace-listener-register.h"
#include "logger/test-trace-listener.h"

#include "memory/i-reference-counted.h"
#include "memory/reference.h"
#include "memory/reference-counted.h"

#include "system/mock-file-system.h"
#include "system/mock-library-manager.h"
#include "system/mock-process-manager.h"
#include "system/mock-system.h"
#include "system/scoped-file-system-register.h"
#include "system/scoped-library-manager-register.h"
#include "system/scoped-process-manager-register.h"
#include "system/scoped-system-register.h"
#include "system/stl-file-system.h"
#include "system/stl-system.h"

#if defined(_WIN32)
#include "system/smart-handle.h"
#include "system/windows-dynamic-library-manager.h"
#include "system/windows-process-manager.h"
#elif defined(__linux__)
#include "system/linux-process-manager.h"
#endif