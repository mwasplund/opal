// <copyright file="console-trace-listener.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <iostream>
#include <memory>
#include <string>
export module Opal:ConsoleTraceListener;
import :TraceListener;

namespace Opal
{
	/// <summary>
	/// Console logger that wraps the base <see cref="TraceListener"/>
	/// </summary>
	export class ConsoleTraceListener : public TraceListener
	{
	private:
		std::mutex _mutex;

	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='ConsoleTraceListener'/> class.
		/// </summary>
		ConsoleTraceListener() :
			TraceListener(),
			_mutex()
		{
		}

		/// <summary>
		/// Initializes a new instance of the <see cref='ConsoleTraceListener'/> class.
		/// </summary>
		ConsoleTraceListener(
			std::string name,
			std::shared_ptr<IEventFilter> filter,
			bool showEventType,
			bool showEventId) :
			TraceListener(
				std::move(name),
				std::move(filter),
				showEventType,
				showEventId)
		{
		}

		/// <summary>
		/// Writes a message and newline terminator
		/// </summary>
		virtual void WriteLine(const std::string& message) override final
		{
			auto lock = std::lock_guard<std::mutex>(_mutex);

			SetConsoleColor();
			std::cout << message << std::endl;

			// TODO: restore color
		}

	private:
		void SetConsoleColor()
		{
			// TODO
			// switch (_currentEvent)
			// {
			//	 case TraceEventType.Error:
			//		 Console.ForegroundColor = ConsoleColor.Red;
			//		 break;
			//	 case TraceEventType.Warning:
			//		 Console.ForegroundColor = ConsoleColor.Yellow;
			//		 break;
			// }
		}
	};
}
