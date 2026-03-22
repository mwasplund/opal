// <copyright file="system-console-manager.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

export module Opal:SystemConsoleManager;
import :IConsoleManager
import :SystemConsoleInputStream

namespace Opal::IO
{
	/// <summary>
	/// The system console manager
	/// </summary>
	export class SystemConsoleManager : public IConsoleManager
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='SystemConsoleManager'/> class.
		/// </summary>
		SystemConsoleManager()
		{
		}

		/// <summary>
		/// Get the standard input stream
		/// </summary>
		virtual std::shared_ptr<IConsoleInputStream> GetStandardInput() override final
		{
			return std::make_shared<SystemConsoleInputStream>();
		}
	};
}
