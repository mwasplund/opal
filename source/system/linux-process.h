// <copyright file="linux-process.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

#pragma once
#include "i-process.h"

namespace Opal::System {
	/// <summary>
	/// A Linux platform specific process executable using system
	/// </summary>
	export class LinuxProcess : public IProcess {
	private:
		// Input
		Path m_executable;
		std::vector<std::string> m_arguments;
		Path m_workingDirectory;
		bool m_interceptInputOutput;

		// Runtime
		pid_t m_processId;
		int m_stdOutReadHandle;
		int m_stdErrReadHandle;

		// Result
		bool m_isFinished;
		std::stringstream m_stdOut;
		std::stringstream m_stdErr;
		int m_exitCode;

	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='LinuxProcess'/> class.
		/// </summary>
		LinuxProcess(
			const Path &executable,
			std::vector<std::string> arguments,
			const Path &workingDirectory,
			bool interceptInputOutput)
			: m_executable(executable),
			  m_arguments(std::move(arguments)),
			  m_workingDirectory(workingDirectory),
			  m_interceptInputOutput(interceptInputOutput),
			  m_processId(),
			  m_stdOutReadHandle(),
			  m_stdErrReadHandle(),
			  m_isFinished(false),
			  m_exitCode(-1) {
		}

		/// <summary>
		/// Execute a process for the provided
		/// </summary>
		void Start() override final {
			int stdOutPipe[2];
			int stdErrPipe[2];
			if (m_interceptInputOutput) {
				// Create a pipe to send stdout to parent
				if (pipe2(stdOutPipe, 0) < 0)
					throw std::runtime_error("Failed to create stdOutPipe");

				// Create a pipe to send stderr to parent
				if (pipe2(stdErrPipe, 0) < 0)
					throw std::runtime_error("Failed to create stdErrPipe");
			}

			// Create a child process
			Log::Diag("Fork");
			pid_t processId = fork();
			if (processId == 0) {
				SetupChildProcess(stdOutPipe, stdErrPipe);
			} else {
				// Parent process still
				Log::Diag("Parent");

				m_processId = processId;

				if (m_interceptInputOutput) {
					// Close our handle on the write end
					close(stdOutPipe[1]);
					close(stdErrPipe[1]);
					m_stdOutReadHandle = stdOutPipe[0];
					m_stdErrReadHandle = stdErrPipe[0];
				}

				Log::Diag("Parent done");
			}
		}

		/// <summary>
		/// Wait for the process to exit
		/// </summary>
		void WaitForExit() override final {
			if (m_interceptInputOutput) {
				ReadAvailableStdOut();
				close(m_stdOutReadHandle);

				ReadAvailableStdErr();
				close(m_stdErrReadHandle);
			}

			// Wait until child process exits.
			int status;
			auto waitResult = waitpid(m_processId, &status, 0);
			if (!waitResult)
			{
				throw std::runtime_error("Execute waitpid Failed Unknown");
			}

			m_exitCode = status;
			m_isFinished = true;
		}

		/// <summary>
		/// Get the exit code
		/// </summary>
		int GetExitCode() override final {
			if (!m_isFinished)
				throw std::runtime_error("Process has not finished.");
			return m_exitCode;
		}

		/// <summary>
		/// Get the standard output
		/// </summary>
		std::string GetStandardOutput() override final {
			if (!m_isFinished)
				throw std::runtime_error("Process has not finished.");
			return m_stdOut.str();
		}

		/// <summary>
		/// Get the standard error output
		/// </summary>
		std::string GetStandardError() override final {
			if (!m_isFinished)
				throw std::runtime_error("Process has not finished.");
			return m_stdErr.str();
		}

	private:
		void ReadAvailableStdOut() {
			// Read all and write to stdout
			int dwRead;
			const int BufferSize = 256;
			char buffer[BufferSize + 1];

			// Read on output
			while (true) {
				dwRead = read(m_stdOutReadHandle, buffer, BufferSize);
				if (dwRead < 0)
					break;
				if (dwRead == 0)
					break;

				m_stdOut << std::string_view(buffer, dwRead);
			}
		}

		void ReadAvailableStdErr() {
			// Read all and write to stdout
			int dwRead;
			const int BufferSize = 256;
			char buffer[BufferSize + 1];

			// Read all errors
			while (true) {
				dwRead = read(m_stdErrReadHandle, buffer, BufferSize);
				if (dwRead < 0)
					break;
				if (dwRead == 0)
					break;

				// Make the string null terminated
				m_stdErr << std::string_view(buffer, dwRead);
			}
		}

		void SetupChildProcess(int stdOutPipe[2], int stdErrPipe[2]) {
			try {
				// We are the child process
				Log::Diag("Child");

				if (m_interceptInputOutput) {
					// Close the read pipe
					close(stdOutPipe[0]);
					close(stdErrPipe[0]);

					// Redirect stdout to the pipe write
					if (dup2(stdOutPipe[1], STDOUT_FILENO) != STDOUT_FILENO)
						throw std::runtime_error("dup2 error to stdout");

					// Redirect stderr to the pipe write
					if (dup2(stdErrPipe[1], STDERR_FILENO) != STDERR_FILENO)
						throw std::runtime_error("dup2 error to stderr");

					// Close our handle on the write end
					close(stdOutPipe[1]);
					close(stdErrPipe[1]);
				}

				// Set current working directory that will be inherited by the child process
				if (chdir(m_workingDirectory.ToString().c_str()) == -1)
					throw std::runtime_error("Failed to set working directory");

				std::vector<const char*> arguments;
				arguments.push_back(m_executable.ToString().c_str());
				for (auto& argument : m_arguments)
					arguments.push_back(argument.c_str());
				arguments.push_back(nullptr);
				
				// Replace runtime with child program
				auto result = execve(
					m_executable.ToString().c_str(),
					const_cast<char **>(arguments.data()),
					environ);
				if (result == -1)
					throw std::runtime_error("Failed to start child");
			} catch (const std::exception &e) {
				std::cerr << e.what() << '\n';
				exit(1234);
			}

			// Running in other program now
		}
	};
}
