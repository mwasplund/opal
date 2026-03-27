module;

#include <charconv>
#include <optional>
#include <stdexcept>
#include <string>
export module Opal;

// io
export import :IConsoleInputStream;
export import :IConsoleManager;
export import :MockConsoleInputStream;
export import :MockConsoleManager;
export import :ScopedConsoleManagerRegister;
export import :SystemConsoleInputStream;
export import :SystemConsoleManager;

// logger
export import :ConsoleTraceListener;
export import :EventTypeFilter;
export import :Log;
export import :ScopedTraceListenerRegister;
export import :TestTraceListener;
export import :TraceListener;

// memory
export import :IReferenceCounted;
export import :ReferenceCounted;
export import :Reference;

// system
export import :IFileSystem;
export import :IFile;
export import :IInputFile;
export import :ILibraryManager;
export import :ILibrary;
export import :IOutputFile;
export import :IProcessManager;
export import :IProcess;
export import :ISystem;
export import :LinuxProcessManager;
export import :LinuxProcess;
export import :MockDirectory;
export import :MockFileSystem;
export import :MockFile;
export import :MockLibraryManager;
export import :MockLibrary;
export import :MockProcessManager;
export import :MockProcess;
export import :MockSystem;
export import :ScopedFileSystemRegister;
export import :ScopedLibraryManagerRegister;
export import :ScopedProcessManagerRegister;
export import :ScopedSystemRegister;
export import :SmartHandle;
export import :STLFileSystem;
export import :STLInputFile;
export import :STLOutputFile;
export import :STLSystem;
export import :WindowsDynamicLibraryManager;
export import :WindowsDynamicLibrary;
export import :WindowsProcessManager;
export import :WindowsProcess;

// utilities
export import :Path;

#include "utilities/semantic-version.h"