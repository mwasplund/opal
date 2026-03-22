// <copyright file="scoped-console-manager-register.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <memory>
export module Opal:ScopedConsoleManagerRegister;
import :IConsoleManager;

namespace Opal::IO
{
	/// <summary>
	/// A scoped network manager registration helper
	/// </summary>
	export class ScopedConsoleManagerRegister
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='ScopedConsoleManagerRegister'/> class.
		/// </summary>
		ScopedConsoleManagerRegister(std::shared_ptr<IConsoleManager> manager)
		{
			IConsoleManager::Register(std::move(manager));
		}

		/// <summary>
		/// Finalizes an instance of the <see cref='ScopedConsoleManagerRegister'/> class.
		/// </summary>
		~ScopedConsoleManagerRegister()
		{
			IConsoleManager::Register(nullptr);
		}
	};
}
