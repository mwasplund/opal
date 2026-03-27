// <copyright file="linux-process-manager.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <array>
#include <memory>
#include <vector>
export module Opal:LinuxProcessManager;
import :IProcessManager;
import :LinuxProcess;

#if defined(__linux__)
namespace Opal::System
{
	/// <summary>
	/// A linux platform specific process executable using system
	/// </summary>
	export class LinuxProcessManager : public IProcessManager
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='LinuxProcessManager'/> class.
		/// </summary>
		LinuxProcessManager()
		{
		}

		/// <summary>
		/// Gets the current process file name
		/// </summary>
		Path GetCurrentProcessFileName() override final
		{
			auto buffer = std::array<char, 1024>();

			// Return written bytes, indicating if memory was sufficient
			int length = readlink("/proc/self/exe", buffer.data(), buffer.size());

			if (length <= 0 || length == buffer.size())
			{
				throw std::runtime_error("readlink /proc/self/exe failed");
			}

			return Path(std::string(buffer.data(), length));
		}

		/// <summary>
		/// Creates a process for the provided executable path
		/// </summary>
		std::shared_ptr<IProcess> CreateProcess(
			const Path& executable,
			std::vector<std::string> arguments,
			const Path& workingDirectory,
			bool interceptInputOutput) override final
		{
			return std::make_shared<LinuxProcess>(
				executable,
				std::move(arguments),
				workingDirectory,
				interceptInputOutput);
		}
	};
}
#endif