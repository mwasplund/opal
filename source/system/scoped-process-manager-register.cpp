// <copyright file="scoped-process-manager-register.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <memory>
export module Opal:ScopedProcessManagerRegister;
import :IProcessManager;

namespace Opal::System
{
	/// <summary>
	/// A scoped process manager registration helper
	/// </summary>
	export class ScopedProcessManagerRegister
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='ScopedProcessManagerRegister'/> class.
		/// </summary>
		ScopedProcessManagerRegister(std::shared_ptr<IProcessManager> listener)
		{
			IProcessManager::Register(std::move(listener));
		}

		/// <summary>
		/// Finalizes an instance of the <see cref='ScopedProcessManagerRegister'/> class.
		/// </summary>
		~ScopedProcessManagerRegister()
		{
			IProcessManager::Register(nullptr);
		}
	};
}
